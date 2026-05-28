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
        public void RegistReflex5562TestItemSetMode()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5562, "SEMITestApp.Src.WinSet.TestItemSetMode5562", SEMI.Util.ChipReflex.SEMI_TEST_ITEM_SET_MODE);
        }
    }
    public class TestItemSetMode5562 : SettingMode
    {
        public class CurrentTestItem : TestItem
        {
            private int activeCurrentMin = 5;
            public int ActiveCurrentMin
            {
                get { return activeCurrentMin; }
                set { if (value != activeCurrentMin) { activeCurrentMin = value; OnPropertyChanged("ActiveCurrentMin"); } }
            }

            private int activeCurrentMax = 60;
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

            private int sleepCurrentMax = 240;
            public int SleepCurrentMax
            {
                get { return sleepCurrentMax; }
                set { if (value != sleepCurrentMax) { sleepCurrentMax = value; OnPropertyChanged("SleepCurrentMax"); } }
            }

            private int deepCurrentMin = 0;
            public int DeepCurrentMin
            {
                get { return deepCurrentMin; }
                set { if (value != deepCurrentMin) { deepCurrentMin = value; OnPropertyChanged("DeepCurrentMin"); } }
            }

            private int deepCurrentMax = 100;
            public int DeepCurrentMax
            {
                get { return deepCurrentMax; }
                set { if (value != deepCurrentMax) { deepCurrentMax = value; OnPropertyChanged("DeepCurrentMax"); } }
            }
            private int vbusactiveCurrentMin = 10;
            public int VbusActiveCurrentMin
            {
                get { return vbusactiveCurrentMin; }
                set { if (value != vbusactiveCurrentMin) { vbusactiveCurrentMin = value; OnPropertyChanged("VbusActiveCurrentMin"); } }
            }

            private int vbusactiveCurrentMax = 60;
            public int VbusActiveCurrentMax
            {
                get { return vbusactiveCurrentMax; }
                set { if (value != vbusactiveCurrentMax) { vbusactiveCurrentMax = value; OnPropertyChanged("VbusActiveCurrentMax"); } }
            }

            private int vbussleepCurrentMin = 0;
            public int VbusSleepCurrentMin
            {
                get { return vbussleepCurrentMin; }
                set { if (value != vbussleepCurrentMin) { vbussleepCurrentMin = value; OnPropertyChanged("VbusSleepCurrentMin"); } }
            }

            private int vbussleepCurrentMax = 240;
            public int VbusSleepCurrentMax
            {
                get { return vbussleepCurrentMax; }
                set { if (value != vbussleepCurrentMax) { vbussleepCurrentMax = value; OnPropertyChanged("VbusSleepCurrentMax"); } }
            }

            private int vbusdeepCurrentMin = 0;
            public int VbusDeepCurrentMin
            {
                get { return vbusdeepCurrentMin; }
                set { if (value != vbusdeepCurrentMin) { vbusdeepCurrentMin = value; OnPropertyChanged("VbusDeepCurrentMin"); } }
            }

            private int vbusdeepCurrentMax = 100;
            public int VbusDeepCurrentMax
            {
                get { return vbusdeepCurrentMax; }
                set { if (value != vbusdeepCurrentMax) { vbusdeepCurrentMax = value; OnPropertyChanged("VbusDeepCurrentMax"); } }
            }
            //private int vbusCurrentMin = 0;
            //public int VbusCurrentMin
            //{
            //    get { return vbusCurrentMin; }
            //    set { if (value != vbusCurrentMin) { vbusCurrentMin = value; OnPropertyChanged("VbusCurrentMin"); } }
            //}

            //private int vbusCurrentMax = 100;
            //public int VbusCurrentMax
            //{
            //    get { return vbusCurrentMax; }
            //    set { if (value != vbusCurrentMax) { vbusCurrentMax = value; OnPropertyChanged("VbusCurrentMax"); } }
            //}
        }

        public class OSCTrimTestItem : TestItem
        {
            private int trim32KStandard = 32;
            public int Trim32KStandard
            {
                get { return trim32KStandard; }
                set { if (value != trim32KStandard) { trim32KStandard = value; OnPropertyChanged("Trim32KStandard"); } }
            }

            private int trim32KMin = 0x10;
            public int Trim32KMin
            {
                get { return trim32KMin; }
                set { if (value != trim32KMin) { trim32KMin = value; OnPropertyChanged("Trim32KMin"); } }
            }

            private int trim32KMax = 0xa1;
            public int Trim32KMax
            {
                get { return trim32KMax; }
                set { if (value != trim32KMax) { trim32KMax = value; OnPropertyChanged("Trim32KMax"); } }
            }

            private uint offset32K = 50;
            public uint Offset32K
            {
                get { return offset32K; }
                set { if (value != offset32K) { offset32K = value; OnPropertyChanged("Offset32K"); } }
            }

            private int trim96MStandard = 96000;
            public int Trim96MStandard
            {
                get { return trim96MStandard; }
                set { if (value != trim96MStandard) { trim96MStandard = value; OnPropertyChanged("Trim96MStandard"); } }
            }
            private int trim96MStandardNo2 = 88000;
            public int Trim96MStandardNo2
            {
                get { return trim96MStandardNo2; }
                set { if (value != trim96MStandardNo2) { trim96MStandardNo2 = value; OnPropertyChanged("Trim96MStandardNo2"); } }
            }

            private int trim96MStandardNo3 = 92000;
            public int Trim96MStandardNo3
            {
                get { return trim96MStandardNo3; }
                set { if (value != trim96MStandardNo3) { trim96MStandardNo3 = value; OnPropertyChanged("Trim96MStandardNo3"); } }
            }

            private int trim96MStandardNo4 = 100000;
            public int Trim96MStandardNo4
            {
                get { return trim96MStandardNo4; }
                set { if (value != trim96MStandardNo4) { trim96MStandardNo4 = value; OnPropertyChanged("Trim96MStandardNo4"); } }
            }

            private int trim96MStandardNo5 = 104000;
            public int Trim96MStandardNo5
            {
                get { return trim96MStandardNo5; }
                set { if (value != trim96MStandardNo5) { trim96MStandardNo5 = value; OnPropertyChanged("Trim96MStandardNo5"); } }
            }

            private int trim96MMin = 0x25;
            public int Trim96MMin
            {
                get { return trim96MMin; }
                set { if (value != trim96MMin) { trim96MMin = value; OnPropertyChanged("Trim96MMin"); } }
            }

            private int trim96MMax = 0x1d4;
            public int Trim96MMax
            {
                get { return trim96MMax; }
                set { if (value != trim96MMax) { trim96MMax = value; OnPropertyChanged("Trim96MMax"); } }
            }

            private uint offset96M = 30;
            public uint Offset96M
            {
                get { return offset96M; }
                set { if (value != offset96M) { offset96M = value; OnPropertyChanged("Offset96M"); } }
            }

            private int speedMode = 0;
            public int SpeedMode
            {
                get { return speedMode; }
                set { if (speedMode != value) { speedMode = value;  OnPropertyChanged("SpeedMode"); } }
            }

            private int trim250MStandard = 250000;
            public int Trim250MStandard
            {
                get { return trim250MStandard; }
                set { if (value != trim250MStandard) { trim250MStandard = value; OnPropertyChanged("Trim250MStandard"); } }
            }

            private int trim250MMin = 0x1;
            public int Trim250MMin
            {
                get { return trim250MMin; }
                set { if (value != trim250MMin) { trim250MMin = value; OnPropertyChanged("Trim250MMin"); } }
            }

            private int trim250MMax = 0x30;
            public int Trim250MMax
            {
                get { return trim250MMax; }
                set { if (value != trim250MMax) { trim250MMax = value; OnPropertyChanged("Trim250MMax"); } }
            }

            private uint offset250M = 100;
            public uint Offset250M
            {
                get { return offset250M; }
                set { if (value != offset250M) { offset250M = value; OnPropertyChanged("Offset250M"); } }
            }

            private bool onlyCheck = false;
            public bool OnlyCheck
            {
                get { return onlyCheck; }
                set { if (value != onlyCheck) { onlyCheck = value; OnPropertyChanged("OnlyCheck"); } }
            }
        }

        public class MTKVersionTestItem : TestItem
        {
            private int mtkVersion = 0xd0516;
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
            private int shortTxMax = 400;
            public int ShortTxMax
            {
                get { return shortTxMax; }
                set { if (value != shortTxMax) { shortTxMax = value; OnPropertyChanged("ShortTxMax"); } }
            }

            private int shortRxMax = 400;
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

            private int highLevelIntMin = 1600;
            public int HighLevelIntMin
            {
                get { return highLevelIntMin; }
                set { highLevelIntMin = value; OnPropertyChanged("HighLevelIntMin"); }
            }

            private int highLevelIntMax = 2000;
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

            private int highLevelI2cMin = 1600;
            public int HighLevelI2cMin
            {
                get { return highLevelI2cMin; }
                set { highLevelI2cMin = value; OnPropertyChanged("HighLevelI2cMin"); }
            }

            private int highLevelI2cMax = 2000;
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

            private int highLevelSpiMin = 1600;
            public int HighLevelSpiMin
            {
                get { return highLevelSpiMin; }
                set { highLevelSpiMin = value; OnPropertyChanged("HighLevelSpiMin"); }
            }

            private int highLevelSpiMax = 2000;
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

            private int rawDataMax = 16000;
            public int RawDataMax
            {
                get { return rawDataMax; }
                set { if (value != rawDataMax) { rawDataMax = value; OnPropertyChanged("RawDataMax"); } }
            }

            private int uniformityHorMax = 20;
            public int UniformityHorMax
            {
                get { return uniformityHorMax; }
                set { if (value != uniformityHorMax) { uniformityHorMax = value; OnPropertyChanged("UniformityHorMax"); } }
            }

            private int uniformityVerMax = 20;
            public int UniformityVerMax
            {
                get { return uniformityVerMax; }
                set { if (value != uniformityVerMax) { uniformityVerMax = value; OnPropertyChanged("UniformityVerMax"); } }
            }

            private Boolean chkUniformityHor = true;
            public Boolean ChkUniformityHor
            {
                get { return chkUniformityHor; }
                set { if (value != chkUniformityHor) { chkUniformityHor = value; OnPropertyChanged("ChkUniformityHor"); } }
            }

            private Boolean chkUniformityVer = true;
            public Boolean ChkUniformityVer
            {
                get { return chkUniformityVer; }
                set { if (value != chkUniformityVer) { chkUniformityVer = value; OnPropertyChanged("ChkUniformityVer"); } }
            }

            private ushort normalizationRatioMin = 100;
            public ushort NormalizationRatioMin
            {
                get { return normalizationRatioMin; }
                set { if (value != normalizationRatioMin) { normalizationRatioMin = (ushort)(value); OnPropertyChanged("NormalizationRatioMin"); } }
            }

            private ushort normalizationRatioMax = 100;
            public ushort NormalizationRatioMax
            {
                get { return normalizationRatioMax; }
                set { if (value != normalizationRatioMax) { normalizationRatioMax = (ushort)(value); OnPropertyChanged("NormalizationRatioMax"); } }
            }

            private ushort h_V_OverLimitRatio = 100;
            public ushort H_V_OverLimitRatio
            {
                get { return h_V_OverLimitRatio; }
                set { if (value != h_V_OverLimitRatio) { h_V_OverLimitRatio = (ushort)(value); OnPropertyChanged("H_V_OverLimitRatio"); } }
            }

            private ushort h_V_OverLimitMaxNum = 10;
            public ushort H_V_OverLimitMaxNum
            {
                get { return h_V_OverLimitMaxNum; }
                set { if (value != h_V_OverLimitMaxNum) { h_V_OverLimitMaxNum = (ushort)(value); OnPropertyChanged("H_V_OverLimitMaxNum"); } }
            }
        }

        public class WBaseTestItem : TestItem
        {
            private ushort node33DiffMax = 400;
            public ushort Node33DiffMax
            {
                get { return node33DiffMax; }
                set { if (value != node33DiffMax) { node33DiffMax = value; OnPropertyChanged("Node33DiffMax"); } }
            }

            private ushort node33NumMax = 8;
            public ushort Node33NumMax
            {
                get { return node33NumMax; }
                set { if (value != node33NumMax) { node33NumMax = value; OnPropertyChanged("Node33NumMax"); } }
            }

            //private ushort node55DiffMax = 300;
            //public ushort Node55DiffMax
            //{
            //    get { return node55DiffMax; }
            //    set { if (value != node55DiffMax) { node55DiffMax = value; OnPropertyChanged("Node55DiffMax"); } }
            //}

            //private ushort node55NumMax = 15;
            //public ushort Node55NumMax
            //{
            //    get { return node55NumMax; }
            //    set { if (value != node55NumMax) { node55NumMax = value; OnPropertyChanged("Node55NumMax"); } }
            //}

            private ushort alldiffMax = 600;
            public ushort AllDiffMax
            {
                get { return alldiffMax; }
                set { if (value != alldiffMax) { alldiffMax = value; OnPropertyChanged("AllDiffMax"); } }
            }

            private ushort allnumMax = 10;
            public ushort AllNumMax
            {
                get { return allnumMax; }
                set { if (value != allnumMax) { allnumMax = value; OnPropertyChanged("AllNumMax"); } }
            }

        }

        public class BaseTestItem : TestItem
        {
            private ushort diffMax = 400;
            public ushort DiffMax
            {
                get { return diffMax; }
                set { if (value != diffMax) { diffMax = value; OnPropertyChanged("DiffMax"); } }
            }

            private ushort numMax = 8;
            public ushort NumMax
            {
                get { return numMax; }
                set { if (value != numMax) { numMax = value; OnPropertyChanged("NumMax"); } }
            }

            private ushort alldiffMax = 600;
            public ushort AllDiffMax
            {
                get { return alldiffMax; }
                set { if (value != alldiffMax) { alldiffMax = value; OnPropertyChanged("AllDiffMax"); } }
            }

            private ushort allnumMax = 10;
            public ushort AllNumMax
            {
                get { return allnumMax; }
                set { if (value != allnumMax) { allnumMax = value; OnPropertyChanged("AllNumMax"); } }
            }

            //private bool saveData = false;
            //public bool SaveData
            //{
            //    get { return saveData; }
            //    set { if (value != saveData) { saveData = value; OnPropertyChanged("SaveData"); } }
            //}
            //private bool simplifyAlgorithm = false;
            //public bool SimplifyAlgorithm
            //{
            //    get { return simplifyAlgorithm; }
            //    set { if (value != simplifyAlgorithm) { simplifyAlgorithm = value; OnPropertyChanged("SimplifyAlgorithm"); } }
            //}

        }

        public class NoiseTestItem : TestItem
        {
            private short noiseTestFrames = 60;
            public short NoiseTestFrames
            {
                get { return noiseTestFrames; }
                set { if (value != noiseTestFrames) { noiseTestFrames = value; OnPropertyChanged("NoiseTestFrames"); } }
            }

            private short noiseMcapBaseValue = 160;
            public short NoiseMcapBaseValue
            {
                get { return noiseMcapBaseValue; }
                set { if (value != noiseMcapBaseValue) { noiseMcapBaseValue = value; OnPropertyChanged("NoiseMcapBaseValue"); } }
            }

            private short noiseScapBaseValue = 160;
            public short NoiseScapBaseValue
            {
                get { return noiseScapBaseValue; }
                set { if (value != noiseScapBaseValue) { noiseScapBaseValue = value; OnPropertyChanged("NoiseScapBaseValue"); } }
            }

            private short noiseTestMaxMcap1 = 100;
            public short NoiseTestMaxMcap1
            {
                get { return noiseTestMaxMcap1; }
                set { if (value != noiseTestMaxMcap1) { noiseTestMaxMcap1 = value; OnPropertyChanged("NoiseTestMaxMcap1"); } }
            }
            private short noiseTestMaxScap1 = 100;
            public short NoiseTestMaxScap1
            {
                get { return noiseTestMaxScap1; }
                set { if (value != noiseTestMaxScap1) { noiseTestMaxScap1 = value; OnPropertyChanged("NoiseTestMaxScap1"); } }
            }

            private short noiseTestMaxMcap2 = 100;
            public short NoiseTestMaxMcap2
            {
                get { return noiseTestMaxMcap2; }
                set { if (value != noiseTestMaxMcap2) { noiseTestMaxMcap2 = value; OnPropertyChanged("NoiseTestMaxMcap2"); } }
            }
            private short noiseTestMaxScap2 = 100;
            public short NoiseTestMaxScap2
            {
                get { return noiseTestMaxScap2; }
                set { if (value != noiseTestMaxScap2) { noiseTestMaxScap2 = value; OnPropertyChanged("NoiseTestMaxScap2"); } }
            }
            private short noiseTestMaxMcap3 = 100;
            public short NoiseTestMaxMcap3
            {
                get { return noiseTestMaxMcap3; }
                set { if (value != noiseTestMaxMcap3) { noiseTestMaxMcap3 = value; OnPropertyChanged("NoiseTestMaxMcap3"); } }
            }
            private short noiseTestMaxScap3 = 100;
            public short NoiseTestMaxScap3
            {
                get { return noiseTestMaxScap3; }
                set { if (value != noiseTestMaxScap3) { noiseTestMaxScap3 = value; OnPropertyChanged("NoiseTestMaxScap3"); } }
            }
            private short noiseTestMaxMcap4 = 100;
            public short NoiseTestMaxMcap4
            {
                get { return noiseTestMaxMcap4; }
                set { if (value != noiseTestMaxMcap4) { noiseTestMaxMcap4 = value; OnPropertyChanged("NoiseTestMaxMcap4"); } }
            }
            private short noiseTestMaxScap4 = 100;
            public short NoiseTestMaxScap4
            {
                get { return noiseTestMaxScap4; }
                set { if (value != noiseTestMaxScap4) { noiseTestMaxScap4 = value; OnPropertyChanged("NoiseTestMaxScap4"); } }
            }
            private short noiseTestMaxMcap5 = 100;
            public short NoiseTestMaxMcap5
            {
                get { return noiseTestMaxMcap5; }
                set { if (value != noiseTestMaxMcap5) { noiseTestMaxMcap5 = value; OnPropertyChanged("NoiseTestMaxMcap5"); } }
            }
            private short noiseTestMaxScap5 = 100;
            public short NoiseTestMaxScap5
            {
                get { return noiseTestMaxScap5; }
                set { if (value != noiseTestMaxScap5) { noiseTestMaxScap5 = value; OnPropertyChanged("NoiseTestMaxScap5"); } }
            }
            private short noiseTestMaxMcap6 = 100;
            public short NoiseTestMaxMcap6
            {
                get { return noiseTestMaxMcap6; }
                set { if (value != noiseTestMaxMcap6) { noiseTestMaxMcap6 = value; OnPropertyChanged("NoiseTestMaxMcap6"); } }
            }
            private short noiseTestMaxScap6 = 100;
            public short NoiseTestMaxScap6
            {
                get { return noiseTestMaxScap6; }
                set { if (value != noiseTestMaxScap6) { noiseTestMaxScap6 = value; OnPropertyChanged("NoiseTestMaxScap6"); } }
            }
            private short noiseTestMaxMcap7 = 100;
            public short NoiseTestMaxMcap7
            {
                get { return noiseTestMaxMcap7; }
                set { if (value != noiseTestMaxMcap7) { noiseTestMaxMcap7 = value; OnPropertyChanged("NoiseTestMaxMcap7"); } }
            }
            private short noiseTestMaxScap7 = 100;
            public short NoiseTestMaxScap7
            {
                get { return noiseTestMaxScap7; }
                set { if (value != noiseTestMaxScap7) { noiseTestMaxScap7 = value; OnPropertyChanged("NoiseTestMaxScap7"); } }
 
            }
            private short noiseTestMaxMcap8 = 100;
            public short NoiseTestMaxMcap8
            {
                get { return noiseTestMaxMcap8; }
                set { if (value != noiseTestMaxMcap8) { noiseTestMaxMcap8 = value; OnPropertyChanged("NoiseTestMaxMcap8"); } }
            }
            private short noiseTestMaxScap8 = 100;
            public short NoiseTestMaxScap8
            {
                get { return noiseTestMaxScap8; }
                set { if (value != noiseTestMaxScap8) { noiseTestMaxScap8 = value; OnPropertyChanged("NoiseTestMaxScap8"); } }
            }
        }

        public class FSDTestItem : TestItem
        {
            private ushort fastDiv = 4;
            public ushort FastDiv
            {
                get { return fastDiv; }
                set { if (value != fastDiv) { fastDiv = value; OnPropertyChanged("FastDiv"); } }
            }

            private ushort slowDiv = 10;
            public ushort SlowDiv
            {
                get { return slowDiv; }
                set { if (value != slowDiv) { slowDiv = value; OnPropertyChanged("SlowDiv"); } }
            }

            private byte xynum = 0x15;
            public byte xy_num
            {
                get { return xynum; }
                set { if (value != xynum) { xynum = value; OnPropertyChanged("xy_num"); } }
            }

            private byte i2vrfb = 0x20;
            public byte i2v_rfb
            {
                get { return i2vrfb; }
                set { if (value != i2vrfb) { i2vrfb = value; OnPropertyChanged("i2v_rfb"); } }
            }

            private byte lpfsft = 0x06;
            public byte lpf_sft
            {
                get { return lpfsft; }
                set { if (value != lpfsft) { lpfsft = value; OnPropertyChanged("lpf_sft"); } }
            }

            private byte decsft = 0x03;
            public byte dec_sft
            {
                get { return decsft; }
                set { if (value != decsft) { decsft = value; OnPropertyChanged("dec_sft"); } }
            }

            private byte c2vrfb = 0x04;
            public byte c2v_rfb
            {
                get { return c2vrfb; }
                set { if (value != c2vrfb) { c2vrfb = value; OnPropertyChanged("c2v_rfb"); } }
            }

            private byte rxrin = 0x00;
            public byte rx_rin
            {
                get { return rxrin; }
                set { if (value != rxrin) { rxrin = value; OnPropertyChanged("rx_rin"); } }
            }

            private ushort fsdFrames = 20;
            public ushort FsdFrames
            {
                get { return fsdFrames; }
                set { if (value != fsdFrames) { fsdFrames = value; OnPropertyChanged("FsdFrames"); } }
            }
            private ushort maxDefault = 600;
            public ushort MaxDefault
            {
                get { return maxDefault; }
                set { if (value != maxDefault) { maxDefault = value; OnPropertyChanged("MaxDefault"); } }
            }

            private bool fastMcapTest = false;
            public bool FastMcapTest
            {
                get { return fastMcapTest; }
                set { if (value != fastMcapTest) { fastMcapTest = value; OnPropertyChanged("FastMcapTest"); } }
            }

            private ushort fastMcapLimit = 30;
            public ushort FastMcapLimit
            {
                get { return fastMcapLimit; }
                set { if (value != fastMcapLimit) { fastMcapLimit = value; OnPropertyChanged("FastMcapLimit"); } }
            }
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
            new ScapRawDataTest{ID = 13, Name="scap_rawdata_test", ItemText="ScapData", MustRequied=false},
            new STCTestItem{ID = 14, Name="stc_test", ItemText="STC", MustRequied=false},
            new MCapRawDataTestItem{ID = 15, Name="mcap_rawdata_test", ItemText="McapData", MustRequied=false},
            new WBaseTestItem{ID = 16, Name="wbase_test", ItemText="WBase", MustRequied=false},
            new BaseTestItem(){ID = 17, Name="base_test", ItemText="Base", MustRequied=false},
            new NoiseTestItem(){ID = 18, Name="noise_test", ItemText="Noise", MustRequied=false},
            new MISCTestItem(){ID = 19, Name="misc_test", ItemText="MISC", MustRequied=false},
            new FSDTestItem(){ID = 20, Name="fsd_test", ItemText="FSD", MustRequied=false},
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
