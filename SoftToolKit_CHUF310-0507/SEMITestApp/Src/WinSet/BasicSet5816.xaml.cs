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

namespace SEMITestApp.Src.WinSet
{
    public partial class SMTestChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexBasicSet5816()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5816, "SEMITestApp.Src.WinSet.BasicSet5816", SEMI.Util.ChipReflex.SEMI_TEST_BASIC_SET);
        }
    }
    /// <summary>
    /// BasicSet.xaml 的交互逻辑
    /// </summary>
    public partial class BasicSet5816 : Page
    {
        public BasicSet5816()
        {
            InitializeComponent();

            this.DataContext = new BasicSetMode5816();
        }

        private void Basic_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            BasicSetMode5816 mode = this.DataContext as BasicSetMode5816;
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
    }
}
