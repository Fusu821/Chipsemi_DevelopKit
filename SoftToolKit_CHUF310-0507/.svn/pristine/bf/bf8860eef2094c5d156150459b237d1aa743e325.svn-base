using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows.Data;
using System.Globalization;

namespace LibraryTools
{
    public enum CheckSumType
    {
        CheckSumU816 = 0,
        CheckSumU16 = 1,
        CheckSumEx = 10,
        CheckSumU8 = 20,
        CheckSum32 = 30,
    }
    public enum EnumTranslateType
    {
        Translate_PackToIIC = 0,
        Translate_PackToSPI = 1,
        Translate_HexToTxt = 10,
        Translate_TxtToHex = 11,
        Translate_PackToSPIx = 20,
        Translate_PackToUSART = 21,
    }
    public enum EnumTransformType
    {
        Transform_IICToCSv = 0,
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
    public class Command : ICommand
    {

        bool ICommand.CanExecute(object parameter)
        {
            return true;
        }

        event EventHandler ICommand.CanExecuteChanged
        {
            add { }
            remove { }
        }

        void ICommand.Execute(object parameter)
        {
            DoExecute.Invoke(parameter);
        }
        public Action<object> DoExecute { get; set; }
    }

}
