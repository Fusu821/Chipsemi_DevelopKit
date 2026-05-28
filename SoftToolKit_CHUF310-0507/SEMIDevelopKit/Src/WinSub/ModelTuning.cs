using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows;
using TuningAction = System.Action<System.Windows.DependencyObject, SEMIDevelopKit.Src.WinSub.AnyTypeData, System.Collections.Generic.List<object>>;
using SEMI.Util;
using System.Xml;
using System.Windows.Data;
using System.Windows.Controls;
using System.IO;
using System.Windows.Markup;
namespace SEMIDevelopKit.Src.WinSub
{
    public enum SITEM_TYPE { U8, S8, U16, S16, U32, S32, }
    public enum ADATA_DISP { DEC, HEX, STR, ARY, MTX, BIT, PIX, }
    public delegate void OnTabSelectionChanged(int oldIndex, int newIndex);
    public class MaxtrixEx
    {
        public static readonly DependencyProperty RowProperty =
           DependencyProperty.RegisterAttached("Row",
           typeof(int), typeof(MaxtrixEx),
              new FrameworkPropertyMetadata(10,
                 new PropertyChangedCallback(OnRowChanged)));

        public static int GetRow(DependencyObject d)
        {
            return (int)d.GetValue(RowProperty);
        }

        public static void SetRow(DependencyObject d, int value)
        {
            d.SetValue(RowProperty, value);
        }
        private static void OnRowChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var fwElement = d as System.Windows.FrameworkElement;

            if (null == fwElement.DataContext) return;

            var anyData = fwElement.DataContext as AnyTypeData;
            int rows = (int)e.NewValue, cols = GetCol(d), keys = GetKey(d);
            anyData.RealData = new DataMatrix(rows, cols, 0, 0);
            anyData.Recalc(d);
        }

        public static readonly DependencyProperty ColProperty =
           DependencyProperty.RegisterAttached("Col",
           typeof(int), typeof(MaxtrixEx),
              new FrameworkPropertyMetadata(20,
                 new PropertyChangedCallback(OnColChanged)));

        public static int GetCol(DependencyObject d)
        {
            return (int)d.GetValue(ColProperty);
        }

        public static void SetCol(DependencyObject d, int value)
        {
            d.SetValue(ColProperty, value);
        }
        private static void OnColChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var fwElement = d as System.Windows.FrameworkElement;

            if (null == fwElement.DataContext) return;

