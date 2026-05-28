using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Input;

namespace SEMIDevelopKit.Src.Util
{
    /// <summary>
    /// IDCToggleButton.xaml 的交互逻辑
    /// </summary>
    public partial class WpfToggleButton : System.Windows.Controls.Primitives.ToggleButton
    {
        static WpfToggleButton()
        {
            FrameworkElement.DefaultStyleKeyProperty.OverrideMetadata(typeof(WpfToggleButton), new FrameworkPropertyMetadata(typeof(WpfToggleButton)));
        }
//         public static readonly DependencyProperty IsCheckedProperty =
//                    DependencyProperty.Register("IsChecked", typeof(bool), typeof(WpfToggleButton), new PropertyMetadata(default(bool), OnIsCheckedChanged));
//         public event RoutedEventHandler Checked;
//         public event RoutedEventHandler UnChecked;
//         public bool IsChecked
//         {
//             get { return (bool)GetValue(IsCheckedProperty); }
//             set { SetValue(IsCheckedProperty, value); }
//         }
//         public WpfToggleButton()
//         {
//             InitializeComponent();
//         }
//         private static void OnIsCheckedChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
//         {
//             (obj as WpfToggleButton).OnIsCheckedChanged(args);
//         }
//         private void OnIsCheckedChanged(DependencyPropertyChangedEventArgs args)
//         {
//             fillRectangle.Visibility = IsChecked ? Visibility.Visible : Visibility.Collapsed;
//             slideBorder.HorizontalAlignment = IsChecked ? HorizontalAlignment.Right : HorizontalAlignment.Left;
//             if (IsChecked && Checked != null)
//             {
//                 Checked(this, new RoutedEventArgs());
//             }
//             if (!IsChecked && UnChecked != null)
//             {
//                 UnChecked(this, new RoutedEventArgs());
//             }
//         }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs args)
        {
            args.Handled = true;
            IsChecked ^= true;
            //SetValue(IsCheckedProperty, !IsChecked);
            base.OnMouseLeftButtonUp(args);
        }
    }
}
