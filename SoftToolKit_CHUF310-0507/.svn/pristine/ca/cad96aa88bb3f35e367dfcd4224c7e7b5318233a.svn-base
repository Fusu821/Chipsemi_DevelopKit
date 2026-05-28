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

namespace SEMITestApp.Src.WinSet
{
    /// <summary>
    /// OfilmCustomizedWin.xaml 的交互逻辑
    /// </summary>
    public partial class OfilmCustomizedWin : Window
    {
        public OfilmCustomizedWin()
        {
            InitializeComponent();
            this.DataContext = new OfilmCustomizedWinMode();
        }

        private void Grid_Loaded(object sender, RoutedEventArgs e)
        {
            var mode = this.DataContext as OfilmCustomizedWinMode;
            if (null == mode) return;

            mode.XMLDataToView();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var mode = this.DataContext as OfilmCustomizedWinMode;
            if (null == mode) return;

            //MainWindow.SMComplexed.GameOver(0);

            mode.ViewToXMLData();


            this.Close();
        }

    }
}
