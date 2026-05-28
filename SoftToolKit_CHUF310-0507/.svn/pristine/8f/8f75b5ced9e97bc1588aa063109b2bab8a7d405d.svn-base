using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Data;
using System.Windows.Controls;
using System.Globalization;
namespace SEMI.Util
{
    public class DataGridExtension
    {
        public static readonly DependencyProperty MatrixSourceProperty =
             DependencyProperty.RegisterAttached("MatrixSource",
             typeof(DataMatrix), typeof(DataGridExtension),
                new FrameworkPropertyMetadata(null,
                   new PropertyChangedCallback(OnMatrixSourceChanged)));

        public static DataMatrix GetMatrixSource(DependencyObject d)
        {
            return (DataMatrix)d.GetValue(MatrixSourceProperty);
        }

        public static void SetMatrixSource(DependencyObject d, DataMatrix value)
        {
            d.SetValue(MatrixSourceProperty, value);
        }

//         public static readonly DependencyProperty ReadOnlyMatrixSourceProperty =
//              DependencyProperty.RegisterAttached("ReadOnlyMatrixSource",
//              typeof(DataMatrix), typeof(DataGridExtension),
//                 new FrameworkPropertyMetadata(null,
//                    new PropertyChangedCallback(OnReadOnlyMatrixSourceChanged)));
// 
//         public static DataMatrix GetReadOnlyMatrixSource(DependencyObject d)
//         {
//             return (DataMatrix)d.GetValue(ReadOnlyMatrixSourceProperty);
//         }
// 
//         public static void SetReadOnlyMatrixSource(DependencyObject d, DataMatrix value)
//         {
//             d.SetValue(ReadOnlyMatrixSourceProperty, value);
//         }

//         private static void OnReadOnlyMatrixSourceChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
//         {
//             GridControl targetDataGrid = d as GridControl;
// 
// 
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
//                     textColumn.AllowEditing = DevExpress.Utils.DefaultBoolean.False;
//                     textColumn.Header = col.Name;
//                     textColumn.Width = 50;
//                     Binding colBinding = new Binding("items");
//                     colBinding.Converter = new ItemsToSingleConverter();
//                     colBinding.ConverterParameter = new MatrixParam(count, dataMatrix);
//                     textColumn.DisplayMemberBinding = colBinding;
// 
//                     targetDataGrid.Columns.Add(textColumn);
//                     count++;
//                 }
//             }
//         }

        private static void OnMatrixSourceChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            DataGrid targetDataGrid = d as DataGrid;
           

            DataMatrix dataMatrix = e.NewValue as DataMatrix;

            targetDataGrid.Columns.Clear();
            targetDataGrid.ItemsSource = null;

            if (null != dataMatrix)
            {
               targetDataGrid.ItemsSource = dataMatrix.Rows;

                foreach (var col in dataMatrix.Columns)
                {
                    DataGridTextColumn textColumn = new DataGridTextColumn();
                    //textColumn.ElementStyle = targetDataGrid.FindResource("CenterAlignmentStyle") as Style;
                    textColumn.Header = col.Name;
                    //textColumn.FieldName = col.Name;
                    //textColumn.Width = 50;
                    Binding b = new Binding(col.Name) { Mode = BindingMode.TwoWay };
                    textColumn.Binding = b;

                    targetDataGrid.Columns.Add(textColumn);
                }
            }
        }

//         public class ItemsToSingleConverter : IValueConverter
//         {
//             public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
//             {
// #if true
//                 return "ss";
// #else
//                 object[] source = value as object[];
//                 MatrixParam param = parameter as MatrixParam;
//                 if (param.Col < source.Length)
//                 {
//                     param.RowObject = value as object[];
//                     return source[param.Col];
//                 }
//                 else
//                     return null;
// #endif
//             }
// 
// 
//             public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
//             {
//                 MatrixParam param = parameter as MatrixParam;
//                 if (null != param.RowObject && param.Col < param.RowObject.Length)
//                 {
//                     object oldVal = param.RowObject[param.Col];
//                     param.RowObject[param.Col] = int.Parse(value.ToString());
//                     if (null != param.Parent.OnMatrixValueChanged && System.Convert.ToInt32(oldVal) != int.Parse(value.ToString()))
//                     {
//                         for (int index = 0; index < param.Parent.Rows.Count; index++)
//                         {
//                             if (param.Parent.Rows[index].items == param.RowObject)
//                             {
//                                 param.Parent.OnMatrixValueChanged(index, param.Col, oldVal, param.RowObject[param.Col]);
//                             }
//                         }
//                     }
//                 }
// 
//                 return param.RowObject;
//             }
//         }


    }
}
