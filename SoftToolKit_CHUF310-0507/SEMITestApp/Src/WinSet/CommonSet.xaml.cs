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
        public void RegistReflexCommonSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_CHIPALL, "SEMITestApp.Src.WinSet.CommonSet", SEMI.Util.ChipReflex.SEMI_TEST_COMMON_SET);
        }
    }
    /// <summary>
    /// CommonSet.xaml 的交互逻辑
    /// </summary>
    public partial class CommonSet : Page
    {
        public CommonSet()
        {
            InitializeComponent();

            this.DataContext = new CommonSetMode();
        }

        private void CommonSet_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            CommonSetMode mode = this.DataContext as CommonSetMode;
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
                    MessageBox.Show( ex.ToString());
                }));
            }

        }
    }
}
