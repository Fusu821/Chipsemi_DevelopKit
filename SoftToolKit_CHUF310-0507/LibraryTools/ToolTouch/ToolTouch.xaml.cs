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
    public partial class ToolTouch : UserControl
    {
        public ToolTouch()
        {
            InitializeComponent();
            this.DataContext = new ToolTouchViewModel();
            this.Loaded  += WindowLoaded;
            
        }
        private void WindowLoaded(object sender, EventArgs e)
        {
            RuningKernel.Instance().StartRun();
        }

        private void SPanel_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            StackPanel stackPanel = sender as StackPanel;
            {
                if (stackPanel!= null)
                {
                    var newWidth = (int)e.NewSize.Width;
                    
                    var newHeight = (int)e.NewSize.Height;

                    var m_ToolTouchViewModel = this.DataContext as ToolTouchViewModel;

                    var side = newHeight - 10;

                    m_ToolTouchViewModel.ToolTouchViewModelRefresh(side);

                }
            
            }

        }
        //protected override void OnRender(DrawingContext dc)
        //{
        //    var a = (int)RenderSize.Width;
        //    var b = (int)RenderSize.Height;
        //    var m_ToolTouchViewModel = this.DataContext as ToolTouchViewModel;
        //    var side = SPanel.Height - 10;
        //    m_ToolTouchViewModel.ModelToolTouch.DisplayHeight = side;
        //    m_ToolTouchViewModel.ModelToolTouch.DisplayWidth = side;
        //}

    }
}
