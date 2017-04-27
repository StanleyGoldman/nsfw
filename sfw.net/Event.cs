using System.Runtime.InteropServices;

namespace sfw.net
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Event
    {
        public EventType Type;
        public string Directory;
        public string FileA;
        public string FileB;
    };
}