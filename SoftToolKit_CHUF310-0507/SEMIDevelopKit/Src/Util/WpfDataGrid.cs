using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows;
using SEMI.Util;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Input;
using SelCoordinate = System.Tuple<int, int>;
using SMInvokeBridge;

namespace SEMIDevelopKit.Src.Util
{
    public class WpfDataGrid : Grid
    {
//         private readonly UniformGrid uniforGridLeft = new UniformGrid();
//         private readonly UniformGrid uniforGridTop = new UniformGrid();
//         private readonly UniformGrid uniforGridContent = new UniformGrid();

        public int[] backColorRule = new int[8 * 2];
        public int Reference
        {
            get { return (int)GetValue(ReferenceProperty);  }
            set { SetValue(ReferenceProperty, value); }
        }

        public static readonly DependencyProperty ReferenceProperty = DependencyProperty.Register("Reference", typeof(int), typeof(WpfDataGrid), new PropertyMetadata(12000, OnReferencePropertyChanged));
        private static void OnReferencePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDataGrid dataView = d as WpfDataGrid;
            dataView.Reference = (int)e.NewValue;

            int ruleHarfLevel = dataView.backColorRule.Length / 2;

            int[] colorLevel = new int[8] { 0x90FF90, 0x90EE90, 0xC1FFC1, 0xF0F8FF, 0xf4f4f4, 0xFFA07A, 0xFF7F50, 0xCD5C5C };

            for (int index = 0; index < dataView.backColorRule.Length; index += 2)
            {
                dataView.backColorRule[index] = dataView.Reference + 100 * (index - ruleHarfLevel);
                dataView.backColorRule[index + 1] = colorLevel[index / 2];
            }
        }

        public Boolean SelComplex
        {
            get { return (Boolean)GetValue(SelComplexProperty); }
            set { SetValue(SelComplexProperty, value); }
        }

        public static readonly DependencyProperty SelComplexProperty = DependencyProperty.Register("SelComplex", typeof(Boolean), typeof(WpfDataGrid), new PropertyMetadata(false, OnSelComplexPropertyChanged));

        private static void OnSelComplexPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDataGrid dataView = d as WpfDataGrid;
        }

        public SelCoordinate SelCoor
        {
            get { return (SelCoordinate)GetValue(SelCoorProperty); }
            set { SetValue(SelCoorProperty, value); }
        }

        public static readonly DependencyProperty SelCoorProperty = DependencyProperty.Register("SelCoor", typeof(SelCoordinate), typeof(WpfDataGrid), new PropertyMetadata(new SelCoordinate(0, 0), OnSelCoorPropertyPropertyChanged));

        private static void OnSelCoorPropertyPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDataGrid dataView = d as WpfDataGrid;

            SelCoordinate oldSel = e.OldValue as SelCoordinate;

            foreach (UniformGrid uniform in dataView.Children)
            {
                foreach (var item in uniform.Children)
                {
                    Border border = item as Border;
                    if (null == border) continue;
                    TextBlock tb = border.Child as TextBlock;
                    if (null == tb) continue;
                    if (null == tb.Tag) continue;

                    tb.Background = Brushes.White;
                }
            }

//             dataView.Children[]
// 
//             foreach (TextBlock item in dataView.uniformGridContent.Children)
//             {
//                 item.Background = new SolidColorBrush(Color.FromRgb(255, 0, 0));
//             }
        }

        public static readonly DependencyProperty MatrixSourceProperty = DependencyProperty.RegisterAttached("MatrixSource", 
            typeof(DataMatrix),
            typeof(WpfDataGrid),
            new FrameworkPropertyMetadata(null, new PropertyChangedCallback(OnMatrixSourceChanged)));

        public static DataMatrix GetMatrixSource(DependencyObject d)
        {
            return (DataMatrix)d.GetValue(MatrixSourceProperty);
        }

        public static void SetMatrixSource(DependencyObject d, DataMatrix value)
        {
            d.SetValue(MatrixSourceProperty, value);
        }

        protected void MouseMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            TextBlock text = sender as TextBlock;

            if (SelComplex)
            {
                SelCoor = text.Tag as SelCoordinate;
                text.Background = Brushes.Green;
            }

            

