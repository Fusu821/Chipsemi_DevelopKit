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
using System.Windows.Shapes;
using MahApps.Metro.Controls;

namespace SEMITestApp.Src.WinSet
{
    /// <summary>
    /// SettingFrame.xaml 的交互逻辑
    /// </summary>
    public partial class SettingFrame : MetroWindow
    {
        public static SettingFrame ExternInterface { get; private set; }
        //private IDictionary<string, object> dcLinkPage = new Dictionary<string, object>();
        public SettingFrame()
        {
            InitializeComponent();

            ExternInterface = this;

            this.DataContext = SettingViewMode.Instance();
        }

        public void ShowFlyout(SettingMode mode)
        {
            var flyout = this.Flyouts.Items[0] as Flyout;
            flyout.Position = Position.Right;
            flyout.Focus();
            flyout.DataContext = mode;

            flyout.IsOpen = !flyout.IsOpen;
        }

        private void treeSets_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            IList<SetNode> listNodes = SettingViewMode.Instance().SetLists;
            TreeView tree = sender as TreeView;

            SetNode s = tree.SelectedValue as SetNode;

            if(null != s)
                this.NaviFrame.Navigate(SMTestChipReflex.Instance.GetSemiModuleByChipAndType(s.NodeType, SettingMode.selectedIC));
            else
                this.NaviFrame.Navigate(null);

//             if (null != s && !string.IsNullOrEmpty(s.LinkUri))
//             {
//                 object content = null;
// 
//                 //if (dcLinkPage.ContainsKey(s.LinkUri))
//                 //    content = dcLinkPage[s.LinkUri];
//                 //else
//                 //{
//                     //Type type = Type.GetType("SEMITestApp.Src.WinSet." + s.LinkUri.Replace(".xaml", ""));
//                     //content = Activator.CreateInstance(type);
//                     //dcLinkPage[s.LinkUri] = content;
//                     SMTestChipReflex.Instance.GetSemiModuleByChipAndType(s.NodeType, SettingMode.selectedIC);
//                 //}
// 
//                 this.NaviFrame.Navigate(content);
//             }
//             else
//             {
//                 this.NaviFrame.Navigate(null);
//             }
        }   
    }
}
