using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows;
using System.Windows.Media;
using System.Globalization;
using SMTestBridge;

namespace SEMITestApp.Src.Util
{
    class AutoNumberValueConverter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            var item = values[0] as System.Windows.Controls.DataGridRow;
            var items = values[1] as System.Windows.Controls.ItemCollection;

            //var index = items.IndexOf(item);
            //return (index + 1).ToString();
            return item.GetIndex() + 1;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, System.Globalization.CultureInfo culture)
        {
            return null;
        }
    }

    public class HexValueStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                int hexVal = int.Parse(value.ToString());

                return String.Format("0x{0:X}", hexVal);
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                string text = value as string;
                return int.Parse(text.Replace("0x", ""), NumberStyles.HexNumber);
            }
            throw new NotImplementedException();
        }
    }

    public class ValueBitConverter : IValueConverter
    {
        private int valueBackUp = 0;
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                int val = (int)value;
                string szPara = parameter as string;

                int position = int.Parse(szPara);

                valueBackUp = val;

                return (val & (0x0001 << position)) > 0;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                bool selected = (bool)value;

                string szPara = parameter as string;

                int position = int.Parse(szPara);

                if (selected)
                    valueBackUp |= (0x0001 << position);
                else
                    valueBackUp &= ~(0x0001 << position);

                return valueBackUp;
            }
            throw new NotImplementedException();
        }
    }

    public class GraphVisibleConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                Boolean bEnterGraphMode = (Boolean)value;

                if (bEnterGraphMode)
                    return (string)parameter == "1" ? Visibility.Visible : Visibility.Collapsed;
                else
                    return (string)parameter == "1" ? Visibility.Collapsed : Visibility.Visible;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    public class StringLenghBooleanConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (String.IsNullOrEmpty(value as string))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    //public class ModeToRowSpanConverter : IValueConverter
    //{
    //    public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
    //    {
    //        if (null != value)
    //        {
    //            int mode = (int)value;

    //            if (mode == Definition.Mode_Multiple2_Test)
    //                return 2;
    //            else
    //                return 1;
    //        }
    //        throw new NotImplementedException();
    //    }
    //    public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
    //    {
    //        throw new NotImplementedException();
    //    }
    //}

    public class ModeToVisibleConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                int mode = (int)value;
                int identity = int.Parse(parameter as string);

                if (identity > mode)
                    return Visibility.Collapsed;
                else
                    return Visibility.Visible;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    //public class ModeToVisibleConverter : IValueConverter
    //{
    //    public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
    //    {
    //        if (null != value)
    //        {
    //            int mode = (int)value;

    //            if (mode == Definition.Mode_Multiple2_Test)
    //                return Visibility.Collapsed;
    //            else
    //                return Visibility.Visible;
    //        }
    //        throw new NotImplementedException();
    //    }
    //    public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
    //    {
    //        throw new NotImplementedException();
    //    }
    //}

    public class SelectToBackgroundConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                Boolean selected = (Boolean)value;

                if (selected)
                    return Brushes.Orange;
                //return new SolidColorBrush(Color.FromArgb(200, 204, 240, 163));
                else
                    return null;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class CheckToVisibleConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                Boolean bChecked = (Boolean)value;

                if (bChecked)
                    return Visibility.Visible;
                else
                    return Visibility.Collapsed;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    public class ItemListToItemConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            List<TestItem> lists = value as List<TestItem>;
            if (null != lists && null != parameter)
            {
                int identity = int.Parse(parameter as string);

                TestItem item = lists.Find((t) => { return t.ID == identity ? true : false; });

                return item;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class StatusArrayToTextConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            byte[] status = value as byte[];

            if (null != status)
            {
                int deviceNum = status.Count( (t) => { return t > 0 ? true : false;} );

                if (deviceNum == 0)
                {
                    return "No Device Connected";
                }
                else
                {
                    string text = "DeviceNumber = " + deviceNum.ToString() + " |";
                    for (int index = 0; index < status.Length; index++)
                    {
                        if (status[index] > 0)
                        {
                            text = text + " " + "MTK" + (index + 1).ToString();
                        }
                    }
                    return text;
                }    
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class TestStatusToTextConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                string strText = "";
                int iResult = int.Parse(value.ToString());
                if (iResult == ExportDeclares.SM_TEST_NONE)
                    strText = "START";
                else if (iResult == ExportDeclares.SM_TEST_PASS)
                    strText = "PASS";
                else if (iResult == ExportDeclares.SM_TEST_NG)
                    strText = "NG";
                else if (iResult == ExportDeclares.SM_TEST_TBD)
                    strText = "TBD";
                else if (iResult == ExportDeclares.SM_TEST_GOING)
                    strText = "TESTING";

                return strText;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class TestStatusToBrushConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                string strText = "";
                int iResult = int.Parse(value.ToString());
                if (iResult == ExportDeclares.SM_TEST_NONE)
                    return null;
                else if (iResult == ExportDeclares.SM_TEST_PASS)
                    return new SolidColorBrush(Color.FromArgb(255, 0, 255, 0));
                else if (iResult == ExportDeclares.SM_TEST_NG)
                    return new SolidColorBrush(Color.FromArgb(255, 255, 0, 0));
                else if (iResult == ExportDeclares.SM_TEST_TBD)
                    return Brushes.Yellow;
                else if (iResult == ExportDeclares.SM_TEST_GOING)
                    return Brushes.Yellow;

                return strText;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class ItemResultToTextConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                string strText = "";
                int iResult = int.Parse(value.ToString());
                if (iResult == ExportDeclares.SM_ITEM_STA_NONE)
                    strText = "";
                else if (iResult == ExportDeclares.SM_ITEM_STA_PASS)
                    strText = "PASS";
                else if (iResult == ExportDeclares.SM_ITEM_STA_FAIL)
                    strText = "FAIL";
                else if (iResult == ExportDeclares.SM_ITEM_STA_TBD)
                    strText = "TBD";
                else if (iResult == ExportDeclares.SM_ITEM_STA_START)
                    strText = "TESTING";
                else if (iResult == ExportDeclares.SM_ITEM_STA_WAIT)
                    strText = "WAITING";
                else if (iResult == ExportDeclares.SM_ITEM_STA_EXCEPTION)
                    strText = "EXCEPTION";

                return strText;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class ItemResultToBrushConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                string strText = "";
                int iResult = int.Parse(value.ToString());
                if (iResult == ExportDeclares.SM_ITEM_STA_NONE)
                    return null;
                else if (iResult == ExportDeclares.SM_ITEM_STA_PASS)
                    return new SolidColorBrush(Color.FromArgb(255, 0, 255, 0));
                else if (iResult == ExportDeclares.SM_ITEM_STA_FAIL)
                    return new SolidColorBrush(Color.FromArgb(255, 255, 0, 0));
                else if (iResult == ExportDeclares.SM_ITEM_STA_TBD)
                    return Brushes.Yellow;
                else if (iResult == ExportDeclares.SM_ITEM_STA_START)
                    return Brushes.Yellow;
                else if (iResult == ExportDeclares.SM_ITEM_STA_WAIT)
                    return Brushes.Blue;
                else if (iResult == ExportDeclares.SM_ITEM_STA_EXCEPTION)
                    return Brushes.Red;

                return strText;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
