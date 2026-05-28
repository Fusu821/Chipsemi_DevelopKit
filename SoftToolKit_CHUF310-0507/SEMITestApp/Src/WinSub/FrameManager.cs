using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SEMITestApp.Src.Util;
using System.Windows;
using System.Windows.Media;
using System.Collections.ObjectModel;
using SMInvokeBridge;
using SEMI.Util;
using SEMIEmsSysUpLoad;
//using SEMIEmsSysUpLoad;

namespace SEMITestApp.Src.WinSub
{
    //class OneAppFrameViewModel : NotifyBase
    //{

    //}
    //public enum Test_Status { TEST_INIT, TEST_GOING, TEST_PASS, TEST_NG, TEST_TBD }
    public class SinglePageViewMode : CtrlEventDispacher
    {
        public int DeviceNo { get; set; }

        private int testStatus = 0;
        public int TestStatus
        {
            get { return testStatus; }
            set { if (value != testStatus) { testStatus = value; OnPropertyChanged("TestStatus"); } }
        }

        private Boolean enterGraphMode = false;
        public Boolean EnterGraphMode
        {
            get { return enterGraphMode; }
            set { if (enterGraphMode != value) { enterGraphMode = value; OnPropertyChanged("EnterGraphMode"); } }
        }

        private int processBarPosition = 0;
        public int ProcessBarPosition
        {
            get { return processBarPosition; }
            set { if (processBarPosition != value) { processBarPosition = value; OnPropertyChanged("ProcessBarPosition"); } }
        }

        private int processBarMax = 100;
        public int ProcessBarMax
        {
            get { return processBarMax; }
            set { if (processBarMax != value) { processBarMax = value; OnPropertyChanged("ProcessBarMax"); } }
        }

//         private bool snCodeEnable = true;
//         public bool SNCodeEnable
//         {
//             get { return snCodeEnable; }
//             set { if (value != snCodeEnable) { snCodeEnable = value; OnPropertyChanged("SNCodeEnable"); } }
//         }

//         Visibility snVisible = Visibility.Collapsed;
//         public Visibility SNCodeVisible
//         {
//             get { return snVisible; }
//             set { if (value != snVisible) { snVisible = value; OnPropertyChanged("SNCodeVisible"); } }
//         }

//         private string snCode = "";
//         public string SNCode
//         {
//             get { return snCode; }
//             set { if (value != snCode) { snCode = value; OnPropertyChanged("SNCode"); } }
//         }

        private TouchReportData touchData = new TouchReportData(0);
        public TouchReportData TouchData
        {
            get { return touchData; }
            set { if (touchData != value) touchData = value; OnPropertyChanged("TouchData"); }
        }


        public int TestMode
        {
            get { return ViewModelManager.Instance().TestMode; }
            set { OnPropertyChanged("TestMode"); }
        }

