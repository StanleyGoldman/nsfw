using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace sfw.net
{
    public class NativeInterface: IDisposable
    {
        private IntPtr _ptr;

        public NativeInterface(string path)
        {
            _ptr = NativeMethods.Create(path);
        }

        public bool HasErrored()
        {
            return NativeMethods.HasError(_ptr);
        }

        public string GetError()
        {
            return NativeMethods.GetError(_ptr);
        }

        public Event[] GetEvents()
        {
            IntPtr eventPtr;
            int count;
            NativeMethods.GetEvents(_ptr, out eventPtr, out count);

            var events = new List<Event>();
            var eventSize = Marshal.SizeOf(typeof(Event));
            for (int i = 0; i < count; i++, eventPtr = new IntPtr(eventPtr.ToInt64() + eventSize))
            {
                events.Add((Event)Marshal.PtrToStructure(eventPtr, typeof(Event)));
            }

            return events.ToArray();
        }

        public void Dispose()
        {
            if (_ptr == IntPtr.Zero)
                return;

            NativeMethods.Delete(_ptr);
            _ptr = IntPtr.Zero;
        }
    }
}