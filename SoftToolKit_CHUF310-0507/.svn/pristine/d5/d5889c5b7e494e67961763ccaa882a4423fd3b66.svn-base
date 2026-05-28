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
    /// KeyPanel.xaml 的交互逻辑
    /// </summary>
    public partial class KeyPanel : UserControl
    {
        public KeyPanel()
        {
            InitializeComponent();
        }

        public void AddKeyControl(KeyControl key)
        {
            this.keyWrapPanel.Children.Add(key);
        }
        public bool IsKeyControlEmpty()
        {
            return this.keyWrapPanel.Children.Count == 0;
        }
        public void ClearKeyControl()
        {
            this.keyWrapPanel.Children.Clear();
        }
    }
}
