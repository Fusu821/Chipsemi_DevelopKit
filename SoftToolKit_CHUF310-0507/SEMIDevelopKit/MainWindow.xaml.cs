using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using MahApps.Metro.Controls;
using System.Windows.Interop;
using SMInvokeBridge;
using System.Runtime.InteropServices;
using SEMIDevelopKit.Src.WinSub;
using System.IO;

namespace SEMIDevelopKit
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        private SEMIDevelopKit.Src.MainViewModel mainViewModel = null;
        private static MetroWindow mainWindow = null;
        public MainWindow()
        {
            InitializeComponent();
            mainWindow = this;
            mainViewModel = new SEMIDevelopKit.Src.MainViewModel(this);

            this.DataContext = mainViewModel;

            this.SourceInitialized += new EventHandler(MainWindowSourceInitialized);
        }

        void MainWindowSourceInitialized(object sender, EventArgs e)
        {
            HwndSource hwndSource = PresentationSource.FromVisual(this) as HwndSource;
            hwndSource.AddHook(new HwndSourceHook(WndProc));

            Guid prtGUID = new Guid("28d78fad-5a12-11D1-ae5b-0000f803a8c2");
            ExportDeclares.CLRRegisterNotification(hwndSource.Handle, prtGUID.ToByteArray());

            Guid hidGUID = new Guid("4d1e55b2-f16f-11cf-88cb-001111000030");
            ExportDeclares.CLRRegisterNotification(hwndSource.Handle, hidGUID.ToByteArray());

            CLRLinkParam param = new CLRLinkParam();
            param.LinkType = CLRLinkParam.CLRLINK_TYPE_USB;
            bool bConnected = ExportDeclares.CLRHalLinkAndDoInit(param);

            DeviceStatusUpdate();

            RuningKernel.Instance().StartRun();
        }

        /// <summary>
        /// 创建人员：Wasim， 日期：2017-04-6
        /// 功能描述：Windows消息响应函数：
        /// 1）此函数用于捕捉设备拔插的消息
        /// </summary>  
        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            //#define WM_KEYDOWN                      0x0100
            //#define WM_KEYUP                        0x0101
            //#define VK_SPACE                        0x20

            if (msg == DeviceManagement.WM_DEVICECHANGED)
            {
                OnDeviceChange(msg, wParam, lParam);
            }
            return (System.IntPtr)0;
        }

        internal void OnDeviceChange(int msg, IntPtr wParam, IntPtr lParam)
        {
            try
            {
                //SysDelay(200);
                if ((int)wParam == DeviceManagement.DBT_DEVICEARRIVAL)
                {
                    DEV_BROADCAST_DEVICEINTERFACE dip;
                    dip = (DEV_BROADCAST_DEVICEINTERFACE)Marshal.PtrToStructure(lParam, typeof(DEV_BROADCAST_DEVICEINTERFACE));
                    string csTemp = dip.dbcc_name;

                    csTemp = csTemp.ToLower();
                    if (-1 == csTemp.IndexOf("vid_248a"))//Check Hid device
                    {
                        return;
                    }

                    CLRLinkParam param = new CLRLinkParam();
                    param.LinkType = (byte)mainViewModel.Agent;
                    param.szCurMsg = csTemp;
                    ExportDeclares.CLRHalLinkAndDoInit(param);

                    DeviceStatusUpdate(); 
                }
                else if ((int)wParam == DeviceManagement.DBT_DEVICEREMOVECOMPLETE)
                {
                    DEV_BROADCAST_DEVICEINTERFACE dip;
                    dip = (DEV_BROADCAST_DEVICEINTERFACE)Marshal.PtrToStructure(lParam, typeof(DEV_BROADCAST_DEVICEINTERFACE));
                    string csTemp = dip.dbcc_name;

                    CLRLinkParam param = new CLRLinkParam();
                    param.LinkType = (byte)mainViewModel.Agent;
                    param.szCurMsg = csTemp;
                    ExportDeclares.CLRHalDetachAndClean(param);

                    DeviceStatusUpdate();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        public void DeviceStatusUpdate()
        {
            byte[] devStatus = new byte[ExportDeclares.MAX_DEVICE_NUMS];

            int numDev = ExportDeclares.GetNumDeviceAttached(devStatus);

            mainViewModel.DeviceStates = devStatus;

            RuningKernel.Instance().Pause(numDev <= 0);

            if (numDev > 0)
            {
                RuningKernel.Instance().Work.AddWorkTemporary(() =>
                {
                    CommContext ctx = new CommContext();
                    ctx.icType = mainViewModel.SelectedIC;
                    ctx.protocalType = (byte)mainViewModel.SelectedProtocal;
                    ctx.slaveAddr = mainViewModel.SlaveAddr;
                    ctx.i2cSpeed = mainViewModel.I2cSpeedIndex;
                    ctx.spiMode = 0;
                    ctx.spiSpeed = mainViewModel.SpiSpeedDivision;
                    ctx.vdd = mainViewModel.VddVotage;
                    ctx.iovdd = mainViewModel.IoVddVotage;
                    ctx.vih = mainViewModel.VIHVotage;

                    SMCommBase.SyncWorkcInit();
                    SMCommBase.SetIoVoltage(mainViewModel.VddVotage, mainViewModel.IoVddVotage, mainViewModel.VIHVotage);
                    SMChipBase.SetICTypeAndCreateComponent(mainViewModel.SelectedIC);
                    SMChipBase.SetCommContext(ctx);
                });
            }  
        }

        private  bool IsRawDataForm = false;
        private  ushort t_DisplayType = dtType.MODE_RAWDATA;
        private void AnchorPane_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "SelectedContentIndex")
            {
                if (this.RawData == AnchorPane.SelectedContent)
                {
                    if ((t_DisplayType == dtType.MODE_TOUCH) || (t_DisplayType == dtType.MODE_NONE))
                    {
                        t_DisplayType = dtType.MODE_RAWDATA;//houjianxing-221206
                    }
                    IsRawDataForm = true;
                    RuningKernel.Instance().Pause(true);
                    if (null != mainViewModel) mainViewModel.DisplayType = t_DisplayType;//houjianxing-221206 切换芯片时保持上一次显示模式仅在RawData界面
                    RuningKernel.Instance().Pause(false);
                }
                else if (this.Touch == AnchorPane.SelectedContent)
                {
                    RuningKernel.Instance().Pause(true);
                    if (null != mainViewModel)
                    {
                        if (IsRawDataForm==true)
                        {
                            t_DisplayType = mainViewModel.DisplayType;//houjianxing-221206
                            IsRawDataForm = false;
                        }                      
                        mainViewModel.DisplayType = dtType.MODE_TOUCH;
                    }
                    RuningKernel.Instance().Pause(false);
                }
                else if (null != AnchorPane.SelectedContent)
                {
                    RuningKernel.Instance().Pause(true);
                    if (null != mainViewModel)
                    {
                        if (IsRawDataForm == true)
                        {
                            t_DisplayType = mainViewModel.DisplayType;//houjianxing-221206
                            IsRawDataForm = false;
                        }                       
                        mainViewModel.DisplayType = dtType.MODE_NONE;
                    }
                    RuningKernel.Instance().Pause(false);
                }
            }
        }

        public void ShowFlyout(SEMIDevelopKit.Src.MainViewModel mode)
        {
            var flyout = this.Flyouts.Items[0] as Flyout;
            flyout.Position = Position.Left;
            flyout.DataContext = mode;
            this.unitcuts.Children.Clear();

            try
            {
                string path = System.Environment.CurrentDirectory + "\\Scripts\\" + eChipTypeList.GetIcName(mainViewModel.SelectedIC) + "\\";
                string[] files = Directory.GetFiles(path);

                foreach (var item in files)
                {
                    Button btn = new Button() { Margin = new Thickness(3), Style = null, Foreground = new SolidColorBrush(Color.FromRgb(0, 0, 255)) };
                    btn.Tag = item;
                    btn.Content = System.IO.Path.GetFileName(item);
                    this.unitcuts.Children.Add(btn);

                    btn.Click += (s, e) =>
                    {
                        Button button = s as Button;
                        string file = button.Tag as string;
                        mode.TextScriptIn = "";
                        mode.TextScriptOut = "";
                        StreamReader sreader = new StreamReader(file, Encoding.Default);
                        mode.TextScriptIn = sreader.ReadToEnd();
                        sreader.Close();

                        mode.OnCtrlClickCommand("script-all-click");
                    };
                }

                string[] dirs = Directory.GetDirectories(path);
                foreach (var dir in dirs)
                {
                    ComboBox cbx = new ComboBox() { Margin = new Thickness(3), Style = null, Foreground = new SolidColorBrush(Color.FromRgb(0, 0, 255)), HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center, VerticalContentAlignment = System.Windows.VerticalAlignment.Center};
                    string[] itemFile = Directory.GetFiles(dir);

                    foreach (var item in itemFile)
                    {
                        ComboBoxItem cbxItem = new ComboBoxItem();
                        cbxItem.Tag = item;
                        cbxItem.Content = System.IO.Path.GetFileName(item);

                        cbx.Items.Add(cbxItem);
                        if (item.Contains("reset")) cbx.SelectedItem = cbxItem;

                        cbxItem.Selected += (s, e) =>
                        {
                            ComboBoxItem childItem = s as ComboBoxItem;
                            string file = childItem.Tag as string;
                            mode.TextScriptIn = "";
                            mode.TextScriptOut = "";
                            StreamReader sreader = new StreamReader(file, Encoding.Default);
                            mode.TextScriptIn = sreader.ReadToEnd();
                            sreader.Close();

                            mode.OnCtrlClickCommand("script-all-click");
                        };
                    }

                    this.unitcuts.Children.Add(cbx);
                }
            }
            catch(Exception ex)
            {
                ex.ToString();
            }

            flyout.IsOpen = !flyout.IsOpen;
        }
        public static MetroWindow AppWin
        {
            get { return mainWindow; }
        }
    }
}
