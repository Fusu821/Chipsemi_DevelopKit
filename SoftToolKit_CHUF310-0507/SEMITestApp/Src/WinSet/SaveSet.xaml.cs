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
        public void RegistReflexSaveSet()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_CHIPALL, "SEMITestApp.Src.WinSet.SaveSet", SEMI.Util.ChipReflex.SEMI_TEST_SAVE_SET);
        }
    }
    /// <summary>
    /// SaveSet.xaml 的交互逻辑
    /// </summary>
    public partial class SaveSet : Page
    {
        public SaveSet()
        {
            InitializeComponent();
            this.DataContext = new SaveSetMode();
        }
    }
}