            var anyData = fwElement.DataContext as AnyTypeData;
            int rows = GetRow(d), cols = (int)e.NewValue, keys = GetKey(d);
            cols = (cols <= 0) ? keys : cols;
            anyData.RealData = new DataMatrix(rows, cols, 0, 0);
            anyData.Recalc(d);
        }

        public static readonly DependencyProperty KeyProperty =
          DependencyProperty.RegisterAttached("Key",
          typeof(int), typeof(MaxtrixEx),
             new FrameworkPropertyMetadata(6,
                new PropertyChangedCallback(OnKeyChanged)));

        public static int GetKey(DependencyObject d)
        {
            return (int)d.GetValue(KeyProperty);
        }

        public static void SetKey(DependencyObject d, int value)
        {
            d.SetValue(KeyProperty, value);
        }
        private static void OnKeyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var fwElement = d as System.Windows.FrameworkElement;

            if (null == fwElement.DataContext) return;

            var anyData = fwElement.DataContext as AnyTypeData;
            int rows = GetRow(d), cols = GetCol(d), keys = (int)e.NewValue;
            anyData.RealData = new DataMatrix(rows, cols, keys);
            anyData.Recalc(d);
        }
    }
    public class TuningItem
    {

        private static IDictionary<string, TuningAction> mapNameToAction = new Dictionary<string, TuningAction>();

        public static readonly DependencyProperty ItemNameProperty =
            DependencyProperty.RegisterAttached("ItemName",
            typeof(string), typeof(TuningItem),
               new FrameworkPropertyMetadata("",
                  new PropertyChangedCallback(OnItemNameChanged)));

        public static readonly DependencyProperty ItemBaseProperty =
            DependencyProperty.RegisterAttached("ItemBase",
            typeof(int), typeof(TuningItem),
               new FrameworkPropertyMetadata(0,
                  null));

        static TuningItem()
        {
            mapNameToAction["Button"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("ButtonCommand") { Source = TuningViewModel.Instance };
                BindingOperations.SetBinding(d, Button.CommandProperty, newBind);
            };

            mapNameToAction["TextBox"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.TwoWay };
                if (data.ADisplay == ADATA_DISP.STR) { }
                else if (data.ADisplay == ADATA_DISP.ARY) { }
                else
                {
                    newBind.Converter = new ValueStringConverter();
                    newBind.ConverterParameter = listParams.ToArray();
                }
                foreach (var rule in data.ListRules)
                    newBind.ValidationRules.Add(rule);

                newBind.ValidatesOnDataErrors = true;
                newBind.ValidatesOnExceptions = true;
                newBind.TargetNullValue = "";
                BindingOperations.SetBinding(d, TextBox.TextProperty, newBind);
            };

            mapNameToAction["DataGrid"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.TwoWay };
                BindingOperations.SetBinding(d, DataGridExtension.MatrixSourceProperty, newBind);
            };

            mapNameToAction["TextBlock"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.TwoWay };
                newBind.Converter = new ValueStringConverter();
                newBind.ConverterParameter = listParams.ToArray();
                BindingOperations.SetBinding(d, TextBlock.TextProperty, newBind);
            };

            mapNameToAction["ComboBox"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.TwoWay };
                newBind.Converter = new BitMaskValueConverter();
                newBind.ConverterParameter = listParams.ToArray();
                BindingOperations.SetBinding(d, ComboBox.SelectedValueProperty, newBind);
            };

            mapNameToAction["CheckBox"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.TwoWay, Converter = new ValueBooleanConverter(), ConverterParameter = listParams.ToArray() };
                BindingOperations.SetBinding(d, CheckBox.IsCheckedProperty, newBind);
            };

            mapNameToAction["TreeViewItem"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.TwoWay, Converter = new ValueBooleanConverter(), ConverterParameter = listParams.ToArray() };
                BindingOperations.SetBinding(d, TreeViewItem.IsSelectedProperty, newBind);
            };

            mapNameToAction["TemplateView"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.OneWay };
                BindingOperations.SetBinding(d, TemplateView.LatestTemplateProperty, newBind);
            };

            mapNameToAction["ProgressBar"] = (d, data, listParams) =>
            {
                Binding newBind = new Binding("RealData") { Mode = BindingMode.OneWay, Converter = new BitMaskValueConverter() };
                BindingOperations.SetBinding(d, ProgressBar.ValueProperty, newBind);
            };
        }

        public static string GetItemName(DependencyObject d)
        {
            return (string)d.GetValue(ItemNameProperty);
        }

        public static void SetItemName(DependencyObject d, string value)
        {
            d.SetValue(ItemNameProperty, value);
        }
        private static void OnItemNameChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            List<object> listParams = new List<object>();
            var ctlElement = d as System.Windows.FrameworkElement;
            int itemBase = (int)d.GetValue(ItemBaseProperty);
            if (null == ctlElement.DataContext) ctlElement.DataContext = AnyTypeDataManager.MakeContextData(d, (string)e.NewValue, itemBase);
            AnyTypeData data = ctlElement.DataContext as AnyTypeData;
            listParams.Add(data);
            if (null != ctlElement.Tag) listParams.Add(ctlElement.Tag);

            Binding visibleBind = new Binding("Visible") { };
            BindingOperations.SetBinding(d, FrameworkElement.VisibilityProperty, visibleBind);

            Binding enableBind = new Binding("Enabled") { };
            BindingOperations.SetBinding(d, FrameworkElement.IsEnabledProperty, enableBind);

            string typeName = ctlElement.GetType().Name;

            TuningAction ack = mapNameToAction.FirstOrDefault(c => 0 == c.Key.CompareTo(typeName)).Value;
            if (null != ack) ack.Invoke(d, data, listParams);
        }

        public static int GetItemBase(DependencyObject d)
        {
            return (int)d.GetValue(ItemNameProperty);
        }

        public static void SetItemBase(DependencyObject d, int value)
        {
            d.SetValue(ItemNameProperty, value);
        }
    }


    public class AnyTypeData : NotifyBase
    {
        private string _name = "";
        public string Name
        {
            get { return _name; }
            set { if (value != _name) { _name = value; } }
        }
        private int _baseAddr = 0;
        public int BaseAddr
        {
            get { return _baseAddr; }
            set { _baseAddr = value; }
        }
        private int _address = -1;
        public int StartAddress
        {
            get { return _address; }
            set { if (value != _address) { _address = value; } }
        }
        public long Identity
        {
            get;set;
        }
        private int _itemNum = 1;
        public int ItemNum
        {
            get { return _itemNum; }
            set { if (value != _itemNum) { _itemNum = value; } }
        }
        private SITEM_TYPE _sType = SITEM_TYPE.U8;
        public SITEM_TYPE SType
        {
            get { return _sType; }
            set { if (value != _sType) { _sType = value; } }
        }
        private ADATA_DISP _aDisplay = ADATA_DISP.DEC;
        public ADATA_DISP ADisplay
        {
            get { return _aDisplay; }
            set { if (value != _aDisplay) { _aDisplay = value; } }
        }
        private object _realData = null;
        public object RealData
        {
            get { return _realData; }
            set { if (value != _realData) { _realData = value; TuningViewModel.Instance.Sync(this); OnPropertyChanged("RealData"); } }
        }
        private Boolean _enabled = true;
        public Boolean Enabled
        {
            get { return _enabled; }
            set { if (value != _enabled) { _enabled = value; OnPropertyChanged("Enabled"); } }
        }
        private Visibility _visible = Visibility.Visible;
        public Visibility Visible
        {
            get { return _visible; }
            set { if (value != _visible) { _visible = value; OnPropertyChanged("Visible"); } }
        }
        private List<ValidationRule> listRules = new List<ValidationRule>();
        public List<ValidationRule> ListRules { get { return listRules; } }
        public void Recalc(DependencyObject d)
        {
            byte[] bufferTuning = TuningViewModel.Instance.BufferOS;
            if (StartAddress < 0) return;

            if (ADATA_DISP.STR == ADisplay)
            {
                StringBuilder strBuilder = new StringBuilder();
                for (int index = 0; index < ItemNum; index++)
                {
                    if (0 == bufferTuning[StartAddress + index])
                        break;
                    strBuilder.Append((char)bufferTuning[StartAddress + index]);
                }
                RealData = strBuilder.ToString();
            }
            else if (ADATA_DISP.ARY == ADisplay)
            {
                StringBuilder strBuilder = new StringBuilder();
                for (int index = 0; index < ItemNum; index++)
                {
                    string strTemp = string.Format("0x{0:X2},", bufferTuning[StartAddress + index]);

                    strBuilder.Append(strTemp);
                }
                strBuilder.Remove(strBuilder.Length - 1, 1);
                RealData = strBuilder.ToString();
            }
            else if (ADATA_DISP.PIX == ADisplay)
            {
                byte[] pixArray = new byte[ItemNum];
                Array.Copy(bufferTuning, StartAddress, pixArray, 0, ItemNum);
                RealData = pixArray;
            }
            else if (ADATA_DISP.MTX == ADisplay)
            {
                if (null == RealData && null != d)
                {
                    RealData = new DataMatrix(MaxtrixEx.GetRow(d), MaxtrixEx.GetCol(d));
                }
                var matrix = RealData as DataMatrix;
                if (null == matrix) return;
                matrix.OnMatrixValueChanged = OnMatrixDataChanged;
                int counter = 0;
                for (int iRow = 0; iRow < matrix.Rows.Count; iRow++)
                {
                    int cols = matrix.Columns.Count;
                    //if (iRow == matrix.Rows.Count - 1)
                    //    cols = matrix.Keys;
                    for (int iCol = 0; iCol < cols; iCol++)
                    {
                        if (iRow * matrix.Columns.Count + iCol >= ItemNum) break;

                        UInt32 uTempData = 0;
                        for (int index = 0; index < AnyTypeDataManager.mapItemSize[SType]; index++)
                        {
                            //uTempData = uTempData << 8;
                            //uTempData += bufferTuning[StartAddress + counter + index];
                            uTempData += (uint)bufferTuning[StartAddress + counter] << (index << 3);
                        }

                        if (SITEM_TYPE.S8 == SType)
                        {
                            matrix[iRow][iCol] = (sbyte)uTempData;
                        }
                        else if (SITEM_TYPE.S16 == SType)
                        {
                            matrix[iRow][iCol] = (Int16)uTempData;
                        }
                        else if (SITEM_TYPE.S32 == SType)
                        {
                            matrix[iRow][iCol] = (Int32)uTempData;
                        }
                        else
                        {
                            matrix[iRow][iCol] = uTempData;
                        }

                        counter += AnyTypeDataManager.mapItemSize[SType];
                    }
                }
            }
            else
            {
                UInt32 uTempData = 0;
                for (int index = 0; index < AnyTypeDataManager.mapItemSize[SType]; index++)
                {
                    //uTempData = uTempData << 8;
                    //uTempData += bufferTuning[StartAddress + index];
                    uTempData += (uint)bufferTuning[StartAddress + index] << (index << 3);
                }
                RealData = uTempData;
            }
        }
        private void OnMatrixDataChanged(int row, int col, object oldVal, object newVal)
        {
            TuningViewModel.Instance.Sync(this);
        }
        public AnyTypeData(string name, int baseAddr) { Name = name; BaseAddr = baseAddr; }
    }

    public class AnyTypeDataManager
    {
        public struct BinXml
        {
            public string name { get; set; }
            public int addr { get; set; }
            public int number { get; set; }
            public SITEM_TYPE type { get; set; }
            public ADATA_DISP disp { get; set; }
        }
        internal struct RulesXml
        {
            public string name { get; set; }
            public string message { get; set; }
            public int? max { get; set; }
            public int? min { get; set; }
            public Boolean? nullable { get; set; }
        }
        public string binFileName = "";
        public static Dictionary<int, BinXml> mapBinXmp = new Dictionary<int, BinXml>();
        private static Dictionary<int, RulesXml> mapRulesXmp = new Dictionary<int, RulesXml>();
        public static Dictionary<long, AnyTypeData> mapAnyData = new Dictionary<long, AnyTypeData>();
        public static Dictionary<SITEM_TYPE, int> mapItemSize = new Dictionary<SITEM_TYPE, int>() 
        {
           { SITEM_TYPE.U8, 1 },
           { SITEM_TYPE.S8, 1 },
           { SITEM_TYPE.U16, 2 },
           { SITEM_TYPE.S16, 2 },
           { SITEM_TYPE.U32, 4 },
           { SITEM_TYPE.S32, 4 },
        };
        public static AnyTypeData MakeContextData(DependencyObject d, string name, int itemBase)
        {
            long identity = (name.GetHashCode() << 32) + itemBase;
            if (mapAnyData.ContainsKey(identity))
            {
                return mapAnyData[identity];
            }
            else
            {
                AnyTypeData any = new AnyTypeData(name, itemBase);
                any.Identity = identity;

                RegistAnyData(d, any);
                return any;
            }
        }
        private static void RegistAnyData(DependencyObject d, AnyTypeData any)
        {
            if (Update(d, any))
            {
                mapAnyData[any.Identity] = any;
            }
        }
        public static AnyTypeData FindDataByName(string name)
        {
            AnyTypeData dataCopy = null;
            if (mapAnyData.ContainsKey(name.GetHashCode()))
            {
                dataCopy = mapAnyData[name.GetHashCode()];
            }

            return dataCopy;
        }
        public static void Init(byte[] bufferOS, ref long fileLen)
        {
            mapAnyData.Clear();
            mapBinXmp.Clear();
            mapRulesXmp.Clear();

            try
            {
                //获取Tuning模板文件所在的路径
                string strBinName = "";
                string strAppModule = TuningViewModel.GetTuningDirectory() + TuningViewModel.Instance.ICKindName + "\\";

                ParseFromBinXml(strAppModule + "Bin.xml", ref strBinName);

                //ParseFromExtendXml(strAppModule + "Extend.xml");

                ParseFromRulesXml(strAppModule + "UIRule.xml");

                FileInfo fileInfo = new FileInfo(strAppModule + strBinName);
                fileLen = fileInfo.Length;

                using (FileStream fs = new FileStream(strAppModule + strBinName, FileMode.Open))
                {
                    fs.Read(bufferOS, 0, (int)fileLen);
                }
            }
            catch
            {

            }
        }
        public static void RefreshAll()
        {
            foreach (var item in mapAnyData)
                item.Value.Recalc(null);
        }
        public static void ParseFromBinXml(string path, ref string binName)
        {
            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load(path);
                // 得到根节点ControlWnd
                XmlNode xn = xmlDoc.SelectSingleNode("ControlWnd");
                xn = xn.FirstChild;
                while (null != xn)
                {
                    if (0 == string.Compare(xn.Name, "Parameters")) break;
                    xn = xn.NextSibling;
                }

                XmlElement parent = (XmlElement)xn;
                int iStartAddr = int.Parse(parent.GetAttribute("Addr").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber);
                int iSize = int.Parse(parent.GetAttribute("Size").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber);
                byte xmlVer = byte.Parse(parent.GetAttribute("VerXml").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber);
                binName = parent.GetAttribute("BinFile").Trim();

                // 遍历所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                foreach (XmlNode node in xnl)
                {
                    BinXml xml = new BinXml();
                    XmlElement xe = (XmlElement)node;

                    xml.name = xe.GetAttribute("Name").Trim();
                    xml.addr = int.Parse(xe.GetAttribute("Offset").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber) + iStartAddr;
                    string strType = xe.GetAttribute("Type").Trim();
                    xml.type = (SITEM_TYPE)Enum.Parse(typeof(SITEM_TYPE), strType);
                    xml.number = int.Parse(xe.GetAttribute("Num").Trim());
                    string strDisplay = xe.GetAttribute("Dsp").Trim();
                    xml.disp = (ADATA_DISP)Enum.Parse(typeof(ADATA_DISP), strDisplay);

                    mapBinXmp.Add(xml.name.GetHashCode(), xml);
                }


            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
            finally
            {
            }
        }
        public static void ParseFromExtendXml(string path)
        {
            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load(path);
                // 得到根节点ControlWnd
                XmlNode xn = xmlDoc.SelectSingleNode("ControlWnd");
                xn = xn.FirstChild;
                while (null != xn)
                {
                    if (0 == string.Compare(xn.Name, "Parameters")) break;
                    xn = xn.NextSibling;
                }

                XmlElement parent = (XmlElement)xn;
                int iStartAddr = int.Parse(parent.GetAttribute("Addr").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber);
                int iSize = int.Parse(parent.GetAttribute("Size").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber);
                byte xmlVer = byte.Parse(parent.GetAttribute("VerXml").Replace("0x", "").Trim(), System.Globalization.NumberStyles.HexNumber);

                // 遍历所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                foreach (XmlNode node in xnl)
                {
                    BinXml xml = new BinXml();
                    XmlElement xe = (XmlElement)node;

                    xml.name = xe.GetAttribute("Name").Trim();
                    xml.addr = int.Parse(xe.GetAttribute("Offset").Trim()) + iStartAddr;
                    string strType = xe.GetAttribute("Type").Trim();
                    xml.type = (SITEM_TYPE)Enum.Parse(typeof(SITEM_TYPE), strType);
                    xml.number = int.Parse(xe.GetAttribute("Num").Trim());
                    string strDisplay = xe.GetAttribute("Dsp").Trim();
                    xml.disp = (ADATA_DISP)Enum.Parse(typeof(ADATA_DISP), strDisplay);

                    mapBinXmp.Add(xml.name.GetHashCode(), xml);
                }


            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
            finally
            {
            }
        }
        public static void ParseFromRulesXml(string path)
        {
            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load(path);
                // 得到根节点ControlWnd
                XmlNode xn = xmlDoc.SelectSingleNode("ControlWnd");
                xn = xn.FirstChild;
                while (null != xn)
                {
                    if (0 == string.Compare(xn.Name, "UIRules")) break;
                    xn = xn.NextSibling;
                }

                // 遍历所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                foreach (XmlNode node in xnl)
                {
                    RulesXml xml = new RulesXml();
                    XmlElement xe = (XmlElement)node;

                    xml.name = xe.GetAttribute("Name").Trim();
                    xml.message = xe.GetAttribute("ErrMsg").Trim();
                    string strMin = xe.GetAttribute("Min").Trim();
                    if (!string.IsNullOrEmpty(strMin))
                        xml.min = int.Parse(strMin);
                    string strMax = xe.GetAttribute("Max").Trim();
                    if (!string.IsNullOrEmpty(strMax))
                        xml.max = int.Parse(strMax);
                    string strNull = xe.GetAttribute("IsNullable").Trim();
                    if (!string.IsNullOrEmpty(strNull))
                        xml.nullable = Boolean.Parse(strNull);

                    mapRulesXmp.Add(xml.name.GetHashCode(), xml);
                }


            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
            finally
            {
            }
        }
        public static bool Update(DependencyObject d, AnyTypeData any)
        {
            int hashCode = any.Name.GetHashCode();
            Boolean bReadyUpdated = mapBinXmp.ContainsKey(hashCode);
            if (bReadyUpdated)
            {
                any.StartAddress = mapBinXmp[hashCode].addr + any.BaseAddr;
                any.ItemNum = mapBinXmp[hashCode].number;
                any.ADisplay = mapBinXmp[hashCode].disp;
                any.SType = mapBinXmp[hashCode].type;

                if (mapRulesXmp.ContainsKey(hashCode))
                {
                    IntegerRangeRule range = new IntegerRangeRule();
                    range.Name = any.Name;
                    range.Min = mapRulesXmp[hashCode].min ?? int.MinValue;
                    range.Max = mapRulesXmp[hashCode].max ?? int.MaxValue;
                    range.ErrMessage = mapRulesXmp[hashCode].message;
                    any.ListRules.Add(range);
                    if (null != mapRulesXmp[hashCode].nullable)
                    {
                        MandatoryRule manda = new MandatoryRule();
                        manda.Name = any.Name;
                        manda.ErrMessage = mapRulesXmp[hashCode].message;
                        any.ListRules.Add(manda);
                    }
                }


                any.Recalc(d);
            }
            return bReadyUpdated;
        }

    }

    public class Converter
    {
        public static uint mask_bit_set(uint org, int bit_t, int bit_f, uint dest)
        {
            uint mask = 0xffffffff;
            mask <<= (31 - bit_t);
            mask >>= (31 - bit_t + bit_f);
            mask <<= bit_f;

            return (org & (~mask)) | ((dest << bit_f) & mask);
        }
        public static uint mask_bit_value(uint org, int bit_t, int bit_f)
        {
            uint mask = 0xffffffff;
            mask <<= (31 - bit_t);
            mask >>= (31 - bit_t + bit_f);
            mask <<= bit_f;

            return (org & (mask)) >> bit_f;
        }
    }
    public class BitMaskValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                object[] listParam = parameter as object[];
                try
                {
                    AnyTypeData anyData = listParam[0] as AnyTypeData;
                    uint RealValue = System.Convert.ToUInt32(value);
                    if (listParam.Length >= 2)
                    {
                        string[] szMask = (listParam[1] as string).Trim().Split(':');
                        int[] masks = szMask.Select((t) => { return int.Parse(t); }).ToArray();
                        RealValue = Converter.mask_bit_value(RealValue, masks[0], masks.Length > 1 ? masks[1] : masks[0]);
                    }
                    return RealValue;
                }
                catch
                {
                    MessageBox.Show("value convert exception, obj = " + value.ToString());
                }
            }
            throw new NotImplementedException();
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                try
                {
                    uint UIValue = 0;
                    object[] listParam = parameter as object[];
                    AnyTypeData anyData = listParam[0] as AnyTypeData;
                    uint RealValue = System.Convert.ToUInt32(anyData.RealData);

                    string szValue = (value as string).Replace("0x", "").Trim();
                    if (ADATA_DISP.HEX == anyData.ADisplay)
                    {
                        UIValue = System.Convert.ToUInt32(szValue, 16);
                    }
                    else
                    {
                        UIValue = System.Convert.ToUInt32(szValue, 10);
                    }

                    if (listParam.Length >= 2)
                    {
                        string[] szMask = (listParam[1] as string).Trim().Split(':');
                        int[] masks = szMask.Select((t) => { return int.Parse(t); }).ToArray();
                        RealValue = Converter.mask_bit_set(RealValue, masks[0], masks.Length > 1 ? masks[1] : masks[0], UIValue);
                    }
                    else
                    {
                        RealValue = UIValue;
                    }

                    return RealValue;
                }
                catch
                {
                    MessageBox.Show("value convert exception, obj = " + value.ToString());
                }
            }
            throw new NotImplementedException();
        }
    }
    public class ValueStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                try
                {
                    object[] listParam = parameter as object[];
                    AnyTypeData data = (AnyTypeData)listParam[0];
                    int size = AnyTypeDataManager.mapItemSize[data.SType];

                    UInt32 RealValue = System.Convert.ToUInt32(data.RealData);

                    if (listParam.Length >= 2)
                    {
                        string[] szMask = (listParam[1] as string).Trim().Split(':');
                        int[] masks = szMask.Select((t) => { return int.Parse(t); }).ToArray();
                        RealValue = Converter.mask_bit_value(RealValue, masks[0], masks.Length > 1 ? masks[1] : masks[0]);
                    }

                    if (ADATA_DISP.HEX == data.ADisplay)
                    {
                        string formatString = string.Format("0x{{0:X{0}}}", size * 2);
                        return string.Format(formatString, RealValue);
                    }
                    else if (SITEM_TYPE.S8 == data.SType && RealValue > SByte.MaxValue)
                    {
                        byte FixedValue = (byte)(Byte.MaxValue - (RealValue & 0xff) + 1);
                        return string.Format("-{0}", FixedValue);
                    }
                    else if (SITEM_TYPE.S16 == data.SType && RealValue > short.MaxValue)
                    {
                        ushort FixedValue = (ushort)(ushort.MaxValue - (RealValue & 0xffff) + 1);
                        return string.Format("-{0}", FixedValue);
                    }
                    else if (SITEM_TYPE.S32 == data.SType && RealValue > int.MaxValue)
                    {
                        UInt32 FixedValue = (UInt32)(UInt32.MaxValue - (RealValue & 0xffffffff) + 1);
                        return string.Format("-{0}", FixedValue);
                    }
                    return RealValue.ToString();
                }
                catch
                {
                    MessageBox.Show("value convert exception, obj = " + value.ToString());
                }
            }
            return "";
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                try
                {
                    Int64 UIValue = 0;
                    object[] listParam = parameter as object[];
                    AnyTypeData data = (AnyTypeData)listParam[0];
                    var RealValue = System.Convert.ToInt64(data.RealData);
                   
                    string szValue = (value as string).Replace("0x", "").Trim();
                    if (ADATA_DISP.HEX == data.ADisplay)
                    {
                        UIValue = System.Convert.ToInt64(szValue, 16);
                    }
                    else
                    {
                        UIValue = System.Convert.ToInt64(szValue, 10);
                    }

                    if (listParam.Length >= 2)
                    {
                        string[] szMask = (listParam[1] as string).Trim().Split(':');
                        int[] masks = szMask.Select((t) => { return int.Parse(t); }).ToArray();
                        RealValue = Converter.mask_bit_set(System.Convert.ToUInt32(RealValue), masks[0], masks.Length > 1 ? masks[1] : masks[0], System.Convert.ToUInt32(UIValue));
                    }
                    else
                    {
                        RealValue = UIValue;
                    }

                    if ((int)RealValue < 0 && SITEM_TYPE.S8 == data.SType)
                    {
                        return (byte)(RealValue & 0xff);
                    }
                    else if ((int)RealValue < 0 && SITEM_TYPE.S16 == data.SType)
                    {
                        return (ushort)(RealValue & 0xffff);
                    }
                    else if ((int)RealValue < 0 && SITEM_TYPE.S32 == data.SType)
                    {
                        return (uint)(RealValue & 0xffffffff);
                    }
                    return RealValue;
                }
                catch
                {
                    MessageBox.Show("value convert exception, obj = " + value.ToString());
                }
            }
            return 0;
        }
    }
    public class ValueBooleanConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                object[] listParam = parameter as object[];
                try
                {
                    if (listParam.Length <= 1)
                    {
                        return System.Convert.ToBoolean(int.Parse(value.ToString()));
                    }
                    AnyTypeData anyData = listParam[0] as AnyTypeData;
                    int index = System.Convert.ToInt32(listParam[1]);
                    uint iReadVal = System.Convert.ToUInt32(value);
                    return (iReadVal & (0x00000001 << index)) > 0;
                }
                catch
                {
                    MessageBox.Show("boolean transfer exception, obj = " + value.ToString());
                }
            }
            return false;
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value)
            {
                object[] listParam = parameter as object[];
                if (listParam.Length <= 1) return System.Convert.ToByte(value);
                AnyTypeData anyData = listParam[0] as AnyTypeData;
                int index = System.Convert.ToInt32(listParam[1]);
                uint iReadVal = System.Convert.ToUInt32(anyData.RealData);
                if (System.Convert.ToBoolean(value)) iReadVal = (iReadVal | ((uint)(0x00000001 << index)));
                else iReadVal = (iReadVal & (uint)(~(0x00000001 << index)));
                return iReadVal;
            }
            throw new NotImplementedException();
        }
    }
