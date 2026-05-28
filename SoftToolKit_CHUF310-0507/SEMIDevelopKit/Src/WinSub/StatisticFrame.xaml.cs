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
using SEMIDevelopKit.Src.Util;

namespace SEMIDevelopKit.Src.WinSub
{
    /// <summary>
    /// StatisticFrane.xaml 的交互逻辑
    /// </summary>
    public partial class StatisticFrame : UserControl
    {
        public StatisticFrame()
        {
            InitializeComponent();
        }

        public void ActionOnICChanged()
        {
            var mdStatistic = SMDevelopChipReflex.Instance.GetSemiModuleByChipAndType(SMDevelopChipReflex.SEMI_DEVLOP_STATIS, MainViewModel.Intr.SelectedIC) as ModelStatistic;
            if (null != mdStatistic)
            {
                mdStatistic.LineChart = FindName("lineBoom") as SEMI.Util.WpfLineChart;
                this.DataContext = mdStatistic;
            }
        }

        private void SaveScanDataClick(object sender, RoutedEventArgs e)
        {
            ModelStatistic mode = this.DataContext as ModelStatistic;
            mode.SaveScan();
        }
    }
}
