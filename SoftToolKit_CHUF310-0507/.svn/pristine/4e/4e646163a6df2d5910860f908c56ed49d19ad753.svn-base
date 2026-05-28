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
    public partial class SMDevelopChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexRawDataFrame7449()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7449, "SEMIDevelopKit.Src.WinSub.RawDataFrame7449", SEMI.Util.ChipReflex.SEMI_DEVLOP_RAWDATA);
        }
    }
    /// <summary>
    /// RawDataFrameE902.xaml 的交互逻辑
    /// </summary>
    public partial class RawDataFrame7449 : UserControl
    {
        private Model7449 viewModel = new Model7449();

        public RawDataFrame7449()
        {
            InitializeComponent();

            viewModel.WpfRawDispView = FindName("dispRawData") as WpfRawDataView;
            viewModel.WpfStatisticRawDispView = FindName("dispStatisticRawData") as WpfRawDataView;
            this.DataContext = viewModel;
        }
    }
}