//             uniformGridContent.
// 
//             int etag = (int)ellipse.Tag;
//             CurSel = ItemsSource.FindIndex((t) =>
//             {
//                 return (int)t.X == etag ? true : false;
//             });
        }

        private static void OnMatrixSourceChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDataGrid contentGrid = d as WpfDataGrid;
            DataMatrix dataMatrix = e.NewValue as DataMatrix;
            if(null == dataMatrix) return;

            contentGrid.Children.Clear();
            contentGrid.RowDefinitions.Clear();
            contentGrid.ColumnDefinitions.Clear();
            contentGrid.RowDefinitions.Add(new RowDefinition()
            { 
                Height = new GridLength(20, GridUnitType.Pixel),
            });
            contentGrid.RowDefinitions.Add(new RowDefinition());

            contentGrid.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(46, GridUnitType.Pixel),
            });
            contentGrid.ColumnDefinitions.Add(new ColumnDefinition());

            UniformGrid uniformGridTop = new UniformGrid()
            {
                Rows = 1,
                Columns = dataMatrix.ColNumber,
            };
            uniformGridTop.SetValue(Grid.ColumnProperty, 1);
            contentGrid.Children.Add(uniformGridTop);

            UniformGrid uniformGridLeft = new UniformGrid()
            {
                Columns = 1,
                Rows = dataMatrix.RowNumber,
            };
            uniformGridLeft.SetValue(Grid.RowProperty, 1);
            contentGrid.Children.Add(uniformGridLeft);

            UniformGrid uniformGridContent = new UniformGrid()
            {
                Rows = dataMatrix.RowNumber,
                Columns = dataMatrix.ColNumber,
            };
            uniformGridContent.SetValue(Grid.RowProperty, 1);
            uniformGridContent.SetValue(Grid.ColumnProperty, 1);
            contentGrid.Children.Add(uniformGridContent);

            int centerRow = dataMatrix.RowNumber;
            if (dataMatrix.RowExp > 0)
            {
                if (MainViewModel.Intr.SelectedIC == eChipTypeList.SM_IC_7126)
                {
                    centerRow = centerRow - 3;
                }
                else
                {
                    centerRow--;
                }
             }
               
            int centerCol = dataMatrix.ColNumber;
            if (dataMatrix.ColExp > 0)
            {
                if (MainViewModel.Intr.SelectedIC == eChipTypeList.SM_IC_7126)
                {
                    centerCol = centerCol - 3;
                }
                else
                {
                    centerCol--;
                }
            }
            uniformGridLeft.Rows = dataMatrix.RowNumber;
            for (int iRow = 0; iRow < dataMatrix.RowNumber; iRow++)
            {
                uniformGridLeft.Children.Add(new TextBox()
                {
                    TextAlignment = TextAlignment.Center,
                    VerticalContentAlignment = VerticalAlignment.Center,
                    Text = iRow < centerRow ? ("Row" + (iRow /*+ 1*/).ToString("00")) : "EXP",
                    BorderThickness = new Thickness(0.5),
                    Background = new SolidColorBrush(Color.FromRgb(255, 232, 166)),
                    IsReadOnly = true,
                    //FontSize = contentGrid.fontsize,
                    //Height = 20,
                });
            }
            uniformGridTop.Columns = dataMatrix.ColNumber;
            for (int iCol = 0; iCol < dataMatrix.ColNumber; iCol++)
            {
                uniformGridTop.Children.Add(new TextBox()
                {
                    TextAlignment = TextAlignment.Center,
                    VerticalContentAlignment = VerticalAlignment.Center,
                    Text = iCol < centerCol ? ("Col" + (iCol /*+ 1*/).ToString("00")) : "EXP",
                    BorderThickness = new Thickness(0.5),
                    Background = new SolidColorBrush(Color.FromRgb(255, 232, 166)),
                    IsReadOnly = true,
                    //FontSize = contentGrid.fontsize,
                    //Width = 20,
                });
            }
            uniformGridContent.Rows = dataMatrix.RowNumber;
            uniformGridContent.Columns = dataMatrix.ColNumber;
            for (int iRow = 0; iRow < dataMatrix.RowNumber; iRow++)
            {
                for (int iCol = 0; iCol < dataMatrix.ColNumber; iCol++)
                {
                    Border br = new Border();
                    TextBlock tb = new TextBlock()
                    {
                        TextAlignment = TextAlignment.Center,
                        VerticalAlignment = VerticalAlignment.Center,
                        Margin = new Thickness(0.5),
                        Tag = new SelCoordinate(iRow, iCol),
                        //FontSize = contentGrid.fontsize,
                        //Height = 20,
                        //Width = 20,
                    };
                    Binding cellBind = new Binding()
                    {
                        Source = dataMatrix.Rows[iRow],
                        Path = new PropertyPath("Col" + (iCol /*+ 1*/).ToString("00")),
                    };
                    Binding backBind = new Binding()
                    {
                        Source = dataMatrix.Rows[iRow], 
                        Path = new PropertyPath("Col" + (iCol /*+ 1*/).ToString("00")),
                        Converter = new ValueToBackGroundConveter() { },
                        ConverterParameter = contentGrid.backColorRule,
                    };
                    tb.MouseLeftButtonDown += contentGrid.MouseMouseLeftButtonDown;
                    br.Child = tb;
                    tb.SetBinding(TextBlock.TextProperty, cellBind);
                    br.SetBinding(Border.BackgroundProperty, backBind);

                    uniformGridContent.Children.Add(br);
                }
            }

         

