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
        public void RegistReflexMainSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_CHIPALL, "SEMITestApp.Src.WinSet.MainSet", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
        }
    }
    /// <summary>
    /// MainSet.xaml 的交互逻辑
    /// </summary>
    public partial class MainSet : Page
    {
        public MainSet()
        {
            InitializeComponent();

            //this.DataContext = SMTestChipReflex.Instance.GetSemiModuleByChipAndType();

            this.DataContext = new MainSettingMode();
        }

        private void Page_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            MainSettingMode mode = this.DataContext as MainSettingMode;
            if (null == mode) return;

            try
            {
                if ((Boolean)e.NewValue == true)
                {
                    mode.XMLDataToView();

                    if (mode.X_Row != mode.Rows)
                    {
                        l_X_Row.Foreground = Brushes.Red;
                    }
                    else
                    {
                        l_X_Row.Foreground = Brushes.Black; 
                    }
                    if (mode.Y_Col != mode.Cols)
                    {
                        l_Y_Col.Foreground = Brushes.Red;
                    }
                    else
                    {
                        l_Y_Col.Foreground = Brushes.Black;
                    }
                }
                else
                {
                    mode.ViewToXMLData();
                }
            }
            catch(Exception ex)
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    MessageBox.Show(ex.ToString());
                }));
            }

        }
    }
}
