using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;

namespace SEMIDevelopKit
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        App()
        {
            SEMI.Util.WinApi.CreateMutex(IntPtr.Zero, 0, "CHIP_SEMI_DEVELOP");
            if (SEMI.Util.WinApi.APP_ALREAD_EXIST == SEMI.Util.WinApi.GetLastError())
            {
                MessageBox.Show("A Instance of SMTest has been on");
                Environment.Exit(0);
            }
        }
    }
}
