using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using System.Windows.Input;
using SEMIDevelopKit.Src.Util;
//using sz_value_pair = System.Collections.Generic.KeyValuePair<int, int>;
using SelCoordinate = System.Tuple<int, int>;
using System.Windows;
//using System.Windows.Forms;
using sz_value_pair = SEMI.Util.TripleStore;

namespace SEMIDevelopKit.Src.WinSub
{
    public class StcIdentity : Identity
    {
        public string fileName{get; set;}
    }
    public class ModelStatistic : CtrlEventDispacher
    {
        protected Statistic statistic = new Statistic();
        private IDictionary<string, DataMatrix> dcMatrix = new Dictionary<string, DataMatrix>();

        public ModelStatistic()
        {
        }

        public WpfLineChart LineChart { get; set; }

        private TripleStore scanPoint = new TripleStore();
        public TripleStore ScanPoint
        {
            get { return scanPoint; }
            set { if (value != scanPoint) { scanPoint = value; OnPropertyChanged("ScanPoint"); } }
        }

        private Queue<List<sz_value_pair>> queueAnalyzed = new Queue<List<sz_value_pair>>();
        public Queue<List<sz_value_pair>> QueueAnalyzed
        {
            get { return queueAnalyzed; }
            set { if (null != queueAnalyzed) { queueAnalyzed = value; OnPropertyChanged("QueueAnalyzed"); } }
        }

        private List<sz_value_pair> sourceAnalyzed = new List<sz_value_pair>();
        public List<sz_value_pair> SourceAnalyzed
        {
            get { return sourceAnalyzed; }
            set { if (null != sourceAnalyzed) { sourceAnalyzed = value; OnPropertyChanged("SourceAnalyzed"); } }
        }

        private Boolean cleanChart = false;
        public Boolean CleanChart
        {
            get { return cleanChart; }
            set { if (cleanChart != value) { cleanChart = value; OnPropertyChanged("CleanChart"); } }
        }

        private Boolean breakChart = false;
        public Boolean BreakChart
        {
            get { return breakChart; }
            set { if (value != breakChart) { breakChart = value; OnPropertyChanged("BreakChart"); } }
        }

        private Boolean speedUp = false;
        public Boolean SpeedUp
        {
            get { return speedUp; }
            set { if (value != speedUp) { speedUp = value; OnPropertyChanged("SpeedUp"); } }
        }

        private int xMin = 0;
        public int XMin
        {
            get { return xMin; }
            set { if (value != xMin) { xMin = value; OnPropertyChanged("XMin"); } }
        }

        private int xMax = 100;
        public int XMax
        {
            get { return xMax; }
            set { if (value != xMax) { xMax = value; OnPropertyChanged("XMax"); } }
        }

        private int yMin = 10000;
        public int YMin
        {
            get { return yMin; }
            set { if (value != yMin) { yMin = value; OnPropertyChanged("YMin"); } }
        }

        private int yMax = 12000;
        public int YMax
        {
            get { return yMax; }
            set { if (value != yMax) { yMax = value; OnPropertyChanged("YMax"); } }
        }

        private Identity curPointIdentity = null;
        public Identity CurPointIdentity
        {
            get { return curPointIdentity; }
            set
            {
                if (value != curPointIdentity)
                {
                    curPointIdentity = value;
                    OnPropertyChanged("CurPointIdentity");

                    SelFileName = ((StcIdentity)curPointIdentity).fileName;
                } 
            }
        }

        private string selFileName = "";
        public string SelFileName
        {
            get { return selFileName; }
            set { if (value != selFileName) { selFileName = value; OnPropertyChanged("SelFileName"); } }
        }

        private SelCoordinate selectedCoor = new SelCoordinate(0,0);
        public SelCoordinate SelectedCoor
        {
            get { return selectedCoor; }
            set
            {
                if (value != selectedCoor)
                {
                    selectedCoor = value;
                    OnPropertyChanged("SelectedCoor");

                    BreakChart = true;
                }
            }
        }

        private string selectPath = "";
        public string SelectPath
        {
            get { return selectPath; }
            set { if (value != selectPath) { selectPath = value; OnPropertyChanged("SelectPath"); } }
        }

        private ushort keyToStc = 0;
        public ushort KeyToStc
        {
            get { return keyToStc; }
            set { if (value != keyToStc) { keyToStc = value; OnPropertyChanged("KeyToStc"); OnAnalyzeByName(); } }
        }

