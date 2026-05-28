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
using SEMITestApp.Src;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using SEMITestApp.Src.WinSub;
using SMInvokeBridge;
using WinRegistry = Microsoft.Win32.Registry;
using System.Threading.Tasks;
using System.Windows.Threading;
using MahApps.Metro.Controls.Dialogs;
using SEMITestApp.Src.WinSet;

namespace SEMITestApp
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        private static SMComplex smComplex = null;
        private MainViewModel mainViewMedel = null;
        private static MetroWindow mainWindow = null;

        private bool _isDisplayWindowShowing = false;
        static public int SnLen { get; private set; }
        static public int NeedClickStart { get; private set; }
        static public int DisplayTest { get; private set; }
        static public int StartTrigger { get; private set; }
        static public int SelectFormat { get; private set; }
        static public ushort Agent { get; private set; }
        static public String SNFilter { get; private set; }
        static public IDictionary<int, string> dcDisplayStrMap = new Dictionary<int, string>() { { 0, "" }, { 1, "" }, { 2, "" }, { 3, "" }, { 4, "" }, { 5, "" }, { 6, "" }, { 7, "" } };
        static public IDictionary<int, string> dcSnStrMap = new Dictionary<int, string>() { { 0, "" }, { 1, "" }, { 2, "" }, { 3, "" }, { 4, "" }, { 5, "" }, { 6, "" }, { 7, "" } };
        public MainWindow()
        {
            InitializeComponent();

            mainWindow = this;

            smComplex = new SMComplex();

            mainViewMedel = new MainViewModel(this);

            this.DataContext = mainViewMedel;

            this.SourceInitialized += new EventHandler(MainWindowSourceInitialized);
        }

        public static MetroWindow AppWin
        {
            get { return mainWindow; }
        }

        public static SMComplex SMComplexed
        {
            get { return smComplex; }
            private set { smComplex = value; }
        }

        public void ShowFlyout()
        {
            ViewModelManager viewManager = ViewModelManager.Instance();
            SnDevices.Clear();

            var flyout = this.Flyouts.Items[0] as Flyout;
            flyout.Position = Position.Top;
            flyout.DataContext = mainViewMedel;

            ListBox lbxCodes = flyout.FindChild<ListBox>("lbxSNCode");
            lbxCodes.Items.Clear();

            SnDevices.OnSnQueueEnqueue = (int cur) =>
            {
                if (cur >= 0 && cur < lbxCodes.Items.Count)
                {
                    DockPanel sp = lbxCodes.Items.GetItemAt(cur) as DockPanel;
                    TextBox tb = sp.Children[1] as TextBox;
                    tb.IsEnabled = true;
                    tb.Text = "";

                    if (cur == SnDevices.FistItemInSnDeviceQueue())
                    {
                        tb.Focus();
                    }
                }
            };

            SnDevices.OnSnQueueDequeue = (int cur) =>
            {
                if (cur >= 0 && cur < lbxCodes.Items.Count)
                {
                    DockPanel sp = lbxCodes.Items.GetItemAt(cur) as DockPanel;
                    TextBox tb = sp.Children[1] as TextBox;
                    tb.IsEnabled = false;
                }

                if (SnDevices.FistItemInSnDeviceQueue() >= 0)
                {
                    SnDevices.OnSnQueueEnqueue(SnDevices.FistItemInSnDeviceQueue());
                }
            };

            for (int index = 0; index < viewManager.TestMode; index++)
            {
                DockPanel sp = new DockPanel() { HorizontalAlignment = HorizontalAlignment.Stretch, };
                TextBlock sn = new TextBlock() { TextAlignment = TextAlignment.Center, FontWeight = FontWeights.Bold, Text = "SN:", Margin = new Thickness(0, 5, 0, 0) };
                sp.Children.Add(sn);

                TextBox tbSNCode = new TextBox() { TextAlignment = TextAlignment.Center, FontWeight = FontWeights.Bold, IsEnabled = false, Style = FindResource("WpfTextBox") as Style, Foreground = new SolidColorBrush(Color.FromArgb(255, 0, 0, 255)), Margin = new Thickness(5, 0, 5, 0) };
                sp.Children.Add(tbSNCode);

                lbxCodes.Items.Add(sp);

                tbSNCode.Tag = index;
                tbSNCode.TextChanged += (object sender, TextChangedEventArgs e) =>
                {
                    //if (3 != StartTrigger) return;
                    if (tbSNCode.Text.Length >= SnLen)
                    {
                        bool start = true;
                        //if (SelectFormat == 8)//Ofilm
                        {
                            var filter = SNFilter.Trim();
                            if (filter!="")
                            {
                                var tes = tbSNCode.Text;

                                var result = tes.StartsWith(filter);
                                if (result == false)
                                {
                                    var str = String.Format("SN CODE ={0},SNFilter ={1} rule error ", tes, filter);
                                    MessageBox.Show(str, "warning");
                                    tbSNCode.Text = "";
                                    start = false;
                                    //return;
                                }
                            
                            }
                        }
                        if (start == true)
                        {
                            //if (DisplayTest == 1)
                            //{
                            //    TouchResultWindow selectWin = new TouchResultWindow();
                            //    selectWin.ShowDialog();
                            //    if (string.IsNullOrEmpty(TouchResultWindow.TouchSelectResult))
                            //    {
                            //        MessageBox.Show("Please select result（PASS or FAIL）！", "note");
                            //        return;
                            //    }
                            //}

                            //if (NeedClickStart!=1)
                            //{
                            //    int device = SnDevices.SnDeviceDequeue();
                            //    smComplex.SendTestRzForDisplay(device, TouchResultWindow.TouchSelectResult);
                            //    if (smComplex.StartTestBySn(device, tbSNCode.Text) > 0)
                            //    {

                            //    }
                            //}
                            //else
                            //{
                            //    int device = SnDevices.SnDeviceDequeue();
                            //    dcDisplayStrMap[device] = TouchResultWindow.TouchSelectResult;
                            //    dcSnStrMap[device] = tbSNCode.Text;
                            //}

                            // Delayed Execution to Resolve UI Timing Conflicts--LHL
                            this.Dispatcher.BeginInvoke(new Action(() =>
                            {
                                string selectResult = string.Empty;
                                if (DisplayTest == 1)
                                {
                                    if (_isDisplayWindowShowing)
                                    {
                                        return;
                                    }

                                    TouchResultWindow selectWin = new TouchResultWindow();
                                    selectWin.Closed += delegate
                                    {
                                        _isDisplayWindowShowing = false;
                                    };
                                    _isDisplayWindowShowing = true;
                                    bool? dialogResult = selectWin.ShowDialog();

                                    selectResult = selectWin.TouchSelectResult;

                                    if (dialogResult != true || string.IsNullOrEmpty(selectResult))
                                    {
                                        MessageBox.Show("Please select result（PASS or FAIL）！", "note");
                                        _isDisplayWindowShowing = false;
                                        return;
                                    }
                                }

                                if (NeedClickStart != 1)
                                {
                                    int device = SnDevices.SnDeviceDequeue();
                                    smComplex.SendTestRzForDisplay(device, selectResult);
                                    if (smComplex.StartTestBySn(device, tbSNCode.Text) > 0)
                                    {
                                    }
                                }
                                else
                                {
                                    int device = SnDevices.SnDeviceDequeue();
                                    dcDisplayStrMap[device] = selectResult;
                                    dcSnStrMap[device] = tbSNCode.Text;
                                }
                            }), System.Windows.Threading.DispatcherPriority.ApplicationIdle);
                        }

                    }
                };

                tbSNCode.AddHandler(TextBox.MouseLeftButtonDownEvent, new MouseButtonEventHandler((o, e) =>
                {
                    int pos = (int)tbSNCode.Tag;
                    SnDevices.SnDeviceJumpQueue(pos);
                }), true);
            }

            flyout.IsOpen = !flyout.IsOpen;

            this.Dispatcher.BeginInvoke(DispatcherPriority.Background, (Action)(() =>
            {
                for (int index = 0; index < viewManager.TestMode; index++)
                {
                    if (1 == mainViewMedel.DeviceStates[index])
                    {
                        SnDevices.SnDeviceEnqueue(index);
                    }
                }
            }));
        }

        /// <summary>
        /// 创建人员：Wasim， 日期：2017-04-6
        /// 功能描述：Windows窗体初始化完成响应函数：
        /// remark...
        /// </summary>  
        void MainWindowSourceInitialized(object sender, EventArgs e)
        {
            smComplex.OnlyReloadXmlConfig();

            InitMainTestView();

            HwndSource hwndSource = PresentationSource.FromVisual(this) as HwndSource;
            hwndSource.AddHook(new HwndSourceHook(WndProc));

            Guid prtGUID = new Guid("28d78fad-5a12-11D1-ae5b-0000f803a8c2");
            ExportDeclares.CLRRegisterNotification(hwndSource.Handle, prtGUID.ToByteArray());

            Guid hidGUID = new Guid("4d1e55b2-f16f-11cf-88cb-001111000030");
            ExportDeclares.CLRRegisterNotification(hwndSource.Handle, hidGUID.ToByteArray());

            CLRLinkParam param = new CLRLinkParam();
            param.LinkType = (byte)Agent;
            bool bConnected = ExportDeclares.CLRHalLinkAndDoInit(param);
           
            SMCallBack callBack = SMCallBack.GetInstance();
            callBack.onOneTestStart = ViewModelManager.OnStartTest;
            callBack.onListItemChange = ViewModelManager.OnListViewUpdate;
            //callBack.onInitProcessBar = OnInitProcessBar;
            callBack.onProcessBarChanging = ViewModelManager.OnProcessBarRefresh;
            callBack.onOneTestOver = ViewModelManager.OnTestFinished;
            callBack.onTouchReport = ViewModelManager.OnTouchReport;
            callBack.OnInforUpload = ViewModelManager.UploadCallBack;
            smComplex.RegistSMTestCallBack(callBack);
            smComplex.ReloadXmlConfig();

            List<SMTestItem> listItems = new List<SMTestItem>();
            smComplex.GetAllTestItemLists(0, listItems);
            ViewModelManager.Instance().InitializeListView(listItems);
     
            CommandLineProcess();
      
            DeviceStatusUpdate();

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
            //#define WM_CHAR                         0x0102
            //#define VK_SPACE                        0x20
            //#define WM_RECV_USER_DATA               WM_USER + 2004   0x400 + 2004
        
            if (msg == DeviceManagement.WM_DEVICECHANGED)
            {
                OnDeviceChange(msg, wParam, lParam);
            }
            else if (0x0101 == msg)
            {
                if ((uint)wParam == (uint)0x20)
                {
                    var flyout = this.Flyouts.Items[0] as Flyout;
                    ListBox lbxCodes = flyout.FindChild<ListBox>("lbxSNCode");
                    if (lbxCodes.Items.Count == 0)
                    {
                        ForcePaint();
                    }
                    else
                    {
                        DockPanel sp = lbxCodes.Items.GetItemAt(0) as DockPanel;
                        TextBox tb = sp.Children[1] as TextBox;
                        if (tb.Text == "")
                        {
                            ForcePaint();
                        }
                    }                   
                }
            }
            else if (0x400 + 2004 == msg)
            {
                smComplex.ActionToOnLineMessage(msg, (int)wParam, (int)lParam);
            }
//             else if (0x102 == msg)
//             {
//                 ViewModelManager viewManager = ViewModelManager.Instance();
//                 if(3 != StartTrigger) return (System.IntPtr)0;
//                 if (viewManager.TestMode == SEMI.Util.Definition.Mode_Singleton_Test && viewManager.GetSinglePageViewMode().SNCodeEnable)
//                 {
//                     char chInput = (char)wParam;
//                     viewManager.GetSinglePageViewMode().SNCode += chInput;
// 
//                     if (viewManager.GetSinglePageViewMode().SNCode.Length >= SnLen)
//                     {
//                         viewManager.GetSinglePageViewMode().SNCodeEnable = false;
// 
//                         int device = viewManager.GetSinglePageViewMode().DeviceNo;
//                         if (smComplex.StartTestBySn(device, viewManager.GetSinglePageViewMode().SNCode) > 0)
//                         {
//                             viewManager.GetSinglePageViewMode().SNCodeEnable = true;
//                             viewManager.GetSinglePageViewMode().SNCode = "";
//                         }
//                     }
//                 }
//             }
            return (System.IntPtr)0;
        }

        internal void ForcePaint()
        {
            if (ViewModelManager.Instance().TestMode > SEMI.Util.Definition.Mode_Singleton_Test)
                return;

            Boolean bInGraph = ViewModelManager.Instance().GetSinglePageViewMode().EnterGraphMode;
            int device = ViewModelManager.Instance().GetSinglePageViewMode().DeviceNo;

            if (0 == smComplex.ForcePaint(device, !bInGraph))
            {
                ViewModelManager.Instance().GetSinglePageViewMode().EnterGraphMode = !bInGraph;
            }
        }
        internal void InitMainTestView()
        {
//             System.Xml.XmlDocument xml = new System.Xml.XmlDocument();
//             string xmlPath = SEMITestApp.Src.WinSet.SettingMode.GetWorkPath() + "config\\semichip_ctp_config.xml";
//             try
//             {
//                 xml.Load(xmlPath);
//                 System.Xml.XmlNode root = xml.SelectSingleNode("semitester");
//                 if (root == null) return;
//                 System.Xml.XmlNode commonNode = root.SelectSingleNode("common");
//                 if (commonNode == null) return;
//                 System.Xml.XmlAttribute stationAttr = commonNode.Attributes["work_station"];
//                 if(null == stationAttr) return;
//                 System.Xml.XmlAttribute projectAttr = commonNode.Attributes["project_name"];
//                 if (null == projectAttr) return;
// 
//                 string workStation = stationAttr.Value;
//                 string projectName = projectAttr.Value;
// 
//                 mainViewMedel.ProjectInfo = "WorkStation: " + workStation + "   ProjectName: " + projectName;
// 
//                 System.Xml.XmlNode nodeStation = root.SelectSingleNode(workStation);
//                 if(nodeStation == null) return;
//                 System.Xml.XmlNode nodeMisc = nodeStation.SelectSingleNode("misc");
//                 if(nodeMisc == null) return;
//                 System.Xml.XmlAttribute startAttr = nodeMisc.Attributes["way_to_start"];
//                 if(startAttr == null) return;
//                 System.Xml.XmlAttribute snLenAttr = nodeMisc.Attributes["sn_length"];
//                 if (snLenAttr == null) return;
// 
//                 StartTrigger = int.Parse(startAttr.Value);
//                 SnLen = int.Parse(snLenAttr.Value);
//                 //start by sn triger
//                 if (StartTrigger == 3)
//                 {
//                     ViewModelManager.Instance().GetSinglePageViewMode().SNCodeVisible = Visibility.Visible;
//                 }
//                 else
//                 {
//                     ViewModelManager.Instance().GetSinglePageViewMode().SNCodeVisible = Visibility.Collapsed;
//                 }
// 
//                 int mode = LoadTestModel();
//                 ViewModelManager.Instance().TestMode = mode;
//                 mainViewMedel.FrameContent = mainViewMedel.ContentMap[mode];
//             }
//             catch (Exception ex)
//             {
//                 ex.ToString();
//             }

            SMViewInfomation info = smComplex.GetViewInfomation();
            if (null == info) return;

            StartTrigger = info.wayToStart;
            SnLen = info.sn_len;
            SelectFormat = info.format;
            Agent = info.test_agent;
            NeedClickStart = info.needclickstart;
            DisplayTest = info.displaytest;
            SNFilter = info.snFilter;
            //start by sn triger
//             if (StartTrigger == 3)
//             {
//                 ViewModelManager.Instance().GetSinglePageViewMode().SNCodeVisible = Visibility.Visible;
//             }
//             else
//             {
//                 ViewModelManager.Instance().GetSinglePageViewMode().SNCodeVisible = Visibility.Collapsed;
//             }

            mainViewMedel.SoftWareVersion = info.szSoftWare;
            mainViewMedel.ProjectInfo = "WorkStation: " + info.szStation + "   ProjectName: " + info.szProjectInfo;

            //int mode = LoadTestModel();
            int mode = (int)info.test_mode;
            ViewModelManager.Instance().TestMode = mode;
            mainViewMedel.FrameContent = mainViewMedel.ContentMap[mode];

        }
        internal void CommandLineProcess()
        {
            string[] commandLines = Environment.GetCommandLineArgs();

            uint commandMode = ExportDeclares.SM_COMMAND_NONE;
            if (commandLines.Contains("-DEBUG"))
                commandMode |= ExportDeclares.SM_COMMAND_DEBUG;
            if (commandLines.Contains("-FAE"))
                commandMode |= ExportDeclares.SM_COMMAND_FAE;
            if (commandLines.Contains("-STOP"))
                commandMode |= ExportDeclares.SM_COMMAND_STOP;

            smComplex.SetCommandLineParam(commandMode);

            bool bRetest = commandLines.Contains("-RETEST");
            if (bRetest)
            {
                System.Threading.Thread t = new System.Threading.Thread(() =>
                {
                    int reTry = 60 * 60 * 24;
                    while (reTry-- > 0)
                    {
                        for (int index = 0; index < ExportDeclares.MAX_DEVICE_NUMS; index++)
                        {
                            MainWindow.SMComplexed.StartTest(index);
                        }

                        System.Threading.Thread.Sleep(3000);
                    }
                });

                t.IsBackground = true;
                t.Start();
            }

            CustomizedInformationDisplay();

            if (PopOutSNOnAppStart()) //start by sn
            {
                Task task = new Task(() =>
                {
                    System.Threading.Thread.Sleep(3 * 1000);
                    this.Dispatcher.Invoke((Action)(() =>
                    {
                        ShowFlyout();
                    }));
                });
                task.Start();
            }

            if (4 == SelectFormat)  //format - hx
            {
                mainViewMedel.OnLineUpdate(1);
            }
        }
        private bool PopOutSNOnAppStart()
        {
            if (3 == SelectFormat) //edo
            {
                return false;
            }
            if (3 == StartTrigger) //start 
            {
                return true;
            }

            return false;
        }
        private void CustomizedInformationDisplay()
        {
            if (8== SelectFormat) //edo
            {

                var ofilm = new OfilmCustomizedWin();

                MainWindow.SMComplexed.GameOver(0);

                ofilm.ShowDialog();

                MainWindow.SMComplexed.GameOver(1);
                MainWindow.SMComplexed.ReloadXmlConfig();
            }

        }
        internal void OnDeviceChange(int msg, IntPtr wParam, IntPtr lParam)
        {
            try
            {
                //System.Threading.Thread.Sleep(1000);
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
                    param.LinkType = (byte)Agent;  
                    param.szCurMsg = csTemp;
                    ExportDeclares.CLRHalLinkAndDoInit(param);

                    smComplex.SetCommContext(param.devID);

                    DeviceStatusUpdate();
                }
                else if ((int)wParam == DeviceManagement.DBT_DEVICEREMOVECOMPLETE)
                {
                    //System.Threading.Thread.Sleep(5000);
                    DEV_BROADCAST_DEVICEINTERFACE dip;
                    dip = (DEV_BROADCAST_DEVICEINTERFACE)Marshal.PtrToStructure(lParam, typeof(DEV_BROADCAST_DEVICEINTERFACE));
                    string csTemp = dip.dbcc_name;

                    CLRLinkParam param = new CLRLinkParam();
                    param.LinkType = (byte)Agent;   
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

            mainViewMedel.DeviceStates = devStatus;

            
        }

        private void MetroWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //SaveTestMode(ViewModelManager.Instance().TestMode);

            smComplex.GameOver( 1 );
        }

//         private int LoadTestModel()
//         {
//             const string KeyPath = "HKEY_CURRENT_USER\\Software\\SemiChip";  
//             const string keyNode = "TestMode";
//             string sType = WinRegistry.GetValue(KeyPath, keyNode, "0") as string;
//             return (string.IsNullOrEmpty(sType) || "0" == sType) ? SEMI.Util.Definition.Mode_Singleton_Test : int.Parse(sType);
//         }

//         private void SaveTestMode(int mode)
//         {
//             const string KeyPath = "HKEY_CURRENT_USER\\Software\\SemiChip";
//             const string keyNode = "TestMode";
//             WinRegistry.SetValue(KeyPath, keyNode, mode.ToString());
//         }
    }
}
 