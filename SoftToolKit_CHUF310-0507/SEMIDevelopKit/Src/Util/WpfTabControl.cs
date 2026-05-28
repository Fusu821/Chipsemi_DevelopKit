using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows;

namespace SEMIDevelopKit.Src.Util
{
    public class WpfTabControl : TabControl
    {
        static WpfTabControl()
        {
            FrameworkElement.DefaultStyleKeyProperty.OverrideMetadata(typeof(WpfTabControl), new FrameworkPropertyMetadata(typeof(WpfTabControl)));
        }
    }
}
