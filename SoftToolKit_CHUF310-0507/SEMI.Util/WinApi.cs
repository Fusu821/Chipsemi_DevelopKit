using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SEMI.Util
{
    public class WinApi
    {
        public const int KEYEVENTF_EXTENDEDKEY = 0x1;
        public const int KEYEVENTF_KEYUP = 0x2;
        public const int VK_NUMLOCK = 0x90;
        public const int VK_CAPITAL = 0x14;
        public const int VK_SCROLL = 0x91;
        public const int VK_SHIFT = 0x10;
        public const int VK_CONTROL = 0x11;

        public const int APP_ALREAD_EXIST = 183;

        [DllImport("user32.dll",CharSet = CharSet.Auto, ExactSpelling = true, CallingConvention = CallingConvention.Winapi)]
        public static extern short GetKeyState(int keyCode);

        [DllImport("Kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr CreateMutex( IntPtr lpMutexAttributes, int bInitialOwner, string lpName );

        [DllImport("Kernel32.dll", CharSet = CharSet.Auto)]
        public static extern ushort GetLastError();
    }
}