//     public class ValueBitValueConverter : IValueConverter
//     {
//         public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
//         {
//             if (null != value)
//             {
//                 object[] listParam = parameter as object[];
//                 if (listParam.Length <= 1) return value;
//                 AnyTypeData anyData = parameter as AnyTypeData;
//                 int index = System.Convert.ToInt32(listParam[1]);
//                 int iReadVal = System.Convert.ToInt32(value);
//                 return iReadVal & (0x00000001 << index);
//             }
//             return false;
//         }
//         public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
//         {
//             if (null != value)
//             {
//                 object[] listParam = parameter as object[];
//                 if (listParam.Length <= 1) return value;
//                 AnyTypeData anyData = parameter as AnyTypeData;
//                 int index = System.Convert.ToInt32(listParam[1]);
//                 int iReadVal = System.Convert.ToInt32(anyData.RealData);
//                 if (System.Convert.ToBoolean(value)) iReadVal = (iReadVal | ((0x00000001 << index)));
//                 else iReadVal = (iReadVal & (~(0x00000001 << index)));
// 
//                 return iReadVal;
//             }
//             throw new NotImplementedException();
//         }
//     }

    public class LinkUriConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (null != value && null != parameter)
            {
                string fullPath = value as string;
                string uri = parameter as string;
                fullPath = fullPath + "\\" + uri;

                ParserContext pContext = new ParserContext();
                pContext.XamlTypeMapper = new XamlTypeMapper(new string[] { });
                pContext.XamlTypeMapper.AddMappingProcessingInstruction("clr-namespace:SEMIDevelopKit.Src.WinSub", "SEMIDevelopKit.Src.WinSub", "SEMIDevelopKit");
                pContext.XmlnsDictionary.Add("viewModel", "clr-namespace:SEMIDevelopKit.Src.WinSub");

                using (System.IO.FileStream fs = new System.IO.FileStream(fullPath, System.IO.FileMode.Open))
                {
                    UserControl obj = XamlReader.Load(fs, pContext) as UserControl;
                    obj.DataContext = TuningViewModel.Instance;
                    //TuningViewModel.Instance.TuningFrame = obj;
                    return obj;
                }
            }
            return null;
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    public class TuningNode : NotifyBase
    {
        private Boolean selected = false;
        public Boolean Selected
        {
            get { return selected; }
            set
            { 
                if (value != selected) 
                    selected = value;
                OnPropertyChanged("Selected");

                ParserContext pContext = new ParserContext();
                pContext.XamlTypeMapper = new XamlTypeMapper(new string[] { });
                pContext.XamlTypeMapper.AddMappingProcessingInstruction("clr-namespace:SEMIDevelopKit.Src.WinSub", "SEMIDevelopKit.Src.WinSub", "SEMIDevelopKit");
                pContext.XmlnsDictionary.Add("viewModel", "clr-namespace:SEMIDevelopKit.Src.WinSub");

                try
                {
                    string fullPath = TuningViewModel.GetTuningDirectory() + TuningViewModel.Instance.ICKindName + "\\" + LinkUri;
                    using (System.IO.FileStream fs = new System.IO.FileStream(fullPath, System.IO.FileMode.Open))
                    {
                        UserControl obj = XamlReader.Load(fs, pContext) as UserControl;
                        obj.DataContext = TuningViewModel.Instance;
                        TuningViewModel.Instance.TuningFrame = obj;
                    }
                }
                catch(Exception ex)
                {
                    ex.ToString();
                }
            }
        }
        public string ItemName { get; set; }

        public string LinkUri { get; set; }

        public int NodeType { get; set; }

        public IList<TuningNode> ItemNodes { get; set; }
    }

    public class TuningViewModel : NotifyBase
    {
        private static TuningViewModel localInstance = null;
        public RoutedCommand ButtonCommand { get; set; }

        private string icKindName = "DEFAULT";
        public string ICKindName
        {
            get { return icKindName; }
            set { icKindName = value; }
        }

        private byte[] bufferOS = new byte[2 * 1024];
        public byte[] BufferOS
        {
            get { return bufferOS; }
            set { bufferOS = value; }
        }
        protected long binFileLen = 256;
        public long BindFileLen
        {
            get { return binFileLen; }
        }

        public static TuningViewModel Instance
        {
            get { return localInstance; }
            set { localInstance = value; }
        }

        protected IList<TuningNode> tuningLists = null;
        public IList<TuningNode> TuningLists
        {
            get { return tuningLists; }
            private set { tuningLists = null; }
        }

        private Control tuningFrame = null;
        public Control TuningFrame
        {
            get { return tuningFrame; }
            set { if (value != tuningFrame) { tuningFrame = value; OnPropertyChanged("TuningFrame"); } }
        }

        public string XamlPath
        {
            get { return TuningViewModel.GetTuningDirectory() + TuningViewModel.Instance.ICKindName; }
            private set {  } 
        }

        private string tuningInfo = "";
        public string TuningInfo
        {
            get { return tuningInfo; }
            set { if (value != tuningInfo) { tuningInfo = value; OnPropertyChanged("TuningInfo"); } }
        }

        public TuningViewModel()
        {
            localInstance = this;

            
            
            //AnyTypeDataManager.Init(bufferOS, ref binFileLen);


            //SetTuningParam(/*IdcStudio.Global.UserLevelClass.AMBIGUOUS_USER_START*/MainViewModel.Intr.iUserLevel, icType, delegateTextChange, delegateVisibleChange, delegateEnableChange, deleteGetParamAddr);
        }

        public static string GetTuningDirectory()
        {
            string strApp = System.Environment.CurrentDirectory;
            strApp += "\\Tuning\\";

            return strApp;
        }

        public void Parse()
        {
            AnyTypeDataManager.Init(bufferOS, ref binFileLen);
        }

        public virtual void OnInitialized(byte[] osBin)
        {

        }

        public virtual void OnButtonClicked(string ctrlName, byte[] osBin)
        {

        }
        public virtual ushort CalcCheckSum(byte[] content, long len)
        {
            ushort checkSum = 0;
            for (int index = 0; index < len; index += 2)
            {
                checkSum += (ushort)((content[index + 1] << 8) + content[index]);
            }

            return (ushort)((~checkSum) + 1);
        }

//         public virtual ushort CalcCheckSum254(byte[] content, long len = 254)
//         {
//             ushort checkSum = 0;
//             for (int index = 0; index < len; index += 2)
//             {
//                 checkSum += (ushort)((content[index + 1] << 8) + content[index]);
//             }
// 
//             return (ushort)((~checkSum) + 1);
//         }

//         public virtual bool CheckAppFile(string fileName)
//         {
//             return false;
//         }

        public virtual void OnTuningValueChanged(string name, int addr, byte[] osBin)
        {

        }

        public void LoadBinFromOutSite(string binPath)
        {
            FileInfo fileInfo = new FileInfo(binPath);
            binFileLen = fileInfo.Length;

            using (FileStream fs = new FileStream(binPath, FileMode.Open))
            {
                fs.Read(bufferOS, 0, (int)binFileLen);
                AnyTypeDataManager.RefreshAll();
                fs.Close();
            }
        }

        public void Sync(AnyTypeData anyData)
        {
            if (anyData.StartAddress < 0) return;
            if (ADATA_DISP.STR == anyData.ADisplay)
            {
                string strTemp = anyData.RealData as string;
                for (int index = 0; index < anyData.ItemNum; index++)
                {
                    if (index < strTemp.Length)
                        bufferOS[anyData.StartAddress + index] = (byte)strTemp[index];
                    else
                        bufferOS[anyData.StartAddress + index] = 0x00;
                }
                try
                {
                    OnTuningValueChanged(anyData.Name, anyData.StartAddress, BufferOS);
                }
                catch
                {
                    MessageBox.Show(anyData.Name);
                }
            }
            else if (ADATA_DISP.MTX == anyData.ADisplay)
            {
                if (null == anyData.RealData) return;
                int counter = anyData.StartAddress;
                DataMatrix matrix = anyData.RealData as DataMatrix;
                if (null == matrix) return;
                for (int iRow = 0; iRow < matrix.Rows.Count; iRow++)
                {
                    int realCol = matrix.Columns.Count;
                    //if (iRow == matrix.Rows.Count - 1) realCol = matrix.Keys;
                    for (int iCol = 0; iCol < realCol; iCol++)
                    {
                        if (iRow * matrix.Columns.Count + iCol >= anyData.ItemNum) break;

                        if (null != matrix[iRow][iCol])
                        {
                            uint data = System.Convert.ToUInt32(matrix[iRow][iCol]);
                            int itemSize = AnyTypeDataManager.mapItemSize[anyData.SType];
                            for (int index = 0; index < itemSize; index++)
                            {
                                //bufferOS[counter + itemSize - index - 1] = (byte)(data & 0xff);
                                bufferOS[counter + index] = (byte)(data & 0xff);
                                data = data >> 8;
                            }

                            counter += AnyTypeDataManager.mapItemSize[anyData.SType];
                        }
                    }
                }
                try
                {
                    OnTuningValueChanged(anyData.Name, anyData.StartAddress, BufferOS);
                }
                catch
                {
                    MessageBox.Show(anyData.Name);
                }
            }
            else if (ADATA_DISP.ARY == anyData.ADisplay)
            {
                string strTemp = anyData.RealData as string;
                string[] items = strTemp.Split(',');
                for (int index = 0; index < anyData.ItemNum && index < items.Length; index++)
                {
                    bufferOS[anyData.StartAddress + index] = Convert.ToByte(items[index].Replace("0x", "").Trim(), 16);
                }
                try
                {
                    OnTuningValueChanged(anyData.Name, anyData.StartAddress, BufferOS);
                }
                catch
                {
                    MessageBox.Show(anyData.Name);
                }
            }
            else if (ADATA_DISP.PIX == anyData.ADisplay) { }
            else
            {
                uint dataTemp = System.Convert.ToUInt32(anyData.RealData);
                int typeSize = AnyTypeDataManager.mapItemSize[anyData.SType];
                for (int index = 0; index < typeSize; index++)
                {
                    //bufferOS[anyData.StartAddress + typeSize - 1 - index] = (byte)(dataTemp & 0xff);
                    bufferOS[anyData.StartAddress + index] = (byte)(dataTemp & 0xff);
                    dataTemp = dataTemp >> 8;
                }
                try
                {
                    OnTuningValueChanged(anyData.Name, anyData.StartAddress, BufferOS);
                }
                catch
                {
                    MessageBox.Show(anyData.Name);
                }
            }
        }
    }
}
