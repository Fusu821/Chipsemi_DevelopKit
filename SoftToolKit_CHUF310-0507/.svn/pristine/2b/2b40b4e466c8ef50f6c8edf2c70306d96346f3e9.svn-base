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
        public void RegistReflexTestItemSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_CHIPALL, "SEMITestApp.Src.WinSet.TestItemSet", SEMI.Util.ChipReflex.SEMI_TEST_ITEM_SET);
        }
    }
    /// <summary>
    /// TestItemSet.xaml 的交互逻辑
    /// </summary>
    public partial class TestItemSet : Page
    {
        public TestItemSet()
        {
            InitializeComponent();

            this.DataContext = SMTestChipReflex.Instance.GetSemiModuleByChipAndType(SMTestChipReflex.SEMI_TEST_ITEM_SET_MODE, SettingMode.selectedIC);
        }

        private void TestItem_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            SettingMode mode = this.DataContext as SettingMode;
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
                ex.ToString();
            }

        }
    }
}