//             Grid targetDataGrid = d as Grid;
//             DataMatrix dataMatrix = e.NewValue as DataMatrix;
// 
//             targetDataGrid.Columns.Clear();
//             targetDataGrid.ItemsSource = null;
// 
//             if (null != dataMatrix)
//             {
//                 targetDataGrid.ItemsSource = dataMatrix.Rows;
// 
//                 int count = 0;
//                 foreach (var col in dataMatrix.Columns)
//                 {
//                     GridColumn textColumn = new GridColumn();
//                     textColumn.EditSettings = new DevExpress.Xpf.Editors.Settings.TextEditSettings() { };
//                     textColumn.Header = col.Name;
//                     textColumn.FieldName = col.Name;
//                     textColumn.Width = 50;
// 
//                     targetDataGrid.Columns.Add(textColumn);
//                     count++;
//                 }
//             }
        }
        // 缩放因子，控制每次缩放的幅度
        private const double ZoomFactor = 0.1;
        // 最小缩放比例
        private const double MinScale = 0.1;
        // 最大缩放比例
        private const double MaxScale = 5.0;
        private double zoom = 1;
        ScaleTransform scaleTransform;
        TranslateTransform translateTransform;
        //private void Grid_MouseWheel(object sender, MouseWheelEventArgs e)
        //{
        //    Point mousePosition = e.GetPosition((IInputElement)sender);

        //    double zoom = e.Delta > 0 ? 1 + ZoomFactor : 1 - ZoomFactor;

        //    double currentScaleX = scaleTransform.ScaleX;
        //    double currentScaleY = scaleTransform.ScaleY;

        //    double newScaleX = currentScaleX * zoom;
        //    double newScaleY = currentScaleY * zoom;

        //    newScaleX = Math.Max(MinScale, Math.Min(MaxScale, newScaleX));
        //    newScaleY = Math.Max(MinScale, Math.Min(MaxScale, newScaleY));

        //    double scaleRatioX = newScaleX / currentScaleX;
        //    double scaleRatioY = newScaleY / currentScaleY;

        //    translateTransform.X = (translateTransform.X - mousePosition.X) * scaleRatioX + mousePosition.X;
        //    translateTransform.Y = (translateTransform.Y - mousePosition.Y) * scaleRatioY + mousePosition.Y;

        //    scaleTransform.ScaleX = newScaleX;
        //    scaleTransform.ScaleY = newScaleY;
        //}
        private void Grid_MouseKeyDown(object sender, MouseButtonEventArgs e)
        {
            scaleTransform.ScaleX = 1;
            scaleTransform.ScaleY = 1;
            translateTransform.X = 0;
            translateTransform.Y = 0;
            zoom = 1;
        }
        public WpfDataGrid()
        {
            this.Background = new SolidColorBrush(Color.FromRgb(125, 125, 125));
            TransformGroup transformGroup = new TransformGroup();

            // 创建 ScaleTransform 对象并设置初始缩放比例
            scaleTransform = new ScaleTransform();
            scaleTransform.ScaleX = 1;
            scaleTransform.ScaleY = 1;

            // 创建 TranslateTransform 对象
            translateTransform = new TranslateTransform();

            // 将 ScaleTransform 和 TranslateTransform 添加到 TransformGroup 中
            transformGroup.Children.Add(scaleTransform);
            transformGroup.Children.Add(translateTransform);
            this.RenderTransform = transformGroup;

            //this.MouseWheel += new MouseWheelEventHandler(Grid_MouseWheel);
            this.MouseRightButtonDown += new MouseButtonEventHandler(Grid_MouseKeyDown);
            this.MouseLeftButtonDown += new MouseButtonEventHandler(WpfDataGrid_MouseLeftButtonDown);
            //this.MouseLeftButtonUp += new MouseButtonEventHandler(WpfDataGrid_MouseLeftButtonUp);
            //this.MouseMove += new MouseEventHandler(WpfDataGrid_MouseMove);

        }

        void WpfDataGrid_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Point mousePosition = e.GetPosition((IInputElement)sender);

            zoom = zoom - ZoomFactor;

            double currentScaleX = scaleTransform.ScaleX;
            double currentScaleY = scaleTransform.ScaleY;

            double newScaleX = currentScaleX * zoom;
            double newScaleY = currentScaleY * zoom;

            newScaleX = Math.Max(MinScale, Math.Min(MaxScale, newScaleX));
            newScaleY = Math.Max(MinScale, Math.Min(MaxScale, newScaleY));

            double scaleRatioX = newScaleX / currentScaleX;
            double scaleRatioY = newScaleY / currentScaleY;

            translateTransform.X = (translateTransform.X - mousePosition.X) * scaleRatioX + mousePosition.X;
            translateTransform.Y = (translateTransform.Y - mousePosition.Y) * scaleRatioY + mousePosition.Y;

            scaleTransform.ScaleX = newScaleX;
            scaleTransform.ScaleY = newScaleY;
        }
    }
}
