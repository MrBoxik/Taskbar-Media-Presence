using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace MusicBeePlugin
{
    /// <summary>
    /// Owns one background thread and executes every queued operation in order.
    /// MusicBee notifications are delivered on arbitrary threads, and Store
    /// builds do not guarantee that Plugin.Initialise has a Windows message
    /// pump. This queue therefore provides explicit serialization without a
    /// hidden WinForms control or SynchronizationContext.
    /// </summary>
    internal sealed class SerializedWorker : IDisposable
    {
        private readonly object _gate = new object();
        private readonly Queue<WorkItem> _queue = new Queue<WorkItem>();
        private readonly AutoResetEvent _workAvailable = new AutoResetEvent(false);
        private readonly Action<Exception> _unhandledException;
        private readonly Thread _thread;
        private bool _accepting = true;
        private bool _disposed;
        private int _threadId;

        public SerializedWorker(string name, Action<Exception> unhandledException)
        {
            _unhandledException = unhandledException;
            _thread = new Thread(Run)
            {
                IsBackground = true,
                Name = name,
            };
            _thread.SetApartmentState(ApartmentState.MTA);
            _thread.Start();
        }

        public bool Post(Action action)
        {
            if (action == null)
                throw new ArgumentNullException(nameof(action));
            return Enqueue(new WorkItem(action, null));
        }

        public T Invoke<T>(
            Func<T> action,
            int timeoutMilliseconds,
            CancellationToken cancellation)
        {
            if (action == null)
                throw new ArgumentNullException(nameof(action));
            if (timeoutMilliseconds <= 0)
                throw new ArgumentOutOfRangeException(nameof(timeoutMilliseconds));

            if (Thread.CurrentThread.ManagedThreadId == Volatile.Read(ref _threadId))
                return action();

            var completion = new TaskCompletionSource<T>(
                TaskCreationOptions.RunContinuationsAsynchronously);
            var item = new WorkItem(
                () =>
                {
                    try
                    {
                        completion.TrySetResult(action());
                    }
                    catch (Exception exception)
                    {
                        completion.TrySetException(exception);
                    }
                },
                () => completion.TrySetCanceled());

            if (!Enqueue(item))
                throw new InvalidOperationException("The MusicBee worker is stopping.");

            try
            {
                bool completed;
                try
                {
                    // Task.Wait uses an internal, short-lived waiter instead of
                    // materializing IAsyncResult.AsyncWaitHandle. The latter
                    // owns a kernel event for the lifetime of the Task and
                    // leaked one handle for every pipe request.
                    completed = completion.Task.Wait(
                        timeoutMilliseconds,
                        cancellation);
                }
                catch (AggregateException)
                {
                    // Preserve the original worker exception instead of the
                    // AggregateException wrapper produced by Task.Wait.
                    return completion.Task.GetAwaiter().GetResult();
                }

                if (!completed)
                {
                    item.Cancel();
                    throw new TimeoutException(
                        "MusicBee did not process the request in time.");
                }

                return completion.Task.GetAwaiter().GetResult();
            }
            catch
            {
                item.Cancel();
                throw;
            }
        }

        public void Invoke(
            Action action,
            int timeoutMilliseconds,
            CancellationToken cancellation)
        {
            Invoke(
                () =>
                {
                    action();
                    return true;
                },
                timeoutMilliseconds,
                cancellation);
        }

        /// <summary>
        /// Stops accepting work, optionally cancels queued operations, and waits
        /// for the background thread. A timed-out worker remains a background
        /// thread, so a broken third-party API can never keep MusicBee alive.
        /// </summary>
        public bool Stop(bool cancelPending, int timeoutMilliseconds)
        {
            if (timeoutMilliseconds < 0)
                throw new ArgumentOutOfRangeException(nameof(timeoutMilliseconds));

            lock (_gate)
            {
                _accepting = false;
                if (cancelPending)
                {
                    while (_queue.Count > 0)
                        _queue.Dequeue().Cancel();
                }
            }
            _workAvailable.Set();

            if (Thread.CurrentThread.ManagedThreadId == Volatile.Read(ref _threadId))
                return false;
            return _thread.Join(timeoutMilliseconds);
        }

        public void Dispose()
        {
            if (_disposed)
                return;
            _disposed = true;

            bool stopped = Stop(true, 3000);
            if (stopped)
                _workAvailable.Dispose();
        }

        private bool Enqueue(WorkItem item)
        {
            lock (_gate)
            {
                if (!_accepting)
                {
                    item.Cancel();
                    return false;
                }
                _queue.Enqueue(item);
            }
            _workAvailable.Set();
            return true;
        }

        private void Run()
        {
            Volatile.Write(ref _threadId, Thread.CurrentThread.ManagedThreadId);
            try
            {
                while (true)
                {
                    WorkItem item = null;
                    lock (_gate)
                    {
                        if (_queue.Count > 0)
                            item = _queue.Dequeue();
                        else if (!_accepting)
                            break;
                    }

                    if (item == null)
                    {
                        _workAvailable.WaitOne();
                        continue;
                    }

                    try
                    {
                        item.Execute();
                    }
                    catch (Exception exception)
                    {
                        try { _unhandledException?.Invoke(exception); } catch { }
                    }
                }
            }
            finally
            {
                lock (_gate)
                {
                    _accepting = false;
                    while (_queue.Count > 0)
                        _queue.Dequeue().Cancel();
                }
                Volatile.Write(ref _threadId, 0);
            }
        }

        private sealed class WorkItem
        {
            private readonly Action _action;
            private readonly Action _cancelled;
            // 0 = queued, 1 = running, 2 = completed, 3 = cancelled.
            private int _state;

            public WorkItem(Action action, Action cancelled)
            {
                _action = action;
                _cancelled = cancelled;
            }

            public void Execute()
            {
                if (Interlocked.CompareExchange(ref _state, 1, 0) != 0)
                    return;
                try
                {
                    _action();
                }
                finally
                {
                    Volatile.Write(ref _state, 2);
                }
            }

            public bool Cancel()
            {
                if (Interlocked.CompareExchange(ref _state, 3, 0) != 0)
                    return false;
                try { _cancelled?.Invoke(); } catch { }
                return true;
            }
        }
    }
}
