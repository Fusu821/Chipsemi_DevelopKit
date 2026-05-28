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
using SEMITestApp.Src.WinSub;

namespace SEMITestApp.Src.WinSet
{
    public partial class SMTestChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexGraphItemSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_CHIPALL, "SEMITestApp.Src.WinSet.GraphItemSet", SEMI.Util.ChipReflex.SEMI_TEST_GRAPH_SET);
        }
    }
    /// <summary>
    /// GraphItemSet.xaml 的交互逻辑
    /// </summary>
    public partial class GraphItemSet : Page
    {
        public GraphItemSet()
        {
            InitializeComponent();
            GraphSettingMode GS_Mode = new GraphSettingMode();
            GS_Mode.Kpanel = FindName("keypanel") as KeyPanel;
            GS_Mode.PhysicalKpanel = FindName("keypanel2") as KeyPanel;
            this.DataContext = GS_Mode;
        }

        private void GraphPage_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            GraphSettingMode mode = this.DataContext as GraphSettingMode;
            if (null == mode) return;

            try
            {
                if ((Boolean)e.NewValue == true)
                {
                    mode.XMLDataToView();
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

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {

        }
    }
}
