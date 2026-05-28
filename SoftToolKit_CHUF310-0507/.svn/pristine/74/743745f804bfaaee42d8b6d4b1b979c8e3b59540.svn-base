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
    public partial class ToolFilterTransform : UserControl
    {
        public ToolFilterTransform()
        {
            InitializeComponent();
            this.DataContext = new ToolFilterTransformViewModel();
        }

        private void Grid_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effects = DragDropEffects.Link;
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }
        }

        private void Grid_Drop(object sender, DragEventArgs e)
        {
            string path = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
            var toolViewModel = this.DataContext as ToolFilterTransformViewModel;
            toolViewModel.DisplayContent(path);

        }
    }
}
