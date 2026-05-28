using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows;
using System.Windows.Media;
using System.Globalization;

namespace SEMI.Util
{
    public enum EnDataType { EnByte = 1, EnUShort = 2, EnUInt = 4, }
    public enum EnUnitType { EnUnitK = 1, EnUnitM = 2, }

    public class AutoNumberValueConverter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            var item = values[0];
            var items = values[1] as System.Windows.Controls.ItemCollection;

            var index = items.IndexOf(item);
            return "Row" + index.ToString("00");
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
            try
            {
                if (null != value)
                {
                    int hexVal = int.Parse(value.ToString());

                    if(null == parameter)
                        return String.Format("0x{0:X}", hexVal);
                    else if (EnDataType.EnUShort == (EnDataType)parameter)
                        return String.Format("0x{0:X4}", hexVal);
                    else if(EnDataType.EnUInt == (EnDataType)parameter)
                        return String.Format("0x{0:X8}", hexVal);
                }
                throw new NotImplementedException();
            }
            catch
            {
                //throw new NotImplementedException();
                return null;
            }
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            try
            {
                if (null != value)
                {
                    string text = value as string;
                    return int.Parse(text.Replace("0x", ""), NumberStyles.HexNumber);
                }
                throw new NotImplementedException();
            }
            catch
            {
                //throw new NotImplementedException();
                return null;
            }
        }
    }

    public class UnitValueStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            try
            {
                if (null != value)
                {
                    float hexVal = float.Parse(value.ToString());
                   
                    if (null == parameter)
                        return hexVal;
                    else if (EnUnitType.EnUnitK == (EnUnitType)parameter)
                        return hexVal;
                    else if (EnUnitType.EnUnitM == (EnUnitType)parameter)
                        return hexVal / 1000;
                }
                throw new NotImplementedException();
            }
            catch
            {
                //throw new NotImplementedException();
                return null;
            }
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            try
            {
                if (null != value)
                {
                    float fVal = float.Parse(value.ToString());

                    if (null == parameter)
                        return fVal;
                    else if (EnUnitType.EnUnitK == (EnUnitType)parameter)
                        return fVal;
                    else if (EnUnitType.EnUnitM == (EnUnitType)parameter)
                        return fVal * 1000;
                }
                throw new NotImplementedException();
            }
            catch
            {
                //throw new NotImplementedException();
                return null;
            }
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

    public class EnumerToVisibleConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                ushort val = (ushort)value;
                ushort par = ushort.Parse(parameter.ToString());
                if (val == par) return Visibility.Visible;
                else return Visibility.Collapsed;
            }
            throw new NotImplementedException();
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    public class EnumToBooleanConverter : IValueConverter
    {
        /// <inheritdoc/>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value == null ? false : value.Equals(parameter);
        }

        /// <inheritdoc/>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value != null && value.Equals(true) ? parameter : Binding.DoNothing;
        }
    }
}
