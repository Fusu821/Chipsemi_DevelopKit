using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
using sz_value_pair = System.Collections.Generic.KeyValuePair<SRange, int>;
using System.Windows.Shapes;
using System.Windows.Input;
public class SRange
{
    public int CPosition { get; set; }
    public double Left { get; set; }
    public double Right { get; set; }

    public SRange(double val, double step = 0)
    {
        CPosition = (int)val;
        Left = val - step / 2;
        Right = val + step / 2;
    }

    public bool InRange(int minVal, int maxVal)
    {
        //return (CPosition >= minVal && CPosition <= maxVal) || (Left >= minVal && Right < maxVal);
        if (Math.Max(minVal, Left) <= Math.Min(maxVal, Right - 0.00001))
            return true;
        else
            return false;
    }

    public override string ToString()
    {
        return CPosition.ToString();
    }
}
namespace SEMI.Util
{
    public class WpfHistogram : Grid
    {
        private readonly Canvas _gridTextH = new Canvas();
        private readonly Grid _gridTextV = new Grid();
        private readonly Grid _gridContent = new Grid();
        private readonly Thickness _viewPortPad = new Thickness(25, 0, 0, 25);
        private enum TextBlock_type { TextBlock_null = -2, TextBlock_Left = -1, TextBlock_Right = 1, TextBlock_Max = 0, TextBlock_Ratio = 2 }
        private System.Windows.Media.Brush _defaultBrush = new SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#FF22B484"));

        private int _chartMaxNumber = 50;
        public  int TotalNumber { get; private set; }

        public int RuleFactor { get; set; }

        public int X_Min { private get; set; }
        public int X_Max { private get; set; }

        public int XLeft
        {
            get {return (int)GetValue(XLeftProperty);}
            set { if (value != XLeft) { SetValue(XLeftProperty, value); } }
        }
        public int XRight
        {
            get { return (int)GetValue(XRightProperty); }
            set { if (value != XRight) { SetValue(XRightProperty, value); } }
        }

        public static readonly DependencyProperty XLeftProperty = DependencyProperty.Register("XLeft", typeof(int), typeof(WpfHistogram), new FrameworkPropertyMetadata(-300) { BindsTwoWayByDefault = true });
        //public static readonly DependencyProperty XRightProperty = DependencyProperty.Register("XRight", typeof(int), typeof(WpfHistogram), new FrameworkPropertyMetadata(100) { BindsTwoWayByDefault = true });

        public static readonly DependencyProperty XRightProperty = DependencyProperty.Register("XRight", typeof(int), typeof(WpfHistogram), new PropertyMetadata(100, OnXRightPropertyChanged));

        public static readonly DependencyProperty ItemsSourceProperty = DependencyProperty.Register("ItemsSource", typeof(IEnumerable<sz_value_pair>), typeof(WpfHistogram), new PropertyMetadata(new List<sz_value_pair>(), OnItemsSourcePropertyChanged));

        public IEnumerable<sz_value_pair> ItemsSource
        {
            get { return (List<sz_value_pair>)GetValue(ItemsSourceProperty); }
            set { SetValue(ItemsSourceProperty, value); }
        }

        private static void OnXRightPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfHistogram histogram = d as WpfHistogram;
            histogram.UpDateTextLable(TextBlock_type.TextBlock_Right);
            
        }

        public static IEnumerable<sz_value_pair> GetItemSource(DependencyObject d)
        {
            return (IEnumerable<sz_value_pair>)d.GetValue(ItemsSourceProperty);
        }

        public static void SetItemSource(DependencyObject d, IEnumerable<sz_value_pair> value)
        {
            d.SetValue(ItemsSourceProperty, value);
        }

        private static void OnItemsSourcePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfHistogram histView = d as WpfHistogram;
            //IEnumerable<sz_value_pair> histData = e.NewValue as IEnumerable<sz_value_pair>;
            //new to be add
            //if (null != histView) histView.InvalidateVisual();

