using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows;

namespace SEMITestApp.Src.Util
{
    public class WpfTabItem : TabItem
    {
        public static readonly DependencyProperty TabItemCheckedProperty = DependencyProperty.Register(
                                "TabItemChecked",
                                typeof(bool),
                                typeof(WpfTabItem),
                                new FrameworkPropertyMetadata(false, FrameworkPropertyMetadataOptions.None, OnTabItemCheckedPropertyChangedCallback));

        private static void OnTabItemCheckedPropertyChangedCallback(DependencyObject dependencyObject, DependencyPropertyChangedEventArgs e)
        {
            var item = dependencyObject as WpfTabItem;
            if (item != null)
            {
                //item.TabItemChecked = (bool)e.NewValue;
                //var chkBox = item.FindName("chkHeader") as CheckBox;
                //if (null != chkBox) chkBox.IsChecked = (bool)e.NewValue;
                //item.IsSelected = true;
            }
        }

        public bool TabItemChecked
        {
            get { return (bool)GetValue(TabItemCheckedProperty); }
            set { SetValue(TabItemCheckedProperty, value); }
        }

        public static readonly DependencyProperty TabItemEnabledProperty = DependencyProperty.Register(
                        "TabItemEnabled",
                        typeof(bool),
                        typeof(WpfTabItem),
                        new FrameworkPropertyMetadata(true, FrameworkPropertyMetadataOptions.None, OnTabItemEnabledPropertyChangedCallback));

        private static void OnTabItemEnabledPropertyChangedCallback(DependencyObject dependencyObject, DependencyPropertyChangedEventArgs e)
        {
            var item = dependencyObject as WpfTabItem;
            if (item != null)
            {
                //item.TabItemChecked = (bool)e.NewValue;
                //var chkBox = item.FindName("chkHeader") as CheckBox;
                //if (null != chkBox) chkBox.IsChecked = (bool)e.NewValue;
            }
        }

        public bool TabItemEnabled
        {
            get { return (bool)GetValue(TabItemEnabledProperty); }
            set { SetValue(TabItemEnabledProperty, value); }
        }
    }
}