        protected List<SMDefinition> listKeys = null;
 
        public List<SMDefinition> ListKeys
        {
            get { return listKeys; }
            set { if (value != listKeys) { listKeys = value; OnPropertyChanged("ListKeys"); } }
        }

        int GetRows() { return 5; }
        int GetCols() { return 10; }

        public void OnAnalyzeByName()
        {
            int rows = GetRows();
            int cols = GetCols();
            int minY = 100000, maxY = 0, maxX = 0; ;
            List<FileParse> lsFiles = new List<FileParse>();
            string strKey = ListKeys.FirstOrDefault(t => { return t.TypeVal == KeyToStc ? true : false; }).TypeName;
            List<int[,]> listSample = statistic.GetListOfData(strKey, rows, cols, null, lsFiles);

            CleanChart = true;
            

            MainViewModel.Intr.ProcessValue = 0;
            MainViewModel.Intr.ProcessMax = (uint)listSample.Count();

            Queue<List<sz_value_pair>> localCatch = new Queue<List<sz_value_pair>>();
            RuningKernel.Instance().Work.AddWorkTemporary(() =>
            {
                for(int index = 0; index < listSample.Count(); index++)
                {
                    List<sz_value_pair> lsItems = new List<sz_value_pair>();
                    
                    for (int iRow = 0; iRow < rows; iRow++)
                    {
                        for (int iCol = 0; iCol < cols; iCol++)
                        {
                            if (0 == listSample[index][iRow, iCol]) continue;

                            maxX = Math.Max(maxX, iRow * cols + iCol);
                            StcIdentity user = new StcIdentity()
                            {
                                id = iRow * cols + iCol,
                                fileName = lsFiles[index].szFileName,
                            };
                            TripleStore pt = new TripleStore()
                            {
                                identify = user,
                                X = iRow * cols + iCol,
                                Y = listSample[index][iRow, iCol],
                            };
                            lsItems.Add(pt);

                            minY = Math.Min(minY, pt.Y);
                            maxY = Math.Max(maxY, pt.Y);
                        }
                    }

                    localCatch.Enqueue(lsItems);
                    MainViewModel.Intr.ProcessValue++;
                }

                XMin = 0;
                XMax = maxX;
                YMin = minY - 20;
                YMax = maxY + 20;
            });

            RuningKernel.Instance().Work.AddWorkTemporary(() =>
            {
                SpeedUp = true;
                MainViewModel.Intr.ProcessValue = 0;
                MainViewModel.Intr.ProcessMax = (uint)listSample.Count();
                foreach (var item in localCatch)
                {
                    LineChart.Sync = true;
                    SourceAnalyzed = item;
                    MainViewModel.Intr.ProcessValue++;
                    while (LineChart.Sync)
                    {
                        System.Threading.Thread.Sleep(5);
                    }
                }
                SpeedUp = false;
            });

        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            try
            {
                if ("sample-load-checked" == strParam)
                {
                    var dialog = new System.Windows.Forms.FolderBrowserDialog();
                    if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        SelectPath = dialog.SelectedPath;
                        statistic.PrepareStatistic(SelectPath, false);
                    }
                }
            }
            catch(Exception ex)
            {
                System.Windows.MessageBox.Show("Excution Failed!\r\n" + ex.ToString());
            }
        }

        public void SaveScan()
        {
            string strScan = "";
            System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
            saveFileDlg.OverwritePrompt = true;
            saveFileDlg.Filter = "log files (*.log)|*.log";
            if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
            {
                string strFileName = saveFileDlg.FileName;
                System.IO.Stream stream = saveFileDlg.OpenFile();
                System.IO.StreamWriter sw = new System.IO.StreamWriter(stream, Encoding.ASCII);

//                 foreach (var item in lsScanData)
//                 {
//                     strScan += string.Format("scan frequency 0x{0:X4}\r\n", item.ScanFreq);
//                     for (int iRow = 0; iRow < ModelBase.Rows + 1; iRow++)
//                     {
//                         for (int iCol = 0; iCol < ModelBase.Cols; iCol++)
//                         {
//                             strScan += string.Format("{0,-5:D}", item.ScanMatrix[iRow, iCol]);
//                         }
//                         strScan += "\r\n";
//                     }
//                     strScan += "\r\n";
//                 }

                sw.Write(strScan);
                sw.Flush();
                sw.Close();
                stream.Close();
            }
        }
    }
}
