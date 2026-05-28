using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Media;

namespace SEMIDevelopKit.Src.Util
{
    public class WpfTabItem : TabItem
    {
        public static readonly DependencyProperty MoverBrushProperty;
        public static readonly DependencyProperty EnterBrushProperty;

        public Brush MoverBrush
        {
            get { return base.GetValue(WpfTabItem.MoverBrushProperty) as Brush; }
            set { base.SetValue(WpfTabItem.MoverBrushProperty, value); }
        }
        public Brush EnterBrush
        {
            get { return base.GetValue(WpfTabItem.EnterBrushProperty) as Brush; }
            set { base.SetValue(WpfTabItem.EnterBrushProperty, value); }
        }
        static WpfTabItem()
        {
            WpfTabItem.MoverBrushProperty = DependencyProperty.Register("MoverBrush", typeof(Brush), typeof(WpfTabItem), new PropertyMetadata(null));
            WpfTabItem.EnterBrushProperty = DependencyProperty.Register("EnterBrush", typeof(Brush), typeof(WpfTabItem), new PropertyMetadata(null));
            FrameworkElement.DefaultStyleKeyProperty.OverrideMetadata(typeof(WpfTabItem), new FrameworkPropertyMetadata(typeof(WpfTabItem)));
        }
        public WpfTabItem()
        {
            base.Header = "ChipSemi-Test";
            base.Background = Brushes.Blue;
        }
    }
}
