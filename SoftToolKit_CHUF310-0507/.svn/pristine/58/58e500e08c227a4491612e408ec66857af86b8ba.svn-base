using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
//using sz_value_pair = System.Collections.Generic.KeyValuePair<SRange, int>;
using System.Windows.Shapes;
using System.Windows.Input;
using sz_value_pair = SEMI.Util.TripleStore;
using System.Threading;

namespace SEMI.Util
{
    public class Identity
    {
        public int id { get; set; }
    }
    public class TripleStore
    {
        public Identity identify { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
    }
    public class WpfLineChart : Grid
    {
        private Brush[] brushes = new Brush[]
            {
                Brushes.Orange,
                Brushes.Pink,
                Brushes.Purple,
                Brushes.Tan,
                Brushes.Green,
            };
        private readonly Grid _gridTextH = new Grid();
        private readonly Grid _gridTextV = new Grid();
        private readonly Canvas _gridContent = new Canvas();
        private readonly Thickness _viewPortPad = new Thickness(38, 0, 0, 25);
        private const int hStep = 20;
        private const int vStep = 20;
        private System.Windows.Media.Brush _defaultBrush = new SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#FF22B484"));

        public int X_Min
        {
            get { return (int)GetValue(X_MinProperty); }
            set { SetValue(X_MinProperty, value); }
        }

        public static readonly DependencyProperty X_MinProperty = DependencyProperty.Register("X_Min", typeof(int), typeof(WpfLineChart), new PropertyMetadata(0, OnXMinPropertyChanged));

        private static void OnXMinPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;
            //chart.X_Min = (int)e.NewValue;
            chartView.InvalidateVisual();
        }

        public int X_Max
        {
            get { return (int)GetValue(X_MaxProperty); }
            set { SetValue(X_MaxProperty, value); }
        }

        public static readonly DependencyProperty X_MaxProperty = DependencyProperty.Register("X_Max", typeof(int), typeof(WpfLineChart), new PropertyMetadata(0, OnXMaxPropertyChanged));

        private static void OnXMaxPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;
            //chart.X_Min = (int)e.NewValue;
            chartView.InvalidateVisual();
        }

        public int Y_Min
        {
            get { return (int)GetValue(Y_MinProperty); }
            set { SetValue(Y_MinProperty, value); }
        }

        public static readonly DependencyProperty Y_MinProperty = DependencyProperty.Register("Y_Min", typeof(int), typeof(WpfLineChart), new PropertyMetadata(0, OnYMinPropertyChanged));

