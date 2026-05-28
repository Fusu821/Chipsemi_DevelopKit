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
        public void RegistReflexRawDataFrame3535()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3535, "SEMIDevelopKit.Src.WinSub.RawDataFrame3535", SEMI.Util.ChipReflex.SEMI_DEVLOP_RAWDATA);
        }
    }
    /// <summary>
    /// RawDataFrame.xaml 的交互逻辑
    /// </summary>
    public partial class RawDataFrame3535 : UserControl
    {
        private Model3535 viewModel = new Model3535();

        public RawDataFrame3535()
        {
            InitializeComponent();

            viewModel.WpfRawDispView = FindName("dispRawData") as WpfRawDataView;
            //viewModel.WpfStatisticRawDispView = FindName("dispStatisticRawData") as WpfRawDataView;
            this.DataContext = viewModel;
        }
    }
}
