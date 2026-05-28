using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMITestApp.Src.Util;
using System.Xml;



namespace SEMITestApp.Src.WinSet
{
    public partial class SMTestChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflex8006TestItemSetMode()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_8006, "SEMITestApp.Src.WinSet.TestItemSetMode8006", SEMI.Util.ChipReflex.SEMI_TEST_ITEM_SET_MODE);
        }
    }
    public class TestItemSetMode8006 : SettingMode
    {
        public class CurrentTestItem : TestItem
        {
            private int activeCurrentMin = 500;
            public int ActiveCurrentMin
            {
                get { return activeCurrentMin; }
                set { if (value != activeCurrentMin) { activeCurrentMin = value; OnPropertyChanged("ActiveCurrentMin"); } }
            }

            private int activeCurrentMax = 3000;
            public int ActiveCurrentMax
            {
                get { return activeCurrentMax; }
                set { if (value != activeCurrentMax) { activeCurrentMax = value; OnPropertyChanged("ActiveCurrentMax"); } }
            }

            private int sleepCurrentMin = 0;
            public int SleepCurrentMin
            {
                get { return sleepCurrentMin; }
                set { if (value != sleepCurrentMin) { sleepCurrentMin = value; OnPropertyChanged("SleepCurrentMin"); } }
            }

            private int sleepCurrentMax = 100;
            public int SleepCurrentMax
            {
                get { return sleepCurrentMax; }
                set { if (value != sleepCurrentMax) { sleepCurrentMax = value; OnPropertyChanged("SleepCurrentMax"); } }
            }
        }

        public class OSCTrimTestItem : TestItem
        {
            private int trim32KStandard = 32;
            public int Trim32KStandard
            {
                get { return trim32KStandard; }
                set { if (value != trim32KStandard) { trim32KStandard = value; OnPropertyChanged("Trim32KStandard"); } }
            }

            private int trim32KMin = 0x50;
            public int Trim32KMin
            {
                get { return trim32KMin; }
                set { if (value != trim32KMin) { trim32KMin = value; OnPropertyChanged("Trim32KMin"); } }
            }

            private int trim32KMax = 0xCF;
            public int Trim32KMax
            {
                get { return trim32KMax; }
                set { if (value != trim32KMax) { trim32KMax = value; OnPropertyChanged("Trim32KMax"); } }
            }

            private int trim64MStandard = 64000;
            public int Trim64MStandard
            {
                get { return trim64MStandard; }
                set { if (value != trim64MStandard) { trim64MStandard = value; OnPropertyChanged("Trim64MStandard"); } }
            }
 
            private int trim64MMin = 0x50;
            public int Trim64MMin
            {
                get { return trim64MMin; }
                set { if (value != trim64MMin) { trim64MMin = value; OnPropertyChanged("Trim64MMin"); } }
            }

            private int trim64MMax = 0xCF;
            public int Trim64MMax
            {
                get { return trim64MMax; }
                set { if (value != trim64MMax) { trim64MMax = value; OnPropertyChanged("Trim64MMax"); } }
            }

        }

        public class MTKVersionTestItem : TestItem
        {
            private int mtkVersion = 0x50924;
            public int MTKVersion
            {
                get { return mtkVersion; }
                set { if (value != mtkVersion) { mtkVersion = value; OnPropertyChanged("MTKVersion"); } }
            }

            private ushort autoUpdate = 0;
            public ushort AutoUpdate
            {
                get { return autoUpdate; }
                set { if (value != autoUpdate) { autoUpdate = value; OnPropertyChanged("AutoUpdate"); } }
            }
            public IList<SDefinition> upgrademode = new List<SDefinition>()
            {
                new SDefinition(0, "Default"),
                new SDefinition(1, "AutoUpdate"),
                new SDefinition(2, "Same"),
            };
            public IList<SDefinition> UpgradeMode
            {
                get { return upgrademode; }
                private set { }
            }
        }

        public class BootTestItem : TestItem
        {
            private bool onlyCheck = false;
            public bool OnlyCheck
            {
                get { return onlyCheck; }
                set { if (value != onlyCheck) { onlyCheck = value; OnPropertyChanged("OnlyCheck"); } }
            }
        }

        public class ConfigTestItem : TestItem
        {
            private bool onlyCheck = false;
            public bool OnlyCheck
            {
                get { return onlyCheck; }
                set { if (value != onlyCheck) { onlyCheck = value; OnPropertyChanged("OnlyCheck"); } }
            }
        }

        public class ScapRawDataTest : TestItem
        {
            private int scapRawDataMin = 3000;
            public int ScapRawDataMin
            {
                get { return scapRawDataMin; }
                set { if (value != scapRawDataMin) { scapRawDataMin = value; OnPropertyChanged("ScapRawDataMin"); } }
            }

            private int scapRawDataMax = 16000;
            public int ScapRawDataMax
            {
                get { return scapRawDataMax; }
                set { if (value != scapRawDataMax) { scapRawDataMax = value; OnPropertyChanged("ScapRawDataMax"); } }
            }
        }

        public class MISCTestItem : TestItem
        {
            private ushort miscMode = 0x0001;
            public ushort MiscMode
            {
                get { return miscMode; }
                set { if (value != miscMode) { miscMode = value; OnPropertyChanged("MiscMode"); } }
            }
        }

        public class ShortTestItem : TestItem
        {
            private int shortTxMax = 600;
            public int ShortTxMax
            {
                get { return shortTxMax; }
                set { if (value != shortTxMax) { shortTxMax = value; OnPropertyChanged("ShortTxMax"); } }
            }

            private int shortRxMax = 600;
            public int ShortRxMax
            {
                get { return shortRxMax; }
                set { if (value != shortRxMax) { shortRxMax = value; OnPropertyChanged("ShortRxMax"); } }
            }
        }

        public class FRTTestItem : TestItem
        {

        }

        public class IOVotageTestItem : TestItem
        {
            private int lowLevelIntMin = 0;
            public int LowLevelIntMin
            {
                get { return lowLevelIntMin; }
                set { lowLevelIntMin = value; OnPropertyChanged("LowLevelIntMin"); }
            }

            private int lowLevelIntMax = 300;
            public int LowLevelIntMax
            {
                get { return lowLevelIntMax; }
                set { lowLevelIntMax = value; OnPropertyChanged("LowLevelIntMax"); }
            }

            private int highLevelIntMin = 1700;
            public int HighLevelIntMin
            {
                get { return highLevelIntMin; }
                set { highLevelIntMin = value; OnPropertyChanged("HighLevelIntMin"); }
            }

            private int highLevelIntMax = 1900;
            public int HighLevelIntMax
            {
                get { return highLevelIntMax; }
                set { highLevelIntMax = value; OnPropertyChanged("HighLevelIntMax"); }
            }

            private int lowLevelI2cMin = 0;
            public int LowLevelI2cMin
            {
                get { return lowLevelI2cMin; }
                set { lowLevelI2cMin = value; OnPropertyChanged("LowLevelI2cMin"); }
            }

            private int lowLevelI2cMax = 300;
            public int LowLevelI2cMax
            {
                get { return lowLevelI2cMax; }
                set { lowLevelI2cMax = value; OnPropertyChanged("LowLevelI2cMax"); }
            }

            private int highLevelI2cMin = 1700;
            public int HighLevelI2cMin
            {
                get { return highLevelI2cMin; }
                set { highLevelI2cMin = value; OnPropertyChanged("HighLevelI2cMin"); }
            }

            private int highLevelI2cMax = 1900;
            public int HighLevelI2cMax
            {
                get { return highLevelI2cMax; }
                set { highLevelI2cMax = value; OnPropertyChanged("HighLevelI2cMax"); }
            }

            private int lowLevelSpiMin = 0;
            public int LowLevelSpiMin
            {
                get { return lowLevelSpiMin; }
                set { lowLevelSpiMin = value; OnPropertyChanged("LowLevelSpiMin"); }
            }

            private int lowLevelSpiMax = 300;
            public int LowLevelSpiMax
            {
                get { return lowLevelSpiMax; }
                set { lowLevelSpiMax = value; OnPropertyChanged("LowLevelSpiMax"); }
            }

            private int highLevelSpiMin = 1700;
            public int HighLevelSpiMin
            {
                get { return highLevelSpiMin; }
                set { highLevelSpiMin = value; OnPropertyChanged("HighLevelSpiMin"); }
            }

            private int highLevelSpiMax = 1900;
            public int HighLevelSpiMax
            {
                get { return highLevelSpiMax; }
                set { highLevelSpiMax = value; OnPropertyChanged("HighLevelSpiMax"); }
            }

            public System.Windows.Visibility IIC_Visible
            {
                get { return selectedProtocal == 0 ? System.Windows.Visibility.Visible : System.Windows.Visibility.Collapsed; }
            }

            public System.Windows.Visibility SPI_Visible
            {
                get { return selectedProtocal == 1 ? System.Windows.Visibility.Visible : System.Windows.Visibility.Collapsed; }
            }
        }

        public class STCTestItem : TestItem
        {
            private ushort clk = 20;
            public ushort Clk
            {
                get { return clk; }
                set { if (value != clk) { clk = (ushort)value; OnPropertyChanged("Clk"); } }
            }

            private int stcMin = 3000;
            public int STCMin
            {
                get { return stcMin; }
                set { if (value != stcMin) { stcMin = value; OnPropertyChanged("STCMin"); } }
            }

            private int stcMax = 10000;
            public int STCMax
            {
                get { return stcMax; }
                set { if (value != stcMax) { stcMax = value; OnPropertyChanged("STCMax"); } }
            }

            private int uniformityHorMax = 10;
            public int UniformityHorMax
            {
                get { return uniformityHorMax; }
                set { if (value != uniformityHorMax) { uniformityHorMax = value; OnPropertyChanged("UniformityHorMax"); } }
            }

            private int uniformityVerMax = 10;
            public int UniformityVerMax
            {
                get { return uniformityVerMax; }
                set { if (value != uniformityVerMax) { uniformityVerMax = value; OnPropertyChanged("UniformityVerMax"); } }
            }
        }

        public class MCapRawDataTestItem : TestItem
        {
            private ushort clk = 12;
            public ushort Clk
            {
                get { return clk; }
                set { if (value != clk) { clk = (ushort)(value); OnPropertyChanged("Clk"); } }
            }

            private int rawDataMin = 3000;
            public int RawDataMin
            {
                get { return rawDataMin; }
                set { if (value != rawDataMin) { rawDataMin = value; OnPropertyChanged("RawDataMin"); } }
            }

            private int rawDataMax = 10000;
            public int RawDataMax
            {
                get { return rawDataMax; }
                set { if (value != rawDataMax) { rawDataMax = value; OnPropertyChanged("RawDataMax"); } }
            }

            private int uniformityHorMax = 10;
            public int UniformityHorMax
            {
                get { return uniformityHorMax; }
                set { if (value != uniformityHorMax) { uniformityHorMax = value; OnPropertyChanged("UniformityHorMax"); } }
            }

            private int uniformityVerMax = 10;
            public int UniformityVerMax
            {
                get { return uniformityVerMax; }
                set { if (value != uniformityVerMax) { uniformityVerMax = value; OnPropertyChanged("UniformityVerMax"); } }
            }

            private Boolean chkUniformityHor = false;
            public Boolean ChkUniformityHor
            {
                get { return chkUniformityHor; }
                set { if (value != chkUniformityHor) { chkUniformityHor = value; OnPropertyChanged("ChkUniformityHor"); } }
            }

            private Boolean chkUniformityVer = false;
            public Boolean ChkUniformityVer
            {
                get { return chkUniformityVer; }
                set { if (value != chkUniformityVer) { chkUniformityVer = value; OnPropertyChanged("ChkUniformityVer"); } }
            }

            private ushort normalizationRatioMin = 50;
            public ushort NormalizationRatioMin
            {
                get { return normalizationRatioMin; }
                set { if (value != normalizationRatioMin) { normalizationRatioMin = (ushort)(value); OnPropertyChanged("NormalizationRatioMin"); } }
            }

            private ushort normalizationRatioMax = 150;
            public ushort NormalizationRatioMax
            {
                get { return normalizationRatioMax; }
                set { if (value != normalizationRatioMax) { normalizationRatioMax = (ushort)(value); OnPropertyChanged("NormalizationRatioMax"); } }
            }
        }

        public class CVDiffYTestItem : TestItem
        {
            private ushort pointRangeY = 100;
            public ushort PointRangeY
            {
                get { return pointRangeY; }
                set { if (value != pointRangeY) { pointRangeY = value; OnPropertyChanged("PointRangeY"); } }
            }

            private ushort cValueDiffRatio = 3;
            public ushort CValueDiffRatio
            {
                get { return cValueDiffRatio; }
                set { if (value != cValueDiffRatio) { cValueDiffRatio = value; OnPropertyChanged("CValueDiffRatio"); } }
            }

            private ushort shakeRangeY = 10;
            public ushort ShakeRangeY
            {
                get { return shakeRangeY; }
                set { if (value != shakeRangeY) { shakeRangeY = value; OnPropertyChanged("ShakeRangeY"); } }
            }
            private ushort timeOutFramesY = 2000;
            public ushort TimeOutFramesY
            {
                get { return timeOutFramesY; }
                set { if (value != timeOutFramesY) { timeOutFramesY = value; OnPropertyChanged("TimeOutFramesY"); } }
            }
            private ushort stablFramesY = 10;
            public ushort StablFramesY
            {
                get { return stablFramesY; }
                set { if (value != stablFramesY) { stablFramesY = value; OnPropertyChanged("StablFramesY"); } }
            }
            private ushort pMinY = 0;
            public ushort  PMinY
            {
                get { return pMinY; }
                set { if (value != pMinY) { pMinY = value; OnPropertyChanged("PMinY"); } }
            }
            private ushort pMaxY = 8192;
            public ushort PMaxY
            {
                get { return pMaxY; }
                set { if (value != pMaxY) { pMaxY = value; OnPropertyChanged("PMaxY"); } }
            }
        }

        public class CVDiffXTestItem : TestItem
        {
            private ushort pointRangeX = 100;
            public ushort PointRangeX
            {
                get { return pointRangeX; }
                set { if (value != pointRangeX) { pointRangeX = value; OnPropertyChanged("PointRangeX"); } }
            }

            private ushort cValueDiffRatioX = 3;
            public ushort CValueDiffRatioX
            {
                get { return cValueDiffRatioX; }
                set { if (value != cValueDiffRatioX) { cValueDiffRatioX = value; OnPropertyChanged("CValueDiffRatioX"); } }
            }

            private ushort shakeRangeX = 10;
            public ushort ShakeRangeX
            {
                get { return shakeRangeX; }
                set { if (value != shakeRangeX) { shakeRangeX = value; OnPropertyChanged("ShakeRangeX"); } }
            }
            private ushort timeOutFramesX = 2000;
            public ushort TimeOutFramesX
            {
                get { return timeOutFramesX; }
                set { if (value != timeOutFramesX) { timeOutFramesX = value; OnPropertyChanged("TimeOutFramesX"); } }
            }
            private ushort stablFramesX = 10;
            public ushort StablFramesX
            {
                get { return stablFramesX; }
                set { if (value != stablFramesX) { stablFramesX = value; OnPropertyChanged("StablFramesX"); } }
            }
            private ushort pMinX = 0;
            public ushort PMinX
            {
                get { return pMinX; }
                set { if (value != pMinX) { pMinX = value; OnPropertyChanged("PMinX"); } }
            }
            private ushort pMaxX = 8192;
            public ushort PMaxX
            {
                get { return pMaxX; }
                set { if (value != pMaxX) { pMaxX = value; OnPropertyChanged("PMaxX"); } }
            }
        }

        public class BaseTestItem : TestItem
        {
            private ushort x_Difference = 1000;
            public ushort X_Difference
            {
                get { return x_Difference; }
                set { if (value != x_Difference) { x_Difference = value; OnPropertyChanged("X_Difference"); } }
            }

            private ushort y_Difference = 1000;
            public ushort Y_Difference
            {
                get { return y_Difference; }
                set { if (value != y_Difference) { y_Difference = value; OnPropertyChanged("Y_Difference"); } }
            }
            private ushort x_Difference_neg = 1000;
            public ushort X_Difference_neg
            {
                get { return x_Difference_neg; }
                set { if (value != x_Difference_neg) { x_Difference_neg = value; OnPropertyChanged("X_Difference_neg"); } }
            }

            private ushort y_Difference_neg = 1000;
            public ushort Y_Difference_neg
            {
                get { return y_Difference_neg; }
                set { if (value != y_Difference_neg) { y_Difference_neg = value; OnPropertyChanged("Y_Difference_neg"); } }
            }
            private ushort ratioNum = 5;
            public ushort RatioNum
            {
                get { return ratioNum; }
                set { if (value != ratioNum) { ratioNum = value; OnPropertyChanged("RatioNum"); } }
            }

            private ushort testTime = 5;
            public ushort TestTime
            {
                get { return testTime; }
                set { if (value != testTime) { testTime = value; OnPropertyChanged("TestTime"); } }
            }
            private ushort proportionValue = 40;
            public ushort ProportionValue
            {
                get { return proportionValue; }
                set { if (value != proportionValue) { proportionValue = value; OnPropertyChanged("ProportionValue"); } }
            }
        }
        public class SDRockerCalibTestItem : TestItem
        {
            private ushort y_Difference = 1000;
            public ushort Y_Difference
            {
                get { return y_Difference; }
                set { if (value != y_Difference) { y_Difference = value; OnPropertyChanged("Y_Difference"); } }
            }

            private ushort y_Difference_neg = 1000;
            public ushort Y_Difference_neg
            {
                get { return y_Difference_neg; }
                set { if (value != y_Difference_neg) { y_Difference_neg = value; OnPropertyChanged("Y_Difference_neg"); } }
            }
            private ushort ratioNum = 5;
            public ushort RatioNum
            {
                get { return ratioNum; }
                set { if (value != ratioNum) { ratioNum = value; OnPropertyChanged("RatioNum"); } }
            }

            private ushort testTime = 5;
            public ushort TestTime
            {
                get { return testTime; }
                set { if (value != testTime) { testTime = value; OnPropertyChanged("TestTime"); } }
            }
            private ushort proportionValue = 40;
            public ushort ProportionValue
            {
                get { return proportionValue; }
                set { if (value != proportionValue) { proportionValue = value; OnPropertyChanged("ProportionValue"); } }
            }
        }

        public class NoiseTestItem : TestItem
        {
            private short noiseTestFrames = 60;
            public short NoiseTestFrames
            {
                get { return noiseTestFrames; }
                set { if (value != noiseTestFrames) { noiseTestFrames = value; OnPropertyChanged("NoiseTestFrames"); } }
            }

            private short noiseTestMaxMcap = 100;
            public short NoiseTestMaxMcap
            {
                get { return noiseTestMaxMcap; }
                set { if (value != noiseTestMaxMcap) { noiseTestMaxMcap = value; OnPropertyChanged("NoiseTestMaxMcap"); } }
            }
            //private short noiseTestMaxScap = 100;
            //public short NoiseTestMaxScap
            //{
            //    get { return noiseTestMaxScap; }
            //    set { if (value != noiseTestMaxScap) { noiseTestMaxScap = value; OnPropertyChanged("NoiseTestMaxScap"); } }
            //}
        }

        protected static IList<TestItem> testItems = new List<TestItem>()
        {
            new TestItem(){ ID = 1, Name = "int_test", ItemText = "Int", MustRequied = true },
            new TestItem(){ ID = 2, Name = "reset_test", ItemText = "Reset", MustRequied = true },
            new ShortTestItem(){ ID = 3, Name = "short_test", ItemText = "Short", MustRequied = true },
            new BootTestItem(){ ID = 5, Name = "boot_test", ItemText = "Boot", MustRequied = false },
            new ConfigTestItem(){ ID = 6, Name = "config_test", ItemText = "Config", MustRequied = false },
            new CurrentTestItem(){ ID = 7, Name = "current_test", ItemText = "Current", MustRequied = false },
            new OSCTrimTestItem(){ID = 8, Name= "osctrim_test", ItemText="OSCTrim", MustRequied=true},
            new MTKVersionTestItem(){ID = 9, Name="mtkversion_test", ItemText="MTKVersion", MustRequied=true},
            //new BaseTestItem(){ID = 10, Name="base_test", ItemText="Base", MustRequied=false},
            new FRTTestItem(){ID = 11, Name="frt_test", ItemText="FRT", MustRequied=false},
            new IOVotageTestItem{ID = 12, Name="iovol_test", ItemText="IoVoltage", MustRequied=false},
            //new ScapRawDataTest{ID = 13, Name="scap_rawdata_test", ItemText="ScapData", MustRequied=false},
            //new STCTestItem{ID = 14, Name="stc_test", ItemText="STC", MustRequied=false},
            new MCapRawDataTestItem{ID = 15, Name="mcap_rawdata_test", ItemText="McapData", MustRequied=false},
            new BaseTestItem(){ID = 17, Name="base_test", ItemText="RockerCalib", MustRequied=false},
            new NoiseTestItem(){ID = 18, Name="noise_test", ItemText="Noise", MustRequied=false},
            new SDRockerCalibTestItem(){ID = 19, Name="sd_rocker_calib_test", ItemText="SDRockerCalib", MustRequied=true},
            new CVDiffYTestItem{ID = 20, Name="cvdiff_y_test", ItemText="CVDiffY", MustRequied=false},
            new CVDiffXTestItem{ID = 21, Name="cvdiff_x_test", ItemText="CVDiffX", MustRequied=false},
        };

        public IList<TestItem> TestItemList
        {
            get { return testItems; }
            set { if (value != testItems) { testItems = value; } }
        }

        void SelectItemByName(XmlNode stNode, string name)
        {
            int selected = GetXmlAttrbuteValue(stNode, name, "selected", 1);

            TestItem item = TestItemList.FirstOrDefault((t) => { return t.Name == name; });

            item.Checked = selected > 0 ? true : false;
        }
        void SaveItemByName(XmlNode stNode, string name)
        {
            TestItem item = TestItemList.FirstOrDefault((t) => { return t.Name == name; });

            SaveXmlAttrbuteValue(stNode, name, "selected", item.Checked ? 1 : 0);
        }
        public override void XMLDataToView()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            foreach (var item in testItems)
                SelectItemByName(stNode, item.Name);

//             SelectItemByName(stNode, "int_test");
//             SelectItemByName(stNode, "reset_test");
//             SelectItemByName(stNode, "boot_test");
//             SelectItemByName(stNode, "config_test");
//             SelectItemByName(stNode, "current_test");
//             SelectItemByName(stNode, "osctrim_test");
//             SelectItemByName(stNode, "mtkversion_test");
//             SelectItemByName(stNode, "base_test");
//             SelectItemByName(stNode, "short_test");
//             SelectItemByName(stNode, "frt_test");
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            foreach (var item in testItems)
                SaveItemByName(stNode, item.Name);

//             SaveItemByName(stNode, "int_test");
//             SaveItemByName(stNode, "reset_test");
//             SaveItemByName(stNode, "boot_test");
//             SaveItemByName(stNode, "config_test");
//             SaveItemByName(stNode, "current_test");
//             SaveItemByName(stNode, "osctrim_test");
//             SaveItemByName(stNode, "mtkversion_test");
//             SaveItemByName(stNode, "base_test");
//             SaveItemByName(stNode, "short_test");
//             SaveItemByName(stNode, "frt_test");

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
