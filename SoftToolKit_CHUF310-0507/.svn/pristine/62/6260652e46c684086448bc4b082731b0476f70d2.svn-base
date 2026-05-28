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

namespace LibraryTools
{
    /// <summary>
    /// ToolFilterTransform.xaml 的交互逻辑
    /// </summary>
    public partial class ToolTouchFrame : UserControl
    {
        public ToolTouchFrame()
        {
            InitializeComponent();
            this.DataContext = new ToolTouchViewModel();
            
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var window = new Window
            {
                Title = "TouchWindow",
                Width = 1100,
                Height = 650
               
            };
            var pToolTouch = new ToolTouch();

            Color color = (Color)ColorConverter.ConvertFromString("#163246");
            SolidColorBrush brush = new SolidColorBrush(color);
            window.Background = brush;

            Color titleColor = (Color)ColorConverter.ConvertFromString("#32648C");
            SolidColorBrush titleBrush = new SolidColorBrush(titleColor);
            window.Foreground = titleBrush;
            window.WindowStyle = WindowStyle.SingleBorderWindow;

            window.Content = pToolTouch;

            window.ShowDialog();

            
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            var window = new Window
            {
                Title = "TouchWindow",
                Width = 1100,
                Height = 650

            };
            var pToolTouch = new ToolRawData();

            Color color = (Color)ColorConverter.ConvertFromString("#163246");
            SolidColorBrush brush = new SolidColorBrush(color);
            window.Background = brush;

            Color titleColor = (Color)ColorConverter.ConvertFromString("#32648C");
            SolidColorBrush titleBrush = new SolidColorBrush(titleColor);
            window.Foreground = titleBrush;
            window.WindowStyle = WindowStyle.SingleBorderWindow;

            window.Content = pToolTouch;

            window.ShowDialog();
        }


    }
}
