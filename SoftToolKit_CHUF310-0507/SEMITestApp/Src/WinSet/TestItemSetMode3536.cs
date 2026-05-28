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
        public void RegistReflex3536TestItemSetMode()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3536, "SEMITestApp.Src.WinSet.TestItemSetMode3536", SEMI.Util.ChipReflex.SEMI_TEST_ITEM_SET_MODE);
        }
    }
    public class TestItemSetMode3536 : SettingMode
    {
        protected class OSTestItem : TestItem
        {
            private ushort intergralTime = 1;
            public ushort IntegralTime
            {
                get { return intergralTime; }
                set { if (value != intergralTime) { intergralTime = value; OnPropertyChanged("IntegralTime"); } }
            }

            private ushort scale_a = 49;
            public ushort ScaleA
            {
                get { return scale_a; }
                set { if (value != scale_a) { scale_a = value; OnPropertyChanged("ScaleA"); } }
            }

            private ushort scale_b = 49;
            public ushort ScaleB
            {
                get { return scale_b; }
                set { if (value != scale_b) { scale_b = value; OnPropertyChanged("ScaleB"); } }
            }

            private ushort osClock = 0x6302;
            public ushort OSClock
            {
                get { return osClock; }
                set { if (osClock != value) { osClock = value; OnPropertyChanged("OSClock"); } }
            }

            private int m2_ratio = 12;
            public int M2Ratio
            {
                get { return m2_ratio; }
                set { if (value != m2_ratio) { m2_ratio = value; OnPropertyChanged("M2Ratio"); } }
            }

            private int m1_ratio_upper_va = 18;
            public int M1RatioUpperVa
            {
                get { return m1_ratio_upper_va; }
                set { if (value != m1_ratio_upper_va) { m1_ratio_upper_va = value; OnPropertyChanged("M1RatioUpperVa"); } }
            }

            private int m1_ratio_lower_va = 18;
            public int M1RatioLowerVa
            {
                get { return m1_ratio_lower_va; }
                set { if (value != m1_ratio_lower_va) { m1_ratio_lower_va = value; OnPropertyChanged("M1RatioLowerVa"); } }
            }

            private int m1_ratio_upper_ref = 43;
            public int M1RatioUpperRef
            {
                get { return m1_ratio_upper_ref; }
                set { if (value != m1_ratio_upper_ref) { m1_ratio_upper_ref = value; OnPropertyChanged("M1RatioUpperRef"); } }
            }

            private int m1_ratio_lower_ref = 31;
            public int M1RatioLowerRef
            {
                get { return m1_ratio_lower_ref; }
                set { if (value != m1_ratio_lower_ref) { m1_ratio_lower_ref = value; OnPropertyChanged("M1RatioLowerRef"); } }
            }

            private int m3_delta_level1 = -80;
            public int M3DeltaLevel1
            {
                get { return m3_delta_level1; }
                set { if (value != m3_delta_level1) { m3_delta_level1 = value; OnPropertyChanged("M3DeltaLevel1"); } }
            }

            private int m3_delta_level2 = -150;
            public int M3DeltaLevel2
            {
                get { return m3_delta_level2; }
                set { if (value != m3_delta_level2) { m3_delta_level2 = value; OnPropertyChanged("M3DeltaLevel2"); } }
            }

            private int m3_delta_va_max = 200;
            public int M3DeltaVaMax
            {
                get { return m3_delta_va_max; }
                set { if (value != m3_delta_va_max) { m3_delta_va_max = value; OnPropertyChanged("M3DeltaVaMax"); } }
            }

            private int m3_delta_ref_max = 200;
            public int M3DeltaRefMax
            {
                get { return m3_delta_ref_max; }
                set { if (value != m3_delta_ref_max) { m3_delta_ref_max = value; OnPropertyChanged("M3DeltaRefMax"); } }
            }
        }


        public class FSDTestItem : TestItem
        {
            private ushort uslow_clk = 0x5503;
            public ushort SlowClock
            {
                get { return uslow_clk; }
                set { if (value != uslow_clk) { uslow_clk = value; OnPropertyChanged("SlowClock"); } }
            }

            private ushort ufast_clk = 0x5501;
            public ushort FastClock
            {
                get { return ufast_clk; }
                set { if (value != ufast_clk) { ufast_clk = value; OnPropertyChanged("FastClock"); } }
            }

            private ushort intergralTime = 1;
            public ushort IntegralTime
            {
                get { return intergralTime; }
                set { if (value != intergralTime) { intergralTime = value; OnPropertyChanged("IntegralTime"); } }
            }

            private bool scaleCheck = true;
            public bool ScaleCheck
            {
                get { return scaleCheck; }
                set { if (value != scaleCheck) { scaleCheck = value; OnPropertyChanged("ScaleCheck"); } }
            }

            private ushort fsdCmpMax = 100;
            public ushort FSDCmpMax
            {
                get { return fsdCmpMax; }
                set { if (value != fsdCmpMax) { fsdCmpMax = value; OnPropertyChanged("FSDCmpMax"); } }
            }

            private int fsdMin = 10;
            public int FSDMin
            {
                get { return fsdMin; }
                set { if (value != fsdMin) { fsdMin = value; OnPropertyChanged("FsdMin"); } }
            }

            private bool fsdReCheck = false;
            public bool FSDReCheck
            {
                get { return fsdReCheck; }
                set { if (value != fsdReCheck) { fsdReCheck = value; OnPropertyChanged("FSDReCheck"); } }
            }

            private int fsdTrigerMin = -150;
            public int FSDTrigerMin
            {
                get { return fsdTrigerMin; }
                set { if (value != fsdTrigerMin) { fsdTrigerMin = value; OnPropertyChanged("FSDTrigerMin"); } }
            }

            private int fsdTrigerMax = 100;
            public int FSDTrigerMax
            {
                get { return fsdTrigerMax; }
                set { if (value != fsdTrigerMax) { fsdTrigerMax = value; OnPropertyChanged("FSDTrigerMax"); } }
            }

            private int fsdSlowCriticalMin = -150;
            public int FSDSlowCriticalMin
            {
                get { return fsdSlowCriticalMin; }
                set { if (value != fsdSlowCriticalMin) { fsdSlowCriticalMin = value; OnPropertyChanged("FSDSlowCriticalMin"); } }
            }

            private int fsdSlowCriticalMax = 2;
            public int FSDSlowCriticalMax
            {
                get { return fsdSlowCriticalMax; }
                set { if (value != fsdSlowCriticalMax) { fsdSlowCriticalMax = value; OnPropertyChanged("FSDSlowCriticalMax"); } }
            }

            private int fsdBesidesMin = 5;
            public int FSDBesidesMin
            {
                get { return fsdBesidesMin; }
                set { if (value != fsdBesidesMin) { fsdBesidesMin = value; OnPropertyChanged("FSDBesidesMin"); } }
            }

            private int fsdFastCriticalMax = 2;
            public int FSDFastCriticalMax
            {
                get { return fsdFastCriticalMax; }
                set { if (value != fsdFastCriticalMax) { fsdFastCriticalMax = value; OnPropertyChanged("FSDFastCriticalMax"); } }
            }

            private bool fsdPlusCheck = true;
            public bool FSDPlusCheck
            {
                get { return fsdPlusCheck; }
                set { if (value != fsdPlusCheck) { fsdPlusCheck = value; OnPropertyChanged("FSDPlusCheck"); } }
            }

            private int fsdT1 = 10;
            public int FSDT1
            {
                get { return fsdT1; }
                set { if (value != fsdT1) { fsdT1 = value; OnPropertyChanged("FSDT1"); } }
            }

            private int fsdT2 = 5;
            public int FSDT2
            {
                get { return fsdT2; }
                set { if (value != fsdT2) { fsdT2 = value; OnPropertyChanged("FSDT2"); } }
            }

            private int fsdT3 = -5;
            public int FSDT3
            {
                get { return fsdT3; }
                set { if (value != fsdT3) { fsdT3 = value; OnPropertyChanged("FSDT3"); } }
            }

            private int fsdT4 = -20;
            public int FSDT4
            {
                get { return fsdT4; }
                set { if (value != fsdT4) { fsdT4 = value; OnPropertyChanged("FSDT4"); } }
            }

            private bool fbCheck = false;
            public bool FBCheck
            {
                get { return fbCheck; }
                set { if (value != fbCheck) { fbCheck = value; OnPropertyChanged("FBCheck"); } }
            }

            private int fbBaseLine = 80;
            public int FBBaseLine
            {
                get { return fbBaseLine; }
                set { if (value != fbBaseLine) { fbBaseLine = value; OnPropertyChanged("FBBaseLine"); } }
            }

            private int fbMin = -20;
            public int FBMin
            {
                get { return fbMin; }
                set { if (value != fbMin) { fbMin = value; OnPropertyChanged("FBMin"); } }
            }

            private int fbMax = 20;
            public int FBMax
            {
                get { return fbMax; }
                set { if (value != fbMax) { fbMax = value; OnPropertyChanged("FBMax"); } }
            }
        }

        public class FSDBKTestItem : TestItem
        {
            private ushort uslow_clk = 0x5503;
            public ushort SlowClock
            {
                get { return uslow_clk; }
                set { if (value != uslow_clk) { uslow_clk = value; OnPropertyChanged("SlowClock"); } }
            }

            private ushort ufast_clk = 0x5501;
            public ushort FastClock
            {
                get { return ufast_clk; }
                set { if (value != ufast_clk) { ufast_clk = value; OnPropertyChanged("FastClock"); } }
            }

            private ushort intergralTime = 1;
            public ushort IntegralTime
            {
                get { return intergralTime; }
                set { if (value != intergralTime) { intergralTime = value; OnPropertyChanged("IntegralTime"); } }
            }

            private bool scaleCheck = true;
            public bool ScaleCheck
            {
                get { return scaleCheck; }
                set { if (value != scaleCheck) { scaleCheck = value; OnPropertyChanged("ScaleCheck"); } }
            }

            private int fsdMin = 10;
            public int FSDMin
            {
                get { return fsdMin; }
                set { if (value != fsdMin) { fsdMin = value; OnPropertyChanged("FsdMin"); } }
            }

            private bool fsdReCheck = false;
            public bool FSDReCheck
            {
                get { return fsdReCheck; }
                set { if (value != fsdReCheck) { fsdReCheck = value; OnPropertyChanged("FSDReCheck"); } }
            }

            private int fsdTrigerMin = -150;
            public int FSDTrigerMin
            {
                get { return fsdTrigerMin; }
                set { if (value != fsdTrigerMin) { fsdTrigerMin = value; OnPropertyChanged("FSDTrigerMin"); } }
            }

            private int fsdTrigerMax = 100;
            public int FSDTrigerMax
            {
                get { return fsdTrigerMax; }
                set { if (value != fsdTrigerMax) { fsdTrigerMax = value; OnPropertyChanged("FSDTrigerMax"); } }
            }

            private int fsdSlowCriticalMin = -150;
            public int FSDSlowCriticalMin
            {
                get { return fsdSlowCriticalMin; }
                set { if (value != fsdSlowCriticalMin) { fsdSlowCriticalMin = value; OnPropertyChanged("FSDSlowCriticalMin"); } }
            }

            private int fsdSlowCriticalMax = 2;
            public int FSDSlowCriticalMax
            {
                get { return fsdSlowCriticalMax; }
                set { if (value != fsdSlowCriticalMax) { fsdSlowCriticalMax = value; OnPropertyChanged("FSDSlowCriticalMax"); } }
            }

            private int fsdBesidesMin = 5;
            public int FSDBesidesMin
            {
                get { return fsdBesidesMin; }
                set { if (value != fsdBesidesMin) { fsdBesidesMin = value; OnPropertyChanged("FSDBesidesMin"); } }
            }

            private int fsdFastCriticalMax = 2;
            public int FSDFastCriticalMax
            {
                get { return fsdFastCriticalMax; }
                set { if (value != fsdFastCriticalMax) { fsdFastCriticalMax = value; OnPropertyChanged("FSDFastCriticalMax"); } }
            }

            private bool fbCheck = false;
            public bool FBCheck
            {
                get { return fbCheck; }
                set { if (value != fbCheck) { fbCheck = value; OnPropertyChanged("FBCheck"); } }
            }

            private int fbBaseLine = 80;
            public int FBBaseLine
            {
                get { return fbBaseLine; }
                set { if (value != fbBaseLine) { fbBaseLine = value; OnPropertyChanged("FBBaseLine"); } }
            }

            private int fbMin = -20;
            public int FBMin
            {
                get { return fbMin; }
                set { if (value != fbMin) { fbMin = value; OnPropertyChanged("FBMin"); } }
            }

            private int fbMax = 20;
            public int FBMax
            {
                get { return fbMax; }
                set { if (value != fbMax) { fbMax = value; OnPropertyChanged("FBMax"); } }
            }
        }

        public class CurrentTestItem : TestItem
        {
            private int workCurrentMin = -100;
            public int WorkCurrentMin
            {
                get { return workCurrentMin; }
                set { if (value != workCurrentMin) { workCurrentMin = value; OnPropertyChanged("WorkCurrentMin"); } }
            }

            private int workCurrentMax = 10;
            public int WorkCurrentMax
            {
                get { return workCurrentMax; }
                set { if (value != workCurrentMax) { workCurrentMax = value; OnPropertyChanged("WorkCurrentMax"); } }
            }

            private int sleepCurrentMin = -100;
            public int SleepCurrentMin
            {
                get { return sleepCurrentMin; }
                set { if (value != sleepCurrentMin) { sleepCurrentMin = value; OnPropertyChanged("SleepCurrentMin"); } }
            }

            private int sleepCurrentMax = 10;
            public int SleepCurrentMax
            {
                get { return sleepCurrentMax; }
                set { if (value != sleepCurrentMax) { sleepCurrentMax = value; OnPropertyChanged("SleepCurrentMax"); } }
            }

            private int activeCurrentMin = 5500;
            public int ActiveCurrentMin
            {
                get { return activeCurrentMin; }
                set { if (value != activeCurrentMin) { activeCurrentMin = value; OnPropertyChanged("ActiveCurrentMin"); } }
            }

            private int activeCurrentMax = 9000;
            public int ActiveCurrentMax
            {
                get { return activeCurrentMax; }
                set { if (value != activeCurrentMax) { activeCurrentMax = value; OnPropertyChanged("ActiveCurrentMax"); } }
            }
			
			private int deltaCurrentMin = -100;
            public int DeltaCurrentMin
            {
                get { return deltaCurrentMin; }
                set { if (value != deltaCurrentMin) { deltaCurrentMin = value; OnPropertyChanged("DeltaCurrentMin"); } }
            }

            private int deltaCurrentMax = 100;
            public int DeltaCurrentMax
            {
                get { return deltaCurrentMax; }
                set { if (value != deltaCurrentMax) { deltaCurrentMax = value; OnPropertyChanged("DeltaCurrentMax"); } }
            }

//             private ushort action = 0x00;
//             public ushort Action
//             {
//                 get { return action; }
//                 set { if (value != action) { action = value; OnPropertyChanged("Action"); } }
//             }
// 
//             private IList<SEMI.Util.SMDefinition> listActions = new List<SEMI.Util.SMDefinition>()
//             {
//                 new SEMI.Util.SMDefinition(0x80, "sleep"),
//                 new SEMI.Util.SMDefinition(0x40, "stop"),
//                 new SEMI.Util.SMDefinition(0x00, "active"),
//             };
//             public IList<SEMI.Util.SMDefinition> ListActions
//             {
//                 get { return listActions; }
//                 set { if (value != listActions) { listActions = value; OnPropertyChanged("ListActions"); } }
//             }
        }

        public class OSCTrimTestItem : TestItem
        {
            private int oscTrimStandard = 607500;
            public int OSCTrimStandard
            {
                get { return oscTrimStandard; }
                set { if (value != oscTrimStandard) { oscTrimStandard = value; OnPropertyChanged("OSCTrimStandard"); } }
            }

            private int oscTrimMin = 0x50;
            public int OSCTrimMin
            {
                get { return oscTrimMin; }
                set { if (value != oscTrimMin) { oscTrimMin = value; OnPropertyChanged("OSCTrimMin"); } }
            }

            private int oscTrimMax = 0xCF;
            public int OSCTrimMax
            {
                get { return oscTrimMax; }
                set { if (value != oscTrimMax) { oscTrimMax = value; OnPropertyChanged("OSCTrimMax"); } }
            }

            private int offsetTick = 50;
            public int OffsetTick
            {
                get { return offsetTick; }
                set { if (value != offsetTick) { offsetTick = value; OnPropertyChanged("OffsetTick"); } }
            }

            private bool mustTest = true;
            public bool MustTest
            {
                get { return  mustTest; }
                set { if (value != mustTest) { mustTest = value; OnPropertyChanged("MustTest"); } }
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

            private int syncLength = 122;
            public int SyncLength
            {
                get { return syncLength; }
                set { if (value != syncLength) { syncLength = value; OnPropertyChanged("SyncLength"); } }
            }

            private ushort sync_type = 0;
            public ushort SyncType
            {
                get { return sync_type; }
                set { if (value != sync_type) { sync_type = value; OnPropertyChanged("SyncType"); } }
            }

            private IList<SEMI.Util.SMDefinition> syncTypeList = new List<SEMI.Util.SMDefinition>()
            {
                new SEMI.Util.SMDefinition( 0, "RW" ),
                new SEMI.Util.SMDefinition( 3, "BS" ),
            };
            public IList<SEMI.Util.SMDefinition> SyncTypeList
            {
                get { return syncTypeList; }
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

        public class RawDataTestItem : TestItem
        {
            private int rawdataMin = 3000;
            public int RawDataMin
            {
                get { return rawdataMin; }
                set { if (value != rawdataMin) { rawdataMin = value; OnPropertyChanged("RawDataMin"); } }
            }

            private int rawdataMax = 16000;
            public int RawDataMax
            {
                get { return rawdataMax; }
                set { if (value != rawdataMax) { rawdataMax = value; OnPropertyChanged("RawDataMax"); } }
            }
        }

        protected class NoiseTestItem : TestItem
        {
            private int noiseFrame = 100;
            public int NoiseFrame
            {
                get { return noiseFrame; }
                set { if (value != noiseFrame) { noiseFrame = value; OnPropertyChanged("NoiseFrame"); } }
            }

            private int noiseMax = 100;
            public int NoiseMax
            {
                get { return noiseMax; }
                set { if (value != noiseMax) { noiseMax = value; OnPropertyChanged("NoiseMax"); } }
            }
        }

        protected class VPTestItem : TestItem
        {
            private int vpTrigger = 100;
            public int VpTrigger
            {
                get { return vpTrigger; }
                set { if (value != vpTrigger) { vpTrigger = value; OnPropertyChanged("VpTrigger"); } }
            }

            private int vpMin = 100;
            public int VpMin
            {
                get { return vpMin; }
                set { if (value != vpMin) { vpMin = value; OnPropertyChanged("VpMin"); } }
            }

            private int outTime = 15;
            public int OutTime
            {
                get { return outTime; }
                set { if (value != outTime) { outTime = value; OnPropertyChanged("OutTime"); } }
            }
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
            //private int lowLevelIIC = 500;
            //public int LowLevelIIC
            //{
            //    get { return lowLevelIIC; }
            //    set { lowLevelIIC = value; OnPropertyChanged("LowLevelIIC"); }
            //}

            //private int lowLevelINT = 500;
            //public int LowLevelINT
            //{
            //    get { return lowLevelINT; }
            //    set { lowLevelINT = value; OnPropertyChanged("LowLevelINT"); }
            //}

            //private int highLevelIIC = 2500;
            //public int HighLevelIIC
            //{
            //    get { return highLevelIIC; }
            //    set { highLevelIIC = value; OnPropertyChanged("HighLevelIIC"); }
            //}

            //private int highLevelINT = 2500;
            //public int HighLevelINT
            //{
            //    get { return highLevelINT; }
            //    set { highLevelINT = value; OnPropertyChanged("HighLevelINT"); }
            //}
        }

        protected static IList<TestItem> testItems = new List<TestItem>()
        {
            new TestItem(){ ID = 1, Name = "int_test", ItemText = "Int", MustRequied = true },
            new TestItem(){ ID = 2, Name = "reset_test", ItemText = "Reset", MustRequied = true },
            new OSTestItem(){ ID = 3, Name = "os_test", ItemText = "OS", MustRequied = true },
            new FSDTestItem(){ ID = 4, Name = "fsd_test", ItemText = "FSD", MustRequied = true, FastClock= 0x5501 },    
            new BootTestItem(){ ID = 5, Name = "boot_test", ItemText = "Boot", MustRequied = false },
            new ConfigTestItem(){ ID = 6, Name = "config_test", ItemText = "Config", MustRequied = false },
            new CurrentTestItem(){ ID = 7, Name = "current_test", ItemText = "Current", MustRequied = false },
            new OSCTrimTestItem(){ID = 8, Name= "osctrim_test", ItemText="OSCTrim", MustRequied=true},
            new MTKVersionTestItem(){ID = 9, Name="mtkversion_test", ItemText="MTKVersion", MustRequied=true},
            new RawDataTestItem(){ID = 10, Name="rawdata_test", ItemText="RawData", MustRequied=false},
            new NoiseTestItem(){ID = 11, Name="noise_test", ItemText="Noise", MustRequied=false},
            new IOVotageTestItem{ID = 12, Name="iovol_test", ItemText="IoVoltage", MustRequied=false},
            new FSDBKTestItem(){ ID = 13, Name = "fsdbk_test", ItemText = "FSDBK", MustRequied = false, FastClock= 0x5501 },
            new VPTestItem{ID = 14, Name="vp_test", ItemText="VP", MustRequied=false},
            new TestItem(){ ID = 15, Name = "algorithm_test", ItemText = "Algorithm", MustRequied = true },
            new TestItem(){ ID = 16, Name = "misc_test", ItemText = "MISC", MustRequied = true },
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
//             SelectItemByName(stNode, "os_test");
//             SelectItemByName(stNode, "fsd_test");
//             SelectItemByName(stNode, "current_test");
//             SelectItemByName(stNode, "osctrim_test");
//             SelectItemByName(stNode, "mtkversion_test");
//             SelectItemByName(stNode, "base_test");
//             SelectItemByName(stNode, "noise_test");
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
//             SaveItemByName(stNode, "os_test");
//             SaveItemByName(stNode, "fsd_test");
//             SaveItemByName(stNode, "current_test");
//             SaveItemByName(stNode, "osctrim_test");
//             SaveItemByName(stNode, "mtkversion_test");
//             SaveItemByName(stNode, "base_test");
//             SaveItemByName(stNode, "noise_test");

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