        private ObservableCollection<SMTestItemRef> listSMTestItems = new ObservableCollection<SMTestItemRef>();
        public ObservableCollection<SMTestItemRef> ListSMTestItems
        {
            get { return listSMTestItems; }
            set { if (value != listSMTestItems) { listSMTestItems = value; OnPropertyChanged("ListSMTestItems"); } }
        }
        public void UpDateListByItemID(int idCode, SMTestItem item)
        {
            SMTestItemRef itemRef = listSMTestItems.FirstOrDefault((t) =>
            {
                return t.testCode == idCode;
            });
            if (null != itemRef)
            {
                //itemRef = new SMTestItemRef(item);
                itemRef.ItemResult = item.testResult;
                itemRef.ItemMark = item.testMark;
            }
        }
        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if("start-button-click" == strParam)
            {

                if (3 == MainWindow.StartTrigger && MainWindow.NeedClickStart == 1)
                {
                    var sn_code = MainWindow.dcSnStrMap[DeviceNo];
                    var display_rz = MainWindow.dcDisplayStrMap[DeviceNo];
                    if (sn_code.Length >= MainWindow.SnLen)
                    {
                        MainWindow.SMComplexed.SendTestRzForDisplay(DeviceNo, display_rz);
                        MainWindow.SMComplexed.StartTestBySn(DeviceNo, sn_code);
                        MainWindow.dcDisplayStrMap[DeviceNo] = "";
                        MainWindow.dcSnStrMap[DeviceNo] = "";
                    }
                }

                if (3 != MainWindow.StartTrigger)
                {
                    MainWindow.SMComplexed.StartTest(DeviceNo);
                }
            }
        }
    }

    public class MutiplePageViewMode : SinglePageViewMode
    {
        public static int viewDevice = 0;

//         private static bool snCodeEnable = true;
//         public bool SNCodeEnable
//         {
//             get { return snCodeEnable; }
//             set { if (value != snCodeEnable) { snCodeEnable = value; OnPropertyChanged("SNCodeEnable"); } }
//         }

//         Visibility snVisible = Visibility.Collapsed;
//         public Visibility SNCodeVisible
//         {
//             get { return snVisible; }
//             set { if (value != snVisible) { snVisible = value; OnPropertyChanged("SNCodeVisible"); } }
//         }

//         private string snCode = "";
//         public string SNCode
//         {
//             get { return snCode; }
//             set { if (value != snCode) { snCode = value; OnPropertyChanged("SNCode"); } }
//         }
    }

    class SnDevices
    {
        public delegate void SnQueueReaction(int dev);
        public static SnQueueReaction OnSnQueueEnqueue;
        public static SnQueueReaction OnSnQueueDequeue;
        private static IList<int> ListSnDevice = new List<int>();

        public static int FistItemInSnDeviceQueue()
        {
            if (ListSnDevice.Count == 0) return -1;

            return ListSnDevice.ElementAt(0);
        }

        public static void SnDeviceJumpQueue(int dev)
        {
            if (ListSnDevice.Contains(dev))
            {
                ListSnDevice.Remove(dev);
            }
            ListSnDevice.Insert(0, dev);
        }

        public static void SnDeviceEnqueue(int dev)
        {
            if (ListSnDevice.Contains(dev))
            {
                ListSnDevice.Remove(dev);
            }
            ListSnDevice.Add(dev);

            if (null != OnSnQueueEnqueue)
            {
                OnSnQueueEnqueue(dev);
            }
        }

        public static int SnDeviceDequeue()
        {
            int dev = 0;
            if (0 == ListSnDevice.Count) return -1;

            dev = ListSnDevice.ElementAt(0);
            ListSnDevice.RemoveAt(0);

            if (null != OnSnQueueDequeue)
            {
                OnSnQueueDequeue(dev);
            }

            return dev;
        }

        public static void Clear()
        {
            ListSnDevice.Clear();
        }
    }
    class ViewModelManager
    {
        private static ViewModelManager managerInstance = null;
        private List<NotifyBase> listViewModle = new List<NotifyBase>();
        public System.Windows.Controls.RichTextBox richTextSin { private get; set; }
        public System.Windows.Controls.RichTextBox richTextMul { private get; set; }
        //public System.Windows.Controls.TextBox textBoxSnCode { private get; set; }
        //public System.Windows.Controls.Label lableSnInfo { private get; set; }
        //public List<int> ListSnDevice { get; private set; }

        //public delegate void SnQueueEnqueueReaction(int dev);
        public static ViewModelManager Instance()
        {
            if(null == managerInstance)
            {
                managerInstance = new ViewModelManager();
            }
            return managerInstance;
        }
        private ViewModelManager()
        {
        }

        

        public SinglePageViewMode GetSinglePageViewMode()
        {
            SinglePageViewMode mode = listViewModle.Find((e) => 
            {
                return e.GetType() == typeof(SinglePageViewMode) ? true : false;
            }) as SinglePageViewMode;
            if(null == mode)
            {
                mode = new SinglePageViewMode();
                listViewModle.Add(mode);
            }

            return mode;
        }
        public MutiplePageViewMode GetMutiplePageViewMode(int deviceNo)
        {
            MutiplePageViewMode mode = listViewModle.Find((e) =>
            {
                if (e.GetType() != typeof(MutiplePageViewMode)) return false;
                MutiplePageViewMode mp = e as MutiplePageViewMode;
                if (mp.DeviceNo == deviceNo) return true;

                return false;
            }) as MutiplePageViewMode;
            if(null == mode)
            {
                mode = new MutiplePageViewMode();
                mode.DeviceNo = deviceNo;
                listViewModle.Add(mode);
            }

            return mode;
        }


        private int testMode = Definition.Mode_Singleton_Test;
        public int TestMode
        {
            get { return testMode; }
            set
            {
                testMode = value;
                foreach(var item in listViewModle)
                {
                    MutiplePageViewMode viewMode = item as MutiplePageViewMode;
                    if (null == viewMode) continue;

                    viewMode.TestMode = testMode;
                }
            }
        }

        private void UpdateFirstRowOfListView(SinglePageViewMode viewModel, int deviceNo, bool bConnected)
        {
            if (bConnected)
            {
                SMTestItem fackItem = new SMTestItem()
                {
                    testCode = 0,
                    testName = "MTK Connection",
                    testResult = ExportDeclares.SM_ITEM_STA_PASS,
                    testMark = "MTK = " + (deviceNo + 1).ToString(),
                };
                viewModel.UpDateListByItemID(0, fackItem);
            }
            else
            {
                SMTestItem fackItem = new SMTestItem()
                {
                    testCode = 0,
                    testName = "MTK Connection",
                    testResult = ExportDeclares.SM_ITEM_STA_FAIL,
                    testMark = "",
                };
                viewModel.UpDateListByItemID(0, fackItem);
            }
        }

        public void OnDeviceStatusChange(byte[] status)
        {
            int counter = status.Count((t) =>
            {
                return t == 1;
            });
            int firstDev = 0;
            for (firstDev = 0; firstDev < status.Length; firstDev++)
                if (1 == status[firstDev]) break;

            SinglePageViewMode slgViewMode = GetSinglePageViewMode();
            if (null != slgViewMode)
            {
                if (counter > 0)
                    UpdateFirstRowOfListView(slgViewMode, firstDev, true);
                else
                    UpdateFirstRowOfListView(slgViewMode, firstDev, false);

                slgViewMode.DeviceNo = firstDev;
            }
            for (int index = 0; index < ExportDeclares.MAX_DEVICE_NUMS; index++)
            {
                MutiplePageViewMode mulViewMode = GetMutiplePageViewMode(index);
                if (null != mulViewMode)
                {
                    int viewNo = mulViewMode.DeviceNo;
                    if (1 == status[viewNo])
                        UpdateFirstRowOfListView(mulViewMode, viewNo, true);
                    else
                        UpdateFirstRowOfListView(mulViewMode, viewNo, false);
                }
            } 
        }
        public void InitializeListView(List<SMTestItem> listVals)
        {
            SinglePageViewMode sinModel = GetSinglePageViewMode();
            if (null != sinModel)
            {
                sinModel.ListSMTestItems.Clear();
                foreach (var val in listVals)
                    sinModel.ListSMTestItems.Add(new SMTestItemRef(val));
            }
            for (int index = 0; index < ExportDeclares.MAX_DEVICE_NUMS; index++)
            {
                MutiplePageViewMode mulModel = GetMutiplePageViewMode(index);
                if (null != mulModel)
                {
                    mulModel.ListSMTestItems.Clear();
                    foreach (var val in listVals)
                        mulModel.ListSMTestItems.Add(new SMTestItemRef(val));
                }
            }
        }
        public void ShowMessageById(int deviceID)
        {
            if (Definition.Mode_Singleton_Test == testMode)
            {

            }
            else 
            {
                MutiplePageViewMode.viewDevice = deviceID;
                List<SMColorText> listText = new List<SMColorText>();
                MainWindow.SMComplexed.GetTestMessage(deviceID, listText);
                FillRichText(richTextMul, listText);
            }
        }
        public static uint OnStartTest(int device)
        {
            MainWindow.AppWin.Dispatcher.Invoke(new Action(() =>
            {
                ViewModelManager manager = ViewModelManager.Instance();
                if (manager.testMode == Definition.Mode_Singleton_Test)
                {
                     SinglePageViewMode sinModel = manager.GetSinglePageViewMode();
                    foreach (var item in sinModel.ListSMTestItems)
                    {
                        item.Reset();
                    }
                    if (null != manager.richTextSin)
                    {
                        manager.richTextSin.Document.Blocks.Clear();
                    }
                    sinModel.TestStatus = ExportDeclares.SM_TEST_GOING;
                }
                else
                {
                    MutiplePageViewMode mulModel = manager.GetMutiplePageViewMode(device);
                    foreach (var item in mulModel.ListSMTestItems)
                    {
                        item.Reset();
                    }
                    if (null != manager.richTextMul)
                    {
                        manager.richTextMul.Document.Blocks.Clear();
                    }
                    mulModel.TestStatus = ExportDeclares.SM_TEST_GOING;
                }
            }));

            uint ret = MainWindow.SMComplexed.UserOperationBeforeTest(device);
            if (0 != ret)
            {
               Application.Current.Dispatcher.Invoke((Action)(() =>
                {
                    MessageBox.Show(MainWindow.SMComplexed.GetOnLineMessageInfo(), "warning");
                    //MahApps.Metro.Controls.Dialogs.DialogManager.ShowMessageAsync(MainWindow.MainWindowSingleInst, "warning",
                    //    MainWindow.SMComplexed.GetOnLineMessageInfo(), MahApps.Metro.Controls.Dialogs.MessageDialogStyle.Affirmative);
                })); 
            }
            return ret;
        }
        public static void OnProcessBarRefresh(int deviceID, int pos, int max)
        {
            ViewModelManager manager = ViewModelManager.Instance();
            if (manager.testMode == Definition.Mode_Singleton_Test)
            {
                SinglePageViewMode sinModel = manager.GetSinglePageViewMode();
                sinModel.ProcessBarPosition = pos;
                sinModel.ProcessBarMax = max;
            }
            else 
            {
                MutiplePageViewMode mulModel = manager.GetMutiplePageViewMode(deviceID);
                mulModel.ProcessBarPosition = pos;
                mulModel.ProcessBarMax = max;
            }
        }
        public static void OnListViewUpdate(SMTestItem item)
        {
            ViewModelManager manager = ViewModelManager.Instance();
            if (manager.testMode == Definition.Mode_Singleton_Test)
            {
                SinglePageViewMode sinModel = manager.GetSinglePageViewMode();
                sinModel.UpDateListByItemID(item.testCode, item);
                sinModel.EnterGraphMode = item.testCode >= ExportDeclares.SM_MIN_GRAPH_ID;
            }
            else
            {
                for (int index = 0; index < ExportDeclares.MAX_DEVICE_NUMS; index++)
                {
                    MutiplePageViewMode mulModel = manager.GetMutiplePageViewMode(index);
                    if (mulModel.DeviceNo != item.ucDevice) continue;

                    mulModel.UpDateListByItemID(item.testCode, item);
                    mulModel.EnterGraphMode = item.testCode >= ExportDeclares.SM_MIN_GRAPH_ID;
                }
            }
        }
        public static void OnTouchReport(int deviceID)
        {
            ViewModelManager manager = ViewModelManager.Instance();
            if (manager.testMode == Definition.Mode_Singleton_Test)
            {
                SinglePageViewMode sinModel = manager.GetSinglePageViewMode();
                sinModel.TouchData = new TouchReportData(deviceID);
            }
            else 
            {
                MutiplePageViewMode mulMode = manager.GetMutiplePageViewMode(deviceID);
                mulMode.TouchData = new TouchReportData(deviceID);
            }
        }
        public static void FillRichText(System.Windows.Controls.RichTextBox rich, List<SMColorText> listText)
        {
            if (null == rich) return;

            rich.Document.Blocks.Clear();
            rich.Document.PageWidth = 2000;
            System.Windows.Documents.Paragraph paragraph = new System.Windows.Documents.Paragraph();
            foreach (var item in listText)
            {
                System.Windows.Documents.Run docRun = new System.Windows.Documents.Run();
                docRun.Text = item.strText;
                docRun.FontSize = 15;
                docRun.Foreground = new SolidColorBrush(Color.FromRgb((byte)(item.dwColor & 0x0000ff), (byte)((item.dwColor & 0x00ff00) >> 8), (byte)((item.dwColor & 0xff0000) >> 16)));
                if (item.bBold)
                {
                    docRun.FontWeight = System.Windows.FontWeights.Bold;
                }
                if (ExportDeclares.SM_TEXT_SIZE_LARGE == item.iHeight)
                {
                    docRun.FontSize = 25;
                }

                paragraph.Inlines.Add(docRun);
            }
            rich.Document.Blocks.Add(paragraph);

            rich.ScrollToEnd();
        }
        public static SMUpLoadInfo UploadCallBack( SMUpLoadInfo info)
        {


            SMUpLoadInfo ret = new SMUpLoadInfo();
            //ret.codenum = 1;
            //ret.str = "11111";
            ret.codenum = MESUpLoad.UpLoadEmsSystem(info, ref ret.str);

            return ret;
        }
        public static uint OnTestFinished(int deviceID, uint finalResult)
        {
            ViewModelManager manager = ViewModelManager.Instance();

            if (manager.testMode == Definition.Mode_Singleton_Test)
            {
                manager.GetSinglePageViewMode().TestStatus = (int)finalResult;
                manager.GetSinglePageViewMode().EnterGraphMode = false;

                List<SMColorText> listText = new List<SMColorText>();
                MainWindow.SMComplexed.GetTestMessage(deviceID, listText);

                if (finalResult > 0)
                {
                    Application.Current.Dispatcher.Invoke((Action)(() =>
                    {
                        SnDevices.SnDeviceEnqueue(deviceID);
                        MainWindow.SMComplexed.UserOperationAfterTest(deviceID, (int)finalResult);
                        FillRichText(manager.richTextSin, listText);

                        MainViewModel mainMode = MainWindow.AppWin.DataContext as MainViewModel;
                        if (null != mainMode) mainMode.StatisticText = MainWindow.SMComplexed.GetStatisticText().Replace('\n', ' ');
                    }));
                }
                else
                {
                    foreach (var item in manager.GetSinglePageViewMode().ListSMTestItems)
                    {
                        item.Reset();
                    }
                    manager.GetSinglePageViewMode().TestStatus = ExportDeclares.SM_TEST_NONE;
                }
            }
            else
            {
                manager.GetMutiplePageViewMode(deviceID).TestStatus = (int)finalResult;
                manager.GetMutiplePageViewMode(deviceID).EnterGraphMode = false;
               
                if (finalResult > 0)
                {
                    List<SMColorText> listText = new List<SMColorText>();
                    if (MutiplePageViewMode.viewDevice == deviceID)
                    {                        
                        MainWindow.SMComplexed.GetTestMessage(deviceID, listText);
                    }
                    Application.Current.Dispatcher.Invoke((Action)(() =>
                    {
                        SnDevices.SnDeviceEnqueue(deviceID);
                        MainWindow.SMComplexed.UserOperationAfterTest(deviceID, (int)finalResult);
                        FillRichText(manager.richTextMul, listText);

                        MainViewModel mainMode = MainWindow.AppWin.DataContext as MainViewModel;
                        if (null != mainMode) mainMode.StatisticText = MainWindow.SMComplexed.GetStatisticText().Replace('\n', ' ');
                    }));

                }
                else
                {
                    foreach (var item in manager.GetMutiplePageViewMode(deviceID).ListSMTestItems)
                    {
                        item.Reset();
                    }
                    manager.GetSinglePageViewMode().TestStatus = ExportDeclares.SM_TEST_NONE;
                }
            }
            

            return 0;
        }
    }
}
