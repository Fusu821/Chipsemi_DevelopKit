using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows.Media;

namespace SEMIDevelopKit.Src.Util
{
    public class ValueToBackGroundConveter : IValueConverter
    {
        //private int refValue = 12000;
        //public int RefValue
        //{
        //    get { return refValue; }
        //    set { refValue = value; }
        //}
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if(null == value)  return null;

            int val = (short)(value);
            int[] levelColor = (int[])parameter;
            for (int index = 0; index < levelColor.Length; index += 2)
            {
                if (val < levelColor[index])
                {
                    int colorVal = levelColor[index + 1];
                    return new SolidColorBrush(Color.FromRgb((byte)(colorVal >> 16), (byte)(colorVal >> 8), (byte)colorVal));
                }
            }

            return new SolidColorBrush(Color.FromRgb(178, 34, 34));


//                 if (null != value && refValue > 0)
//                 {
//                     int val = (short)(value);
//                     if (val < refValue)
//                         return new SolidColorBrush(Color.FromRgb(244, 244, 244));
//                     else if (val < RefValue + 50)
//                         return new SolidColorBrush(Color.FromRgb(253, 219, 217));
//                     else if (val < RefValue + 150)
//                         return new SolidColorBrush(Color.FromRgb(249, 143, 138));
//                     else if (val < RefValue + 200)
//                         return new SolidColorBrush(Color.FromRgb(245, 70, 0));
//                     else
//                         return new SolidColorBrush(Color.FromRgb(255, 0, 0));
//                 }
//             return null;
            //throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class ReturnCodeToColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                uint val = (uint)(value);

                if (val > 0)
                    return new SolidColorBrush(Color.FromRgb(255, 0, 0));
                else
                    return new SolidColorBrush(Color.FromRgb(0, 255, 0));

            }
            return null;
            //throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class ReturnCodeToTextConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                uint val = (uint)(value);

                return SMInvokeBridge.ExportDeclares.CLRGetErrorMessage(val);

            }
            return null;
            //throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class BurnTypeToVisibleConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                ushort val = (ushort)(value);
                ushort par = ushort.Parse(parameter.ToString());

                if (0 == par)
                    return (val & 0x000f) > 0 ? System.Windows.Visibility.Visible : System.Windows.Visibility.Hidden;
                else if(1 == par)
                    return (val & 0x00f0) > 0 ? System.Windows.Visibility.Visible : System.Windows.Visibility.Hidden;

            }
            return null;
            //throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class BooleanNegtiveConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                Boolean val = (Boolean)(value);

                return !val;
            }
            return null;
            //throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                Boolean val = (Boolean)(value);

                return !val;
            }
            return null;
        }
    }
}
