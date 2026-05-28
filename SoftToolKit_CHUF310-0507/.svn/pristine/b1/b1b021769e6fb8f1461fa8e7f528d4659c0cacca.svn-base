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
        public void RegistReflexRawDataFrameE902()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5472, "SEMIDevelopKit.Src.WinSub.RawDataFrameE902", SEMI.Util.ChipReflex.SEMI_DEVLOP_RAWDATA);
        }
    }
    /// <summary>
    /// RawDataFrameE902.xaml 的交互逻辑
    /// </summary>
    public partial class RawDataFrameE902 : UserControl
    {
        private Model5472 viewModel = new Model5472();

        public RawDataFrameE902()
        {
            InitializeComponent();

            viewModel.WpfRawDispView = FindName("dispRawData") as WpfRawDataView;
            viewModel.WpfStatisticRawDispView = FindName("dispStatisticRawData") as WpfRawDataView;
            this.DataContext = viewModel;
        }
    }
}