        private static void OnYMinPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;
            //chart.X_Min = (int)e.NewValue;
            chartView.InvalidateVisual();
        }

        public int Y_Max
        {
            get { return (int)GetValue(Y_MaxProperty); }
            set { SetValue(Y_MaxProperty, value); }
        }

        public static readonly DependencyProperty Y_MaxProperty = DependencyProperty.Register("Y_Max", typeof(int), typeof(WpfLineChart), new PropertyMetadata(0, OnYMaxPropertyChanged));

        private static void OnYMaxPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;
            //chart.X_Min = (int)e.NewValue;
            chartView.InvalidateVisual();
        }

        public Boolean BreakDown
        {
            get { return (Boolean)GetValue(BreakDownProperty); }
            set { SetValue(BreakDownProperty, value); }
        }

        public Boolean Sync { get; set; }

        public static readonly DependencyProperty BreakDownProperty = DependencyProperty.Register("BreakDown", typeof(Boolean), typeof(WpfLineChart), new PropertyMetadata(false, OnBreakDownPropertyChanged));

        private static void OnBreakDownPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;

            if (chartView.BreakDown)
            {
                if (chartView.ItemsSource.Count > 0)
                {
                    List<sz_value_pair> lsCopy = new List<sz_value_pair>(chartView.ItemsSource);
                    chartView.ItemsCollectQueue.Enqueue(lsCopy);
                    chartView.ItemsSource.Clear();
                }
            }
            else
            {

            }
        }

        public Boolean Clean
        {
            get { return (Boolean)GetValue(CleanProperty); }
            set { SetValue(CleanProperty, value); }
        }

        public static readonly DependencyProperty CleanProperty = DependencyProperty.Register("Clean", typeof(Boolean), typeof(WpfLineChart), new PropertyMetadata(false, OnCleanPropertyChanged));

        private static void OnCleanPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;

            if (chartView.Clean)
            {
                chartView._gridContent.Children.Clear();
                chartView.ItemsCollectQueue.Clear();
                chartView.ItemsSource.Clear();
                chartView.InvalidateVisual();
            }
            else
            {

            }
        }

        public Boolean SpeedUp
        {
            get { return (Boolean)GetValue(SpeedUpProperty); }
            set { SetValue(SpeedUpProperty, value); }
        }

        public static readonly DependencyProperty SpeedUpProperty = DependencyProperty.Register("SpeedUp", typeof(Boolean), typeof(WpfLineChart), new PropertyMetadata(false, OnSpeedUpPropertyChanged));

        private static void OnSpeedUpPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;

            if (chartView.SpeedUp)
            {
                chartView.Children.Remove(chartView._gridContent);
            }
            else
            {
                chartView.Children.Add(chartView._gridContent);
            }
        }

        public Identity SelIdentity
        {
            get { return (Identity)GetValue(SelIdentityProperty); }
            set { SetValue(SelIdentityProperty, value); }
        }

        public static readonly DependencyProperty SelIdentityProperty = DependencyProperty.Register("SelIdentity", typeof(Identity), typeof(WpfLineChart), new PropertyMetadata(null, OnCurSelChanged));

        private static void OnCurSelChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;
        }

        public TripleStore LatestPair
        {
            get { return (TripleStore)GetValue(LatestPairProperty); }
            set { SetValue(LatestPairProperty, value); }
        }

        public static readonly DependencyProperty LatestPairProperty = DependencyProperty.Register("LatestPair", typeof(TripleStore), typeof(WpfLineChart), new PropertyMetadata(new TripleStore(), OnLatestPairPropertyChanged));

        private static void OnLatestPairPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chart = d as WpfLineChart;
            if (null == chart) return;

            TripleStore pt = (TripleStore)e.NewValue;
            chart.OnNewDataArrive(pt);
        }

        public static readonly DependencyProperty ItemsSourceProperty = DependencyProperty.Register("ItemsSource", typeof(List<sz_value_pair>), typeof(WpfLineChart), new PropertyMetadata(new List<sz_value_pair>(), OnItemsSourcePropertyChanged));

        public List<sz_value_pair> ItemsSource
        {
            get { return (List<sz_value_pair>)GetValue(ItemsSourceProperty); }
            set { SetValue(ItemsSourceProperty, value); }
        }

        private static void OnItemsSourcePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;

            if (null == chartView) return;

            chartView.OnItemsSourceChange((List<sz_value_pair>)e.NewValue);
        }

        public static readonly DependencyProperty ItemsCollectProperty = DependencyProperty.Register("ItemsCollect", typeof(Queue<List<sz_value_pair>>), typeof(WpfLineChart), new PropertyMetadata(new Queue<List<sz_value_pair>>(), OnItemsCollectPropertyChanged));

        ///private IEnumerable<sz_value_pair> ItemsDisplayed = new List<sz_value_pair>();

        private Queue<List<sz_value_pair>> ItemsCollectQueue = new Queue<List<sz_value_pair>>();
        //private List<sz_value_pair> ItemsSource = new List<sz_value_pair>();

        public List<sz_value_pair> ItemsCollect
        {
            get { return (List<sz_value_pair>)GetValue(ItemsCollectProperty); }
            set { SetValue(ItemsCollectProperty, value); }
        }

        public static List<sz_value_pair> GetItemSource(DependencyObject d)
        {
            return (List<sz_value_pair>)d.GetValue(ItemsCollectProperty);
        }

        public static void SetItemSource(DependencyObject d, List<sz_value_pair> value)
        {
            d.SetValue(ItemsCollectProperty, value);
        }

        private static void OnItemsCollectPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfLineChart chartView = d as WpfLineChart;

            if (null == chartView) return;

            chartView.OnItemsCollectChange((Queue<List<sz_value_pair>>)e.NewValue);

