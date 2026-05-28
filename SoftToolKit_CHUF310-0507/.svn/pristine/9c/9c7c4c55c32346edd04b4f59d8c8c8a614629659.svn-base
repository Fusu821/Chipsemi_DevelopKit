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

namespace SEMITestApp.Src.WinSub
{
    /// <summary>
    /// MutiplePage.xaml 的交互逻辑
    /// </summary>
    public partial class MutiplePage : Page
    {
        public MutiplePage()
        {
            InitializeComponent();

            ContentControl content = null;
            content = this.FindName("tester1") as ContentControl;
            if(content != null)  content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(0);
            content = this.FindName("tester2") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(1);
            content = this.FindName("tester3") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(2);
            content = this.FindName("tester4") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(3);
            content = this.FindName("tester5") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(4);
            content = this.FindName("tester6") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(5);
            content = this.FindName("tester7") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(6);
            content = this.FindName("tester8") as ContentControl;
            if (content != null) content.DataContext = ViewModelManager.Instance().GetMutiplePageViewMode(7);

            ViewModelManager.Instance().richTextMul = this.testMessage;
        }

        private void CbxDeviceItem_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cbx = sender as ComboBox;
            if (null != cbx)
            {
                int itemIndex = cbx.SelectedIndex;
                ViewModelManager.Instance().ShowMessageById(itemIndex);
            }
        }
    }
}
