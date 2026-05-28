using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class BasicSetMode810 : TestItemSetMode810
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
            if(null != osctrimItem)
            {
                osctrimItem.Trim32KStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_32k_standard", 32);
                osctrimItem.Trim32KMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_min", 0x40);
                osctrimItem.Trim32KMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_max", 0x80);

                osctrimItem.Trim64MStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_64m_standard", 64000);
                osctrimItem.Trim64MMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_min", 0x50);
                osctrimItem.Trim64MMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_max", 0xA0);
            }

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                mtkversionItem.MTKVersion = GetXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", 0x51030);
                mtkversionItem.AutoUpdate = (ushort)(GetXmlAttrbuteValue(stNode, "mtkversion_test", "auto_update", 0));
            }

//             var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
//             if (null != baseItem)
//             {
//                 baseItem.BaseMin = GetXmlAttrbuteValue(stNode, "base_test", "base_min", 3000);
//                 baseItem.BaseMax = GetXmlAttrbuteValue(stNode, "base_test", "base_max", 16000);
//             }

            var shortItem = TestItemList.FirstOrDefault((t) => { return t.Name == "short_test" ? true : false; }) as ShortTestItem;
            if (null != shortItem)
            {
                shortItem.ShortTxMax = GetXmlAttrbuteValue(stNode, "short_test", "short_tx_max", 600);
                shortItem.ShortRxMax = GetXmlAttrbuteValue(stNode, "short_test", "short_rx_max", 600);
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

                ioVolItem.LowLevelSpiMin = GetXmlAttrbuteValue(stNode, "iovol_test", "spi_low_min", 0);
                ioVolItem.LowLevelSpiMax = GetXmlAttrbuteValue(stNode, "iovol_test", "spi_low_max", 300);
                ioVolItem.HighLevelSpiMin = GetXmlAttrbuteValue(stNode, "iovol_test", "spi_high_min", 1700);
                ioVolItem.HighLevelSpiMax = GetXmlAttrbuteValue(stNode, "iovol_test", "spi_high_max", 1900);

            }

            var currentItem = TestItemList.FirstOrDefault((t) => { return t.Name == "current_test" ? true : false; }) as CurrentTestItem;
            if (null != currentItem)
            {
                currentItem.ActiveCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "active_current_min", 500);
                currentItem.ActiveCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "active_current_max", 3000);
                currentItem.Suspend0CurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "suspend0_current_min", 0);
                currentItem.Suspend0CurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "suspend0_current_max", 100);
                currentItem.Suspend1CurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "suspend1_current_min", 0);
                currentItem.Suspend1CurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "suspend1_current_max", 100);
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

            var mcapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mcap_rawdata_test" ? true : false; }) as MCapRawDataTestItem;
            if (null != mcapRawDataItem)
            {
                mcapRawDataItem.Clk = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "clk_div", 12);
                mcapRawDataItem.RawDataMin = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_min", 3000);
                mcapRawDataItem.RawDataMax = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_max", 16000);
                mcapRawDataItem.UniformityHorMax = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_hor_max", 10);
                mcapRawDataItem.UniformityVerMax = GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_ver_max", 10);
                mcapRawDataItem.ChkUniformityHor = 1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_hor", 0);
                mcapRawDataItem.ChkUniformityVer = 1 == GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_ver", 0);
                mcapRawDataItem.NormalizationRatioMin = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_min", 50);
                mcapRawDataItem.NormalizationRatioMax = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_max", 150);
            }

            var cvDiffItemY = TestItemList.FirstOrDefault((t) => { return t.Name == "cvdiff_y_test" ? true : false; }) as CVDiffYTestItem;
            if (null != cvDiffItemY)
            {
                cvDiffItemY.PointRangeY = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "point_range_y", 100);
                cvDiffItemY.CValueDiffRatio = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "c_value_diff_ratio_y", 3);
                cvDiffItemY.ShakeRangeY = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "shake_range_y", 10);
                cvDiffItemY.TimeOutFramesY = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "time_out_frames_y", 2000);
                cvDiffItemY.StablFramesY = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "stabl_frames_y", 10);

                cvDiffItemY.PMinY = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "p_min_y", 0);
                cvDiffItemY.PMaxY = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_y_test", "p_max_y", 8192);
            }
            var cvDiffItemX = TestItemList.FirstOrDefault((t) => { return t.Name == "cvdiff_x_test" ? true : false; }) as CVDiffXTestItem;
            if (null != cvDiffItemX)
            {
                cvDiffItemX.PointRangeX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "point_range_x", 100);
                cvDiffItemX.CValueDiffRatioX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "c_value_diff_ratio_x", 3);
                cvDiffItemX.ShakeRangeX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "shake_range_x", 10);
                cvDiffItemX.TimeOutFramesX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "time_out_frames_x", 2000);
                cvDiffItemX.StablFramesX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "stabl_frames_x", 10);

                cvDiffItemX.PMinX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "p_min_x", 0);
                cvDiffItemX.PMaxX = (ushort)GetXmlAttrbuteValue(stNode, "cvdiff_x_test", "p_max_x", 8192);
            }


            var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            if (null != baseItem)
            {
                baseItem.X_Difference = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "x_difference", 1000);
                baseItem.Y_Difference = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "y_difference", 1000);
                baseItem.X_Difference_neg = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "x_difference_neg", 1000);
                baseItem.Y_Difference_neg = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "y_difference_neg", 1000);
                baseItem.RatioNum = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "ratio_num", 5);
                baseItem.TestTime = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "test_time", 5);
                baseItem.ProportionValue = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "proportion_value", 40);
                baseItem.ExitSize = (ushort)GetXmlAttrbuteValue(stNode, "base_test", "exit_size", 3500);
            }
            var SDRockerCalibItem = TestItemList.FirstOrDefault((t) => { return t.Name == "sd_rocker_calib_test" ? true : false; }) as SDRockerCalibTestItem;
            if (null != SDRockerCalibItem)
            {
                SDRockerCalibItem.X_Difference = (ushort)GetXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "x_difference", 1000);
                SDRockerCalibItem.X_Difference_neg = (ushort)GetXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "x_difference_neg", 1000);
                SDRockerCalibItem.RatioNum = (ushort)GetXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "ratio_num", 5);
                SDRockerCalibItem.TestTime = (ushort)GetXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "test_time", 5);
                SDRockerCalibItem.ProportionValue = (ushort)GetXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "proportion_value", 40);
                SDRockerCalibItem.ExitSize = (ushort)GetXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "exit_size", 3500);
            }

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != baseItem)
            {
                noiseItem.NoiseTestFrames = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_frames", 60);
                noiseItem.NoiseTestMaxMcap = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max_mcap", 100);
               // noiseItem.NoiseTestMaxScap = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max_scap", 100);
            }

            //var miscItem = TestItemList.FirstOrDefault((t) => { return t.Name == "misc_test" ? true : false; }) as MISCTestItem;
            //if (null != miscItem)
            //{
            //    miscItem.MiscMode = (ushort)GetXmlAttrbuteValue(stNode, "misc_test", "misc_mode", 1);
            //}
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

                SaveXmlAttrbuteValue(stNode, "current_test", "suspend0_current_min", currentItem.Suspend0CurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "suspend0_current_max", currentItem.Suspend0CurrentMax);

                SaveXmlAttrbuteValue(stNode, "current_test", "suspend1_current_min", currentItem.Suspend1CurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "suspend1_current_max", currentItem.Suspend1CurrentMax);
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
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_min", osctrimItem.Trim32KMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_32k_max", osctrimItem.Trim32KMax);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_64m_standard", osctrimItem.Trim64MStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_min", osctrimItem.Trim64MMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_max", osctrimItem.Trim64MMax);
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

            var shortItem = TestItemList.FirstOrDefault((t) => { return t.Name == "short_test" ? true : false; }) as ShortTestItem;
            if (null != shortItem)
            {
                SaveXmlAttrbuteValue(stNode, "short_test", "short_tx_max", shortItem.ShortTxMax);
                SaveXmlAttrbuteValue(stNode, "short_test", "short_rx_max", shortItem.ShortRxMax);
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

                SaveXmlAttrbuteValue(stNode, "iovol_test", "spi_low_min", ioVolItem.LowLevelSpiMin);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "spi_low_max", ioVolItem.LowLevelSpiMax);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "spi_high_min", ioVolItem.HighLevelSpiMin);
                SaveXmlAttrbuteValue(stNode, "iovol_test", "spi_high_max", ioVolItem.HighLevelSpiMax);
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

            var mcapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mcap_rawdata_test" ? true : false; }) as MCapRawDataTestItem;
            if (null != mcapRawDataItem)
            {
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "clk_div", mcapRawDataItem.Clk);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_min", mcapRawDataItem.RawDataMin);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "mcap_rawdata_max", mcapRawDataItem.RawDataMax);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_hor_max", mcapRawDataItem.UniformityHorMax);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "uniformity_ver_max", mcapRawDataItem.UniformityVerMax);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_hor", mcapRawDataItem.ChkUniformityHor ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "check_uniformity_ver", mcapRawDataItem.ChkUniformityVer ? 1 : 0);

                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_min", (mcapRawDataItem.NormalizationRatioMin < 50 ? 50 : mcapRawDataItem.NormalizationRatioMin));
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "normalization_ratio_max", (mcapRawDataItem.NormalizationRatioMax > 150 ? 150 : mcapRawDataItem.NormalizationRatioMax));
            }

            var cvDiffItemY = TestItemList.FirstOrDefault((t) => { return t.Name == "cvdiff_y_test" ? true : false; }) as CVDiffYTestItem;
            if (null != cvDiffItemY)
            {
                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "point_range_y", cvDiffItemY.PointRangeY);
                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "c_value_diff_ratio_y", cvDiffItemY.CValueDiffRatio);
                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "shake_range_y", cvDiffItemY.ShakeRangeY);

                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "time_out_frames_y", cvDiffItemY.TimeOutFramesY);
                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "stabl_frames_y", cvDiffItemY.StablFramesY);

                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "p_min_y", cvDiffItemY.PMinY > 8192 ? 8192 : cvDiffItemY.PMinY);
                SaveXmlAttrbuteValue(stNode, "cvdiff_y_test", "p_max_y", cvDiffItemY.PMaxY > 8192 ? 8192 : cvDiffItemY.PMaxY);

            }

            var cvDiffItemX = TestItemList.FirstOrDefault((t) => { return t.Name == "cvdiff_x_test" ? true : false; }) as CVDiffXTestItem;
            if (null != cvDiffItemX)
            {
                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "point_range_x", cvDiffItemX.PointRangeX);
                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "c_value_diff_ratio_x", cvDiffItemX.CValueDiffRatioX);
                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "shake_range_x", cvDiffItemX.ShakeRangeX);

                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "time_out_frames_x", cvDiffItemX.TimeOutFramesX);
                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "stabl_frames_x", cvDiffItemX.StablFramesX);

                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "p_min_x", cvDiffItemX.PMinX > 8192 ? 8192 : cvDiffItemX.PMinX);
                SaveXmlAttrbuteValue(stNode, "cvdiff_x_test", "p_max_x", cvDiffItemX.PMaxX > 8192 ? 8192 : cvDiffItemX.PMaxX);
            }

            var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            if (null != baseItem)
            {
                SaveXmlAttrbuteValue(stNode, "base_test", "x_difference", baseItem.X_Difference);
                SaveXmlAttrbuteValue(stNode, "base_test", "y_difference", baseItem.Y_Difference);
                SaveXmlAttrbuteValue(stNode, "base_test", "x_difference_neg", baseItem.X_Difference_neg);
                SaveXmlAttrbuteValue(stNode, "base_test", "y_difference_neg", baseItem.Y_Difference_neg);
                SaveXmlAttrbuteValue(stNode, "base_test", "ratio_num", baseItem.RatioNum > 30 ? 30 : baseItem.RatioNum);
                SaveXmlAttrbuteValue(stNode, "base_test", "test_time", baseItem.TestTime > 100 ? 100 : baseItem.TestTime);
                baseItem.ProportionValue = baseItem.ProportionValue > (ushort)999 ? (ushort)999 : baseItem.ProportionValue;
                SaveXmlAttrbuteValue(stNode, "base_test", "proportion_value", baseItem.ProportionValue );

                SaveXmlAttrbuteValue(stNode, "base_test", "exit_size", (baseItem.ExitSize > 5000 ? 5000 : baseItem.ExitSize));
            }

            var SDRockerCalibItem = TestItemList.FirstOrDefault((t) => { return t.Name == "sd_rocker_calib_test" ? true : false; }) as SDRockerCalibTestItem;
            if (null != SDRockerCalibItem)
            {
                SaveXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "x_difference", SDRockerCalibItem.X_Difference);
                SaveXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "x_difference_neg", SDRockerCalibItem.X_Difference_neg);
                SaveXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "ratio_num", SDRockerCalibItem.RatioNum > 30 ? 30 : SDRockerCalibItem.RatioNum);
                SaveXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "test_time", SDRockerCalibItem.TestTime > 100 ? 100 : SDRockerCalibItem.TestTime);
                SDRockerCalibItem.ProportionValue = SDRockerCalibItem.ProportionValue > (ushort)999 ? (ushort)999 : SDRockerCalibItem.ProportionValue;
                SaveXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "proportion_value", SDRockerCalibItem.ProportionValue);

                SaveXmlAttrbuteValue(stNode, "sd_rocker_calib_test", "exit_size", (SDRockerCalibItem.ExitSize > 5000 ? 5000 : SDRockerCalibItem.ExitSize));
            }

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != noiseItem)
            {
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_frames", noiseItem.NoiseTestFrames);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max_mcap", noiseItem.NoiseTestMaxMcap);
                //SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max_scap", noiseItem.NoiseTestMaxScap);
            }

            //var miscItem = TestItemList.FirstOrDefault((t) => { return t.Name == "misc_test" ? true : false; }) as MISCTestItem;
            //if (null != miscItem)
            //{
            //    SaveXmlAttrbuteValue(stNode, "misc_test", "misc_mode", miscItem.MiscMode);
            //}

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
