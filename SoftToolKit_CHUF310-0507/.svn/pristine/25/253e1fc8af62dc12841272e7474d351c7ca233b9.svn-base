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

//namespace SEMITestApp
//{
//    /// <summary>
//    /// TouchResultWindow.xaml 的交互逻辑
//    /// </summary>
//    public partial class TouchResultWindow : Window
//    {
//        public TouchResultWindow()
//        {
//            InitializeComponent();
//        }
//    }
//}
//using System;
//using System.Windows;
using MahApps.Metro.Controls;

namespace SEMITestApp
{
    /// <summary>
    /// TouchResultWindow.xaml 的交互逻辑
    /// </summary>
    public partial class TouchResultWindow : MetroWindow
    {
        //public static string TouchSelectResult = string.Empty;
        public string TouchSelectResult { get; private set; }

        public TouchResultWindow()
        {
            InitializeComponent();
            TouchSelectResult = string.Empty;
            this.Owner = Application.Current.MainWindow;
        }

        private void BtnOK_Click(object sender, RoutedEventArgs e)
        {
            TouchSelectResult = "PASS";
            this.DialogResult = true;
            //this.Close();
        }

        private void BtnNG_Click(object sender, RoutedEventArgs e)
        {
            TouchSelectResult = "FAIL";
            this.DialogResult = true;
            //this.Close();
        }

        //// 色块点击事件（复用按钮逻辑，支持点击色块选择）
        //private void PASS_Block_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        //{
        //    BtnOK_Click(null, null);
        //}

        //private void FAIL_Block_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        //{
        //    BtnNG_Click(null, null);
        //}
    }
}