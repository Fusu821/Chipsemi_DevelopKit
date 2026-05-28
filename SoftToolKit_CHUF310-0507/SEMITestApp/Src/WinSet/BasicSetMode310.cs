using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class BasicSetMode310 : TestItemSetMode310
    {
        public override void XMLDataToView()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

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
            if (null != osctrimItem)
            {
                osctrimItem.Trim32KStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_32k_standard", 32);
                osctrimItem.Trim32KMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_min", 0x10);
                osctrimItem.Trim32KMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_max", 0xa1);
                osctrimItem.Offset32K = (uint)GetXmlAttrbuteValue(stNode, "osctrim_test", "offset_32k", 50);

                osctrimItem.Trim52MStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standard", 52000);
                osctrimItem.Trim52MStandardNo1 = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standardNo1", 52000);
                osctrimItem.Trim52MStandardNo2 = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standardNo2", 41600);
                osctrimItem.Trim52MStandardNo3 = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standardNo3", 62400);
                osctrimItem.Trim52MMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_52m_min", 0x25);
                osctrimItem.Trim52MMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_52m_max", 0x1d4);
                osctrimItem.Offset52M = (uint)GetXmlAttrbuteValue(stNode, "osctrim_test", "offset_52m", 30);

                //osctrimItem.Trim250MStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_250m_standard", 250000);
                //osctrimItem.Trim250MMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_250m_min", 0x1);
                //osctrimItem.Trim250MMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_250m_max", 0x30);
                //osctrimItem.Offset250M = (uint)GetXmlAttrbuteValue(stNode, "osctrim_test", "offset_250m", 100);

                osctrimItem.SpeedMode = GetXmlAttrbuteValue(stNode, "osctrim_test", "speed_mode", 0);

                osctrimItem.OnlyCheck = GetXmlAttrbuteValue(stNode, "osctrim_test", "only_check", 0) > 0 ? true : false;
            }

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                mtkversionItem.MTKVersion = GetXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", 0xd0516);
                mtkversionItem.AutoUpdate = (ushort)(GetXmlAttrbuteValue(stNode, "mtkversion_test", "auto_update", 0));
            }

            //             var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            //             if (null != baseItem)
            //             {
            //                 baseItem.BaseMin = GetXmlAttrbuteValue(stNode, "base_test", "base_min", 3000);
            //                 baseItem.BaseMax = GetXmlAttrbuteValue(stNode, "base_test", "base_max", 16000);
            //             }

            var pixeldefectItem = TestItemList.FirstOrDefault((t) => { return t.Name == "pixeldefect_test" ? true : false; }) as PixelDefectTestItem;
            if (null != pixeldefectItem)
            {
                pixeldefectItem.Pixel_raw_max =(short) GetXmlAttrbuteValue(stNode, "pixeldefect_test", "pixel_raw_max", 400);
                pixeldefectItem.Pixel_raw_min =(short)GetXmlAttrbuteValue(stNode, "pixeldefect_test", "pixel_raw_min", 400);

                pixeldefectItem.Gain1_0_max = GetXmlAttrbuteFloatValue(stNode, "pixeldefect_test", "gain1_0_max", 2);
                pixeldefectItem.Gain1_0_min = GetXmlAttrbuteFloatValue(stNode, "pixeldefect_test", "gain1_0_min", 1);
                pixeldefectItem.Gain2_1_max = GetXmlAttrbuteFloatValue(stNode, "pixeldefect_test", "gain2_1_max", 2);
                pixeldefectItem.Gain2_1_min = GetXmlAttrbuteFloatValue(stNode, "pixeldefect_test", "gain2_1_min", 1);
            }

            var ioVolItem = TestItemList.FirstOrDefault((t) => { return t.Name == "iovol_test" ? true : false; }) as IOVotageTestItem;
            if (null != ioVolItem)
            {
                ioVolItem.LowInt0_1p2_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_low_min", 0);
                ioVolItem.LowInt0_1p2_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_low_max", 100);
                ioVolItem.HighInt0_1p2_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_high_min", 1000);
                ioVolItem.HighInt0_1p2_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_high_max", 1400);

                ioVolItem.LowInt2_1p2_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_low_min", 0);
                ioVolItem.LowInt2_1p2_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_low_max", 100);
                ioVolItem.HighInt2_1p2_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_high_min", 1000);
                ioVolItem.HighInt2_1p2_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_high_max", 1400);

                ioVolItem.LowInt0_1p8_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_low_min", 0);
                ioVolItem.LowInt0_1p8_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_low_max", 100);
                ioVolItem.HighInt0_1p8_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_high_min", 1600);
                ioVolItem.HighInt0_1p8_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_high_max", 2000);

                ioVolItem.LowInt2_1p8_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_low_min", 0);
                ioVolItem.LowInt2_1p8_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_low_max", 100);
                ioVolItem.HighInt2_1p8_Min = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_high_min", 1600);
                ioVolItem.HighInt2_1p8_Max = GetXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_high_max", 2000);

            }

            var currentItem = TestItemList.FirstOrDefault((t) => { return t.Name == "current_test" ? true : false; }) as CurrentTestItem;
            if (null != currentItem)
            {
                currentItem.ActiveCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "active_current_min", 5);
                currentItem.ActiveCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "active_current_max", 60);
                currentItem.SleepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_min", 0);
                currentItem.SleepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_max", 240);
                currentItem.IdleCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "idle_current_min", 0);
                currentItem.IdleCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "idle_current_max", 100);

                //currentItem.VbusActiveCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "vbus_active_current_min", 10);
                //currentItem.VbusActiveCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "vbus_active_current_max", 60);
                //currentItem.VbusSleepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "vbus_sleep_current_min", 0);
                //currentItem.VbusSleepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "vbus_sleep_current_max", 240);
                //currentItem.VbusDeepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "vbus_deep_current_min", 0);
                //currentItem.VbusDeepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "vbus_deep_current_max", 100);
            }

            //var scapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "scap_rawdata_test" ? true : false; }) as ScapRawDataTest;
            //if (null != scapRawDataItem)
            //{
            //    scapRawDataItem.ScapRawDataMin = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_min", 3000);
            //    scapRawDataItem.ScapRawDataMax = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_max", 16000);
            //}

            //var stc_Item = TestItemList.FirstOrDefault((t) => { return t.Name == "stc_test" ? true : false; }) as STCTestItem;
            //if (null != stc_Item)
            //{
            //    stc_Item.Clk = (ushort)GetXmlAttrbuteValue(stNode, "stc_test", "clk_div", 20);
            //    stc_Item.STCMin = GetXmlAttrbuteValue(stNode, "stc_test", "stc_min", 0);
            //    stc_Item.STCMax = GetXmlAttrbuteValue(stNode, "stc_test", "stc_max", 60);
            //    stc_Item.UniformityHorMax = GetXmlAttrbuteValue(stNode, "stc_test", "uniformity_hor_max", 10);
            //    stc_Item.UniformityVerMax = GetXmlAttrbuteValue(stNode, "stc_test", "uniformity_ver_max", 10);
            //}

            //var mcapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mcap_rawdata_test" ? true : false; }) as MCapRawDataTestItem;
            //if (null != mcapRawDataItem)
            //{
            //    mcapRawDataItem.Clk = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "clk_div", 12);
            //    mcapRawDataItem.RawDataMin = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_min", 3000);
            //    mcapRawDataItem.RawDataMax = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_max", 16000);
            //    mcapRawDataItem.UniformityHorMax = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_hor_max", 20);
            //    mcapRawDataItem.UniformityVerMax = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_ver_max", 20);
            //    mcapRawDataItem.ChkUniformityHor = 1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_hor", 1);
            //    mcapRawDataItem.ChkUniformityVer = 1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_ver", 1);
            //    mcapRawDataItem.NormalizationRatioMin = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_min", 100);
            //    mcapRawDataItem.NormalizationRatioMax = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_max", 100);

            //    mcapRawDataItem.H_V_OverLimitRatio = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "h_v_over_limit_ratio", 100);
            //    mcapRawDataItem.H_V_OverLimitMaxNum = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "h_v_over_limit_maxnum", 10);
            //}

            //var wbaseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "wbase_test" ? true : false; }) as WBaseTestItem;
            //if (null != wbaseItem)
            //{
            //    wbaseItem.Node33DiffMax = (ushort)GetXmlAttrbuteValue(stNode, "wbase_test", "wbase_node33_diff_max", 400);
            //    wbaseItem.Node33NumMax = (ushort)GetXmlAttrbuteValue(stNode, "wbase_test", "wbase_node33_num_max", 8);

            //    //wbaseItem.Node55DiffMax = (ushort)GetXmlAttrbuteValue(stNode, "wbase_test", "wbase_node55_diff_max", 300);
            //    //wbaseItem.Node55NumMax = (ushort)GetXmlAttrbuteValue(stNode, "wbase_test", "wbase_node55_num_max", 15);

            //    wbaseItem.AllDiffMax = (ushort)GetXmlAttrbuteValue(stNode, "wbase_test", "wbase_all_diff_max", 600);
            //    wbaseItem.AllNumMax = (ushort)GetXmlAttrbuteValue(stNode, "wbase_test", "wbase_all_num_max", 10);
            //}

            //var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            //if (null != baseItem)
            //{
            //    baseItem.DiffMax = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "base_diff_max", 400);
            //    baseItem.NumMax = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "base_num_max", 8);
            //    baseItem.AllDiffMax = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "base_all_diff_max", 600);
            //    baseItem.AllNumMax = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "base_all_num_max", 10);
            //    //baseItem.CoverDiffMax = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "base_cover_diff_max", 50);
            //    //baseItem.SaveData = GetXmlAttrbuteValue(stNode, "base_test", "base_save_data", 0) > 0 ? true : false;
            //    //baseItem.SimplifyAlgorithm = GetXmlAttrbuteValue(stNode, "base_test", "base_simplify_algorithm", 0) > 0 ? true : false;
            //}

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != noiseItem)
            {
                noiseItem.NoiseTestFrames = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_frames", 32);
                noiseItem.NoiseTestMaxTime_A = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max_time_A", 100);
                noiseItem.NoiseTestMaxSpace_A = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max_space_A", 100);
                noiseItem.NoiseTestMaxTime_P = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max_time_P", 100);
                noiseItem.NoiseTestMaxSpace_P = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max_space_P", 100);
            }

            var srfItem = TestItemList.FirstOrDefault((t) => { return t.Name == "srf_test" ? true : false; }) as SRFTestItem;
            if (null != srfItem)
            {
                srfItem.Srfreq_max = GetXmlAttrbuteFloatValue(stNode, "srf_test", "srfreq_max", 14);
                srfItem.Srfreq_min = GetXmlAttrbuteFloatValue(stNode, "srf_test", "srfreq_min", 10);
            }

            var otpItem = TestItemList.FirstOrDefault((t) => { return t.Name == "otp_test" ? true : false; }) as OtpTestItem;
            if (null != otpItem)
            {
                otpItem.OnlyCheck = GetXmlAttrbuteValue(stNode, "otp_test", "only_check", 0) > 0 ? true : false;
                otpItem.Simplelog = GetXmlAttrbuteValue(stNode, "otp_test", "simplelog", 0) > 0 ? true : false;
            }

            var adcItem = TestItemList.FirstOrDefault((t) => { return t.Name == "adc_test" ? true : false; }) as ADCTestItem;
            if (null != adcItem)
            {
                adcItem.Adc_tx_max = (short)GetXmlAttrbuteValue(stNode, "adc_test", "adc_tx_max", 800);
                adcItem.Adc_tx_min = (short)GetXmlAttrbuteValue(stNode, "adc_test", "adc_tx_min", 100);
                adcItem.Adc_notx_max = (short)GetXmlAttrbuteValue(stNode, "adc_test", "adc_notx_max", 20);
                adcItem.Adc_notx_min = (short)GetXmlAttrbuteValue(stNode, "adc_test", "adc_notx_min", 0);
            }

            var flytimeItem = TestItemList.FirstOrDefault((t) => { return t.Name == "flytime_test" ? true : false; }) as FlyTimeTestItem;
            if (null != flytimeItem)
            {
                flytimeItem.Flytime_code_max = (short)GetXmlAttrbuteValue(stNode, "flytime_test", "flytime_code_max", 90);
                flytimeItem.Flytime_code_min = (short)GetXmlAttrbuteValue(stNode, "flytime_test", "flytime_code_min", 40);
                flytimeItem.Flytime_val_max = (short)GetXmlAttrbuteValue(stNode, "flytime_test", "flytime_val_max", 20000);
                flytimeItem.Flytime_val_min = (short)GetXmlAttrbuteValue(stNode, "flytime_test", "flytime_val_min", 500);
                flytimeItem.Flytime_std_max = (short)GetXmlAttrbuteValue(stNode, "flytime_test", "flytime_std_max", 10);
                flytimeItem.Flytime_std_min = (short)GetXmlAttrbuteValue(stNode, "flytime_test", "flytime_std_min", 0);
            }
            //var miscItem = TestItemList.FirstOrDefault((t) => { return t.Name == "misc_test" ? true : false; }) as MISCTestItem;
            //if (null != miscItem)
            //{
            //    miscItem.MiscMode = (ushort)GetXmlAttrbuteValue(stNode, "misc_test", "misc_mode", 1);
            //}

        //    var fsdItem = TestItemList.FirstOrDefault((t) => { return t.Name == "fsd_test" ? true : false; }) as FSDTestItem;
        //    if (null != fsdItem)
        //    {
        //        fsdItem.FastDiv = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_fast_div", 4);
        //        fsdItem.SlowDiv = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_slow_div", 10);

        //        fsdItem.xy_num = (byte)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_xy_num", 0x15);
        //        fsdItem.i2v_rfb = (byte)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_i2v_rfb", 0x20);

        //        fsdItem.lpf_sft = (byte)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_lpf_sft", 0x06);
        //        fsdItem.dec_sft = (byte)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_dec_sft", 0x03);

        //        fsdItem.c2v_rfb = (byte)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_c2v_rfb", 0x4);
        //        fsdItem.rx_rin = (byte)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_rx_rin", 0x00);

        //        fsdItem.FsdFrames = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_frames", 20);
        //        fsdItem.MaxDefault = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_diff_max_default", 600);

        //        fsdItem.FastMcapTest = GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_fast_mcap_test", 0) > 0 ? true : false;
        //        fsdItem.FastMcapLimit = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "fsd_fast_mcap_limit", 30);
        //    }
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            var currentItem = TestItemList.FirstOrDefault((t) => { return t.Name == "current_test" ? true : false; }) as CurrentTestItem;
            if (null != currentItem)
            {
                //SaveXmlAttrbuteValue(stNode, "current_test", "action", currentItem.Action);
                SaveXmlAttrbuteValue(stNode, "current_test", "active_current_min", currentItem.ActiveCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "active_current_max", currentItem.ActiveCurrentMax);
                SaveXmlAttrbuteValue(stNode, "current_test", "sleep_current_min", currentItem.SleepCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "sleep_current_max", currentItem.SleepCurrentMax);
                SaveXmlAttrbuteValue(stNode, "current_test", "idle_current_min", currentItem.IdleCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "idle_current_max", currentItem.IdleCurrentMax);

                //SaveXmlAttrbuteValue(stNode, "current_test", "vbus_active_current_min", currentItem.VbusActiveCurrentMin);
                //SaveXmlAttrbuteValue(stNode, "current_test", "vbus_active_current_max", currentItem.VbusActiveCurrentMax);
                //SaveXmlAttrbuteValue(stNode, "current_test", "vbus_sleep_current_min", currentItem.VbusSleepCurrentMin);
                //SaveXmlAttrbuteValue(stNode, "current_test", "vbus_sleep_current_max", currentItem.VbusSleepCurrentMax);
                //SaveXmlAttrbuteValue(stNode, "current_test", "vbus_deep_current_min", currentItem.VbusDeepCurrentMin);
                //SaveXmlAttrbuteValue(stNode, "current_test", "vbus_deep_current_max", currentItem.VbusDeepCurrentMax);
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
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_32k_standard", osctrimItem.Trim32KStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_min", osctrimItem.Trim32KMin > 0xff ? 0xff : osctrimItem.Trim32KMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_max", osctrimItem.Trim32KMax > 0xff ? 0xff : osctrimItem.Trim32KMax);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "offset_32k", osctrimItem.Offset32K > 500 ? 500 : osctrimItem.Offset32K);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standard", osctrimItem.Trim52MStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standardNo1", osctrimItem.Trim52MStandardNo1);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standardNo2", osctrimItem.Trim52MStandardNo2);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_52m_standardNo3", osctrimItem.Trim52MStandardNo3);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_52m_min", osctrimItem.Trim52MMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_52m_max", osctrimItem.Trim52MMax);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "offset_52m", osctrimItem.Offset52M > 500 ? 500 : osctrimItem.Offset52M);

                //SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_250m_standard", osctrimItem.Trim250MStandard);
                //SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_250m_min", osctrimItem.Trim250MMin > 0xff ? 0xff : osctrimItem.Trim250MMin);
                //SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_250m_max", osctrimItem.Trim250MMax > 0xff ? 0xff : osctrimItem.Trim250MMax);
                //SaveXmlAttrbuteValue(stNode, "osctrim_test", "offset_250m", osctrimItem.Offset250M > 500 ? 500 : osctrimItem.Offset250M);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "speed_mode", osctrimItem.SpeedMode);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "only_check", osctrimItem.OnlyCheck ? 1 : 0);
            }

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", mtkversionItem.MTKVersion);
                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "auto_update", (mtkversionItem.AutoUpdate));
            }

            //             var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            //             if (null != baseItem)
            //             {
            //                 SaveXmlAttrbuteValue(stNode, "base_test", "base_min", baseItem.BaseMin);
            //                 SaveXmlAttrbuteValue(stNode, "base_test", "base_max", baseItem.BaseMax);
            //             }

            var pixeldefectItem = TestItemList.FirstOrDefault((t) => { return t.Name == "pixeldefect_test" ? true : false; }) as PixelDefectTestItem;
            if (null != pixeldefectItem)
            {
                SaveXmlAttrbuteValue(stNode, "pixeldefect_test", "pixel_raw_max", pixeldefectItem.Pixel_raw_max);
                SaveXmlAttrbuteValue(stNode, "pixeldefect_test", "pixel_raw_min", pixeldefectItem.Pixel_raw_min);
                SaveXmlAttrbuteValue(stNode, "pixeldefect_test", "gain1_0_max", pixeldefectItem.Gain1_0_max);
                SaveXmlAttrbuteValue(stNode, "pixeldefect_test", "gain1_0_min", pixeldefectItem.Gain1_0_min);
                SaveXmlAttrbuteValue(stNode, "pixeldefect_test", "gain2_1_max", pixeldefectItem.Gain2_1_max);
                SaveXmlAttrbuteValue(stNode, "pixeldefect_test", "gain2_1_min", pixeldefectItem.Gain2_1_min);
            }

            var ioVolItem = TestItemList.FirstOrDefault((t) => { return t.Name == "iovol_test" ? true : false; }) as IOVotageTestItem;
            if (null != ioVolItem)
            {
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_high_max", ioVolItem.HighInt0_1p2_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_high_min", ioVolItem.HighInt0_1p2_Min);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_low_max", ioVolItem.LowInt0_1p2_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p2_low_min", ioVolItem.LowInt0_1p2_Min);

                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_high_max", ioVolItem.HighInt2_1p2_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_high_min", ioVolItem.HighInt2_1p2_Min);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_low_max", ioVolItem.LowInt2_1p2_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p2_low_min", ioVolItem.LowInt2_1p2_Min);

                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_high_max", ioVolItem.HighInt0_1p8_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_high_min", ioVolItem.HighInt0_1p8_Min);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_low_max", ioVolItem.LowInt0_1p8_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int0_1p8_low_min", ioVolItem.LowInt0_1p8_Min);

                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_high_max", ioVolItem.HighInt2_1p8_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_high_min", ioVolItem.HighInt2_1p8_Min);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_low_max", ioVolItem.LowInt2_1p8_Max);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "int2_1p8_low_min", ioVolItem.LowInt2_1p8_Min);
            }

            //var scapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "scap_rawdata_test" ? true : false; }) as ScapRawDataTest;
            //if (null != scapRawDataItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_min", scapRawDataItem.ScapRawDataMin);
            //    SaveXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_max", scapRawDataItem.ScapRawDataMax);
            //}

            //var stcItem = TestItemList.FirstOrDefault((t) => { return t.Name == "stc_test" ? true : false; }) as STCTestItem;
            //if (null != stcItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "stc_test", "clk_div", stcItem.Clk);
            //    SaveXmlAttrbuteValue(stNode, "stc_test", "stc_min", stcItem.STCMin);
            //    SaveXmlAttrbuteValue(stNode, "stc_test", "stc_max", (stcItem.STCMax > 90 ? 90 : stcItem.STCMax));
            //    SaveXmlAttrbuteValue(stNode, "stc_test", "uniformity_hor_max", stcItem.UniformityHorMax);
            //    SaveXmlAttrbuteValue(stNode, "stc_test", "uniformity_ver_max", stcItem.UniformityVerMax);
            //}

            //var mcapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mcap_rawdata_test" ? true : false; }) as MCapRawDataTestItem;
            //if (null != mcapRawDataItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "clk_div", mcapRawDataItem.Clk);
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_min", mcapRawDataItem.RawDataMin);
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_max", mcapRawDataItem.RawDataMax);
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_hor_max", mcapRawDataItem.UniformityHorMax);
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_ver_max", mcapRawDataItem.UniformityVerMax);
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_hor", mcapRawDataItem.ChkUniformityHor ? 1 : 0);
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_ver", mcapRawDataItem.ChkUniformityVer ? 1 : 0);

            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_min", (mcapRawDataItem.NormalizationRatioMin < 50 ? 50 : mcapRawDataItem.NormalizationRatioMin));
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_max", (mcapRawDataItem.NormalizationRatioMax > 150 ? 150 : mcapRawDataItem.NormalizationRatioMax));


            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "h_v_over_limit_ratio", (mcapRawDataItem.H_V_OverLimitRatio > 100 ? 100 : mcapRawDataItem.H_V_OverLimitRatio));
            //    SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "h_v_over_limit_maxnum", (mcapRawDataItem.H_V_OverLimitMaxNum));
            //}

            //var wbaseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "wbase_test" ? true : false; }) as WBaseTestItem;
            //if (null != wbaseItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "wbase_test", "wbase_node33_diff_max", wbaseItem.Node33DiffMax);
            //    SaveXmlAttrbuteValue(stNode, "wbase_test", "wbase_node33_num_max", wbaseItem.Node33NumMax);

            //    //SaveXmlAttrbuteValue(stNode, "wbase_test", "wbase_node55_diff_max", wbaseItem.Node55DiffMax);
            //    //SaveXmlAttrbuteValue(stNode, "wbase_test", "wbase_node55_num_max", wbaseItem.Node55NumMax);

            //    SaveXmlAttrbuteValue(stNode, "wbase_test", "wbase_all_diff_max", wbaseItem.AllDiffMax);
            //    SaveXmlAttrbuteValue(stNode, "wbase_test", "wbase_all_num_max", wbaseItem.AllNumMax);

            //}

            //var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            //if (null != baseItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "base_test", "base_diff_max", baseItem.DiffMax);
            //    SaveXmlAttrbuteValue(stNode, "base_test", "base_num_max", baseItem.NumMax);

            //    SaveXmlAttrbuteValue(stNode, "base_test", "base_all_diff_max", baseItem.AllDiffMax);
            //    SaveXmlAttrbuteValue(stNode, "base_test", "base_all_num_max", baseItem.AllNumMax);
            //    //SaveXmlAttrbuteValue(stNode, "base_test", "base_cover_diff_max", baseItem.CoverDiffMax);

            //    //SaveXmlAttrbuteValue(stNode, "base_test", "base_save_data", baseItem.SaveData ? 1 : 0);
            //    //SaveXmlAttrbuteValue(stNode, "base_test", "base_simplify_algorithm", baseItem.SimplifyAlgorithm ? 1 : 0);
            //}

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != noiseItem)
            {
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_frames", noiseItem.NoiseTestFrames);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max_time_A", noiseItem.NoiseTestMaxTime_A);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max_space_A", noiseItem.NoiseTestMaxSpace_A);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max_time_P", noiseItem.NoiseTestMaxTime_P);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max_space_P", noiseItem.NoiseTestMaxSpace_P);
            }

            var srfItem = TestItemList.FirstOrDefault((t) => { return t.Name == "srf_test" ? true : false; }) as SRFTestItem;
            if (null != srfItem)
            {
                SaveXmlAttrbuteValue(stNode, "srf_test", "srfreq_max", srfItem.Srfreq_max);
                SaveXmlAttrbuteValue(stNode, "srf_test", "srfreq_min", srfItem.Srfreq_min);

            }

            var otpItem = TestItemList.FirstOrDefault((t) => { return t.Name == "otp_test" ? true : false; }) as OtpTestItem;
            if (null != otpItem)
            {
                SaveXmlAttrbuteValue(stNode, "otp_test", "only_check", otpItem.OnlyCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "otp_test", "simplelog", otpItem.Simplelog ? 1 : 0);

            }

            var adcItem = TestItemList.FirstOrDefault((t) => { return t.Name == "adc_test" ? true : false; }) as ADCTestItem;
            if (null != adcItem)
            {
                SaveXmlAttrbuteValue(stNode, "adc_test", "adc_tx_max", adcItem.Adc_tx_max);
                SaveXmlAttrbuteValue(stNode, "adc_test", "adc_tx_min", adcItem.Adc_tx_min);
                SaveXmlAttrbuteValue(stNode, "adc_test", "adc_notx_max", adcItem.Adc_notx_max);
                SaveXmlAttrbuteValue(stNode, "adc_test", "adc_notx_min", adcItem.Adc_notx_min);

            }

            var flytimeItem = TestItemList.FirstOrDefault((t) => { return t.Name == "flytime_test" ? true : false; }) as FlyTimeTestItem;
            if (null != flytimeItem)
            {
                SaveXmlAttrbuteValue(stNode, "flytime_test", "flytime_code_max", flytimeItem.Flytime_code_max);
                SaveXmlAttrbuteValue(stNode, "flytime_test", "flytime_code_min", flytimeItem.Flytime_code_min);
                SaveXmlAttrbuteValue(stNode, "flytime_test", "flytime_val_max", flytimeItem.Flytime_val_max);
                SaveXmlAttrbuteValue(stNode, "flytime_test", "flytime_val_min", flytimeItem.Flytime_val_min);
                SaveXmlAttrbuteValue(stNode, "flytime_test", "flytime_std_max", flytimeItem.Flytime_std_max);
                SaveXmlAttrbuteValue(stNode, "flytime_test", "flytime_std_min", flytimeItem.Flytime_std_min);
            }


            //var miscItem = TestItemList.FirstOrDefault((t) => { return t.Name == "misc_test" ? true : false; }) as MISCTestItem;
            //if (null != miscItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "misc_test", "misc_mode", miscItem.MiscMode);
            //}

            //var fsdItem = TestItemList.FirstOrDefault((t) => { return t.Name == "fsd_test" ? true : false; }) as FSDTestItem;
            //if (null != fsdItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_fast_div", fsdItem.FastDiv);
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_slow_div", fsdItem.SlowDiv);

            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_xy_num", fsdItem.xy_num);
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_i2v_rfb", fsdItem.i2v_rfb);

            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_lpf_sft", fsdItem.lpf_sft > 0x0f ? 0x0f : fsdItem.lpf_sft);
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_dec_sft", fsdItem.dec_sft > 0x07 ? 0x07 : fsdItem.dec_sft);

            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_c2v_rfb", fsdItem.c2v_rfb > 0x07 ? 0x07 : fsdItem.c2v_rfb);
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_rx_rin", fsdItem.rx_rin > 0x07 ? 0x07 : fsdItem.rx_rin);

            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_frames", fsdItem.FsdFrames > 100 ? 100 : fsdItem.FsdFrames);
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_diff_max_default", fsdItem.MaxDefault);

            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_fast_mcap_test", fsdItem.FastMcapTest ? 1 : 0);
            //    SaveXmlAttrbuteValue(stNode, "fsd_test", "fsd_fast_mcap_limit", fsdItem.FastMcapLimit > 99 ? 99 : fsdItem.FastMcapLimit);
            //}

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}