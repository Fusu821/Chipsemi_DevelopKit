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
        public void RegistReflexBasicSet570()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_570, "SEMITestApp.Src.WinSet.BasicSet570", SEMI.Util.ChipReflex.SEMI_TEST_BASIC_SET);
        }
    }
    /// <summary>
    /// BasicSet.xaml 的交互逻辑
    /// </summary>
    public partial class BasicSet570 : Page
    {
        public BasicSet570()
        {
            InitializeComponent();

            this.DataContext = new BasicSetMode570();
        }

        private void Basic_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            BasicSetMode570 mode = this.DataContext as BasicSetMode570;
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
