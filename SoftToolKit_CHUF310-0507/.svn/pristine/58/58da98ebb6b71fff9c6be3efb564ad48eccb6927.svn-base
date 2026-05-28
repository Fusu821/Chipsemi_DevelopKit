using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using SMInvokeBridge;
using System.Windows.Media;

namespace SEMITestApp.Src.Util
{
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

    public class VIHToCodeConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                ushort code = (ushort)value;

                float k = 0.025809374f, b = 0.0222f;
                return (k * code + b).ToString("0.000");
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                float VIH = float.Parse(value.ToString());

                float k = 38.7455f, b = -0.85997f;
                return (short)Math.Ceiling(k * VIH + b);
            }
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
                else if (iResult == ExportDeclares.SM_ITEM_STA_PRESS)
                    strText = "按压SENSOR";

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
                else if (iResult == ExportDeclares.SM_ITEM_STA_PRESS)
                    return Brushes.DeepPink;

                return strText;
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

    public class ItemListToSubItemConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            List<TestItem> lists = value as List<TestItem>;
            if (null != lists && null != parameter)
            {
                Boolean bMustRequied = int.Parse(parameter as string) > 0 ? true : false;

                var item = lists.Where((t) => { return t.MustRequied == bMustRequied ? true : false; });

                return item.ToList();
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
