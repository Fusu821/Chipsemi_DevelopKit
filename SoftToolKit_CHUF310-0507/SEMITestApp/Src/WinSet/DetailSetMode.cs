using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMITestApp.Src.Util;
using System.Windows.Data;
using System.Xml;
using System.Windows;
using SEMI.Util;
using SMInvokeBridge;
using System.IO;
using System.Windows.Controls;
using System.Data;

namespace SEMITestApp.Src.WinSet
{
    public partial class SMTestChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexDetailSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3535, "SEMITestApp.Src.WinSet.DetailSetModeScap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3536, "SEMITestApp.Src.WinSet.DetailSetModeScap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5472, "SEMITestApp.Src.WinSet.DetailSetModeMcap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5562, "SEMITestApp.Src.WinSet.DetailSetModeMcap550", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5816, "SEMITestApp.Src.WinSet.DetailSetModeMcap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7449, "SEMITestApp.Src.WinSet.DetailSetModeMcap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_8006, "SEMITestApp.Src.WinSet.DetailSetModeMcap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_810, "SEMITestApp.Src.WinSet.DetailSetModeMcap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7126, "SEMITestApp.Src.WinSet.DetailSetModeMcap550", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_570, "SEMITestApp.Src.WinSet.DetailSetModeMcap550", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_310, "SEMITestApp.Src.WinSet.DetailSetModeMcap", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE);
        }
    }
    public class DetailSetMode : SettingMode
    {
        public class ItemRule
        {
            public string keyWord { get; private set; }
            public int RuleFactor { get; private set; }
            public int xMin { get; private set; }
            public int xMax { get; private set; }
            public int ThreadCoeficient { get; set; }
            public ItemRule(string key, int min = -100, int max = 100, int rule = -1)
            {
                keyWord = key;
                RuleFactor = rule;
                xMin = min;
                xMax = max;
            }
        }
        protected Statistic statistic = new Statistic();
        public System.Windows.Controls.Primitives.UniformGrid HistGrid { set; private get; }
        public Statistic StatisticInfo { get { return statistic; } }

        public IDictionary<string, ItemRule> MapItemToKeyWords = null;
        //         public IDictionary<string, ItemRule> MapItemToKeyWords = new Dictionary<string, ItemRule>()
        //         {
        //             {"os_base", new ItemRule("OS - M1:")},
        //             {"fsd_base", new ItemRule("FSD Data:") },
        //             {"fsd_fast", new ItemRule("Fast CLK RawData:") },
        //             {"fsd_slow", new ItemRule("Slow CLK RawData:") },
        //             {"fsd_delta_max", new ItemRule("FSD Delta:", 0, 80, 1) },
        //             {"fsd_uniformity_left", new ItemRule("FSD Delta Uniformity Left:", -65, 65, -1) },
        //             {"fsd_uniformity_right", new ItemRule("FSD Delta Uniformity Right:", -65, 65, -1) },
        //             {"fsd_deviation", new ItemRule("FSD Deviation:", -600, 200, -3) },
        //         };

        private WpfTabItem curSelItem = null;
        public WpfTabItem CurSelItem
        {
            get { return curSelItem; }
            set
            {
                curSelItem = value;
                if (curSelItem == null) return;

                if (null != curSelItem.Tag && (bool)curSelItem.Tag) 
                {
                    HistGrid.Visibility = Visibility.Visible;
                    string title = CurSelItem.Header as string;
                    if (title.IndexOf('\t') > 0) title = title.Remove(title.IndexOf('\t'));
                    System.Threading.Thread t = new System.Threading.Thread(() =>
                    {
                        ShowHistGraph(title);
                    }) { IsBackground = true };

                    t.Start();
                }
                else
                {
                    HistGrid.Visibility = Visibility.Hidden;
                }
            }
        }

//         private IList<DataGridCellInfo> SelCellInfoList()
//         {
//             var dataGrid = CurSelItem.Content as System.Windows.Controls.DataGrid;
//             return dataGrid.SelectedCells;
//         }
        

        private IDictionary<string, DataMatrix> dcMatrix = new Dictionary<string, DataMatrix>();
        public IDictionary<string, DataMatrix> DcMatrix
        {
            get { return dcMatrix; }
        }

        private string selectedFolder = "";
        public string SelectedFolder
        {
            get { return selectedFolder; }
            set { if (value != selectedFolder) { selectedFolder = value; OnPropertyChanged("SelectedFolder"); } }
        }

        private int analyzeRatio = 10;
        public int AnalyzeRatio
        {
            get { return analyzeRatio; }
            set { if (value != analyzeRatio) { analyzeRatio = value; OnPropertyChanged("AnalyzeRatio"); } }
        }
        private int setValue = 0;
        public int SetValue
        {
            get { return setValue; }
            set { if (value != setValue) { setValue = value; OnPropertyChanged("SetValue"); } }
        }

        private int thresholdCof = 12;
        public int ThresholdCof
        {
            get { return thresholdCof; }
            set { if (value != thresholdCof) { thresholdCof = value; OnPropertyChanged("ThresholdCof"); } }
        }

        private Boolean refreshBase = true;
        public Boolean RefreshBase
        {
            get { return refreshBase; }
            set { if (value != refreshBase) { refreshBase = value; OnPropertyChanged("RefreshBase"); } }
        }

        private Boolean genThreshold = false;
        public Boolean GenThreshold
        {
            get { return genThreshold; }
            set { if (value != genThreshold) { genThreshold = value; OnPropertyChanged("GenThreshold"); } }
        }

        private Boolean simulate = false;
        public Boolean Simulate
        {
            get { return simulate; }
            set { if (value != simulate) { simulate = value; OnPropertyChanged("Simulate"); } }
        }

        private int analyzeProcessVal = 0;
        public int AnalyzeProcessVal
        {
            get { return analyzeProcessVal; }
            set { if (value != analyzeProcessVal) { analyzeProcessVal = value; OnPropertyChanged("AnalyzeProcessVal"); } }
        }

        private string analyzeResultText = "";
        public string AnalyzeResultText
        {
            get { return analyzeResultText; }
            set { if (value != analyzeResultText) { analyzeResultText = value; OnPropertyChanged("AnalyzeResultText"); } }
        }

        public virtual Boolean ExcludeTBD()
        {
            return false;
        }

        public string GetThreadCoeficientText(string keyword)
        {
            string szCoeficient = "";
            if (MapItemToKeyWords.Keys.Contains(keyword))
            {
                szCoeficient = string.Format("\t({0:D}%)", MapItemToKeyWords[keyword].ThreadCoeficient);
            }
            return szCoeficient;
        }

        private void ShowHistGraph(string header)
        {
            int rows = SettingMode.GetRows(), cols = SettingMode.GetCols();

            for (int iRow = 0; iRow < rows; iRow++)
            {
                for (int iCol = 0; iCol < cols; iCol++)
                {
                    DetailSetMode.ItemRule rules = MapItemToKeyWords[header];
                    var itemSource = StatisticInfo.GetStatisticResult(rules.keyWord, rows, cols, iRow, iCol, rules.xMin, rules.xMax);
                    if (0 == itemSource.Count()) continue;

                    HistGrid.Dispatcher.Invoke(new Action(() =>
                    {
                        //var HistGrid = FindName("uiniGridHist") as System.Windows.Controls.Primitives.UniformGrid;
                        WpfHistogram hist = HistGrid.Children[iRow * HistGrid.Columns + iCol] as WpfHistogram;

                        DataMatrix matrix = DcMatrix[header];

                        Binding newBind = new Binding() { Source = matrix[iRow], Path = new System.Windows.PropertyPath("Col" + (iCol + 1).ToString("00")), Mode = BindingMode.TwoWay };
                        hist.SetBinding(WpfHistogram.XRightProperty, newBind);
                        hist.RuleFactor = rules.RuleFactor;

                        hist.ItemsSource = itemSource;
                    }));
                }
            }
        }

        protected void AnalyzeByName(string keyName, IList<FileParse> lsContentCopy, Func<IList<FileParse>, string, int, int, int> function)
        {
            if (!dcMatrix.ContainsKey(keyName)) return;
            if (lsContentCopy.Count() == 0) return;
            if (!DetailSet.DetailHandle().CheckItemChecked(keyName)) return;

            DataMatrix matrix = dcMatrix[keyName];
            string keyWords = MapItemToKeyWords[keyName].keyWord;
            MapItemToKeyWords[keyName].ThreadCoeficient = ThresholdCof;

            statistic.GetListOfData(keyWords, matrix.RowNumber, matrix.ColNumber);

            Func<int, int> funGetCols = new Func<int, int>((row) =>
            {
                if (matrix.RowExp > 0)
                    return (row == matrix.RowNumber - 1) ? Math.Min(matrix.RowExp, matrix.ColNumber) : matrix.ColNumber;
                else
                    return matrix.ColNumber;
            });

            for (int iRow = 0; iRow < matrix.RowNumber; iRow++)
                for (int iCol = 0; iCol < funGetCols(iRow); iCol++)
                    matrix[iRow][iCol] = function(lsContentCopy, keyWords, iRow, iCol);

            //matrix[iRow][iCol] = lsContentCopy.Sum(o => o.ContentMap[keyWords][iRow, iCol]) / lsContentCopy.Count();
        }

        protected virtual void SimulateTest(IList<FileParse> parser)
        {
            CLRLinkParam linkParam = new CLRLinkParam();
            linkParam.LinkType = CLRLinkParam.CLRLINK_TYPE_FAKE;
            bool bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);

            int index = 0, fileSize = (int)parser.Count;

            //CMD_OPEN_TST        = 0x20,
            //CMD_FSD_TST         = 0x24,
            foreach (var item in parser)
            {
                Dictionary<int, int[,]> dcFackData = new Dictionary<int, int[,]>();

                if (item.ContentMap.ContainsKey("OS - M1:"))
                    dcFackData[(0 << 8) + 0x20] = item.ContentMap["OS - M1:"];
                if (item.ContentMap.ContainsKey("Fast CLK RawData:"))
                    dcFackData[(0 << 8) + 0x24] = item.ContentMap["Fast CLK RawData:"];
                if (item.ContentMap.ContainsKey("Slow CLK RawData:"))
                    dcFackData[(1 << 8) + 0x24] = item.ContentMap["Slow CLK RawData:"];

                SEMITestApp.MainWindow.SMComplexed.SimulateTest(0, dcFackData);

                AnalyzeProcessVal = (++index) * 100 / fileSize;
            }

            linkParam.LinkType = CLRLinkParam.CLRLINK_TYPE_USB;
            bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);
        }

        protected void MakeDirectoryClean(string srcPath)
        {
            try
            {
                DirectoryInfo dirInfo = new DirectoryInfo(srcPath);
                if (!dirInfo.Exists) return;

                //DirectoryInfo d1 = new DirectoryInfo(d);
                foreach (var item in dirInfo.GetFiles())
                {
                    File.Delete(item.FullName);
                }
                foreach (var item in dirInfo.GetDirectories())
                {
                    MakeDirectoryClean(item.FullName);
                }

                Directory.Delete(srcPath);
            }
            catch (Exception ex)
            {
                ex.ToString();
            }
        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if ("detail-import-click" == strParam)
            {
                //var dialog = new CommonOpenFileDialog();
                //dialog.IsFolderPicker = true;
                //CommonFileDialogResult result = dialog.ShowDialog();
                //if (result == CommonFileDialogResult.Ok)
                string DirectoryPath = GetWorkPath();
                if (FolderBrowserDialog.Active(ref DirectoryPath) == System.Windows.Forms.DialogResult.OK)
                {
                    SelectedFolder = DirectoryPath;

                    try
                    {
                        statistic.PrepareStatistic(SelectedFolder, ExcludeTBD());

                        OnInportClick();
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Load Sample Failed!\r\n" + ex.ToString());
                    }

                }
            }
            else if ("detail-add-click" == strParam)
            {
                if (null != CurSelItem && !string.IsNullOrEmpty(CurSelItem.Header as string))
                {
                    string title = CurSelItem.Header as string;
                    if (title.IndexOf('\t') > 0) title = title.Remove(title.IndexOf('\t'));
                    DataMatrix matrix = dcMatrix[title];
                    var dataGrid = CurSelItem.Content as System.Windows.Controls.DataGrid;
                    var listInfo = dataGrid.SelectedCells;
                    if (0 == listInfo.Count)
                    {
                        for (int iRow = 0; iRow < matrix.RowNumber; iRow++)
                            for (int iCol = 0; iCol < matrix.ColNumber; iCol++)
                                if ("/" != (matrix[iRow][iCol] as string)) matrix[iRow][iCol] = (int)matrix[iRow][iCol] + 1;
                    }
                    else 
                    {
                        
                        foreach (var cell in listInfo)
                        {
                            DataRowView item = cell.Item as DataRowView;
                            int iRow = dataGrid.Items.IndexOf(cell.Item);
                            int iCol = cell.Column.DisplayIndex;
                            if ("/" != (matrix[iRow][iCol] as string)) matrix[iRow][iCol] = (int)matrix[iRow][iCol] + 1;
                        }
                    }
                }
            }
            else if ("detail-dec-click" == strParam)
            {
                string title = CurSelItem.Header as string;
                if (title.IndexOf('\t') > 0) title = title.Remove(title.IndexOf('\t'));
                DataMatrix matrix = dcMatrix[title];
                var dataGrid = CurSelItem.Content as System.Windows.Controls.DataGrid;
                var listInfo = dataGrid.SelectedCells;
                if (0 == listInfo.Count)
                {
                    for (int iRow = 0; iRow < matrix.RowNumber; iRow++)
                        for (int iCol = 0; iCol < matrix.ColNumber; iCol++)
                            if ("/" != (matrix[iRow][iCol] as string)) matrix[iRow][iCol] = (int)matrix[iRow][iCol] - 1;
                }
                else
                {
                    foreach (var cell in listInfo)
                    {
                        DataRowView item = cell.Item as DataRowView;
                        int iRow = dataGrid.Items.IndexOf(cell.Item);
                        int iCol = cell.Column.DisplayIndex;
                        if ("/" != (matrix[iRow][iCol] as string)) matrix[iRow][iCol] = (int)matrix[iRow][iCol] - 1;
                    }
                }
            }
            else if ("detail-set-click" == strParam)
            {
                string title = CurSelItem.Header as string;
                if (title.IndexOf('\t') > 0) title = title.Remove(title.IndexOf('\t'));
                if ("uniformity_invalid" == title || "noise_scap_base" == title || "noise_mcap_base" == title || "fsd_diff_max" == title || "mcap_uniformity_h" == title || "mcap_uniformity_v" == title)
                {
                    DataMatrix matrix = dcMatrix[title];
                    var dataGrid = CurSelItem.Content as System.Windows.Controls.DataGrid;
                    var listInfo = dataGrid.SelectedCells;
                    if (0 == listInfo.Count)
                    {
                        //for (int iRow = 0; iRow < matrix.RowNumber; iRow++)
                        //    for (int iCol = 0; iCol < matrix.ColNumber; iCol++)
                        //        if ("/" != (matrix[iRow][iCol] as string)) matrix[iRow][iCol] = SetValue;
                    }
                    else
                    {
                        foreach (var cell in listInfo)
                        {
                            DataRowView item = cell.Item as DataRowView;
                            int iRow = dataGrid.Items.IndexOf(cell.Item);
                            int iCol = cell.Column.DisplayIndex;
                            if (("/" != (matrix[iRow][iCol] as string)) && (null != (matrix[iRow][iCol])))
                            {
                                matrix[iRow][iCol] = SetValue;
                            }
                               
                        }
                    }
                }

            }
        }

        protected void SaveDetailData(XmlNode node, string subNode, DataMatrix matrix/*, bool keyInclude = false*/)
        {
            if (null == node) return;
            if (null == matrix) return;
            //XmlNode child = node.SelectSingleNode(subNode);

            //int Rows = 0 == matrix.Keys ? matrix.RowNumber : matrix.RowNumber - 1;
            for (int iRow = 0; iRow < matrix.RowNumber; iRow++)
            {
                string subName = string.Format("{0}_{1}", subNode, iRow);
                XmlNode child = node.SelectSingleNode(subName);
                if (null == child)
                {
                    child = xml.CreateElement(subName);
                    node.AppendChild(child);
                }

                MatrixRow mxRow = matrix[iRow];
                string oneRow = "";
                for (int iCol = 0; iCol < matrix.ColNumber; iCol++)
                {
                    oneRow += string.Format("{0} ", matrix[iRow][iCol]);
                }

                child.InnerXml = oneRow;
            }

            if (MapItemToKeyWords.Keys.Contains(subNode))
            {
                SaveXmlAttrbuteValue(node.ParentNode, node.Name, subNode + "_coef", MapItemToKeyWords[subNode].ThreadCoeficient);
            }
        }
        protected DataMatrix GetDetailData(XmlNode node, string subNode, int dafault = 0, bool keyInclude = false)
        {
            int refs = keyInclude ? GetRefs() : 0;
            DataMatrix mx = new DataMatrix(GetRows(), GetCols(), refs);

            for (int iRow = 0; iRow < mx.RowNumber; iRow++)
            {
                for (int iCol = 0; iCol < mx.ColNumber; iCol++)
                {
                    mx[iRow][iCol] = dafault;
                }
            }
            if (refs > 0)
            {
                for (int iCol = mx.RowExp; iCol < mx.ColNumber; iCol++)
                {
                    mx[mx.RowNumber - 1][iCol] = 0;
                }
            }

            if (null == node) return mx;

            for (int iRow = 0; iRow < mx.RowNumber; iRow++)
            {
                string szNode = string.Format("{0}_{1}", subNode, iRow);
                XmlNode child = node.SelectSingleNode(szNode);
                if (null != child)
                {
                    string szValue = child.InnerXml;
                    szValue.Replace("\t", " ");
                    string[] szArray = szValue.Split(' ');
                    szArray = szArray.Where((t) => !string.IsNullOrEmpty(t)).ToArray();

                    for (int iCol = 0; (iCol < (int)szArray.Length) && (iCol < GetCols()); iCol++)
                    {
                        if ("/" == szArray[iCol].Trim())
                            mx[iRow][iCol] = "/";
                        else
                            mx[iRow][iCol] = int.Parse(szArray[iCol].Trim());
                    }
                }
            }

            if (MapItemToKeyWords.Keys.Contains(subNode))
            {
                int coeficient = GetXmlAttrbuteValue(node.ParentNode, node.Name, subNode + "_coef", 0);
                MapItemToKeyWords[subNode].ThreadCoeficient = coeficient;
            }

            return mx;
        }
        private void PrepatchMatrix(DataMatrix mx, int[] cols, int val)
        {
            for (int iRow = 0; iRow < mx.RowNumber; iRow++)
            {
                foreach (var col in cols)
                {
                    string szNode = mx[iRow][col] as string;
                    if (null == szNode)
                    {
                        mx[iRow][col] = (int)mx[iRow][col] + val;
                    }
                }
            }
        }
        protected void InvalidMatrix(DataMatrix mx, int row = 0xff, int col = 0xff)
        {
            if (row < mx.RowNumber)
            {
                for (int iCol = 0; iCol < mx.ColNumber; iCol++)
                {
                    mx[row][iCol] = "/";
                }
            }
            if (col < mx.ColNumber)
            {
                for (int iRow = 0; iRow < mx.RowNumber; iRow++)
                {
                    mx[iRow][col] = "/";
                }
            }
        }
        protected DataMatrix GetMScapDetailData(XmlNode node, string subNode, int dafault = 0, bool keyInclude = false)
        {
            int refs = keyInclude ? GetRefs() : 0;
            DataMatrix mx = new DataMatrix(2, Math.Max(GetRows(), GetCols()));

            for (int iCol = 0; iCol < GetCols(); iCol++)
            {
                mx[0][iCol] = dafault;
            }
            for (int iCol = 0; iCol < GetRows(); iCol++)
            {
                mx[1][iCol] = dafault;
            }

            if (null == node) return mx;

            for (int iRow = 0; iRow < mx.RowNumber; iRow++)
            {
                string szNode = string.Format("{0}_{1}", subNode, iRow);
                XmlNode child = node.SelectSingleNode(szNode);
                if (null != child)
                {
                    string szValue = child.InnerXml;
                    szValue.Replace("\t", " ");
                    string[] szArray = szValue.Split(' ');
                    szArray = szArray.Where((t) => !string.IsNullOrEmpty(t)).ToArray();

                    for (int iCol = 0; (iCol < (int)szArray.Length) && (iCol < mx.ColNumber); iCol++)
                    {
                        if ("/" == szArray[iCol].Trim())
                            mx[iRow][iCol] = "/";
                        else
                            mx[iRow][iCol] = int.Parse(szArray[iCol].Trim());
                    }
                }
            }

            if (MapItemToKeyWords.Keys.Contains(subNode))
            {
                int coeficient = GetXmlAttrbuteValue(node.ParentNode, node.Name, subNode + "_coef", 0);
                MapItemToKeyWords[subNode].ThreadCoeficient = coeficient;
            }

            return mx;
        }

        protected DataMatrix GetVtDetailData(XmlNode node, string subNode, int dafault = 0, bool keyInclude = false)
        {
            DataMatrix mx = new DataMatrix(1, GetRows());

            for (int iCol = 0; iCol < GetRows(); iCol++)
            {
                mx[0][iCol] = dafault;
            }
            if (null == node) return mx;

            for (int iRow = 0; iRow < mx.RowNumber; iRow++)
            {
                string szNode = string.Format("{0}_{1}", subNode, iRow);
                XmlNode child = node.SelectSingleNode(szNode);
                if (null != child)
                {
                    string szValue = child.InnerXml;
                    szValue.Replace("\t", " ");
                    string[] szArray = szValue.Split(' ');
                    szArray = szArray.Where((t) => !string.IsNullOrEmpty(t)).ToArray();

                    for (int iCol = 0; (iCol < (int)szArray.Length) && (iCol < mx.ColNumber); iCol++)
                    {
                        if ("/" == szArray[iCol].Trim())
                            mx[iRow][iCol] = "/";
                        else
                            mx[iRow][iCol] = int.Parse(szArray[iCol].Trim());
                    }
                }
            }

            if (MapItemToKeyWords.Keys.Contains(subNode))
            {
                int coeficient = GetXmlAttrbuteValue(node.ParentNode, node.Name, subNode + "_coef", 0);
                MapItemToKeyWords[subNode].ThreadCoeficient = coeficient;
            }

            return mx;
        }

        public virtual void OnInportClick()
        {
        }
    }

    public class DetailSetModeMcap : DetailSetMode
    {
        public DetailSetModeMcap()
        {
            MapItemToKeyWords = new Dictionary<string, ItemRule>()
            {
                {"stc_mean", new ItemRule("stc_rawdata", 2000, 14000, -1)},
                {"stc_mse", new ItemRule("stc_rawdata")},

                {"mcap_rawdata_min", new ItemRule("mcap_rawdata")},
                {"mcap_rawdata_max", new ItemRule("mcap_rawdata")},
                {"scap_rawdata_min", new ItemRule("Scap Data")},
                {"scap_rawdata_max", new ItemRule("Scap Data")},

            };
        }

        public override Boolean ExcludeTBD()
        {
            return false;
        }

        public override void XMLDataToView()
        {
            DcMatrix.Clear();

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            XmlNode invalidNode = stNode.SelectSingleNode("invalidnode");
            DcMatrix["invalid"] = GetDetailData(invalidNode, "invalid", 1, true);

            XmlNode buttonTest = stNode.SelectSingleNode("button_test");
            var KeyChannelDefault = GetXmlAttrbuteValue(stNode, "button_test", "key_channel_invalid", 0) > 0;
            //2024.05.23-hjx 20240604
            if (KeyChannelDefault == true)
            {
                int rows = DcMatrix["invalid"].RowNumber;
                for (int index = 0; (index < DcMatrix["invalid"].ColNumber) && (keyNum > 0); index++)
                {
                    int pos = listKeyChannels.FindIndex((o) =>
                    {
                        return o == index ? true : false;
                    });
                    DcMatrix["invalid"][rows - 1][index] = pos >= 0 ? 1 : 0;
                }
            }

                   
            XmlNode osTest = stNode.SelectSingleNode("os_test");
            if (1 == GetXmlAttrbuteValue(stNode, "os_test", "selected"))
            {
                DcMatrix["os_base"] = GetDetailData(osTest, "os_base", 2000, true);
            }


            XmlNode stcTest = stNode.SelectSingleNode("stc_test");
            if (1 == GetXmlAttrbuteValue(stNode, "stc_test", "selected"))
            {
                DcMatrix["stc_mean"] = GetDetailData(stcTest, "stc_mean", 0);
                DcMatrix["stc_mse"] = GetDetailData(stcTest, "stc_mse", 10);
            }

            XmlNode mcapTest = stNode.SelectSingleNode("mcap_rawdata_test");
            if (1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "selected"))
            {
                //DcMatrix["mcap_rawdata"] = GetDetailData(mcapTest, "mcap_rawdata", 6000);

                int min = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_min");
                DcMatrix["mcap_rawdata_min"] = GetDetailData(mcapTest, "mcap_rawdata_min", min);
                int max = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_max");
                DcMatrix["mcap_rawdata_max"] = GetDetailData(mcapTest, "mcap_rawdata_max", max);
                int uniformityHor = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_hor_max");
                DcMatrix["mcap_uniformity_h"] = GetDetailData(mcapTest, "uniformity_hor_max", uniformityHor);
                int uniformityVer = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_ver_max");
                DcMatrix["mcap_uniformity_v"] = GetDetailData(mcapTest, "uniformity_ver_max", uniformityVer);

                InvalidMatrix(DcMatrix["mcap_uniformity_h"], 0, 0xff);
                InvalidMatrix(DcMatrix["mcap_uniformity_v"], 0xff, 0);
            }

            XmlNode scapRawDataTest = stNode.SelectSingleNode("scap_rawdata_test");
            if (1 == GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "selected"))
            {
                int min = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_min");
                DcMatrix["scap_rawdata_min"] = GetMScapDetailData(scapRawDataTest, "scap_rawdata_min", min);
                int max = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_max");
                DcMatrix["scap_rawdata_max"] = GetMScapDetailData(scapRawDataTest, "scap_rawdata_max", max);
            }

        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            XmlNode invalidNode = stNode.SelectSingleNode("invalidnode");
            if (null == invalidNode)
            {
                invalidNode = xml.CreateElement("invalidnode");
                stNode.AppendChild(invalidNode);
            }
            SaveDetailData(invalidNode, "invalid", DcMatrix["invalid"]);

            if (1 == GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "selected"))
            {
                XmlNode scapDataTest = stNode.SelectSingleNode("scap_rawdata_test");
                SaveDetailData(scapDataTest, "scap_rawdata_min", DcMatrix["scap_rawdata_min"]);
                SaveDetailData(scapDataTest, "scap_rawdata_max", DcMatrix["scap_rawdata_max"]);
            }
            if (1 == GetXmlAttrbuteValue(stNode, "stc_test", "selected"))
            {
                XmlNode stcTest = stNode.SelectSingleNode("stc_test");
                SaveDetailData(stcTest, "stc_mean", DcMatrix["stc_mean"]);
                SaveDetailData(stcTest, "stc_mse", DcMatrix["stc_mse"]);
            }
            if (1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "selected"))
            {
                XmlNode mcapRawDataTest = stNode.SelectSingleNode("mcap_rawdata_test");
                SaveDetailData(mcapRawDataTest, "mcap_rawdata_min", DcMatrix["mcap_rawdata_min"]);
                SaveDetailData(mcapRawDataTest, "mcap_rawdata_max", DcMatrix["mcap_rawdata_max"]);
                SaveDetailData(mcapRawDataTest, "uniformity_hor_max", DcMatrix["mcap_uniformity_h"]);
                SaveDetailData(mcapRawDataTest, "uniformity_ver_max", DcMatrix["mcap_uniformity_v"]);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }

        protected override void SimulateTest(IList<FileParse> parser)
        {
            if (null == parser) return;
            CLRLinkParam linkParam = new CLRLinkParam();
            linkParam.LinkType = CLRLinkParam.CLRLINK_TYPE_FAKE;
            bool bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);

            int index = 0, fileSize = (int)parser.Count;

            //CMD_OPEN_TST        = 0x20,
            //CMD_FSD_TST         = 0x24,
            foreach (var item in parser)
            {
                Dictionary<int, int[,]> dcFackData = new Dictionary<int, int[,]>();

                if (item.ContentMap.ContainsKey("Scap Data"))
                    dcFackData[(0xfa << 16) + 0x28] = item.ContentMap["Scap Data"];
                if (item.ContentMap.ContainsKey("stc_rawdata"))
                    dcFackData[(0xfb << 16) + 0x28] = item.ContentMap["stc_rawdata"];
                if (item.ContentMap.ContainsKey("mcap_rawdata"))
                    dcFackData[(0xfc << 16) + 0x28] = item.ContentMap["mcap_rawdata"];

                dcFackData[(0 << 16) + 0x01] = new int[1, 16] { {0x66, 0x43, 0x02, 0xE9, 0xFD, 0x16, 0x00, 0x00, 0x07, 0x00, 0x00, 0xB8, 0x94, 0x03, 0x00, 0x01} };

                dcFackData[(0 << 16) + 0x31] = new int[1, 0x34];
                dcFackData[(0 << 16) + 0x31][0,16] = 0xfa;
                dcFackData[(0x80 << 16) + 0x31] = new int[1, 0x100];

                SEMITestApp.MainWindow.SMComplexed.SimulateTest(0, dcFackData);

                AnalyzeProcessVal = (++index) * 100 / fileSize;
            }

            linkParam.LinkType = CLRLinkParam.CLRLINK_TYPE_USB;
            bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);
        }

        public override void OnInportClick()
        {
            IList<FileParse> finalParses = new List<FileParse>();
            AnalyzeResultText = string.Format("{0}: {1}     ", "Total", statistic.TotalCount()) + "Valid:  ";
            {
                IList<FileParse> stcParses = new List<FileParse>();
                string stcKeyWord = MapItemToKeyWords["stc_mean"].keyWord;
                statistic.TickOut(stcKeyWord, ref stcParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(stcParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "stc_mean", stcParses.Count());

                //if (RefreshBase)
                {
                    AnalyzeByName("stc_mean", stcParses, (t, k, i, j) => { return (int)t.Average(o => o.ContentMap[k][i, j]); });

                    AnalyzeByName("stc_mse", stcParses, (t, k, i, j) =>
                    {
                        double avg = t.Average(o => o.ContentMap[k][i, j]);
                        double var = t.Sum(o => (o.ContentMap[k][i, j] - avg) * (o.ContentMap[k][i, j] - avg)) / t.Count();
                        int mse = (int)(Math.Sqrt(var) * 10);
                        if (stcParses.Count < 50) mse = Math.Max(1500, mse);
                        return mse;
                    });
                }

                IList<FileParse> mcapParses = new List<FileParse>();
                string mcapKeyWord = MapItemToKeyWords["mcap_rawdata_min"].keyWord;
                statistic.TickOut(mcapKeyWord, ref mcapParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(mcapParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "mcap_rawdata", mcapParses.Count());

                //if (GenThreshold)
                {
                    AnalyzeByName("mcap_rawdata_min", mcapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg - avg * ThresholdCof / 100;
                    });
                    AnalyzeByName("mcap_rawdata_max", mcapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg + avg * ThresholdCof / 100;
                    });
                }

                IList<FileParse> scapParses = new List<FileParse>();
                string strKeyWord = MapItemToKeyWords["scap_rawdata_min"].keyWord;
                statistic.TickOutMScap(strKeyWord, ref scapParses, GetCols(), GetRows(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(scapParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "scap_data", scapParses.Count());

                //if (GenThreshold)
                {
                    AnalyzeByName("scap_rawdata_min", scapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg - avg * ThresholdCof / 100;
                    });
                    AnalyzeByName("scap_rawdata_max", scapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg + avg * ThresholdCof / 100;
                    });
                }

                if (Simulate)
                {
                    ViewToXMLData();

                    SEMITestApp.MainWindow.SMComplexed.OnlyReloadXmlConfig();

                    new System.Threading.Thread(() =>
                    {
                        string fakeDir = GetWorkPath() + "TestResult\\Fake";

                        MakeDirectoryClean(fakeDir);

                        SimulateTest(finalParses);

                    }).Start();
                }
            }
        }
    }

    public class DetailSetModeScap : DetailSetMode
    {
        public DetailSetModeScap()
        {
            MapItemToKeyWords = new Dictionary<string, ItemRule>()
            {
                {"rawdata_min", new ItemRule("ScapData:")},
                {"rawdata_max", new ItemRule("ScapData:")},
                {"os_base", new ItemRule("OS - M1:")},
                {"fsd_base", new ItemRule("FSD Data:") },
                {"fsd_fast", new ItemRule("Fast CLK RawData:") },
                {"fsd_slow", new ItemRule("Slow CLK RawData:") },
                {"fsd_delta_max", new ItemRule("FSD Delta:", 0, 80, 1) },
                {"fsd_uniformity_left", new ItemRule("FSD Delta Uniformity Left:", -65, 65, -1) },
                {"fsd_uniformity_right", new ItemRule("FSD Delta Uniformity Right:", -65, 65, -1) },
                {"fsd_deviation", new ItemRule("FSD Deviation:", -600, 200, -3) },
            };
        }

        public override Boolean ExcludeTBD()
        {
            return GenThreshold;
        }

        public override void XMLDataToView()
        {
            DcMatrix.Clear();

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            XmlNode invalidNode = stNode.SelectSingleNode("invalidnode");
            DcMatrix["invalid"] = GetDetailData(invalidNode, "invalid", 1, true);

            XmlNode buttonTest = stNode.SelectSingleNode("button_test");
            var KeyChannelDefault = GetXmlAttrbuteValue(stNode, "button_test", "key_channel_invalid", 0) > 0;
            if (KeyChannelDefault == true)
            {
                int refs =  GetRefs();
                if (refs > 0)
                {
                    for (int iCol = 0; iCol < DcMatrix["invalid"].ColNumber; iCol++)
                    {
                        DcMatrix["invalid"][DcMatrix["invalid"].RowNumber - 1][iCol] = DcMatrix["invalid"].RowExp > iCol ? 1 : 0;
                    }
                }
            }

            XmlNode rawdataTest = stNode.SelectSingleNode("rawdata_test");
            if (1 == GetXmlAttrbuteValue(stNode, "rawdata_test", "selected"))
            {
                int min = GetXmlAttrbuteValue(stNode, "rawdata_test", "rawdata_min");
                DcMatrix["rawdata_min"] = GetDetailData(rawdataTest, "rawdata_min", min, true);
                int max = GetXmlAttrbuteValue(stNode, "rawdata_test", "rawdata_max");
                DcMatrix["rawdata_max"] = GetDetailData(rawdataTest, "rawdata_max", max, true);
                //int coeficient = GetXmlAttrbuteValue(stNode, "rawdata_test", "coeficient", 0);
                //MapItemToKeyWords["rawdata_min"].ThreadCoeficient = coeficient;
            }

            XmlNode osTest = stNode.SelectSingleNode("os_test");
            if (1 == GetXmlAttrbuteValue(stNode, "os_test", "selected"))
            {
                DcMatrix["os_base"] = GetDetailData(osTest, "os_base", 2000, true);
            }

            XmlNode fsdTest = stNode.SelectSingleNode("fsd_test");
            if (1 == GetXmlAttrbuteValue(stNode, "fsd_test", "selected"))
            {
                DcMatrix["fsd_base"] = GetDetailData(fsdTest, "fsd_base", 30);
                DcMatrix["fsd_fast"] = GetDetailData(fsdTest, "fsd_fast", 2426);
                DcMatrix["fsd_slow"] = GetDetailData(fsdTest, "fsd_slow", 2456);
                DcMatrix["fsd_delta_max"] = GetDetailData(fsdTest, "fsd_delta_max", 20);
                DcMatrix["fsd_uniformity_left"] = GetDetailData(fsdTest, "fsd_uniformity_left", 20);
                DcMatrix["fsd_uniformity_right"] = GetDetailData(fsdTest, "fsd_uniformity_right", 20);
                DcMatrix["fsd_deviation"] = GetDetailData(fsdTest, "fsd_deviation", 50);
            }

            XmlNode fsdbkTest = stNode.SelectSingleNode("fsdbk_test");
            if (1 == GetXmlAttrbuteValue(stNode, "fsdbk_test", "selected"))
            {
                DcMatrix["fsd_base"] = GetDetailData(fsdbkTest, "fsd_base", 30, true);
                DcMatrix["fsd_fast"] = GetDetailData(fsdbkTest, "fsd_fast", 2426, true);
                DcMatrix["fsd_slow"] = GetDetailData(fsdbkTest, "fsd_slow", 2456, true);
                DcMatrix["fsd_delta_max"] = GetDetailData(fsdbkTest, "fsd_delta_max", 20, true);
                DcMatrix["fsd_uniformity_left"] = GetDetailData(fsdbkTest, "fsd_uniformity_left", 20);
                DcMatrix["fsd_uniformity_right"] = GetDetailData(fsdbkTest, "fsd_uniformity_right", 20);
                DcMatrix["fsd_deviation"] = GetDetailData(fsdbkTest, "fsd_deviation", 50, true);
            }
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            XmlNode invalidNode = stNode.SelectSingleNode("invalidnode");
            if (null == invalidNode)
            {
                invalidNode = xml.CreateElement("invalidnode");
                stNode.AppendChild(invalidNode);
            }
            SaveDetailData(invalidNode, "invalid", DcMatrix["invalid"]);

            if (1 == GetXmlAttrbuteValue(stNode, "rawdata_test", "selected"))
            {
                XmlNode rawdataTest = stNode.SelectSingleNode("rawdata_test");
                SaveDetailData(rawdataTest, "rawdata_min", DcMatrix["rawdata_min"]);
                SaveDetailData(rawdataTest, "rawdata_max", DcMatrix["rawdata_max"]);
                //SaveXmlAttrbuteValue(stNode, "rawdata_test", "coeficient", MapItemToKeyWords["rawdata_min"].ThreadCoeficient);
            }

            if (1 == GetXmlAttrbuteValue(stNode, "os_test", "selected"))
            {
                XmlNode osTest = stNode.SelectSingleNode("os_test");
                SaveDetailData(osTest, "os_base", DcMatrix["os_base"]);
            }

            if (1 == GetXmlAttrbuteValue(stNode, "fsd_test", "selected"))
            {
                XmlNode fsdTest = stNode.SelectSingleNode("fsd_test");
                SaveDetailData(fsdTest, "fsd_base", DcMatrix["fsd_base"]);
                SaveDetailData(fsdTest, "fsd_fast", DcMatrix["fsd_fast"]);
                SaveDetailData(fsdTest, "fsd_slow", DcMatrix["fsd_slow"]);
                SaveDetailData(fsdTest, "fsd_delta_max", DcMatrix["fsd_delta_max"]);
                SaveDetailData(fsdTest, "fsd_uniformity_left", DcMatrix["fsd_uniformity_left"]);
                SaveDetailData(fsdTest, "fsd_uniformity_right", DcMatrix["fsd_uniformity_right"]);
                SaveDetailData(fsdTest, "fsd_deviation", DcMatrix["fsd_deviation"]);
            }

            if (1 == GetXmlAttrbuteValue(stNode, "fsdbk_test", "selected"))
            {
                XmlNode fsdbkTest = stNode.SelectSingleNode("fsdbk_test");
                SaveDetailData(fsdbkTest, "fsd_base", DcMatrix["fsd_base"]);
                SaveDetailData(fsdbkTest, "fsd_fast", DcMatrix["fsd_fast"]);
                SaveDetailData(fsdbkTest, "fsd_slow", DcMatrix["fsd_slow"]);
                SaveDetailData(fsdbkTest, "fsd_delta_max", DcMatrix["fsd_delta_max"]);
                SaveDetailData(fsdbkTest, "fsd_uniformity_left", DcMatrix["fsd_uniformity_left"]);
                SaveDetailData(fsdbkTest, "fsd_uniformity_right", DcMatrix["fsd_uniformity_right"]);
                SaveDetailData(fsdbkTest, "fsd_deviation", DcMatrix["fsd_deviation"]);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }

        public override void OnInportClick()
        {
            AnalyzeResultText = string.Format("{0}: {1}     ", "Total File Count", statistic.TotalCount()) + "Valid Sample File:  ";
            {
                IList<FileParse> osParses = new List<FileParse>();
                string strKeyWord = MapItemToKeyWords["os_base"].keyWord;
                statistic.TickOut(strKeyWord, ref osParses, GetRows(), GetCols(), AnalyzeRatio, 0);

                if (RefreshBase)
                {
                    AnalyzeByName("os_base", osParses, (t, k, i, j) => { return t.Sum(o => o.ContentMap[k][i, j]) / t.Count(); });
                }

                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "os_base", osParses.Count());
            }
            {
                int offset_t = 2048 - 1338;
                if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_3535 & 0xff00)) offset_t = 0;
                IList<FileParse> fastParses = null;
                IList<FileParse> slowParses = null;
                string fastKeyWord = MapItemToKeyWords["fsd_fast"].keyWord;
                statistic.TickOut(fastKeyWord, ref fastParses, GetRows(), GetCols(), AnalyzeRatio, offset_t);
                string slowKeyWord = MapItemToKeyWords["fsd_slow"].keyWord;
                statistic.TickOut(slowKeyWord, ref slowParses, GetRows(), GetCols(), AnalyzeRatio, offset_t);
                IList<FileParse> sectionParser = new List<FileParse>();
                if (null != fastParses) sectionParser = fastParses.Intersect(slowParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "fsd_base", sectionParser.Count());

                //if (RefreshBase)
                {
                    //AnalyzeByName("fsd_base", sectionParser, (t, k, i, j) =>
                    //{
                    //    return t.Sum(o => o.ContentMap[k][i, j]) / t.Count();
                    //});

                    AnalyzeByName("fsd_fast", sectionParser, (t, k, i, j) =>
                    {
                        return t.Sum(o => o.ContentMap[k][i, j]) / t.Count();
                    });

                    AnalyzeByName("fsd_slow", sectionParser, (t, k, i, j) =>
                    {
                        return t.Sum(o => o.ContentMap[k][i, j]) / t.Count();
                    });

                    if (DcMatrix.ContainsKey("fsd_base"))
                    {
                        DataMatrix matrix = DcMatrix["fsd_base"];
                        DataMatrix matrix_s = DcMatrix["fsd_slow"];
                        DataMatrix matrix_f = DcMatrix["fsd_fast"];

                        for (int iRow = 0; iRow < matrix.RowNumber; iRow++)
                            for (int iCol = 0; iCol < matrix.ColNumber; iCol++)
                                matrix[iRow][iCol] = (int)matrix_s[iRow][iCol] - (int)matrix_f[iRow][iCol];
                    }
                }

                IList<FileParse> scapParses = new List<FileParse>();
                string strKeyWord = MapItemToKeyWords["rawdata_min"].keyWord;
                statistic.TickOut(strKeyWord, ref scapParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                //if (Simulate) finalParses = finalParses.Union(scapParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "rawdata_data", scapParses.Count());

                //if (GenThreshold)
                {
                    AnalyzeByName("rawdata_min", scapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg - avg * ThresholdCof / 100;
                    });
                    AnalyzeByName("rawdata_max", scapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg + avg * ThresholdCof / 100;
                    });
                }

                //if (GenThreshold)
                {
                    AnalyzeByName("fsd_delta_max", sectionParser, (t, k, i, j) =>
                    {
                        return t.Max(o => Math.Abs(o.ContentMap[k][i, j]));
                    });

                    AnalyzeByName("fsd_uniformity_left", sectionParser, (t, k, i, j) =>
                    {
                        return t.Max(o => Math.Abs(o.ContentMap[k][i, j]));
                    });

                    AnalyzeByName("fsd_uniformity_right", sectionParser, (t, k, i, j) =>
                    {
                        return t.Max(o => Math.Abs(o.ContentMap[k][i, j]));
                    });

                    AnalyzeByName("fsd_deviation", sectionParser, (t, k, i, j) =>
                    {
                        return Math.Max(t.Max(o => o.ContentMap[k][i, j]), -t.Min(o => o.ContentMap[k][i, j]) / 3);
                    });
                }

                if (Simulate)
                {
                    ViewToXMLData();

                    SEMITestApp.MainWindow.SMComplexed.OnlyReloadXmlConfig();

                    new System.Threading.Thread(() =>
                    {
                        string fakeDir = GetWorkPath() + "TestResult\\Fake";

                        MakeDirectoryClean(fakeDir);

                        SimulateTest(sectionParser);

                    }).Start();
                }
            }
        }
    }

    public class DetailSetModeMcap550 : DetailSetMode
    {
        public DetailSetModeMcap550()
        {
            MapItemToKeyWords = new Dictionary<string, ItemRule>()
            {
                {"stc_mean", new ItemRule("stc_rawdata", 2000, 14000, -1)},
                {"stc_mse", new ItemRule("stc_rawdata")},

                {"uniformity_invalid", new ItemRule("uniformity_invalid")},
                {"mcap_rawdata_min", new ItemRule("mcap_rawdata")},
                {"mcap_rawdata_max", new ItemRule("mcap_rawdata")},
                {"scap_rawdata_min", new ItemRule("Scap Data")},
                {"scap_rawdata_max", new ItemRule("Scap Data")},

                {"fsd_fast", new ItemRule("fsd_fast")},
                {"fsd_slow", new ItemRule("fsd_slow")},
                {"fsd_diff_max", new ItemRule("fsd_diff_max")},

                //{"vt_on", new ItemRule("vt_on")},
                //{"vt_off", new ItemRule("vt_off")},
                //{"vt_diff_max", new ItemRule("vt_diff_max")},

                {"tmp_invalid", new ItemRule("tmp_invalid")},
                {"tmp_1_mcapdata", new ItemRule("tmp_1_mcapdata")},
                {"tmp_2_mcapdata", new ItemRule("tmp_2_mcapdata")},
                {"tmp_3_mcapdata", new ItemRule("tmp_3_mcapdata")},
                {"tmp_4_mcapdata", new ItemRule("tmp_4_mcapdata")},
                {"tmp_5_mcapdata", new ItemRule("tmp_5_mcapdata")},
                {"tmp_6_mcapdata", new ItemRule("tmp_6_mcapdata")},
                {"tmp_7_mcapdata", new ItemRule("tmp_7_mcapdata")},
                {"tmp_8_mcapdata", new ItemRule("tmp_8_mcapdata")},

                {"noise_mcap_base", new ItemRule("noise_mcap_base")},
                {"noise_scap_base", new ItemRule("noise_scap_base")},

            };
        }

        public override Boolean ExcludeTBD()
        {
            return false;
        }

        public override void XMLDataToView()
        {
            DcMatrix.Clear();

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            XmlNode invalidNode = stNode.SelectSingleNode("invalidnode");
            DcMatrix["invalid"] = GetDetailData(invalidNode, "invalid", 1, true);

            XmlNode buttonTest = stNode.SelectSingleNode("button_test");
            var KeyChannelDefault = GetXmlAttrbuteValue(stNode, "button_test", "key_channel_invalid", 0) > 0;
            //2024.05.23-hjx 20240604
            if (KeyChannelDefault == true)
            {
                int rows = DcMatrix["invalid"].RowNumber;
                for (int index = 0; (index < DcMatrix["invalid"].ColNumber) && (keyNum > 0); index++)
                {
                    int pos = listKeyChannels.FindIndex((o) =>
                    {
                        return o == index ? true : false;
                    });
                    DcMatrix["invalid"][rows - 1][index] = pos >= 0 ? 1 : 0;
                }
            }


            XmlNode osTest = stNode.SelectSingleNode("os_test");
            if (1 == GetXmlAttrbuteValue(stNode, "os_test", "selected"))
            {
                DcMatrix["os_base"] = GetDetailData(osTest, "os_base", 2000, true);
            }


            XmlNode stcTest = stNode.SelectSingleNode("stc_test");
            if (1 == GetXmlAttrbuteValue(stNode, "stc_test", "selected"))
            {
                DcMatrix["stc_mean"] = GetDetailData(stcTest, "stc_mean", 0);
                DcMatrix["stc_mse"] = GetDetailData(stcTest, "stc_mse", 10);
            }

            XmlNode mcapTest = stNode.SelectSingleNode("mcap_rawdata_test");
            if (1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "selected"))
            {
                //DcMatrix["mcap_rawdata"] = GetDetailData(mcapTest, "mcap_rawdata", 6000);

                int min = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_min");
                DcMatrix["mcap_rawdata_min"] = GetDetailData(mcapTest, "mcap_rawdata_min", min);
                int max = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_max");
                DcMatrix["mcap_rawdata_max"] = GetDetailData(mcapTest, "mcap_rawdata_max", max);
                int uniformityHor = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_hor_max");
                DcMatrix["mcap_uniformity_h"] = GetDetailData(mcapTest, "uniformity_hor_max", uniformityHor);
                int uniformityVer = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_ver_max");
                DcMatrix["mcap_uniformity_v"] = GetDetailData(mcapTest, "uniformity_ver_max", uniformityVer);

                InvalidMatrix(DcMatrix["mcap_uniformity_h"], 0, 0xff);
                InvalidMatrix(DcMatrix["mcap_uniformity_v"], 0xff, 0);

                DcMatrix["uniformity_invalid"] = GetDetailData(mcapTest, "uniformity_invalid", 1);
            }

            XmlNode fsdTest = stNode.SelectSingleNode("fsd_test");
            if (1 == GetXmlAttrbuteValue(stNode, "fsd_test", "selected"))
            {
                int max = GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_diff_max_default");
                DcMatrix["fsd_diff_max"] = GetDetailData(fsdTest, "fsd_diff_max", max);
                DcMatrix["fsd_fast"] = GetDetailData(fsdTest, "fsd_fast", 1000);
                DcMatrix["fsd_slow"] = GetDetailData(fsdTest, "fsd_slow", 0);
            }

            //XmlNode vtTest = stNode.SelectSingleNode("vt_test");
            //if (1 == GetXmlAttrbuteValue(stNode, "vt_test", "selected") && (SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_5562 & 0xff00))
            //{
            //    int max = GetXmlAttrbuteValue(stNode, "vt_test", "vt_max");
            //    DcMatrix["vt_diff_max"] = GetVtDetailData(vtTest, "vt_diff_max", max);
            //    DcMatrix["vt_on"] = GetVtDetailData(vtTest, "vt_on", 1000);
            //    DcMatrix["vt_off"] = GetVtDetailData(vtTest, "vt_off", 0);
            //}

            XmlNode baseTest = stNode.SelectSingleNode("base_test");
            if (1 == GetXmlAttrbuteValue(stNode, "base_test", "selected"))
            {
                DcMatrix["tmp_invalid"] = GetDetailData(baseTest, "tmp_invalid", 1);
                DcMatrix["tmp_1_mcapdata"] = GetDetailData(baseTest, "tmp_1_mcapdata", 0);
                DcMatrix["tmp_2_mcapdata"] = GetDetailData(baseTest, "tmp_2_mcapdata", 0);
                DcMatrix["tmp_3_mcapdata"] = GetDetailData(baseTest, "tmp_3_mcapdata", 0);
                DcMatrix["tmp_4_mcapdata"] = GetDetailData(baseTest, "tmp_4_mcapdata", 0);
                DcMatrix["tmp_5_mcapdata"] = GetDetailData(baseTest, "tmp_5_mcapdata", 0);
                DcMatrix["tmp_6_mcapdata"] = GetDetailData(baseTest, "tmp_6_mcapdata", 0);
                DcMatrix["tmp_7_mcapdata"] = GetDetailData(baseTest, "tmp_7_mcapdata", 0);
                DcMatrix["tmp_8_mcapdata"] = GetDetailData(baseTest, "tmp_8_mcapdata", 0);

            }

            XmlNode wbaseTest = stNode.SelectSingleNode("wbase_test");
            if (1 == GetXmlAttrbuteValue(stNode, "wbase_test", "selected"))
            {
                DcMatrix["tmp_invalid"] = GetDetailData(wbaseTest, "tmp_invalid", 1);
                DcMatrix["tmp_1_mcapdata"] = GetDetailData(wbaseTest, "tmp_1_mcapdata", 1);
                DcMatrix["tmp_2_mcapdata"] = GetDetailData(wbaseTest, "tmp_2_mcapdata", 1);
                DcMatrix["tmp_3_mcapdata"] = GetDetailData(wbaseTest, "tmp_3_mcapdata", 1);
                DcMatrix["tmp_4_mcapdata"] = GetDetailData(wbaseTest, "tmp_4_mcapdata", 1);
                DcMatrix["tmp_5_mcapdata"] = GetDetailData(wbaseTest, "tmp_5_mcapdata", 1);
                DcMatrix["tmp_6_mcapdata"] = GetDetailData(wbaseTest, "tmp_6_mcapdata", 1);
                DcMatrix["tmp_7_mcapdata"] = GetDetailData(wbaseTest, "tmp_7_mcapdata", 1);
                DcMatrix["tmp_8_mcapdata"] = GetDetailData(wbaseTest, "tmp_8_mcapdata", 1);

            }

            XmlNode scapRawDataTest = stNode.SelectSingleNode("scap_rawdata_test");
            if (1 == GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "selected"))
            {
                int min = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_min");
                DcMatrix["scap_rawdata_min"] = GetMScapDetailData(scapRawDataTest, "scap_rawdata_min", min);
                int max = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_max");
                DcMatrix["scap_rawdata_max"] = GetMScapDetailData(scapRawDataTest, "scap_rawdata_max", max);
            }

            XmlNode noiseTest = stNode.SelectSingleNode("noise_test");
            if (1 == GetXmlAttrbuteValue(stNode, "noise_test", "selected") )
            {
                int mcapBaseValue = GetXmlAttrbuteValue(stNode, "noise_test", "noise_mcap_base_value_default");
                DcMatrix["noise_mcap_base"] = GetDetailData(noiseTest, "noise_mcap_base", mcapBaseValue);

                int scapBaseValue = GetXmlAttrbuteValue(stNode, "noise_test", "noise_scap_base_value_default");
                DcMatrix["noise_scap_base"] = GetMScapDetailData(noiseTest, "noise_scap_base", scapBaseValue);
            }
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            XmlNode invalidNode = stNode.SelectSingleNode("invalidnode");
            if (null == invalidNode)
            {
                invalidNode = xml.CreateElement("invalidnode");
                stNode.AppendChild(invalidNode);
            }
            SaveDetailData(invalidNode, "invalid", DcMatrix["invalid"]);

            if (1 == GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "selected"))
            {
                XmlNode scapDataTest = stNode.SelectSingleNode("scap_rawdata_test");
                SaveDetailData(scapDataTest, "scap_rawdata_min", DcMatrix["scap_rawdata_min"]);
                SaveDetailData(scapDataTest, "scap_rawdata_max", DcMatrix["scap_rawdata_max"]);
            }
            if (1 == GetXmlAttrbuteValue(stNode, "stc_test", "selected"))
            {
                XmlNode stcTest = stNode.SelectSingleNode("stc_test");
                SaveDetailData(stcTest, "stc_mean", DcMatrix["stc_mean"]);
                SaveDetailData(stcTest, "stc_mse", DcMatrix["stc_mse"]);
            }
            if (1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "selected"))
            {
                XmlNode mcapRawDataTest = stNode.SelectSingleNode("mcap_rawdata_test");
                SaveDetailData(mcapRawDataTest, "mcap_rawdata_min", DcMatrix["mcap_rawdata_min"]);
                SaveDetailData(mcapRawDataTest, "mcap_rawdata_max", DcMatrix["mcap_rawdata_max"]);
                SaveDetailData(mcapRawDataTest, "uniformity_hor_max", DcMatrix["mcap_uniformity_h"]);
                SaveDetailData(mcapRawDataTest, "uniformity_ver_max", DcMatrix["mcap_uniformity_v"]);
  

                for (int iRow = 0; iRow < DcMatrix["uniformity_invalid"].RowNumber; iRow++)
                {
                    for (int iCol = 0; iCol < DcMatrix["uniformity_invalid"].ColNumber; iCol++)
                    {
                        DcMatrix["uniformity_invalid"][iRow][iCol] = (int)DcMatrix["uniformity_invalid"][iRow][iCol] < 0 ? 0 : DcMatrix["uniformity_invalid"][iRow][iCol];
                        DcMatrix["uniformity_invalid"][iRow][iCol] = (int)DcMatrix["uniformity_invalid"][iRow][iCol] > 1 ? 1 : DcMatrix["uniformity_invalid"][iRow][iCol];
                    }

                }
                SaveDetailData(mcapRawDataTest, "uniformity_invalid", DcMatrix["uniformity_invalid"]);
                
            }

            if (1 == GetXmlAttrbuteValue(stNode, "fsd_test", "selected"))
            {
                XmlNode fsdData = stNode.SelectSingleNode("fsd_test");
                SaveDetailData(fsdData, "fsd_diff_max", DcMatrix["fsd_diff_max"]);
                SaveDetailData(fsdData, "fsd_fast", DcMatrix["fsd_fast"]);
                SaveDetailData(fsdData, "fsd_slow", DcMatrix["fsd_slow"]);
            }

            //if (1 == GetXmlAttrbuteValue(stNode, "vt_test", "selected") && (SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_5562 & 0xff00))
            //{
            //    XmlNode vtData = stNode.SelectSingleNode("vt_test");
            //    SaveDetailData(vtData, "vt_diff_max", DcMatrix["vt_diff_max"]);
            //    SaveDetailData(vtData, "vt_on", DcMatrix["vt_on"]);
            //    SaveDetailData(vtData, "vt_off", DcMatrix["vt_off"]);
            //}

            if (1 == GetXmlAttrbuteValue(stNode, "base_test", "selected") )
            {
                XmlNode tmp_mcapRawData = GetXmlAttrbuteValue(stNode, "base_test", "selected") == 1 ? stNode.SelectSingleNode("base_test") : stNode.SelectSingleNode("wbase_test");
                SaveDetailData(tmp_mcapRawData, "tmp_invalid", DcMatrix["tmp_invalid"]);
                SaveDetailData(tmp_mcapRawData, "tmp_1_mcapdata", DcMatrix["tmp_1_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_2_mcapdata", DcMatrix["tmp_2_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_3_mcapdata", DcMatrix["tmp_3_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_4_mcapdata", DcMatrix["tmp_4_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_5_mcapdata", DcMatrix["tmp_5_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_6_mcapdata", DcMatrix["tmp_6_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_7_mcapdata", DcMatrix["tmp_7_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_8_mcapdata", DcMatrix["tmp_8_mcapdata"]);
            }

            if (1 == GetXmlAttrbuteValue(stNode, "wbase_test", "selected") )
            {
                XmlNode tmp_mcapRawData = stNode.SelectSingleNode("wbase_test");
                SaveDetailData(tmp_mcapRawData, "tmp_invalid", DcMatrix["tmp_invalid"]);
                SaveDetailData(tmp_mcapRawData, "tmp_1_mcapdata", DcMatrix["tmp_1_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_2_mcapdata", DcMatrix["tmp_2_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_3_mcapdata", DcMatrix["tmp_3_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_4_mcapdata", DcMatrix["tmp_4_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_5_mcapdata", DcMatrix["tmp_5_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_6_mcapdata", DcMatrix["tmp_6_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_7_mcapdata", DcMatrix["tmp_7_mcapdata"]);
                SaveDetailData(tmp_mcapRawData, "tmp_8_mcapdata", DcMatrix["tmp_8_mcapdata"]);
            }

            if (1 == GetXmlAttrbuteValue(stNode, "noise_test", "selected"))
            {
                XmlNode noiseData = stNode.SelectSingleNode("noise_test");
                SaveDetailData(noiseData, "noise_mcap_base", DcMatrix["noise_mcap_base"]);
                SaveDetailData(noiseData, "noise_scap_base", DcMatrix["noise_scap_base"]);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }

        protected override void SimulateTest(IList<FileParse> parser)
        {
            if (null == parser) return;
            CLRLinkParam linkParam = new CLRLinkParam();
            linkParam.LinkType = CLRLinkParam.CLRLINK_TYPE_FAKE;
            bool bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);

            int index = 0, fileSize = (int)parser.Count;

            //CMD_OPEN_TST        = 0x20,
            //CMD_FSD_TST         = 0x24,
            foreach (var item in parser)
            {
                Dictionary<int, int[,]> dcFackData = new Dictionary<int, int[,]>();

                if (item.ContentMap.ContainsKey("Scap Data"))
                    dcFackData[(0xfa << 16) + 0x28] = item.ContentMap["Scap Data"];
                if (item.ContentMap.ContainsKey("stc_rawdata"))
                    dcFackData[(0xfb << 16) + 0x28] = item.ContentMap["stc_rawdata"];
                if (item.ContentMap.ContainsKey("mcap_rawdata"))
                    dcFackData[(0xfc << 16) + 0x28] = item.ContentMap["mcap_rawdata"];

                dcFackData[(0 << 16) + 0x01] = new int[1, 16] { { 0x66, 0x43, 0x02, 0xE9, 0xFD, 0x16, 0x00, 0x00, 0x07, 0x00, 0x00, 0xB8, 0x94, 0x03, 0x00, 0x01 } };

                dcFackData[(0 << 16) + 0x31] = new int[1, 0x34];
                dcFackData[(0 << 16) + 0x31][0, 16] = 0xfa;
                dcFackData[(0x80 << 16) + 0x31] = new int[1, 0x100];

                SEMITestApp.MainWindow.SMComplexed.SimulateTest(0, dcFackData);

                AnalyzeProcessVal = (++index) * 100 / fileSize;
            }

            linkParam.LinkType = CLRLinkParam.CLRLINK_TYPE_USB;
            bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);
        }

        public override void OnInportClick()
        {
            IList<FileParse> finalParses = new List<FileParse>();
            AnalyzeResultText = string.Format("{0}: {1}     ", "Total", statistic.TotalCount()) + "Valid:  ";
            {
                IList<FileParse> stcParses = new List<FileParse>();
                string stcKeyWord = MapItemToKeyWords["stc_mean"].keyWord;
                statistic.TickOut(stcKeyWord, ref stcParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(stcParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "stc_mean", stcParses.Count());

                //if (RefreshBase)
                {
                    AnalyzeByName("stc_mean", stcParses, (t, k, i, j) => { return (int)t.Average(o => o.ContentMap[k][i, j]); });

                    AnalyzeByName("stc_mse", stcParses, (t, k, i, j) =>
                    {
                        double avg = t.Average(o => o.ContentMap[k][i, j]);
                        double var = t.Sum(o => (o.ContentMap[k][i, j] - avg) * (o.ContentMap[k][i, j] - avg)) / t.Count();
                        int mse = (int)(Math.Sqrt(var) * 10);
                        if (stcParses.Count < 50) mse = Math.Max(1500, mse);
                        return mse;
                    });
                }

                IList<FileParse> mcapParses = new List<FileParse>();
                string mcapKeyWord = MapItemToKeyWords["mcap_rawdata_min"].keyWord;
                statistic.TickOut(mcapKeyWord, ref mcapParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(mcapParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "mcap_rawdata", mcapParses.Count());

                //if (GenThreshold)
                {
                    AnalyzeByName("mcap_rawdata_min", mcapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg - avg * ThresholdCof / 100;
                    });
                    AnalyzeByName("mcap_rawdata_max", mcapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg + avg * ThresholdCof / 100;
                    });
                }

                for (int a = 1; a <= 8; a++)
                {
                    var str = String.Format("tmp_{0}_mcapdata", a);
                    IList<FileParse> tmpmcapParses = new List<FileParse>();
                    string tmpmcapKeyWord = MapItemToKeyWords[str].keyWord;
                    statistic.TickOut(tmpmcapKeyWord, ref tmpmcapParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                    if (Simulate) finalParses = finalParses.Union(tmpmcapParses).ToList();
                    if (a == 1) AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "tmp_mcapdata", tmpmcapParses.Count());

                    //if (GenThreshold)
                    {
                        AnalyzeByName(str, tmpmcapParses, (t, k, i, j) =>
                        {
                            int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                            return avg;
                        });

                    }
                }



                IList<FileParse> scapParses = new List<FileParse>();
                string strKeyWord = MapItemToKeyWords["scap_rawdata_min"].keyWord;
                statistic.TickOutMScap(strKeyWord, ref scapParses, GetCols(), GetRows(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(scapParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "scap_data", scapParses.Count());

                //if (GenThreshold)
                {
                    AnalyzeByName("scap_rawdata_min", scapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg - avg * ThresholdCof / 100;
                    });
                    AnalyzeByName("scap_rawdata_max", scapParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg + avg * ThresholdCof / 100;
                    });
                }

                IList<FileParse> fsdParses = new List<FileParse>();
                string fsdKeyWord = MapItemToKeyWords["fsd_fast"].keyWord;
                statistic.TickOut(fsdKeyWord, ref fsdParses, GetRows(), GetCols(), AnalyzeRatio, 0);
                if (Simulate) finalParses = finalParses.Union(fsdParses).ToList();
                AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "fsd", fsdParses.Count());

                //if (GenThreshold)
                {
                    AnalyzeByName("fsd_fast", fsdParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg;
                    });
                    AnalyzeByName("fsd_slow", fsdParses, (t, k, i, j) =>
                    {
                        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                        return avg;
                    });
                }

                //IList<FileParse> vtParses = new List<FileParse>();
                //string vtKeyWord = MapItemToKeyWords["vt_on"].keyWord;
                //statistic.TickOut(vtKeyWord, ref vtParses, 1, GetRows(), AnalyzeRatio, 0);
                //if (Simulate) finalParses = finalParses.Union(vtParses).ToList();
                //AnalyzeResultText = AnalyzeResultText + string.Format("{0}: {1}     ", "vt", vtParses.Count());

                ////if (GenThreshold)
                //{
                //    AnalyzeByName("vt_on", vtParses, (t, k, i, j) =>
                //    {
                //        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                //        return avg;
                //    });
                //    AnalyzeByName("vt_off", vtParses, (t, k, i, j) =>
                //    {
                //        int avg = (int)t.Average(o => o.ContentMap[k][i, j]);
                //        return avg;
                //    });
                //}

                if (Simulate)
                {
                    ViewToXMLData();

                    SEMITestApp.MainWindow.SMComplexed.OnlyReloadXmlConfig();

                    new System.Threading.Thread(() =>
                    {
                        string fakeDir = GetWorkPath() + "TestResult\\Fake";

                        MakeDirectoryClean(fakeDir);

                        SimulateTest(finalParses);

                    }).Start();
                }
            }
        }
    }



}