            if (null == histView) return;
            if (null == histView.ItemsSource) return;
            if (0 == histView.ItemsSource.Count()) return;

            histView.X_Min = histView.ItemsSource.Min(o => o.Key.CPosition);
            histView.X_Max = histView.ItemsSource.Max(o => o.Key.CPosition);
            histView.TotalNumber = histView.ItemsSource.Sum(o => o.Value);
            if (histView.X_Min == histView.X_Max)
            {
                histView.X_Min = -10;
                histView.X_Max = 10;
            }

            histView.DrawVTextCollection();
            histView.DrawCoordinate();
            histView.DrawHTextCollection();

            histView.InvalidateVisual();
        }

        public WpfHistogram()
        {
            //_gridTextV.Background = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            //_gridTextH.Background = new SolidColorBrush(Color.FromRgb(0, 150, 200));
            //_gridContent.Background = new SolidColorBrush(Color.FromRgb(0, 0, 255));
            RuleFactor = 1;
            X_Max = 10;
            X_Min = -10;

            this.Children.Add(_gridTextV);
            this.Children.Add(_gridTextH);
            this.Children.Add(_gridContent);

            _gridTextH.Margin = new Thickness(_viewPortPad.Left, 0, 0, 0);

            this.MouseEnter += Hist_MouseEnter;
            this.MouseLeave += Hist_MouseLeave;
        }

        private void HistRuleEual(TextBlock_type moveType)
        {
            int tmpLeft = XLeft;
            int tmpRight = XRight;

            if (moveType == TextBlock_type.TextBlock_Right)
                XLeft = RuleFactor * tmpRight;
            else if (moveType == TextBlock_type.TextBlock_Left)
                XRight = tmpLeft / RuleFactor;
            else
                XLeft = RuleFactor * tmpRight;
        }

        protected override void OnRender(DrawingContext dc)
        {
            UpDateCoordinate();
            //DrawHTextCollection();
            UpDateTextLable();

            base.OnRender(dc);
        }

        private void UpDateTextLable(TextBlock_type moveType = TextBlock_type.TextBlock_null)
        {
            HistRuleEual(moveType);

            double dwLeft = HistToPosition(XLeft);
            double dwRight = HistToPosition(XRight);

            foreach (var item in _gridTextH.Children)
            {
                if (null != item as TextBlock)
                {
                    TextBlock tb = item as TextBlock;
                    if (TextBlock_type.TextBlock_Right == (TextBlock_type)tb.Tag)
                    {
                        tb.Text = XRight.ToString();
                        tb.SetValue(Canvas.LeftProperty, dwRight - 25);
                    }
                    else if (TextBlock_type.TextBlock_Left == (TextBlock_type)tb.Tag)
                    {
                        tb.Text = XLeft.ToString();
                        tb.SetValue(Canvas.LeftProperty, dwLeft - 25);
                    }
                    else if (TextBlock_type.TextBlock_Ratio == (TextBlock_type)tb.Tag)
                    {
                        tb.Text = string.Format("{0:P2}", CalcRatio());
                    }
                }
                else if (null != item as Path)
                {
                    Path path = item as Path;
                    LineGeometry line = path.Data as LineGeometry;

                    if (TextBlock_type.TextBlock_Right == (TextBlock_type)path.Tag)
                    {
                        //line.StartPoint = new Point(dwRight, ActualHeight * 0.8);
                        line.StartPoint = new Point(dwRight, ActualHeight - _viewPortPad.Bottom);
                        line.EndPoint = new Point(dwRight, _viewPortPad.Bottom);
                    }
                    else if (TextBlock_type.TextBlock_Left == (TextBlock_type)path.Tag)
                    {
                        //line.StartPoint = new Point(dwLeft, ActualHeight * 0.8);
                        line.StartPoint = new Point(dwLeft, ActualHeight - _viewPortPad.Bottom);
                        line.EndPoint = new Point(dwLeft, _viewPortPad.Bottom);
                    }
                }
            }
        }

        private double HistToPosition(int histVal)
        {
            double dw = (_gridTextH.ActualWidth) * (histVal - X_Min) / (X_Max - X_Min);
            return (_gridTextH.ActualWidth) * (histVal - X_Min) / (X_Max - X_Min);
        }

        private int PositionToHist(double dwPositon = 0)
        {
            return (int)(dwPositon / _gridTextH.ActualWidth * (X_Max - X_Min) + X_Min);
        }

        private double CalcRatio()
        {
            int iLeft = XLeft, iRight = XRight;
            if (iLeft == iRight) iLeft = 0;
            int calcSum = ItemsSource.Sum(o => o.Key.InRange(iLeft, iRight) ? o.Value : 0);

            return (double)calcSum / TotalNumber;
        }

        void Hist_MouseEnter(object sender, MouseEventArgs e)
        {
            if (sender != this) return;
            foreach (var item in _gridTextH.Children)
            {
                Path tmp = item as Path;
                if (null == tmp) continue;
                tmp.StrokeThickness = 3;
            }
            e.Handled = true;
        }

        void Hist_MouseLeave(object sender, MouseEventArgs e)
        {
            foreach (var item in _gridTextH.Children)
            {
                Path tmp = item as Path;
                if (null == tmp) continue;
                tmp.StrokeThickness = 0.5;
            }
            e.Handled = true;
        }

       // Point pos = new Point();
        void path_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            //pos = e.GetPosition(null);
            var tmp = sender as Path;
            tmp.CaptureMouse();
            tmp.Cursor = Cursors.Hand;

            tmp.Focus();

            e.Handled = true;
        }

        void path_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                Path tmp = (Path)sender;

                if (TextBlock_type.TextBlock_Right == (TextBlock_type)tmp.Tag)
                {
                    XRight = PositionToHist(e.GetPosition(_gridTextH).X);
                }
                else if (TextBlock_type.TextBlock_Left == (TextBlock_type)tmp.Tag)
                {
                    XLeft = PositionToHist(e.GetPosition(_gridTextH).X);
                }

                UpDateTextLable((TextBlock_type)tmp.Tag);

                e.Handled = true;
            }

        }

        void path_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Path tmp = (Path)sender;
            tmp.ReleaseMouseCapture();

            tmp.Focus();

            e.Handled = true;
        }

        void path_PreKeyDown(object sender, KeyEventArgs e)
        {
            Path tmp = (Path)sender;
            //LineGeometry line = tmp.Data as LineGeometry;

            int xShift = Key.Right == e.Key ? 1 : (Key.Left == e.Key ? - 1 : 0);

            if (TextBlock_type.TextBlock_Right == (TextBlock_type)tmp.Tag)
                XRight += xShift;
            else if (TextBlock_type.TextBlock_Left == (TextBlock_type)tmp.Tag)
                XLeft += xShift;

            UpDateTextLable((TextBlock_type)tmp.Tag);

            e.Handled = true;
        }

        void DrawHTextCollection()
        {
            if(ItemsSource.Count() <= 0) return;

            _gridTextH.Children.Clear();
            //_gridTextH.SetValue(Grid.MarginProperty, new Thickness(_viewPortPad.Left, 0, 0, 0));
            int maxHistVal = ItemsSource.FirstOrDefault(o => o.Value == _chartMaxNumber).Key.CPosition;

            //left line
            {
                TextBlock tb = new TextBlock() { Text = XLeft.ToString(), Tag = TextBlock_type.TextBlock_Left, Width = 50 };
                tb.SetValue(Canvas.BottomProperty, _viewPortPad.Bottom - 15);
                tb.TextAlignment = TextAlignment.Center;
                _gridTextH.Children.Add(tb);

                LineGeometry line = new LineGeometry();
                var path = new Path()
                {
                    Stroke = Brushes.Blue,
                    StrokeThickness = 0.5,
                    Data = line,
                    Focusable = true,
                    Tag = TextBlock_type.TextBlock_Left
                };

                path.MouseLeftButtonDown += path_MouseLeftButtonDown;
                path.MouseMove += path_MouseMove;
                path.MouseLeftButtonUp += path_MouseLeftButtonUp;
                path.PreviewKeyDown += path_PreKeyDown;

//                 path.MouseEnter += Hist_MouseEnter;
//                 path.MouseLeave += Hist_MouseLeave;

                _gridTextH.Children.Add(path);              
            }

            //right line
            {
                TextBlock tb = new TextBlock() { Text = XRight.ToString(), Tag = TextBlock_type.TextBlock_Right, Width = 50 };
                tb.SetValue(Canvas.BottomProperty, _viewPortPad.Bottom - 15);
                tb.TextAlignment = TextAlignment.Center;
                _gridTextH.Children.Add(tb);

                LineGeometry line = new LineGeometry();
                var path = new Path()
                {
                    Stroke = Brushes.Blue,
                    StrokeThickness = 0.5,
                    Data = line,
                    Focusable = true,
                    Tag = TextBlock_type.TextBlock_Right
                };

                path.MouseLeftButtonDown += path_MouseLeftButtonDown;
                path.MouseMove += path_MouseMove;
                path.MouseLeftButtonUp += path_MouseLeftButtonUp;
                path.PreviewKeyDown += path_PreKeyDown;

//                 path.MouseEnter += Hist_MouseEnter;
//                 path.MouseLeave += Hist_MouseLeave;

                _gridTextH.Children.Add(path);
            }


            //max
            {

                TextBlock tb = new TextBlock() { Text = maxHistVal.ToString(), Tag = TextBlock_type.TextBlock_Max, Width = 50, TextAlignment = TextAlignment.Center };
                tb.SetValue(Canvas.BottomProperty, _viewPortPad.Bottom - 15);
                tb.SetValue(Canvas.LeftProperty, HistToPosition(maxHistVal) - 25);
                _gridTextH.Children.Add(tb);
            }

            //rate
            {
                TextBlock tb = new TextBlock() { Foreground = Brushes.Blue, Tag = TextBlock_type.TextBlock_Ratio, Width = 50, TextAlignment = TextAlignment.Center };
                tb.SetValue(Canvas.TopProperty, _viewPortPad.Top + 3);
                tb.SetValue(Canvas.LeftProperty, ActualWidth / 2 - 25);
                _gridTextH.Children.Add(tb);
            }

            //UpDateTextLable();
        }

        IEnumerable<double> GetVTextCollection(int num = 5)
        {
            if (null == ItemsSource || ItemsSource.Count() == 0) return new List<double>() { 4,3,2,1,0};

            _chartMaxNumber = (int)ItemsSource.Max(o => o.Value);

            num = Math.Min(_chartMaxNumber, num);
            double step = (double)_chartMaxNumber / num;

            IList<double> lsVText = new List<double>();
            for (double s = 0; s < _chartMaxNumber; s += step)
            {
                lsVText.Add(s);
            }

            return lsVText.OrderByDescending(t => t);
        }

        void DrawVTextCollection()
        {
            _gridTextV.RowDefinitions.Clear();
            _gridTextV.Children.Clear();
            _gridTextV.ColumnDefinitions.Clear();
            _gridTextV.Margin = new Thickness(0, _viewPortPad.Top, 0, _viewPortPad.Bottom);
            _gridTextV.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(_viewPortPad.Left, GridUnitType.Pixel)
            });
            _gridTextV.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(1, GridUnitType.Star)
            });
            foreach (var v in GetVTextCollection())
            {
                TextBlock tb = new TextBlock()
                {
                    Text = v.ToString("0"),
                    Margin = new Thickness(0, 0, 5, 0),
                    HorizontalAlignment = HorizontalAlignment.Right,
                    VerticalAlignment = VerticalAlignment.Bottom
                };
                Border border = new Border()
                {
                    BorderBrush = new SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#FFc0c0c0")),
                    BorderThickness = new Thickness(0, 0, 0, 1),
                    VerticalAlignment = VerticalAlignment.Bottom
                };

                _gridTextV.Children.Add(tb);
                _gridTextV.Children.Add(border);
                _gridTextV.RowDefinitions.Add(new RowDefinition());
                Grid.SetRow(tb, _gridTextV.RowDefinitions.Count - 1);
                Grid.SetColumn(border, 1);
                Grid.SetRow(border, _gridTextV.RowDefinitions.Count - 1);
            }
        }

        void UpDateCoordinate()
        {
            var maxHeight = _gridContent.ActualHeight - _viewPortPad.Top - _viewPortPad.Bottom;
            var maxWidth = _gridContent.ActualWidth - _viewPortPad.Left;

            foreach( var item in _gridContent.Children)
            {
                var rectange = item as System.Windows.Shapes.Rectangle;
                if(null == rectange) continue;

                int val = (int)rectange.Tag;
                rectange.Height = maxHeight * val / _chartMaxNumber;
                rectange.Width = maxWidth / ItemsSource.Count();
            }
        }

        void DrawCoordinate()
        {
            _gridContent.ColumnDefinitions.Clear();
            _gridContent.RowDefinitions.Clear();
            _gridContent.Children.Clear();

            //_gridContent.Margin = new Thickness(_viewPortPad.Left, 0, 0, _viewPortPad.Bottom);
            _gridContent.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(_viewPortPad.Left, GridUnitType.Pixel)
            });
            _gridContent.RowDefinitions.Add(new RowDefinition()
            {
                Height = new GridLength(1, GridUnitType.Star)
            });
            _gridContent.RowDefinitions.Add(new RowDefinition()
            {
                Height = new GridLength(_viewPortPad.Bottom, GridUnitType.Pixel)
            });

            var maxHeight = _gridContent.ActualHeight - _viewPortPad.Top - _viewPortPad.Bottom;
            var maxWidth = _gridContent.ActualWidth - _viewPortPad.Left;

            var list = ItemsSource;
            foreach (var v in list)
            {
                System.Windows.Shapes.Rectangle rectangle = new System.Windows.Shapes.Rectangle()
                {
                    Fill = _defaultBrush,
                    Height = maxHeight * v.Value / _chartMaxNumber,
                    Width = maxWidth / list.Count() * 1,
                    VerticalAlignment = VerticalAlignment.Bottom,
                    Tag = v.Value,
                };

                _gridContent.Children.Add(rectangle);
                //var doubleAnimation = new DoubleAnimation(0, maxHeight * (v.Value / _chartMaxNumber),
                //    new Duration(new TimeSpan(0, 0, 0, 0, 1000)));

                //rectangle.BeginAnimation(Rectangle.HeightProperty, doubleAnimation);

                rectangle.Tag = v.Value;

                //if (v.Value == this._maxValue)
                //    rectangle.Fill = _maxValueBrush;

                //TextBlock tb = new TextBlock()
                //{
                //    Text = v.Value.ToString("f"),
                //    Margin = new Thickness(0, 0, 0, maxHeight * (v.Value / _chartMaxNumber) + 5),
                //    VerticalAlignment = VerticalAlignment.Bottom,
                //    HorizontalAlignment = HorizontalAlignment.Center,

                //};
                //_gridContent.Children.Add(tb);

                //var thicknessAnimation = new ThicknessAnimation(new Thickness(0, 0, 0, 0),
                //    new Thickness(0, 0, 0, maxHeight * (v.Value / _chartMaxNumber) + 5),
                //    new Duration(new TimeSpan(0, 0, 0, 0, 1000)));
                //tb.BeginAnimation(TextBlock.MarginProperty, thicknessAnimation);

                //rectangle.MouseEnter += Rectangle_MouseEnter;
                //rectangle.MouseLeave += Rectangle_MouseLeave;
                _gridContent.ColumnDefinitions.Add(new ColumnDefinition());
                Grid.SetColumn(rectangle, _gridContent.ColumnDefinitions.Count - 1);
                //Grid.SetColumn(tb, _gridContent.ColumnDefinitions.Count - 1);
            }
        }
    }
}
