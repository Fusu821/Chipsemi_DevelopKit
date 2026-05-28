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
        public void RegistReflexRawDataFrame7126()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7126, "SEMIDevelopKit.Src.WinSub.RawDataFrame7126", SEMI.Util.ChipReflex.SEMI_DEVLOP_RAWDATA);
        }
    }
    /// <summary>
    /// RawDataFrame7126.xaml 的交互逻辑
    /// </summary>
    public partial class RawDataFrame7126 : UserControl
    {
        private Model7126 viewModel = new Model7126();

        public RawDataFrame7126()
        {
            InitializeComponent();

            viewModel.WpfRawDispView = FindName("dispRawData") as WpfRawDataView;
            viewModel.WpfStatisticRawDispView = FindName("dispStatisticRawData") as WpfRawDataView;
            this.DataContext = viewModel;
        }
    }
}
