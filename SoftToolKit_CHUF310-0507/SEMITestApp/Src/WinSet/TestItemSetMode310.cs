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
        public void RegistReflex310TestItemSetMode()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_310, "SEMITestApp.Src.WinSet.TestItemSetMode310", SEMI.Util.ChipReflex.SEMI_TEST_ITEM_SET_MODE);
        }
    }
    public class TestItemSetMode310 : SettingMode
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

            private int idleCurrentMin = 0;
            public int IdleCurrentMin
            {
                get { return idleCurrentMin; }
                set { if (value != idleCurrentMin) { idleCurrentMin = value; OnPropertyChanged("IdleCurrentMin"); } }
            }

            private int idleCurrentMax = 100;
            public int IdleCurrentMax
            {
                get { return idleCurrentMax; }
                set { if (value != idleCurrentMax) { idleCurrentMax = value; OnPropertyChanged("IdleCurrentMax"); } }
            }
            //private int vbusactiveCurrentMin = 10;
            //public int VbusActiveCurrentMin
            //{
            //    get { return vbusactiveCurrentMin; }
            //    set { if (value != vbusactiveCurrentMin) { vbusactiveCurrentMin = value; OnPropertyChanged("VbusActiveCurrentMin"); } }
            //}

            //private int vbusactiveCurrentMax = 60;
            //public int VbusActiveCurrentMax
            //{
            //    get { return vbusactiveCurrentMax; }
            //    set { if (value != vbusactiveCurrentMax) { vbusactiveCurrentMax = value; OnPropertyChanged("VbusActiveCurrentMax"); } }
            //}

            //private int vbussleepCurrentMin = 0;
            //public int VbusSleepCurrentMin
            //{
            //    get { return vbussleepCurrentMin; }
            //    set { if (value != vbussleepCurrentMin) { vbussleepCurrentMin = value; OnPropertyChanged("VbusSleepCurrentMin"); } }
            //}

            //private int vbussleepCurrentMax = 240;
            //public int VbusSleepCurrentMax
            //{
            //    get { return vbussleepCurrentMax; }
            //    set { if (value != vbussleepCurrentMax) { vbussleepCurrentMax = value; OnPropertyChanged("VbusSleepCurrentMax"); } }
            //}

            //private int vbusdeepCurrentMin = 0;
            //public int VbusDeepCurrentMin
            //{
            //    get { return vbusdeepCurrentMin; }
            //    set { if (value != vbusdeepCurrentMin) { vbusdeepCurrentMin = value; OnPropertyChanged("VbusDeepCurrentMin"); } }
            //}

            //private int vbusdeepCurrentMax = 100;
            //public int VbusDeepCurrentMax
            //{
            //    get { return vbusdeepCurrentMax; }
            //    set { if (value != vbusdeepCurrentMax) { vbusdeepCurrentMax = value; OnPropertyChanged("VbusDeepCurrentMax"); } }
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

            private int trim52MStandard = 52000;
            public int Trim52MStandard
            {
                get { return trim52MStandard; }
                set { if (value != trim52MStandard) { trim52MStandard = value; OnPropertyChanged("Trim52MStandard"); } }
            }
            private int trim52MStandardNo1 = 52000;//--
            public int Trim52MStandardNo1
            {
                get { return trim52MStandardNo1; }
                set { if (value != trim52MStandardNo1) { trim52MStandardNo1 = value; OnPropertyChanged("Trim52MStandardNo1"); } }
            }

            private int trim52MStandardNo2 = 41600;//--
            public int Trim52MStandardNo2
            {
                get { return trim52MStandardNo2; }
                set { if (value != trim52MStandardNo2) { trim52MStandardNo2 = value; OnPropertyChanged("Trim52MStandardNo2"); } }
            }

            private int trim52MStandardNo3 = 62400;
            public int Trim52MStandardNo3
            {
                get { return trim52MStandardNo3; }
                set { if (value != trim52MStandardNo3) { trim52MStandardNo3 = value; OnPropertyChanged("Trim52MStandardNo3"); } }
            }


            private int trim52MMin = 0x25;
            public int Trim52MMin
            {
                get { return trim52MMin; }
                set { if (value != trim52MMin) { trim52MMin = value; OnPropertyChanged("Trim52MMin"); } }
            }

            private int trim52MMax = 0x1d4;
            public int Trim52MMax
            {
                get { return trim52MMax; }
                set { if (value != trim52MMax) { trim52MMax = value; OnPropertyChanged("Trim52MMax"); } }
            }

            private uint offset52M = 30;
            public uint Offset52M
            {
                get { return offset52M; }
                set { if (value != offset52M) { offset52M = value; OnPropertyChanged("Offset52M"); } }
            }

            private int speedMode = 0;
            public int SpeedMode
            {
                get { return speedMode; }
                set { if (speedMode != value) { speedMode = value; OnPropertyChanged("SpeedMode"); } }
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

        //public class ScapRawDataTest : TestItem
        //{
        //    private int scapRawDataMin = 3000;
        //    public int ScapRawDataMin
        //    {
        //        get { return scapRawDataMin; }
        //        set { if (value != scapRawDataMin) { scapRawDataMin = value; OnPropertyChanged("ScapRawDataMin"); } }
        //    }

        //    private int scapRawDataMax = 16000;
        //    public int ScapRawDataMax
        //    {
        //        get { return scapRawDataMax; }
        //        set { if (value != scapRawDataMax) { scapRawDataMax = value; OnPropertyChanged("ScapRawDataMax"); } }
        //    }
        //}

        //public class MISCTestItem : TestItem
        //{
        //    private ushort miscMode = 0x0001;
        //    public ushort MiscMode
        //    {
        //        get { return miscMode; }
        //        set { if (value != miscMode) { miscMode = value; OnPropertyChanged("MiscMode"); } }
        //    }
        //}

        public class PixelDefectTestItem : TestItem
        {
            private short pixel_raw_max = 900;
            public short Pixel_raw_max
            {
                get { return pixel_raw_max; }
                set { if (value != pixel_raw_max) { pixel_raw_max = value; OnPropertyChanged("Pixel_raw_max"); } }
            }

            private short pixel_raw_min = 900;
            public short Pixel_raw_min
            {
                get { return pixel_raw_min; }
                set { if (value != pixel_raw_min) { pixel_raw_min = value; OnPropertyChanged("Pixel_raw_min"); } }
            }

            private double gain1_0_max = 2;
            public double Gain1_0_max
            {
                get { return gain1_0_max; }
                set { if (value != gain1_0_max) { gain1_0_max = value; OnPropertyChanged("Gain1_0_max"); } }
            }

            private double gain1_0_min = 1;
            public double Gain1_0_min
            {
                get { return gain1_0_min; }
                set { if (value != gain1_0_min) { gain1_0_min = value; OnPropertyChanged("Gain1_0_min"); } }
            }

            private double gain2_1_max = 2;
            public double Gain2_1_max
            {
                get { return gain2_1_max; }
                set { if (value != gain2_1_max) { gain2_1_max = value; OnPropertyChanged("Gain2_1_max"); } }
            }

            private double gain2_1_min = 1;
            public double Gain2_1_min
            {
                get { return gain2_1_min; }
                set { if (value != gain2_1_min) { gain2_1_min = value; OnPropertyChanged("Gain2_1_min"); } }
            }

        }

        public class FRTTestItem : TestItem
        {

        }

        public class IOVotageTestItem : TestItem
        {
            private int lowInt0_1p2_Min = 0;
            public int LowInt0_1p2_Min
            {
                get { return lowInt0_1p2_Min; }
                set { if (value != lowInt0_1p2_Min) { lowInt0_1p2_Min = (ushort)value; OnPropertyChanged("LowInt0_1p2_Min"); } }
            }

            private int lowInt0_1p2_Max = 0;
            public int LowInt0_1p2_Max
            {
                get { return lowInt0_1p2_Max; }
                set { if (value != lowInt0_1p2_Max) { lowInt0_1p2_Max = (ushort)value; OnPropertyChanged("LowInt0_1p2_Max"); } }
            }

            private int highInt0_1p2_Min = 0;
            public int HighInt0_1p2_Min
            {
                get { return highInt0_1p2_Min; }
                set { if (value != highInt0_1p2_Min) { highInt0_1p2_Min = (ushort)value; OnPropertyChanged("HighInt0_1p2_Min"); } }
            }

            private int highInt0_1p2_Max = 0;
            public int HighInt0_1p2_Max
            {
                get { return highInt0_1p2_Max; }
                set { if (value != highInt0_1p2_Max) { highInt0_1p2_Max = (ushort)value; OnPropertyChanged("HighInt0_1p2_Max"); } }
            }

            private int lowInt2_1p2_Min = 0;
            public int LowInt2_1p2_Min
            {
                get { return lowInt2_1p2_Min; }
                set { if (value != lowInt2_1p2_Min) { lowInt2_1p2_Min = (ushort)value; OnPropertyChanged("LowInt2_1p2_Min"); } }
            }

            private int lowInt2_1p2_Max = 0;
            public int LowInt2_1p2_Max
            {
                get { return lowInt2_1p2_Max; }
                set { if (value != lowInt2_1p2_Max) { lowInt2_1p2_Max = (ushort)value; OnPropertyChanged("LowInt2_1p2_Max"); } }
            }

            private int highInt2_1p2_Min = 0;
            public int HighInt2_1p2_Min
            {
                get { return highInt2_1p2_Min; }
                set { if (value != highInt2_1p2_Min) { highInt2_1p2_Min = (ushort)value; OnPropertyChanged("HighInt2_1p2_Min"); } }
            }

            private int highInt2_1p2_Max = 0;
            public int HighInt2_1p2_Max
            {
                get { return highInt2_1p2_Max; }
                set { if (value != highInt2_1p2_Max) { highInt2_1p2_Max = (ushort)value; OnPropertyChanged("HighInt2_1p2_Max"); } }
            }


            private int lowInt0_1p8_Min = 0;
            public int LowInt0_1p8_Min
            {
                get { return lowInt0_1p8_Min; }
                set { if (value != lowInt0_1p8_Min) { lowInt0_1p8_Min = (ushort)value; OnPropertyChanged("LowInt0_1p8_Min"); } }
            }

            private int lowInt0_1p8_Max = 0;
            public int LowInt0_1p8_Max
            {
                get { return lowInt0_1p8_Max; }
                set { if (value != lowInt0_1p8_Max) { lowInt0_1p8_Max = (ushort)value; OnPropertyChanged("LowInt0_1p8_Max"); } }
            }

            private int highInt0_1p8_Min = 0;
            public int HighInt0_1p8_Min
            {
                get { return highInt0_1p8_Min; }
                set { if (value != highInt0_1p8_Min) { highInt0_1p8_Min = (ushort)value; OnPropertyChanged("HighInt0_1p8_Min"); } }
            }

            private int highInt0_1p8_Max = 0;
            public int HighInt0_1p8_Max
            {
                get { return highInt0_1p8_Max; }
                set { if (value != highInt0_1p8_Max) { highInt0_1p8_Max = (ushort)value; OnPropertyChanged("HighInt0_1p8_Max"); } }
            }

            private int lowInt2_1p8_Min = 0;
            public int LowInt2_1p8_Min
            {
                get { return lowInt2_1p8_Min; }
                set { if (value != lowInt2_1p8_Min) { lowInt2_1p8_Min = (ushort)value; OnPropertyChanged("LowInt2_1p8_Min"); } }
            }

            private int lowInt2_1p8_Max = 0;
            public int LowInt2_1p8_Max
            {
                get { return lowInt2_1p8_Max; }
                set { if (value != lowInt2_1p8_Max) { lowInt2_1p8_Max = (ushort)value; OnPropertyChanged("LowInt2_1p8_Max"); } }
            }

            private int highInt2_1p8_Min = 0;
            public int HighInt2_1p8_Min
            {
                get { return highInt2_1p8_Min; }
                set { if (value != highInt2_1p8_Min) { highInt2_1p8_Min = (ushort)value; OnPropertyChanged("HighInt2_1p8_Min"); } }
            }

            private int highInt2_1p8_Max = 0;
            public int HighInt2_1p8_Max
            {
                get { return highInt2_1p8_Max; }
                set { if (value != highInt2_1p8_Max) { highInt2_1p8_Max = (ushort)value; OnPropertyChanged("HighInt2_1p8_Max"); } }
            }



        }

        //public class STCTestItem : TestItem
        //{
        //    private ushort clk = 20;
        //    public ushort Clk
        //    {
        //        get { return clk; }
        //        set { if (value != clk) { clk = (ushort)value; OnPropertyChanged("Clk"); } }
        //    }

        //    private int stcMin = 3000;
        //    public int STCMin
        //    {
        //        get { return stcMin; }
        //        set { if (value != stcMin) { stcMin = value; OnPropertyChanged("STCMin"); } }
        //    }

        //    private int stcMax = 10000;
        //    public int STCMax
        //    {
        //        get { return stcMax; }
        //        set { if (value != stcMax) { stcMax = value; OnPropertyChanged("STCMax"); } }
        //    }

        //    private int uniformityHorMax = 10;
        //    public int UniformityHorMax
        //    {
        //        get { return uniformityHorMax; }
        //        set { if (value != uniformityHorMax) { uniformityHorMax = value; OnPropertyChanged("UniformityHorMax"); } }
        //    }

        //    private int uniformityVerMax = 10;
        //    public int UniformityVerMax
        //    {
        //        get { return uniformityVerMax; }
        //        set { if (value != uniformityVerMax) { uniformityVerMax = value; OnPropertyChanged("UniformityVerMax"); } }
        //    }
        //}

        //public class MCapRawDataTestItem : TestItem
        //{
        //    private ushort clk = 12;
        //    public ushort Clk
        //    {
        //        get { return clk; }
        //        set { if (value != clk) { clk = (ushort)(value); OnPropertyChanged("Clk"); } }
        //    }

        //    private int rawDataMin = 3000;
        //    public int RawDataMin
        //    {
        //        get { return rawDataMin; }
        //        set { if (value != rawDataMin) { rawDataMin = value; OnPropertyChanged("RawDataMin"); } }
        //    }

        //    private int rawDataMax = 16000;
        //    public int RawDataMax
        //    {
        //        get { return rawDataMax; }
        //        set { if (value != rawDataMax) { rawDataMax = value; OnPropertyChanged("RawDataMax"); } }
        //    }

        //    private int uniformityHorMax = 20;
        //    public int UniformityHorMax
        //    {
        //        get { return uniformityHorMax; }
        //        set { if (value != uniformityHorMax) { uniformityHorMax = value; OnPropertyChanged("UniformityHorMax"); } }
        //    }

        //    private int uniformityVerMax = 20;
        //    public int UniformityVerMax
        //    {
        //        get { return uniformityVerMax; }
        //        set { if (value != uniformityVerMax) { uniformityVerMax = value; OnPropertyChanged("UniformityVerMax"); } }
        //    }

        //    private Boolean chkUniformityHor = true;
        //    public Boolean ChkUniformityHor
        //    {
        //        get { return chkUniformityHor; }
        //        set { if (value != chkUniformityHor) { chkUniformityHor = value; OnPropertyChanged("ChkUniformityHor"); } }
        //    }

        //    private Boolean chkUniformityVer = true;
        //    public Boolean ChkUniformityVer
        //    {
        //        get { return chkUniformityVer; }
        //        set { if (value != chkUniformityVer) { chkUniformityVer = value; OnPropertyChanged("ChkUniformityVer"); } }
        //    }

        //    private ushort normalizationRatioMin = 100;
        //    public ushort NormalizationRatioMin
        //    {
        //        get { return normalizationRatioMin; }
        //        set { if (value != normalizationRatioMin) { normalizationRatioMin = (ushort)(value); OnPropertyChanged("NormalizationRatioMin"); } }
        //    }

        //    private ushort normalizationRatioMax = 100;
        //    public ushort NormalizationRatioMax
        //    {
        //        get { return normalizationRatioMax; }
        //        set { if (value != normalizationRatioMax) { normalizationRatioMax = (ushort)(value); OnPropertyChanged("NormalizationRatioMax"); } }
        //    }

        //    private ushort h_V_OverLimitRatio = 100;
        //    public ushort H_V_OverLimitRatio
        //    {
        //        get { return h_V_OverLimitRatio; }
        //        set { if (value != h_V_OverLimitRatio) { h_V_OverLimitRatio = (ushort)(value); OnPropertyChanged("H_V_OverLimitRatio"); } }
        //    }

        //    private ushort h_V_OverLimitMaxNum = 10;
        //    public ushort H_V_OverLimitMaxNum
        //    {
        //        get { return h_V_OverLimitMaxNum; }
        //        set { if (value != h_V_OverLimitMaxNum) { h_V_OverLimitMaxNum = (ushort)(value); OnPropertyChanged("H_V_OverLimitMaxNum"); } }
        //    }
        //}

        //public class WBaseTestItem : TestItem
        //{
        //    private ushort node33DiffMax = 400;
        //    public ushort Node33DiffMax
        //    {
        //        get { return node33DiffMax; }
        //        set { if (value != node33DiffMax) { node33DiffMax = value; OnPropertyChanged("Node33DiffMax"); } }
        //    }

        //    private ushort node33NumMax = 8;
        //    public ushort Node33NumMax
        //    {
        //        get { return node33NumMax; }
        //        set { if (value != node33NumMax) { node33NumMax = value; OnPropertyChanged("Node33NumMax"); } }
        //    }

        //    private ushort alldiffMax = 600;
        //    public ushort AllDiffMax
        //    {
        //        get { return alldiffMax; }
        //        set { if (value != alldiffMax) { alldiffMax = value; OnPropertyChanged("AllDiffMax"); } }
        //    }

        //    private ushort allnumMax = 10;
        //    public ushort AllNumMax
        //    {
        //        get { return allnumMax; }
        //        set { if (value != allnumMax) { allnumMax = value; OnPropertyChanged("AllNumMax"); } }
        //    }

        //}

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

        }

        public class NoiseTestItem : TestItem
        {
            private short noiseTestFrames = 32;
            public short NoiseTestFrames
            {
                get { return noiseTestFrames; }
                set { if (value != noiseTestFrames) { noiseTestFrames = value; OnPropertyChanged("NoiseTestFrames"); } }
            }

            private short noiseTestMaxTime_A = 100;
            public short NoiseTestMaxTime_A
            {
                get { return noiseTestMaxTime_A; }
                set { if (value != noiseTestMaxTime_A) { noiseTestMaxTime_A = value; OnPropertyChanged("NoiseTestMaxTime_A"); } }
            }
            private short noiseTestMaxTime_P = 100;
            public short NoiseTestMaxTime_P
            {
                get { return noiseTestMaxTime_P; }
                set { if (value != noiseTestMaxTime_P) { noiseTestMaxTime_P = value; OnPropertyChanged("NoiseTestMaxTime_P"); } }
            }

            private short noiseTestMaxSpace_A = 100;
            public short NoiseTestMaxSpace_A
            {
                get { return noiseTestMaxSpace_A; }
                set { if (value != noiseTestMaxSpace_A) { noiseTestMaxSpace_A = value; OnPropertyChanged("NoiseTestMaxSpace_A"); } }
            }
            private short noiseTestMaxSpace_P = 100;
            public short NoiseTestMaxSpace_P
            {
                get { return noiseTestMaxSpace_P; }
                set { if (value != noiseTestMaxSpace_P) { noiseTestMaxSpace_P = value; OnPropertyChanged("NoiseTestMaxSpace_P"); } }
            }

        }

        //public class FSDTestItem : TestItem
        //{
        //    private ushort fastDiv = 4;
        //    public ushort FastDiv
        //    {
        //        get { return fastDiv; }
        //        set { if (value != fastDiv) { fastDiv = value; OnPropertyChanged("FastDiv"); } }
        //    }

        //    private ushort slowDiv = 10;
        //    public ushort SlowDiv
        //    {
        //        get { return slowDiv; }
        //        set { if (value != slowDiv) { slowDiv = value; OnPropertyChanged("SlowDiv"); } }
        //    }

        //    private byte xynum = 0x15;
        //    public byte xy_num
        //    {
        //        get { return xynum; }
        //        set { if (value != xynum) { xynum = value; OnPropertyChanged("xy_num"); } }
        //    }

        //    private byte i2vrfb = 0x20;
        //    public byte i2v_rfb
        //    {
        //        get { return i2vrfb; }
        //        set { if (value != i2vrfb) { i2vrfb = value; OnPropertyChanged("i2v_rfb"); } }
        //    }

        //    private byte lpfsft = 0x06;
        //    public byte lpf_sft
        //    {
        //        get { return lpfsft; }
        //        set { if (value != lpfsft) { lpfsft = value; OnPropertyChanged("lpf_sft"); } }
        //    }

        //    private byte decsft = 0x03;
        //    public byte dec_sft
        //    {
        //        get { return decsft; }
        //        set { if (value != decsft) { decsft = value; OnPropertyChanged("dec_sft"); } }
        //    }

        //    private byte c2vrfb = 0x04;
        //    public byte c2v_rfb
        //    {
        //        get { return c2vrfb; }
        //        set { if (value != c2vrfb) { c2vrfb = value; OnPropertyChanged("c2v_rfb"); } }
        //    }

        //    private byte rxrin = 0x00;
        //    public byte rx_rin
        //    {
        //        get { return rxrin; }
        //        set { if (value != rxrin) { rxrin = value; OnPropertyChanged("rx_rin"); } }
        //    }

        //    private ushort fsdFrames = 20;
        //    public ushort FsdFrames
        //    {
        //        get { return fsdFrames; }
        //        set { if (value != fsdFrames) { fsdFrames = value; OnPropertyChanged("FsdFrames"); } }
        //    }
        //    private ushort maxDefault = 600;
        //    public ushort MaxDefault
        //    {
        //        get { return maxDefault; }
        //        set { if (value != maxDefault) { maxDefault = value; OnPropertyChanged("MaxDefault"); } }
        //    }

        //    private bool fastMcapTest = false;
        //    public bool FastMcapTest
        //    {
        //        get { return fastMcapTest; }
        //        set { if (value != fastMcapTest) { fastMcapTest = value; OnPropertyChanged("FastMcapTest"); } }
        //    }

        //    private ushort fastMcapLimit = 30;
        //    public ushort FastMcapLimit
        //    {
        //        get { return fastMcapLimit; }
        //        set { if (value != fastMcapLimit) { fastMcapLimit = value; OnPropertyChanged("FastMcapLimit"); } }
        //    }
        //}

        public class TemperatureTestItem : TestItem
        {

        }

        public class OtpTestItem : TestItem
        {
            private bool onlyCheck = false;
            public bool OnlyCheck
            {
                get { return onlyCheck; }
                set { if (value != onlyCheck) { onlyCheck = value; OnPropertyChanged("OnlyCheck"); } }
            }

            private bool simplelog = false;
            public bool Simplelog
            {
                get { return simplelog; }
                set { if (value != simplelog) { simplelog = value; OnPropertyChanged("Simplelog"); } }
            }

        }

        public class pressure_contact_impedanceTestItem : TestItem
        {

        }

        public class CommunicationTestItem : TestItem
        {

        }

        public class ADCTestItem : TestItem
        {
            private short adc_tx_min = 0;
            public short Adc_tx_min
            {
                get { return adc_tx_min; }
                set { if (value != adc_tx_min) { adc_tx_min = value; OnPropertyChanged("Adc_tx_min"); } }
            }

            private short adc_tx_max = 20;
            public short Adc_tx_max
            {
                get { return adc_tx_max; }
                set { if (value != adc_tx_max) { adc_tx_max = value; OnPropertyChanged("Adc_tx_max"); } }
            }

            private short adc_notx_min = 0;
            public short Adc_notx_min
            {
                get { return adc_notx_min; }
                set { if (value != adc_notx_min) { adc_notx_min = value; OnPropertyChanged("Adc_notx_min"); } }
            }

            private short adc_notx_max = 20;
            public short Adc_notx_max
            {
                get { return adc_notx_max; }
                set { if (value != adc_notx_max) { adc_notx_max = value; OnPropertyChanged("Adc_notx_max"); } }
            }
        }

        public class SRFTestItem : TestItem
        {

            private double srfreq_min = 10.0;
            public double Srfreq_min
            {
                get { return srfreq_min; }
                set { if (value != srfreq_min) { srfreq_min = value; OnPropertyChanged("Srfreq_min"); } }
            }

            private double srfreq_max = 15.0;
            public double Srfreq_max
            {
                get { return srfreq_max; }
                set { if (value != srfreq_max) { srfreq_max = value; OnPropertyChanged("Srfreq_max"); } }
            }


        }

        public class FlyTimeTestItem : TestItem
        {

            private short flytime_code_min = 40;
            public short Flytime_code_min
            {
                get { return flytime_code_min; }
                set { if (value != flytime_code_min) { flytime_code_min = value; OnPropertyChanged("Flytime_code_min"); } }
            }

            private short flytime_code_max = 90;
            public short Flytime_code_max
            {
                get { return flytime_code_max; }
                set { if (value != flytime_code_max) { flytime_code_max = value; OnPropertyChanged("Flytime_code_max"); } }
            }

            private short flytime_val_min = 5000;
            public short Flytime_val_min
            {
                get { return flytime_val_min; }
                set { if (value != flytime_val_min) { flytime_val_min = value; OnPropertyChanged("Flytime_val_min"); } }
            }

            private short flytime_val_max = 20000;
            public short Flytime_val_max
            {
                get { return flytime_val_max; }
                set { if (value != flytime_val_max) { flytime_val_max = value; OnPropertyChanged("Flytime_val_max"); } }
            }

            private short flytime_std_min = 0;
            public short Flytime_std_min
            {
                get { return flytime_std_min; }
                set { if (value != flytime_std_min) { flytime_std_min = value; OnPropertyChanged("Flytime_std_min"); } }
            }

            private short flytime_std_max = 10;
            public short Flytime_std_max
            {
                get { return flytime_std_max; }
                set { if (value != flytime_std_max) { flytime_std_max = value; OnPropertyChanged("Flytime_std_max"); } }
            }

        }


        protected static IList<TestItem> testItems = new List<TestItem>()
        {
            new MTKVersionTestItem(){ID = 1, Name="mtkversion_test", ItemText="MTKVersion", MustRequied=true},
            new TestItem(){ ID = 2, Name = "reset_test", ItemText = "Reset", MustRequied = true },
            new OSCTrimTestItem(){ID = 3, Name= "osctrim_test", ItemText="OSCTrim", MustRequied=true},
            new OtpTestItem(){ID = 4, Name="otp_test", ItemText="OTP", MustRequied=true},
            new CurrentTestItem(){ ID = 5, Name = "current_test", ItemText = "Current", MustRequied = true },
            new IOVotageTestItem{ID = 6, Name="iovol_test", ItemText="IoVoltage", MustRequied=true},

            new ADCTestItem(){ID = 7, Name="adc_test", ItemText="ADC", MustRequied=false},
            new NoiseTestItem(){ID = 8, Name="noise_test", ItemText="Noise", MustRequied=false},
            new PixelDefectTestItem(){ ID = 9, Name = "pixeldefect_test", ItemText = "PixelDefect", MustRequied = false },
            new FlyTimeTestItem(){ID = 10, Name="flytime_test", ItemText="Flytime", MustRequied=false},
            new SRFTestItem(){ID = 11, Name="srf_test", ItemText="SRF", MustRequied=false},

            new BootTestItem(){ ID = 12, Name = "boot_test", ItemText = "Boot", MustRequied = false },
            new ConfigTestItem(){ ID = 13, Name = "config_test", ItemText = "Config", MustRequied = false },
            //new pressure_contact_impedanceTestItem(){ID = 23, Name="pressure_contact_test", ItemText="Pressure_Contact", MustRequied=false},
            //new CommunicationTestItem(){ID = 24, Name="communication_test", ItemText="Communication", MustRequied=false},
            //new TemperatureTestItem(){ID = 21, Name="temperature_test", ItemText="Temperature", MustRequied=false},
            //new TestItem(){ ID = 1, Name = "int_test", ItemText = "Int", MustRequied = true },
            //new MISCTestItem(){ID = 19, Name="misc_test", ItemText="MISC", MustRequied=false},
            //new FSDTestItem(){ID = 20, Name="fsd_test", ItemText="FSD", MustRequied=false},
            //new BaseTestItem(){ID = 10, Name="base_test", ItemText="Base", MustRequied=false},
            //new FRTTestItem(){ID = 11, Name="frt_test", ItemText="FRT", MustRequied=false},
            //new ScapRawDataTest{ID = 13, Name="scap_rawdata_test", ItemText="ScapData", MustRequied=false},
            //new STCTestItem{ID = 14, Name="stc_test", ItemText="STC", MustRequied=false},
            //new MCapRawDataTestItem{ID = 15, Name="mcap_rawdata_test", ItemText="McapData", MustRequied=false},
            //new WBaseTestItem{ID = 16, Name="wbase_test", ItemText="WBase", MustRequied=false},
            //new BaseTestItem(){ID = 17, Name="base_test", ItemText="Base", MustRequied=false},

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
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            foreach (var item in testItems)
                SaveItemByName(stNode, item.Name);


            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