//             if (null == chartView.ItemsSource) return;
//             if (0 == chartView.ItemsSource.Count()) return;
 
//              chartView.DrawVTextCollection();
//              chartView.DrawCoordinate();
//              chartView.DrawHTextCollection();

//            chartView.InvalidateVisual();
        }

        public WpfLineChart()
        {
            //X_Min = 0x0239;
            //X_Max = 0x0272;
            //Y_Min = 1500;
            //Y_Max = 1570;


            this.Children.Add(_gridTextV);
            this.Children.Add(_gridTextH);
            this.Children.Add(_gridContent);
        }

        protected override void OnRender(DrawingContext dc)
        {
            //UpDateCoordinate();
            //DrawHTextCollection();
            //UpDateTextLable();

            DrawVTextCollection();
            DrawHTextCollection();
            DrawDataCollection();

            base.OnRender(dc);
        }

        public void OnItemsSourceChange(List<sz_value_pair> newItems)
        {
            if (Clean) Clean = false;
            if (BreakDown) BreakDown = false;

            ItemsCollectQueue.Enqueue(newItems);

            int lineCnt = ItemsCollectQueue.Count();
            DrawOneDataLine(newItems, brushes[lineCnt % 5], true);

            Sync = false;
        }

        public void OnItemsCollectChange(Queue<List<sz_value_pair>> newItems)
        {
            if (Clean) Clean = false;
            if (BreakDown) BreakDown = false;

            ItemsCollectQueue = newItems;
        }

        public void OnNewDataArrive(sz_value_pair item)
        {
            if (Clean) Clean = false;
            if (BreakDown) BreakDown = false;

            int diameter = 5;
            double x = 0, y = 0;
            PointToCoordinate(item.X, item.Y, diameter, ref x, ref y);

            Ellipse ellipse = new Ellipse()
            {
                Tag = item,
                Width = diameter,
                Height = diameter,
                Fill = Brushes.Red,
                ToolTip = new ToolTip() { Content = string.Format("{0},{1}", (int)item.X, item.Y) },
            };
            Canvas.SetLeft(ellipse, x - diameter / 2);
            Canvas.SetTop(ellipse, y - diameter / 2);
            ellipse.MouseEnter += Hist_MouseEnter;
            ellipse.MouseLeave += Hist_MouseLeave;
            ellipse.MouseLeftButtonDown += path_MouseLeftButtonDown;

            _gridContent.Children.Add(ellipse);

            ItemsSource.Add(item);



//             ItemsSource.Add(pair);
// 
//             double diameter = 5;
//             _gridContent.Children.Clear();
//             _gridContent.Margin = new Thickness(_viewPortPad.Left, 0, 0, _viewPortPad.Bottom);
// 
//             var polyline = new Polyline();
//             foreach (var item in ItemsSource)
//             {
//                 double x = 0, y = 0;
//                 PointToCoordinate(item.Key, item.Value, ref x, ref y);
//                 polyline.Points.Add(new Point(x, y));
//                 polyline.Stroke = Brushes.Blue;
// 
//                 Ellipse ellipse = new Ellipse()
//                 {
//                     Width = diameter,
//                     Height = diameter,
//                     Fill = Brushes.Red,
//                 };
//                 Canvas.SetLeft(ellipse, x - diameter / 2);
//                 Canvas.SetTop(ellipse, y - diameter / 2);
//                 ellipse.MouseEnter += Hist_MouseEnter;
//                 ellipse.MouseLeave += Hist_MouseLeave;
// 
//                 _gridContent.Children.Add(ellipse);
//             }
// 
//             _gridContent.Children.Add(polyline);
        }

        void Hist_MouseEnter(object sender, MouseEventArgs e)
        {
            var ellipse = sender as Ellipse;
            if (null == ellipse) return;

            double diameter = 10, oldDiameter = ellipse.Width;

            ellipse.Width = diameter;
            ellipse.Height = diameter;

            double x = Canvas.GetLeft(ellipse);
            double y = Canvas.GetTop(ellipse);

            Canvas.SetLeft(ellipse, x + oldDiameter / 2 - diameter / 2);
            Canvas.SetTop(ellipse, y + oldDiameter / 2 - diameter / 2);
        }

        void Hist_MouseLeave(object sender, MouseEventArgs e)
        {
            var ellipse = sender as Ellipse;
            if (null == ellipse) return;

            double diameter = 5, oldDiameter = ellipse.Width;

            ellipse.Width = diameter;
            ellipse.Height = diameter;

            double x = Canvas.GetLeft(ellipse);
            double y = Canvas.GetTop(ellipse);

            Canvas.SetLeft(ellipse, x + oldDiameter / 2 - diameter / 2);
            Canvas.SetTop(ellipse, y + oldDiameter / 2 - diameter / 2);
        }

       // Point pos = new Point();
        void path_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Ellipse ellipse = sender as Ellipse;
            sz_value_pair pairVal = ellipse.Tag as sz_value_pair;

            if (null != pairVal)
            {
                SelIdentity = pairVal.identify;
            }
            //int etag = (int)ellipse.Tag;
            //CurSel = ItemsSource.FindIndex((t) =>
            //{
            //    return (int)t.X == etag ? true : false;
            //});
        }

        void path_MouseMove(object sender, MouseEventArgs e)
        {

        }

        void path_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
        }

        void path_PreKeyDown(object sender, KeyEventArgs e)
        {
        }

        IEnumerable<int> GetHTextCollection()
        {
            int step = Math.Max(1, (X_Max - X_Min) / hStep);
            //int step = (X_Max - X_Min + 1) / hStep;
            IList<int> lsHText = new List<int>();
            for (int s = X_Min; s <= X_Max; s += step)
            {
                lsHText.Add(s);
            }

            return lsHText;
        }

        void DrawHTextCollection()
        {
            _gridTextH.RowDefinitions.Clear();
            _gridTextH.ColumnDefinitions.Clear();
            _gridTextH.Children.Clear();
            _gridTextH.Margin = new Thickness(_viewPortPad.Left, 0, 0, 0);

            IEnumerable<int> hTextList = GetHTextCollection();

            _gridTextH.RowDefinitions.Add(new RowDefinition()
            {
                Height = new GridLength(1, GridUnitType.Star),
            });
            _gridTextH.RowDefinitions.Add(new RowDefinition()
            {
                Height = new GridLength(_viewPortPad.Bottom, GridUnitType.Pixel),
            });

            foreach (var item in hTextList)
            {
                var textblock = new TextBlock()
                {
                    Text = string.Format("{0,4:D}", item),
                    HorizontalAlignment = HorizontalAlignment.Left,
                    VerticalAlignment = VerticalAlignment.Top,
                    TextAlignment = TextAlignment.Left,
                    Margin = new Thickness(0, 2, 0, 0),
                };

//                 Border border = new Border()
//                 {
//                     BorderBrush = new SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#FFc0c0c0")),
//                     BorderThickness = new Thickness(0, 0, 0, 10),
//                     HorizontalAlignment = HorizontalAlignment.Center,
//                 };

                _gridTextH.Children.Add(textblock);
                //_gridTextH.Children.Add(border);
                _gridTextH.ColumnDefinitions.Add(new ColumnDefinition());
                Grid.SetRow(textblock, 1);
                Grid.SetColumn(textblock, _gridTextH.ColumnDefinitions.Count - 1);
                //Grid.SetRow(border, 0);
                //Grid.SetColumn(border, _gridTextH.ColumnDefinitions.Count - 1);

            }
        }

        IEnumerable<int> GetVTextCollection()
        {
            int step = Math.Max(1, (Y_Max - Y_Min) / hStep);
            IList<int> lsVText = new List<int>();
            for (int s = Y_Min; s <= Y_Max; s += step)
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

            //_gridTextV.Background = Brushes.Yellow;

            _gridTextV.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(_viewPortPad.Left, GridUnitType.Pixel)
            });
            _gridTextV.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(1, GridUnitType.Star)
            });

            IEnumerable<int> vTextList = GetVTextCollection();

            foreach (var item in vTextList)
            {
                var textblock = new TextBlock()
                {
                    Text = string.Format("{0,4:D}", item),
                    HorizontalAlignment = HorizontalAlignment.Right,
                    VerticalAlignment = VerticalAlignment.Bottom,
                    TextAlignment = TextAlignment.Right,
                    Margin = new Thickness(0, 0, 5, 0),
                };
                Border border = new Border()
                {
                    BorderBrush = new SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString("#FFc0c0c0")),
                    BorderThickness = new Thickness(0, 0, 0, 1),
                    VerticalAlignment = VerticalAlignment.Bottom,
                };

                _gridTextV.Children.Add(textblock);
                _gridTextV.Children.Add(border);
                _gridTextV.RowDefinitions.Add(new RowDefinition());
                Grid.SetRow(textblock, _gridTextV.RowDefinitions.Count - 1);
                Grid.SetColumn(border, 1);
                Grid.SetRow(border, _gridTextV.RowDefinitions.Count - 1);
            }  
        }

        private void PointToCoordinate(double px, double py, double diameter, ref double x, ref double y)
        {
            double real_x = (ActualWidth - _viewPortPad.Left);
            //double real_y = (ActualHeight - _viewPortPad.Bottom);
            double real_y = (ActualHeight - _viewPortPad.Bottom) * (vStep - 1) / vStep;

            x = real_x * (px - X_Min) / (X_Max - X_Min);
            y = (ActualHeight - _viewPortPad.Bottom - diameter / 2) - real_y * (py - Y_Min) / (Y_Max - Y_Min);
        }

        void DrawOneDataLine(List<sz_value_pair> itemsSource, Brush brush, Boolean notify, Boolean eclips = true)
        {
            double diameter = 5;
            var polyline = new Polyline();
            foreach (var item in itemsSource)
            {
                double x = 0, y = 0;
                PointToCoordinate(item.X, item.Y, diameter, ref x, ref y);

                polyline.Points.Add(new Point(x, y));
                polyline.Stroke = brush;

                if (eclips)
                {
                    Ellipse ellipse = new Ellipse()
                    {
                        Tag = item,
                        Width = diameter,
                        Height = diameter,
                        Fill = Brushes.Red,
                        ToolTip = new ToolTip() { Content = string.Format("{0},{1}", (int)item.X, item.Y) },
                    };
                    Canvas.SetLeft(ellipse, x - diameter / 2);
                    Canvas.SetTop(ellipse, y - diameter / 2);
                    ellipse.MouseEnter += Hist_MouseEnter;
                    ellipse.MouseLeave += Hist_MouseLeave;
                    if (notify)
                    {
                        ellipse.MouseLeftButtonDown += path_MouseLeftButtonDown;
                    }

                    _gridContent.Children.Add(ellipse);
                }
            }

            _gridContent.Children.Add(polyline);
        }

        void DrawDataCollection()
        {
            //sz_value_pair lastPair = ;
            
            _gridContent.Children.Clear();
            _gridContent.Margin = new Thickness(_viewPortPad.Left, 0, 0, _viewPortPad.Bottom);

            DrawOneDataLine(ItemsSource, Brushes.Blue, true);

            int index = 0;
            foreach (var item in ItemsCollectQueue)
            {
                DrawOneDataLine(item, brushes[++index % 5], true);
            }
        }
    }
}
