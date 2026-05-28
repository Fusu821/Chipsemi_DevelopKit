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
using SEMITestApp.Src.Util;
using SMInvokeBridge;
using SEMI.Util;


namespace SEMITestApp.Src.WinSet
{
    public partial class SMTestChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexTestDetailSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_CHIPALL, "SEMITestApp.Src.WinSet.DetailSet", SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET);
        }
    }
    /// <summary>
    /// DetailSet.xaml 的交互逻辑
    /// </summary>
    public partial class DetailSet : Page
    {
        private static DetailSet detailHandle = null;

        private int scale_factor_x = 0;
        private int scale_factor_y = 0;

        public static DetailSet DetailHandle()
        {
            return detailHandle;
        }

        public DetailSet()
        {
            InitializeComponent();

            detailHandle = this;

            //this.DataContext = new DetailSetMode();
            this.DataContext = SMTestChipReflex.Instance.GetSemiModuleByChipAndType(SEMI.Util.ChipReflex.SEMI_TEST_DETAIL_SET_MODE, SettingMode.selectedIC);
        }



        private DataGrid GenGridTemplate(DetailSetMode mode, string szHeader)
        {
            DataGrid dataGrid = new DataGrid();

            dataGrid.Style = null;
            dataGrid.RowHeaderWidth = 50;
            dataGrid.AutoGenerateColumns = false;
            dataGrid.CanUserResizeColumns = false;
            dataGrid.CanUserReorderColumns = false;
            dataGrid.CanUserSortColumns = false;
            dataGrid.GridLinesVisibility = DataGridGridLinesVisibility.All;
            dataGrid.SelectionUnit = DataGridSelectionUnit.Cell;
            dataGrid.SelectionMode = DataGridSelectionMode.Extended;
            dataGrid.RowHeaderStyle = FindResource("AutoGenRowHeader") as Style;

            dataGrid.IsVisibleChanged += (sender, e) =>
            {
                if ((Boolean)e.NewValue == true)
                {
                    dataGrid.UnselectAllCells();
                }
            };
            
            //dataGrid.RowHeaderWidth = 40;

            //DataGridExtension extProp = new DataGridExtension();

            //DataMatrix maxtrix = new DataMatrix(Rows, Cols, Keys);
            DataGridExtension.SetMatrixSource(dataGrid, mode.DcMatrix[szHeader]);
            //dataGrid.LoadingRow += new EventHandler<DataGridRowEventArgs>(DataGridLoadingRow);

            return dataGrid;
        }

        private void DataGridLoadingRow(object sender, DataGridRowEventArgs e)
        {
            e.Row.Header = e.Row.GetIndex().ToString("00");
        }

        private void GenTabItem(TabControl tabDetails, DetailSetMode mode, string szHeader, bool hasHist = false, string bindChkBox = "", string coeficient = "", bool enable = true)
        {
            if (mode.DcMatrix.ContainsKey(szHeader))
            {
                WpfTabItem newTabItem = new WpfTabItem()
                {
                    Header = szHeader + coeficient,
                    Content = GenGridTemplate(mode, szHeader),
                    Tag = hasHist,
                    Height = 29,
                };
                newTabItem.Style = FindResource("norTabItem") as Style;

                if ((!string.IsNullOrEmpty(bindChkBox)) && enable)
                {
                    Binding bind = new Binding() { ElementName = bindChkBox, Path = new PropertyPath("IsChecked"), Mode = BindingMode.OneWay, };
                    newTabItem.SetBinding(WpfTabItem.TabItemCheckedProperty, bind);
                    newTabItem.TabItemEnabled = enable;
                }
                else
                {
                    newTabItem.TabItemEnabled = enable;
                }
                tabDetails.Items.Add(newTabItem);
            }
        }

        public bool CheckItemChecked(string szHeader)
        {
            foreach(WpfTabItem it in this.tabDetails.Items)
            {
                //if (0 == string.Compare(szHeader, it.Header.ToString()))
                if (it.Header.ToString().Contains(szHeader))
                    return it.TabItemChecked;
            }

            return false;
        }

        private void InitTabView()
        {
            DetailSetMode mode = this.DataContext as DetailSetMode;
            this.tabDetails.Items.Clear();

            if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_3536 & 0xff00))
            {
                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "os_base", false, "chkBase");

                GenTabItem(tabDetails, mode, "fsd_base", false, "chkBase");
                GenTabItem(tabDetails, mode, "fsd_fast", false, "chkBase");
                GenTabItem(tabDetails, mode, "fsd_slow", false, "chkBase");
                GenTabItem(tabDetails, mode, "fsd_delta_max", false, "");
                GenTabItem(tabDetails, mode, "fsd_uniformity_left", false, "");
                GenTabItem(tabDetails, mode, "fsd_uniformity_right", false, "");
                GenTabItem(tabDetails, mode, "fsd_deviation", false, "");

                GenTabItem(tabDetails, mode, "rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("rawdata_min"));
                GenTabItem(tabDetails, mode, "rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("rawdata_max"));
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_3535 & 0xff00))
            {
                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "os_base", false, "chkBase");

                GenTabItem(tabDetails, mode, "fsd_base", false, "chkBase");
                GenTabItem(tabDetails, mode, "fsd_fast", false, "chkBase");
                GenTabItem(tabDetails, mode, "fsd_slow", false, "chkBase");
                GenTabItem(tabDetails, mode, "fsd_delta_max", false, "");
                GenTabItem(tabDetails, mode, "fsd_uniformity_left", false, "");
                GenTabItem(tabDetails, mode, "fsd_uniformity_right", false, "");
                GenTabItem(tabDetails, mode, "fsd_deviation", false, "");
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_5472 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "", mode.GetThreadCoeficientText("scap_rawdata_min"),false);
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "", mode.GetThreadCoeficientText("scap_rawdata_max"), false);
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_5562 & 0xff00)
                || (SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_570 & 0xff00)
                || (SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_7126 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));

                GenTabItem(tabDetails, mode, "uniformity_invalid", false);
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "", mode.GetThreadCoeficientText("scap_rawdata_min"));
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "", mode.GetThreadCoeficientText("scap_rawdata_max"));

                GenTabItem(tabDetails, mode, "fsd_fast", false, "chkThr");
                GenTabItem(tabDetails, mode, "fsd_slow", false, "chkThr");
                GenTabItem(tabDetails, mode, "fsd_diff_max", false);

                //GenTabItem(tabDetails, mode, "vt_on", false, "chkThr");
                //GenTabItem(tabDetails, mode, "vt_off", false, "chkThr");
                //GenTabItem(tabDetails, mode, "vt_diff_max", false);

                GenTabItem(tabDetails, mode, "tmp_invalid");
                GenTabItem(tabDetails, mode, "tmp_1_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_2_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_3_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_4_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_5_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_6_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_7_mcapdata", false, "chkThr");
                GenTabItem(tabDetails, mode, "tmp_8_mcapdata", false, "chkThr");

                GenTabItem(tabDetails, mode, "noise_mcap_base", false);
                GenTabItem(tabDetails, mode, "noise_scap_base", false);
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_8006 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "", mode.GetThreadCoeficientText("scap_rawdata_min"));
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "", mode.GetThreadCoeficientText("scap_rawdata_max"));
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_810 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "", mode.GetThreadCoeficientText("scap_rawdata_min"));
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "", mode.GetThreadCoeficientText("scap_rawdata_max"));
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_7449 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "", mode.GetThreadCoeficientText("scap_rawdata_min"), false);
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "", mode.GetThreadCoeficientText("scap_rawdata_max"), false);
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_5816 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "base_min");
                //GenTabItem(tabDetails, mode, "base_max");

                //GenTabItem(tabDetails, mode, "low_freq_rawdata_min");
                //GenTabItem(tabDetails, mode, "low_freq_rawdata_max");
                //GenTabItem(tabDetails, mode, "low_freq_uniformity_h");
                //GenTabItem(tabDetails, mode, "low_freq_uniformity_v");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("scap_rawdata_min"), false);
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("scap_rawdata_max"), false);
            }
            else if ((SettingMode.selectedIC & 0xff00) == (eChipTypeList.SM_IC_310 & 0xff00))
            {
                //GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "invalid");

                GenTabItem(tabDetails, mode, "stc_mean", false, "chkBase");
                GenTabItem(tabDetails, mode, "stc_mse", false, "chkBase");

                GenTabItem(tabDetails, mode, "mcap_rawdata_min", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_min"));
                GenTabItem(tabDetails, mode, "mcap_rawdata_max", false, "chkThr", mode.GetThreadCoeficientText("mcap_rawdata_max"));
                GenTabItem(tabDetails, mode, "mcap_uniformity_h");
                GenTabItem(tabDetails, mode, "mcap_uniformity_v");

                GenTabItem(tabDetails, mode, "scap_rawdata_min", false, "", mode.GetThreadCoeficientText("scap_rawdata_min"), false);
                GenTabItem(tabDetails, mode, "scap_rawdata_max", false, "", mode.GetThreadCoeficientText("scap_rawdata_max"), false);
            }
        }

        private void OnHistMouseLeftClick(object sender, MouseButtonEventArgs e)
        {
            var HistGrid = FindName("uiniGridHist") as System.Windows.Controls.Primitives.UniformGrid;

            if (scale_factor_x == 0 && scale_factor_y == 0)
            {
                scale_factor_x = (int)HistGrid.ActualWidth;
                scale_factor_y = (int)HistGrid.ActualHeight;
            }
            if ((0x8000 & SEMI.Util.WinApi.GetKeyState(SEMI.Util.WinApi.VK_CONTROL)) == 0)
                return;

            double dwRate = 0.5;
            HistGrid.MinWidth = HistGrid.ActualWidth + dwRate * scale_factor_x;
            HistGrid.MinHeight = HistGrid.ActualHeight + dwRate * scale_factor_y;
        }

        private void OnHistMouseRightClick(object sender, MouseButtonEventArgs e)
        {
            var HistGrid = FindName("uiniGridHist") as System.Windows.Controls.Primitives.UniformGrid;

            if (scale_factor_x == 0 && scale_factor_y == 0)
            {
                scale_factor_x = (int)HistGrid.ActualWidth;
                scale_factor_y = (int)HistGrid.ActualHeight;
            }
            if ((0x8000 & WinApi.GetKeyState(WinApi.VK_CONTROL)) == 0)
                return;

            double dwRate = -0.5;
            HistGrid.MinWidth = scale_factor_x;
            HistGrid.MinHeight = scale_factor_y;
            HistGrid.MaxWidth = HistGrid.ActualWidth + dwRate * scale_factor_x;
            HistGrid.MaxHeight = HistGrid.ActualHeight + dwRate * scale_factor_y;
        }

        private void InitHistGraph()
        {
            DetailSetMode mode = this.DataContext as DetailSetMode;
            if (null == mode) return;

            var HistGrid = FindName("uiniGridHist") as System.Windows.Controls.Primitives.UniformGrid;
            if (null == HistGrid) return;

            var grp = FindName("grpHist") as GroupBox;
            grp.PreviewMouseLeftButtonUp += OnHistMouseLeftClick;
            grp.PreviewMouseRightButtonUp += OnHistMouseRightClick;

            HistGrid.Rows = SettingMode.GetRows();
            HistGrid.Columns = SettingMode.GetCols();
            for (int iRow = 0; iRow < HistGrid.Rows; iRow++)
            {
                for (int iCol = 0; iCol < HistGrid.Columns; iCol++)
                {
                    SEMI.Util.WpfHistogram hist = new SEMI.Util.WpfHistogram();
                    hist.Background = new SolidColorBrush(Color.FromArgb(0, 243, 243, 243));
                    hist.Margin = new Thickness(2, 2, 2, 2);
                    HistGrid.Children.Add(hist);
                }
            }
        }

        private void Detail_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            DetailSetMode mode = this.DataContext as DetailSetMode;
            if (null == mode) return;

            try
            {
                if ((Boolean)e.NewValue == true)
                {
                    mode.XMLDataToView();

                    mode.HistGrid = FindName("uiniGridHist") as System.Windows.Controls.Primitives.UniformGrid;

                    InitTabView();

                    InitHistGraph();
                }
                else
                {
                    mode.ViewToXMLData();
                }
            }
            catch (Exception ex)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    MessageBox.Show(ex.ToString());
                }));
            }
        }
    }
}
