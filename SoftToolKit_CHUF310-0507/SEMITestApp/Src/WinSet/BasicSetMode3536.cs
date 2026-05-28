using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class BasicSetMode3536 : TestItemSetMode3536
    {
        public override void XMLDataToView()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            var osItem = TestItemList.FirstOrDefault((t) => { return t.Name == "os_test" ? true : false; }) as OSTestItem;
            if (null != osItem)
            {
                osItem.IntegralTime = (ushort)GetXmlAttrbuteValue(stNode, "os_test", "integral", 1);
                osItem.ScaleA = (ushort)GetXmlAttrbuteValue(stNode, "os_test", "scale_a", 0x31);
                osItem.ScaleB = (ushort)GetXmlAttrbuteValue(stNode, "os_test", "scale_b", 0x31);
                osItem.OSClock = (ushort)GetXmlAttrbuteValue(stNode, "os_test", "os_clk", 0x6302);
                osItem.M2Ratio = (int)GetXmlAttrbuteValue(stNode, "os_test", "m2_ratio", 12);
                osItem.M1RatioLowerVa = (int)GetXmlAttrbuteValue(stNode, "os_test", "m1_ratio_lower_va", 18);
                osItem.M1RatioUpperVa = (int)GetXmlAttrbuteValue(stNode, "os_test", "m1_ratio_upper_va", 18);
                osItem.M1RatioLowerRef = (int)GetXmlAttrbuteValue(stNode, "os_test", "m1_ratio_lower_ref", 31);
                osItem.M1RatioUpperRef = (int)GetXmlAttrbuteValue(stNode, "os_test", "m1_ratio_upper_ref", 43);
                osItem.M3DeltaLevel1 = (int)GetXmlAttrbuteValue(stNode, "os_test", "m3_delta_level1", -80);
                osItem.M3DeltaLevel2 = (int)GetXmlAttrbuteValue(stNode, "os_test", "m3_delta_level2", -150);
                osItem.M3DeltaVaMax = (int)GetXmlAttrbuteValue(stNode, "os_test", "m3_delta_va_max", 200);
                osItem.M3DeltaRefMax = (int)GetXmlAttrbuteValue(stNode, "os_test", "m3_delta_ref_max", 200);
            }

            var fsdItem = TestItemList.FirstOrDefault((t) => { return t.Name == "fsd_test" ? true : false; }) as FSDTestItem;
            if (null != fsdItem)
            {
                fsdItem.FastClock = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "f_clk", 0x5501);
                fsdItem.SlowClock = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "s_clk", 0x5503);
                fsdItem.FSDCmpMax = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "cmp_max", 100);
                fsdItem.FSDMin = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_min", 10);
                fsdItem.FSDReCheck = GetXmlAttrbuteValue(stNode, "fsd_test", "recheck", 0) > 0;
                fsdItem.FSDTrigerMin = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "triger_min", 0);
                fsdItem.FSDTrigerMax = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "triger_max", 0);
                fsdItem.FSDSlowCriticalMin = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "slow_critical_min", -150);
                fsdItem.FSDSlowCriticalMax = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "slow_critical_max", 2);
                fsdItem.FSDBesidesMin = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_besides_min", 5);
                fsdItem.FSDFastCriticalMax = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fast_critical_max", 1);
                fsdItem.FSDPlusCheck = GetXmlAttrbuteValue(stNode, "fsd_test", "pluscheck", 0) > 0;
                fsdItem.FSDT1 = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_t1", 10);
                fsdItem.FSDT2 = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_t2", 5);
                fsdItem.FSDT3 = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_t3", -5);
                fsdItem.FSDT4 = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_t4", -20);
                fsdItem.FBCheck = GetXmlAttrbuteValue(stNode, "fsd_test", "fbcheck", 0) > 0;
                fsdItem.FBBaseLine = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fb_base", 80);
                fsdItem.FBMin = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fb_min", -20);
                fsdItem.FBMax = (int)GetXmlAttrbuteValue(stNode, "fsd_test", "fb_max", 20);
                fsdItem.ScaleCheck = GetXmlAttrbuteValue(stNode, "fsd_test", "scale_check", 1) > 0;
                fsdItem.IntegralTime = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "integral", 1);
            }

            var fsdBKItem = TestItemList.FirstOrDefault((t) => { return t.Name == "fsdbk_test" ? true : false; }) as FSDBKTestItem;
            if (null != fsdBKItem)
            {
                fsdBKItem.FastClock = (ushort)GetXmlAttrbuteValue(stNode, "fsdbk_test", "f_clk", 0x5501);
                fsdBKItem.SlowClock = (ushort)GetXmlAttrbuteValue(stNode, "fsdbk_test", "s_clk", 0x5503);
                fsdBKItem.FSDMin = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "fsd_min", 10);
                fsdBKItem.FSDReCheck = GetXmlAttrbuteValue(stNode, "fsdbk_test", "recheck", 0) > 0;
                fsdBKItem.FSDTrigerMin = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "triger_min", 0);
                fsdBKItem.FSDTrigerMax = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "triger_max", 0);
                fsdBKItem.FSDSlowCriticalMin = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "slow_critical_min", -150);
                fsdBKItem.FSDSlowCriticalMax = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "slow_critical_max", 2);
                fsdBKItem.FSDBesidesMin = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "fsd_besides_min", 5);
                fsdBKItem.FSDFastCriticalMax = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "fast_critical_max", 1);
                fsdBKItem.FBCheck = GetXmlAttrbuteValue(stNode, "fsdbk_test", "fbcheck", 0) > 0;
                fsdBKItem.FBBaseLine = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "fb_base", 80);
                fsdBKItem.FBMin = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "fb_min", -20);
                fsdBKItem.FBMax = (int)GetXmlAttrbuteValue(stNode, "fsdbk_test", "fb_max", 20);
                fsdBKItem.ScaleCheck = GetXmlAttrbuteValue(stNode, "fsdbk_test", "scale_check", 1) > 0;
                fsdBKItem.IntegralTime = (ushort)GetXmlAttrbuteValue(stNode, "fsdbk_test", "integral", 1);
            }

            var currentItem = TestItemList.FirstOrDefault((t) => { return t.Name == "current_test" ? true : false; }) as CurrentTestItem;
            if (null != currentItem)
            {
                //currentItem.Action = (ushort)GetXmlAttrbuteValue(stNode, "current_test", "action", 0x00);
                currentItem.WorkCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "work_current_min", -100);
                currentItem.WorkCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "work_current_max", 32);
                currentItem.SleepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_min", -100);
                currentItem.SleepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_max", 32);
                currentItem.DeltaCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "delta_current_min", -100);
                currentItem.DeltaCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "delta_current_max", 100);
                currentItem.ActiveCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "active_current_min", 5500);
                currentItem.ActiveCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "active_current_max", 9000);
            }

            var bootItem = TestItemList.FirstOrDefault((t) => { return t.Name == "boot_test" ? true : false; }) as BootTestItem;
            if (null != bootItem)
            {
                bootItem.OnlyCheck = GetXmlAttrbuteValue(stNode, "boot_test", "only_check", 0) > 0 ? true : false;
            }

            var configItem = TestItemList.FirstOrDefault((t) => { return t.Name == "config_test" ? true : false; }) as ConfigTestItem;
            if (null != configItem)
            {
                configItem.OnlyCheck = GetXmlAttrbuteValue(stNode, "config_test", "only_check", 0) > 0 ? true : false;
            }

            var osctrimItem = TestItemList.FirstOrDefault((t) => { return t.Name == "osctrim_test" ? true : false; }) as OSCTrimTestItem;
            if(null != osctrimItem)
            {
                osctrimItem.OSCTrimStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_standard", 607500);
                osctrimItem.OSCTrimMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "osctrim_min", 0x50);
                osctrimItem.OSCTrimMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "osctrim_max", 0xCF);
                osctrimItem.OffsetTick = GetXmlAttrbuteValue(stNode, "osctrim_test", "offset_tick", 50);
                osctrimItem.MustTest = GetXmlAttrbuteValue(stNode, "osctrim_test", "must_test", 1) > 0;
            }

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                mtkversionItem.MTKVersion = GetXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", 0x51030);
                mtkversionItem.AutoUpdate = (ushort)(GetXmlAttrbuteValue(stNode, "mtkversion_test", "auto_update", 0));
                mtkversionItem.SyncLength = GetXmlAttrbuteValue(stNode, "mtkversion_test", "sync_length", 122);
                mtkversionItem.SyncType = (ushort)GetXmlAttrbuteValue(stNode, "mtkversion_test", "sync_type", 0);
            }

            var rawdataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "rawdata_test" ? true : false; }) as RawDataTestItem;
            if (null != rawdataItem)
            {
                rawdataItem.RawDataMin = GetXmlAttrbuteValue(stNode, "rawdata_test", "rawdata_min", 3000);
                rawdataItem.RawDataMax = GetXmlAttrbuteValue(stNode, "rawdata_test", "rawdata_max", 16000);
            }

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != noiseItem)
            {
                noiseItem.NoiseFrame = GetXmlAttrbuteValue(stNode, "noise_test", "noise_frame", 100);
                noiseItem.NoiseMax = GetXmlAttrbuteValue(stNode, "noise_test", "noise_max", 100);
            }

            var ioVolItem = TestItemList.FirstOrDefault((t) => { return t.Name == "iovol_test" ? true : false; }) as IOVotageTestItem;
            if (null != ioVolItem)
            {
                ioVolItem.LowLevelIntMin = GetXmlAttrbuteValue(stNode, "iovol_test", "int_low_min", 0);
                ioVolItem.LowLevelIntMax = GetXmlAttrbuteValue(stNode, "iovol_test", "int_low_max", 300);
                ioVolItem.HighLevelIntMin = GetXmlAttrbuteValue(stNode, "iovol_test", "int_high_min", 1700);
                ioVolItem.HighLevelIntMax = GetXmlAttrbuteValue(stNode, "iovol_test", "int_high_max", 1900);

                ioVolItem.LowLevelI2cMin = GetXmlAttrbuteValue(stNode, "iovol_test", "iic_low_min", 0);
                ioVolItem.LowLevelI2cMax = GetXmlAttrbuteValue(stNode, "iovol_test", "iic_low_max", 300);
                ioVolItem.HighLevelI2cMin = GetXmlAttrbuteValue(stNode, "iovol_test", "iic_high_min", 1700);
                ioVolItem.HighLevelI2cMax = GetXmlAttrbuteValue(stNode, "iovol_test", "iic_high_max", 1900);
                //ioVolItem.LowLevelINT = GetXmlAttrbuteValue(stNode, "iovol_test", "int_low", 500);
                //ioVolItem.HighLevelINT = GetXmlAttrbuteValue(stNode, "iovol_test", "int_high", 1650);

                //ioVolItem.LowLevelIIC = GetXmlAttrbuteValue(stNode, "iovol_test", "iic_low", 500);
                //ioVolItem.HighLevelIIC = GetXmlAttrbuteValue(stNode, "iovol_test", "iic_high", 1650);
            }

            var vpItem = TestItemList.FirstOrDefault((t) => { return t.Name == "vp_test" ? true : false; }) as VPTestItem;
            if (null != vpItem)
            {
                vpItem.VpTrigger = GetXmlAttrbuteValue(stNode, "vp_test", "vp_trigger", 100);
                vpItem.VpMin = GetXmlAttrbuteValue(stNode, "vp_test", "vp_min", 400);
                vpItem.OutTime = GetXmlAttrbuteValue(stNode, "vp_test", "vp_out_time", 15);
            }
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            var osItem = TestItemList.FirstOrDefault((t) => { return t.Name == "os_test" ? true : false; }) as OSTestItem;
            if (null != osItem)
            {
                SaveXmlAttrbuteValue(stNode, "os_test", "integral", osItem.IntegralTime);
                SaveXmlAttrbuteValue(stNode, "os_test", "scale_a", osItem.ScaleA, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "os_test", "scale_b", osItem.ScaleB, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "os_test", "os_clk", osItem.OSClock, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "os_test", "m1_ratio_lower_va", osItem.M1RatioLowerVa);
                SaveXmlAttrbuteValue(stNode, "os_test", "m1_ratio_upper_va", osItem.M1RatioUpperVa);
                SaveXmlAttrbuteValue(stNode, "os_test", "m1_ratio_lower_ref", osItem.M1RatioLowerRef);
                SaveXmlAttrbuteValue(stNode, "os_test", "m1_ratio_upper_ref", osItem.M1RatioUpperRef);
                SaveXmlAttrbuteValue(stNode, "os_test", "m2_ratio", osItem.M2Ratio);
                SaveXmlAttrbuteValue(stNode, "os_test", "m3_delta_level1", osItem.M3DeltaLevel1);
                SaveXmlAttrbuteValue(stNode, "os_test", "m3_delta_level2", osItem.M3DeltaLevel2);
                SaveXmlAttrbuteValue(stNode, "os_test", "m3_delta_va_max", osItem.M3DeltaVaMax);
                SaveXmlAttrbuteValue(stNode, "os_test", "m3_delta_ref_max", osItem.M3DeltaRefMax);
            }

            var fsdItem = TestItemList.FirstOrDefault((t) => { return t.Name == "fsd_test" ? true : false; }) as FSDTestItem;
            if (null != fsdItem)
            {
                SaveXmlAttrbuteValue(stNode, "fsd_test", "f_clk", fsdItem.FastClock, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "fsd_test", "s_clk", fsdItem.SlowClock, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "fsd_test", "cmp_max", fsdItem.FSDCmpMax);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_min", fsdItem.FSDMin);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "recheck", fsdItem.FSDReCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "triger_min", fsdItem.FSDTrigerMin);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "triger_max", fsdItem.FSDTrigerMax);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "slow_critical_min", fsdItem.FSDSlowCriticalMin);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "slow_critical_max", fsdItem.FSDSlowCriticalMax);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_besides_min", fsdItem.FSDBesidesMin);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fast_critical_max", fsdItem.FSDFastCriticalMax);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "pluscheck", fsdItem.FSDPlusCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_t1", fsdItem.FSDT1);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_t2", fsdItem.FSDT2);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_t3", fsdItem.FSDT3);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_t4", fsdItem.FSDT4);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fbcheck", fsdItem.FBCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fb_base", fsdItem.FBBaseLine);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fb_min", fsdItem.FBMin);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "fb_max", fsdItem.FBMax);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "scale_check", fsdItem.ScaleCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsd_test", "integral", fsdItem.IntegralTime);
            }

            var fsdBKItem = TestItemList.FirstOrDefault((t) => { return t.Name == "fsdbk_test" ? true : false; }) as FSDBKTestItem;
            if (null != fsdBKItem)
            {
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "f_clk", fsdBKItem.FastClock, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "s_clk", fsdBKItem.SlowClock, "0x{0:X}");
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fsd_min", fsdBKItem.FSDMin);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "recheck", fsdBKItem.FSDReCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "triger_min", fsdBKItem.FSDTrigerMin);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "triger_max", fsdBKItem.FSDTrigerMax);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "slow_critical_min", fsdBKItem.FSDSlowCriticalMin);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "slow_critical_max", fsdBKItem.FSDSlowCriticalMax);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fsd_besides_min", fsdBKItem.FSDBesidesMin);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fast_critical_max", fsdBKItem.FSDFastCriticalMax);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fbcheck", fsdBKItem.FBCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fb_base", fsdBKItem.FBBaseLine);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fb_min", fsdBKItem.FBMin);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "fb_max", fsdBKItem.FBMax);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "scale_check", fsdBKItem.ScaleCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "fsdbk_test", "integral", fsdBKItem.IntegralTime);
            }

            var currentItem = TestItemList.FirstOrDefault((t) => { return t.Name == "current_test" ? true : false; }) as CurrentTestItem;
            if (null != currentItem)
            {
                //SaveXmlAttrbuteValue(stNode, "current_test", "action", currentItem.Action);
                SaveXmlAttrbuteValue(stNode, "current_test", "work_current_min", currentItem.WorkCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "work_current_max", currentItem.WorkCurrentMax);
                SaveXmlAttrbuteValue(stNode, "current_test", "sleep_current_min", currentItem.SleepCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "sleep_current_max", currentItem.SleepCurrentMax);
                SaveXmlAttrbuteValue(stNode, "current_test", "delta_current_min", currentItem.DeltaCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "delta_current_max", currentItem.DeltaCurrentMax);
                SaveXmlAttrbuteValue(stNode, "current_test", "active_current_min", currentItem.ActiveCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "active_current_max", currentItem.ActiveCurrentMax);
            }

            var bootItem = TestItemList.FirstOrDefault((t) => { return t.Name == "boot_test" ? true : false; }) as BootTestItem;
            if (null != bootItem)
            {
                SaveXmlAttrbuteValue(stNode, "boot_test", "only_check", bootItem.OnlyCheck ? 1 : 0);
            }

            var configItem = TestItemList.FirstOrDefault((t) => { return t.Name == "config_test" ? true : false; }) as ConfigTestItem;
            if (null != configItem)
            {
                SaveXmlAttrbuteValue(stNode, "config_test", "only_check", configItem.OnlyCheck ? 1 : 0);
            }

            var osctrimItem = TestItemList.FirstOrDefault((t) => { return t.Name == "osctrim_test" ? true : false; }) as OSCTrimTestItem;
            if (null != osctrimItem)
            {
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_standard", osctrimItem.OSCTrimStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "osctrim_min", osctrimItem.OSCTrimMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "osctrim_max", osctrimItem.OSCTrimMax);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "offset_tick", osctrimItem.OffsetTick > 500 ? 500 : osctrimItem.OffsetTick);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "must_test", osctrimItem.MustTest ? 1 : 0);
            }

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", mtkversionItem.MTKVersion);
                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "auto_update", (mtkversionItem.AutoUpdate));

                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "sync_length", mtkversionItem.SyncLength);
                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "sync_type", mtkversionItem.SyncType);
            }

            var rawdataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "rawdata_test" ? true : false; }) as RawDataTestItem;
            if (null != rawdataItem)
            {
                SaveXmlAttrbuteValue(stNode, "rawdata_test", "rawdata_min", rawdataItem.RawDataMin);
                SaveXmlAttrbuteValue(stNode, "rawdata_test", "rawdata_max", rawdataItem.RawDataMax);
            }

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != noiseItem)
            {
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_frame", noiseItem.NoiseFrame);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max", noiseItem.NoiseMax);
            }

            var ioVolItem = TestItemList.FirstOrDefault((t) => { return t.Name == "iovol_test" ? true : false; }) as IOVotageTestItem;
            if (null != ioVolItem)
            {
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int_low_min", ioVolItem.LowLevelIntMin);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int_low_max", ioVolItem.LowLevelIntMax);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int_high_min", ioVolItem.HighLevelIntMin);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int_high_max", ioVolItem.HighLevelIntMax);

                SaveXmlAttrbuteValue(stNode, "iovol_test", "iic_low_min", ioVolItem.LowLevelI2cMin);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "iic_low_max", ioVolItem.LowLevelI2cMax);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "iic_high_min", ioVolItem.HighLevelI2cMin);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "iic_high_max", ioVolItem.HighLevelI2cMax);

                //SaveXmlAttrbuteValue(stNode, "iovol_test", "int_low", ioVolItem.LowLevelINT);
                //SaveXmlAttrbuteValue(stNode, "iovol_test", "int_high", ioVolItem.HighLevelINT);
                //SaveXmlAttrbuteValue(stNode, "iovol_test", "iic_low", ioVolItem.LowLevelIIC);
                //SaveXmlAttrbuteValue(stNode, "iovol_test", "iic_high", ioVolItem.HighLevelIIC);
            }

            var vpItem = TestItemList.FirstOrDefault((t) => { return t.Name == "vp_test" ? true : false; }) as VPTestItem;
            if (null != vpItem)
            {
                SaveXmlAttrbuteValue(stNode, "vp_test", "vp_trigger", vpItem.VpTrigger);
                SaveXmlAttrbuteValue(stNode, "vp_test", "vp_min", vpItem.VpMin);
                SaveXmlAttrbuteValue(stNode, "vp_test", "vp_out_time", vpItem.OutTime > 60 ? 60 : vpItem.OutTime);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
