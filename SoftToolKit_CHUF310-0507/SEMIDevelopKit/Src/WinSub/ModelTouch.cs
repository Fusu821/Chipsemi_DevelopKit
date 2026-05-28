using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using System.ComponentModel;
using SEMIDevelopKit.Src.Util;
using SMInvokeBridge;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.IO;
namespace SEMIDevelopKit.Src.WinSub
{
    public class ModelTouch : ModelBase
    {
        public class ReportPacket
        {
            public static int counter { get; set; }
            public int index { get; set; }
            public DateTime dt { get; set; }
            public string text { get; set; }
            public ReportPacket(string _text)
            {
                index = ++counter;
                dt = DateTime.Now;
                text = _text;
            }
            public ReportPacket(int iter, string _text)
            {
                index = iter;
                dt = DateTime.Now;
                text = _text;
            }
            public override string ToString()
            {
                return string.Format("{0:D1}\t", index) + string.Format("{0:HH-mm-ss:ffff}\t", dt) + text;
            }
        }

        public ModelTouch()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_TOUCH, eChipTypeList.SM_CHIPALL, this);
        }

        public WpfDisplayView DispView { get; set; }

        private TouchReportData touchData = null;
        public TouchReportData TouchData
        {
            get { return touchData; }
            set {  touchData = value; OnPropertyChanged("TouchData"); }
        }

        private bool clearScreen = false;
        public bool ClearScreen
        {
            get { return clearScreen; }
            set { if (value != clearScreen) { clearScreen = value; OnPropertyChanged("ClearScreen"); } }
        }

        private Boolean _ShowCoordinate = true;
        public Boolean ShowCoordinate
        {
            get { return _ShowCoordinate; }
            set { if (value != _ShowCoordinate) { _ShowCoordinate = value; OnPropertyChanged("ShowCoordinate"); } }
        }
        private Boolean _GraphOnce = true;
        public Boolean GraphOnce
        {
            get { return _GraphOnce; }
            set { if (value != _GraphOnce) { _GraphOnce = value; OnPropertyChanged("GraphOnce"); } }
        }
        //private Boolean _HideTickRate = false;
        //public Boolean HideTickRate
        //{
        //    get { return _HideTickRate; }
        //    set { if (value != _HideTickRate) { _HideTickRate = value; OnPropertyChanged("HideTickRate"); } }
        //}

        private Boolean _ShowPackets = false;
        public Boolean ShowPackets
        {
            get { return _ShowPackets; }
            set
            {
                if (value != _ShowPackets)
                {
                    _ShowPackets = value;
                    OnPropertyChanged("ShowPackets");
                }
                if (_ShowPackets)
                {
                     ListPacket.Clear();
                    int cnts = Math.Min(250, LocalListPacket.Count);
                    for (int index = 0; index < cnts; index++)
                        ListPacket.Add(new ModelTouch.ReportPacket(cnts - index, TouchPacketToString(LocalListPacket[index])));
                }
                if (null != DispView) DispView.InvalidateVisual();
            }
        }

        private Boolean _ShowHandStyleData = false;
        public Boolean ShowHandStyleData
        {
            get { return _ShowHandStyleData; }
            set
            {
                if (value != _ShowHandStyleData)
                {
                    _ShowHandStyleData = value;
                    OnPropertyChanged("ShowHandStyleData");
                }
                if (null != DispView) DispView.InvalidateVisual();
            }
        }

        private int _LineSize = 1;
        public int LineSize
        {
            get { return _LineSize; }
            set { if (value != _LineSize) { _LineSize = value; OnPropertyChanged("LineSize"); } }
        }

        private int _PointSize = 15;
        public int PointSize
        {
            get { return _PointSize; }
            set { if (value != _PointSize) { _PointSize = value; OnPropertyChanged("PointSize"); } }
        }

        public int ResolutionX
        {
            get { return ModelBase.XPixel; }
            set { ModelBase.XPixel = value; OnPropertyChanged("ResolutionX"); DispView.InvalidateVisual(); }
        }

        public int ResolutionY
        {
            get { return ModelBase.YPixel; }
            set { ModelBase.YPixel = value; OnPropertyChanged("ResolutionY"); DispView.InvalidateVisual(); }
        }

        private int linesX = 10;
        public int LinesX
        {
            get { return linesX; }
            set { if (value != linesX) { linesX = value; OnPropertyChanged("LinesX"); DispView.InvalidateVisual(); } }
        }

        private int linesY = 10;
        public int LinesY
        {
            get { return linesY; }
            set { if (value != linesY) { linesY = value; OnPropertyChanged("LinesY"); DispView.InvalidateVisual(); } }
        }

        private Boolean _CatchDatastatus = false;
        public Boolean CatchDatastatus
        {
            get { return _CatchDatastatus; }
            set { if (value != _CatchDatastatus) { _CatchDatastatus = value; } }
        }

        private readonly object _touchLock = new object();
        private readonly Queue<TouchReportData> _queueCatchTouchData = new Queue<TouchReportData>();

        public TouchReportData LocalSingleData { get; set; }

        public IList<TouchReportData> LocalListPacket = new List<TouchReportData>();
        //public IList<ModelTouch.ReportPacket> StcListPacket { get { return stcListPacket; } }
        private BindingList<ModelTouch.ReportPacket> _ListPacket = new BindingList<ModelTouch.ReportPacket>();
        public BindingList<ModelTouch.ReportPacket> ListPacket
        {
            get { return _ListPacket; }
            set
            {
                if (value != _ListPacket)
                {
                    _ListPacket = value;
                    OnPropertyChanged("ListPacket");
                }
            }
        }

        public void OnReport(TouchReportData report)
        {
            DispView.OnTouchReport(report);

            //ReportPacketToCatch( report );
        }

        public void ReportPacketToCatch(TouchReportData report)
        {
            if (ShowPackets)
                ListPacket.Insert(0, new ModelTouch.ReportPacket(TouchPacketToString(report)));
 
            LocalListPacket.Insert(0, report);
            LocalSingleData = report.Colne();
            CatchDatastatus = true;

            if (ListPacket.Count > 250)
                ListPacket.RemoveAt(ListPacket.Count - 1);
            if (LocalListPacket.Count > 25000)
                LocalListPacket.RemoveAt(LocalListPacket.Count - 1);
        }

        public string TouchPacketToString(TouchReportData touch)
        {
            StringBuilder strRet = new StringBuilder();
            //ModelTouch viewModel = this.DataContext as ModelTouch;
            if (ShowCoordinate)
            {
                if (touch.TCnt == 0) return "None";
                int pointNumber = 0;
                for (int ptId = 0; ptId < ExportDeclares.SM_MAX_NUM_POINT + ExportDeclares.SM_OTHER_NUM_POINT; ptId++)
                {
                    if (null == touch.Points(ptId)) continue;
                    //if (touch.Points(index).X == 0xffff) continue;
                    //if (touch.Points(index).Y == 0xffff) continue;
                     strRet.Append("P" + (++pointNumber).ToString() + "(" + ptId.ToString() + "," + touch.Points(ptId).X.ToString() + "," + touch.Points(ptId).Y.ToString() + ") ");

                }
            }
            else
            {
                strRet.Append(touch.ToString());
            }
            return strRet.ToString();
        }

        public void ReportShowHandStyleData(TouchReportData report)
        {
            if(report.report[0]==0xfe)
            {
                StringBuilder strRet = new StringBuilder();
                strRet.Append(report.ToString());
                ListPacket.Insert(0, new ModelTouch.ReportPacket(strRet.ToString()));
            
            }
        }

        private byte _GraghMode = 1;
        public byte GraghMode
        {
            get { return _GraghMode; }
            set { if (value != _GraghMode) { _GraghMode = value; OnPropertyChanged("GraghMode"); } }
        }

        public IList<SMDefinition> listAccuracy = new List<SMDefinition>()
        {
            new SMDefinition(16, "16位"),
            new SMDefinition(15, "15位"),
            new SMDefinition(14, "14位"),
            new SMDefinition(13, "13位"),
            new SMDefinition(12, "12位"),
            new SMDefinition(11, "11位"),
            new SMDefinition(10, "10位"),
            new SMDefinition(9,  "9位"),
            new SMDefinition(8,  "8位"),
        };
        public IList<SMDefinition> ListAccuracy
        {
            get { return listAccuracy; }
            private set { }
        }
        private ushort accuracy = 16;
        public ushort Accuracy
        {
            get { return accuracy; }
            set { 
                if (value != accuracy) 
                { 
                    accuracy = value; 
                    OnPropertyChanged("Accuracy");
                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        MainViewModel.Intr.Accuracy = accuracy;
                        //Byte[] ret = new Byte[16];
                        //SMChipBase.IncokeCommand((Byte)(0x70), accuracy, 1, 1, ret);

                    });
                }
            }
        }

        private byte _DrawType = 1;
        public byte DrawType
        {
            get { return _DrawType; }
            set { if (value != _DrawType) { _DrawType = value; OnPropertyChanged("DrawType"); } }
        }

        private uint _ReportRate = 0;
        public uint ReportRate
        {
            get { return _ReportRate; }
            set { if (value != _ReportRate) { _ReportRate = value; } }
        }

        private uint _ReportPenRate = 0;
        public uint ReportPenRate
        {
            get { return _ReportPenRate; }
            set { if (value != _ReportPenRate) { _ReportPenRate = value; } }
        }

        private double displayWidth = 100;
        public double DisplayWidth
        {
            get { return displayWidth; }
            set { if (value != displayWidth) { displayWidth = value; OnPropertyChanged("DisplayWidth"); } }
        }

        private double displayHeight = 100;
        public double DisplayHeight
        {
            get { return displayHeight; }
            set { if (value != displayHeight) { displayHeight = value; OnPropertyChanged("DisplayHeight"); } }
        }

        public override void ActionOnChannelNumChange()
        {
            ResolutionX = ModelBase.XPixel;
            ResolutionY = ModelBase.YPixel;
        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            string str = "";
            //if (null == strParam) return;
            if (string.IsNullOrEmpty(strParam)) return;

            if ("touch-catch-checked" == strParam)
            {
                //queueCatchData.Clear();
                lock (_touchLock)
                {
                    _queueCatchTouchData.Clear();
                }

                string exportPath = "";
                //string exportPath = string.Empty;
                frames = 0;

                try
                {
                    using (SaveFileDialog saveFileDialog = new SaveFileDialog())
                    {
                        saveFileDialog.Filter = "Text Files (*.txt;)|*.txt";//|Hex Files(*.bin;)|*.bin
                        if (DialogResult.OK == saveFileDialog.ShowDialog())
                        {
                            exportPath = saveFileDialog.FileName;
                            if (!exportPath.EndsWith(".txt", StringComparison.OrdinalIgnoreCase))
                            {
                                exportPath += ".txt";
                            }
                            //exportPath.EndsWith(".txt");
                        }
                        else
                        {
                            // Client cancle--return
                            return;
                        }
                    }
                }
                catch (Exception ex)
                {
                    ex.ToString();
                    return;
                }

                RuningKernel.Instance().Work.AddWorkTemporary(() =>
                {
                    if (CatchChecked && LocalSingleData != null && CatchDatastatus == true)
                    {
                        //TouchReportData dataCopy = CloneTouchData(LocalSingleData);
                        EnqueueTouchData(LocalSingleData);
                        CatchDatastatus = false;
                    }

                }, new WorkComplete(() =>
                {
                    return CatchChecked ? false : true;
                    //return !CatchChecked;
                }));

                Task task = new Task(() =>
                {
                    //StreamWriter sw = new StreamWriter(exportPath, true, Encoding.Default);
                    using (StreamWriter sw = new StreamWriter(exportPath, true, Encoding.Default))
                    {
                        while (CatchChecked || GetTouchDataCount() > 0)
                        {
                             if (GetTouchDataCount() != 0)
                            {
                                 TouchReportData data = TryDequeueTouchData();
                                 if (data != null)
                                 {
                                     str = TouchPacketToString(data);
                                     sw.WriteLine(str);
                                     sw.Flush();
                                     frames++;
                                 }

                            }
                            //else
                            //{
                            //    Thread.Sleep(10);
                            //}
                        }
                        sw.Close();
                     }
                });
                task.Start();
            }
            else if ("touch-stopcatch-unchecked" == strParam)
            {
                //try
                //{
                //    SaveFileDialog saveFileDialog = new SaveFileDialog();
                //    saveFileDialog.Filter = "Text Files (*.txt;)|*.txt|Hex Files(*.bin;)|*.bin";
                //    if (DialogResult.OK == saveFileDialog.ShowDialog())
                //    {
                //        string exportPath = saveFileDialog.FileName;

                //        if (exportPath.EndsWith(".txt"))
                //        {
                //            saveTextData(exportPath);
                //        }
                //        else 
                //        {
                //            saveHexData(exportPath);
                //        }
                //    }
                //}
                //catch (Exception ex)
                //{
                //    ex.ToString();
                //}
            }
        }
        #region 
        private void EnqueueTouchData(TouchReportData data)
        {
            lock (_touchLock)
            {
                _queueCatchTouchData.Enqueue(data);
            }
        }

        private int GetTouchDataCount()
        {
            lock (_touchLock)
            {
                return _queueCatchTouchData.Count;
            }
        }

        private TouchReportData TryDequeueTouchData()
        {
            lock (_touchLock)
            {
                return _queueCatchTouchData.Count > 0 ? _queueCatchTouchData.Dequeue() : null;
            }
        }
        #endregion
    }
}
