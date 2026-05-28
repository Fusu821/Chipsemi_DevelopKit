using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMTestBridge;
using System.ComponentModel;

namespace SEMITestApp.Src.Util
{
    public class HexValue<T>
    {
        public HexValue(T val)
        {
            _hexVal = val;
        }
        public override string ToString()
        {
            if (string.IsNullOrEmpty(FormatString))
                return string.Format("0x{0:X}", _hexVal);
            else
                return string.Format(FormatString, _hexVal);
        }

        private T _hexVal;
        public T hexVal { get { return _hexVal; } }
        public string FormatString { get; set; }
    }

//     public class HexShortValue<T>
//     {
//         public HexShortValue(T val)
//         {
//             _hexVal = val;
//         }
//         public override string ToString()
//         {
//             if (string.IsNullOrEmpty(FormatString))
//                 return string.Format("0x{0:X}", _hexVal);
//             else
//                 return string.Format(FormatString, _hexVal);
//         }
// 
//         private T _hexVal;
//         public T hexVal { get { return _hexVal; } }
//         public string FormatString { get; set; }
//     }

    public class DecValue
    {
        public DecValue(int val)
        {
            _decVal = val;
        }
        public DecValue(object val)
        {
            _decVal = System.Convert.ToInt32(val);
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(FormatString))
                return string.Format("{0:D}", _decVal);
            else
                return string.Format(FormatString, _decVal);
        }

        private int _decVal;
        public int decVal { get { return _decVal; } }
        public string FormatString { get; set; }
    }
    public class DoubleValue
    {
        public DoubleValue(double val)
        {
            _douVal = val;
        }
        public DoubleValue(object val)
        {
            _douVal = System.Convert.ToDouble(val);
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(FormatString))
                return string.Format("{0:F1}", _douVal);
            else
                return string.Format(FormatString, _douVal);
        }

        private double _douVal;
        public double douVal { get { return _douVal; } }
        public string FormatString { get; set; }
    }

    public class BitValue
    {
        private int val;
        public BitValue(int temp)
        {
            val = temp;
        }
        public bool Bit(int index)
        {
            //uint tempVal = uint.Parse(val.ToString());
            return (val & (0x00000001 << index)) > 0;
        }
        public int MaskValue(uint masked)
        {
            int ret = 0;
            for (int index = 32 - 1; index >= 0; index--)
            {
                ret = ret << 1;
                if (((masked & (0x00000001 << index)) > 0) && Bit(index))
                    ret += 1;
            }
            return ret;
        }

        public Byte ByteValue
        {
            get { return (byte)val; }
        }

        public ushort UShortValue
        {
            get { return (ushort)val; }
        }

        public int IntValue
        {
            get { return (int)val; }
        }

    }

    public class DataArrayInit
    {
        static DataArrayInit()
        {
            if (0 == _dec_0_to_100_step_2.Count)
            {
                for (int index = 0; index < 100; index += 2)
                {
                    _dec_0_to_100_step_2.Add(new DecValue((int)index));
                }
            }
        }

        private static List<DecValue> _dec_0_to_100_step_2 = new List<DecValue>();
        public static List<DecValue> dec_0_to_100_step_2
        {
            get
            {
                return _dec_0_to_100_step_2;
            }
        }
    }

    public class TestItem : NotifyBase
    {
        public int ID { get; set; }
        public String Name { get; set; }

        private Boolean bChecked = false;
        public Boolean Checked
        {
            get { return bChecked; }
            set { if (value != bChecked) { bChecked = value; OnPropertyChanged("Checked"); } }
        }
        public string ItemText { get; set; }
    }

    public class SMTestItemRef : SMTestItem, INotifyPropertyChanged
    {
        public SMTestItemRef() { }
        public SMTestItemRef(SMTestItem item)
        {
            this.testCode = item.testCode;
            this.testMark = item.testMark;
            this.testName = item.testName;
            this.testResult = item.testResult;
        }
        
        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string strPropertyInfo)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(strPropertyInfo));
            }
        }

        public int ItemCode
        {
            get { return testCode; }
            set { if (value != testCode) { testCode = value; OnPropertyChanged("ItemCode"); } }
        }

        public int ItemResult
        {
            get { return testResult; }
            set { if (value != testResult) { testResult = value; OnPropertyChanged("ItemResult"); } }
        }

        public string ItemName
        {
            get { return testName; }
            set { if (value != testName) { testName = value; OnPropertyChanged("ItemName"); } }
        }

        public string ItemMark
        {
            get { return testMark; }
            set { if (value != testMark) { testMark = value; OnPropertyChanged("ItemMark"); } }
        }

        public void Reset()
        {
            ItemResult = 0;
            ItemMark = "";
        }
    }
}
