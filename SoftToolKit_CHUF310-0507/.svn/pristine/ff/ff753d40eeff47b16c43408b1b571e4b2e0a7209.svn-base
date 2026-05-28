using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class BasicSetMode7449 : TestItemSetMode7449
    {
        public override void XMLDataToView()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            var bootItem = TestItemList.FirstOrDefault((t) => { return t.Name == "boot_test" ? true : false; }) as BootTestItem;
            if (null != bootItem)
            {
                bootItem.OnlyCheck = GetXmlAttrbuteValue(stNode, "boot_test", "only_check", 0) > 0 ? true : false;
                bootItem.ExistBootloader = GetXmlAttrbuteValue(stNode, "boot_test", "exist_bootloader", 0) > 0 ? true : false;
                bootItem.Set_Version = (uint)GetXmlAttrbuteValue(stNode, "boot_test", "set_version", 0);
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

                osctrimItem.Trim48MStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_48m_standard", 48000);
                osctrimItem.Trim48MMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_48m_min", 0x50);
                osctrimItem.Trim48MMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_48m_max", 0xA0);

                osctrimItem.Trim64MStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_64m_standard", 64000);
                osctrimItem.Trim64MMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_min", 0x50);
                osctrimItem.Trim64MMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_max", 0xA0);

                osctrimItem.Trim150MStandard = GetXmlAttrbuteValue(stNode, "osctrim_test", "tick_150m_standard", 150000);
                osctrimItem.Trim150MMin = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_150m_min", 0x01);
                osctrimItem.Trim150MMax = GetXmlAttrbuteValue(stNode, "osctrim_test", "trim_150m_max", 0x10);

                osctrimItem.SpeedMode = GetXmlAttrbuteValue(stNode, "osctrim_test", "speed_mode", 0);
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
                currentItem.SleepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_min", 0);
                currentItem.SleepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_max", 100);
                currentItem.DeepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "deep_current_min", 0);
                currentItem.DeepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "deep_current_max", 100);
            }

            var scapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "scap_rawdata_test" ? true : false; }) as ScapRawDataTest;
            if (null != scapRawDataItem)
            {
                scapRawDataItem.ScapRawDataMin = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_min", 3000);
                scapRawDataItem.ScapRawDataMax = GetXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_max", 16000);
            }

            var stc_Item = TestItemList.FirstOrDefault((t) => { return t.Name == "stc_test" ? true : false; }) as STCTestItem;
            if (null != stc_Item)
            {
                stc_Item.Clk = (ushort)GetXmlAttrbuteValue(stNode, "stc_test", "clk_div", 20);
                stc_Item.STCMin = GetXmlAttrbuteValue(stNode, "stc_test", "stc_min", 0);
                stc_Item.STCMax = GetXmlAttrbuteValue(stNode, "stc_test", "stc_max", 60);
                stc_Item.UniformityHorMax = GetXmlAttrbuteValue(stNode, "stc_test", "uniformity_hor_max", 10);
                stc_Item.UniformityVerMax = GetXmlAttrbuteValue(stNode, "stc_test", "uniformity_ver_max", 10);
            }

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

                mcapRawDataItem.RanksAllowOverrunNum = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "ranks_allow_overrun_num", 0);
                mcapRawDataItem.AllowOverrunNum = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "allow_overrun_num", 0);
                mcapRawDataItem.AllowOverrunRatio = (ushort)GetXmlAttrbuteValue(stNode, "mcap_rawdata_test", "allow_overrun_ratio", 0);
            }

            var vtItem = TestItemList.FirstOrDefault((t) => { return t.Name == "vt_test" ? true : false; }) as VTTestItem;
            if (null != vtItem)
            {
                vtItem.VTTestMin = (short)GetXmlAttrbuteValue(stNode, "vt_test", "vt_min", 100);
                vtItem.VTTestMax = (short)GetXmlAttrbuteValue(stNode, "vt_test", "vt_max", 1000);
            }

            var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            if (null != baseItem)
            {
                baseItem.BaseTestMin = (short)GetXmlAttrbuteValue(stNode, "base_test", "base_min", 900);
                baseItem.BaseTestMax = (short)GetXmlAttrbuteValue(stNode, "base_test", "base_max", 1024);
            }
            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != baseItem)
            {
                noiseItem.NoiseTestFrames = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_frames", 60);
                noiseItem.NoiseTestMax = (short)GetXmlAttrbuteValue(stNode, "noise_test", "noise_max", 100);
            }
            var miscItem = TestItemList.FirstOrDefault((t) => { return t.Name == "misc_test" ? true : false; }) as MISCTestItem;
            if (null != miscItem)
            {
                miscItem.MiscMode = (ushort)GetXmlAttrbuteValue(stNode, "misc_test", "misc_mode", 1);
            }

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
                SaveXmlAttrbuteValue(stNode, "current_test", "deep_current_min", currentItem.DeepCurrentMin);
                SaveXmlAttrbuteValue(stNode, "current_test", "deep_current_max", currentItem.DeepCurrentMax);
            }

            var bootItem = TestItemList.FirstOrDefault((t) => { return t.Name == "boot_test" ? true : false; }) as BootTestItem;
            if (null != bootItem)
            {
                SaveXmlAttrbuteValue(stNode, "boot_test", "only_check", bootItem.OnlyCheck ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "boot_test", "exist_bootloader", bootItem.ExistBootloader ? 1 : 0);
                SaveXmlAttrbuteValue(stNode, "boot_test", "set_version", bootItem.Set_Version);
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

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_48m_standard", osctrimItem.Trim48MStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_48m_min", osctrimItem.Trim48MMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_48m_max", osctrimItem.Trim48MMax);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_64m_standard", osctrimItem.Trim64MStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_min", osctrimItem.Trim64MMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_64m_max", osctrimItem.Trim64MMax);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "tick_150m_standard", osctrimItem.Trim150MStandard);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_150m_min", osctrimItem.Trim150MMin);
                SaveXmlAttrbuteValue(stNode, "osctrim_test", "trim_150m_max", osctrimItem.Trim150MMax);

                SaveXmlAttrbuteValue(stNode, "osctrim_test", "speed_mode", osctrimItem.SpeedMode);
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

            var scapRawDataItem = TestItemList.FirstOrDefault((t) => { return t.Name == "scap_rawdata_test" ? true : false; }) as ScapRawDataTest;
            if (null != scapRawDataItem)
            {
                SaveXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_min", scapRawDataItem.ScapRawDataMin);
                SaveXmlAttrbuteValue(stNode, "scap_rawdata_test", "scap_rawdata_max", scapRawDataItem.ScapRawDataMax);
            }

            var stcItem = TestItemList.FirstOrDefault((t) => { return t.Name == "stc_test" ? true : false; }) as STCTestItem;
            if (null != stcItem)
            {
                SaveXmlAttrbuteValue(stNode, "stc_test", "clk_div", stcItem.Clk);
                SaveXmlAttrbuteValue(stNode, "stc_test", "stc_min", stcItem.STCMin);
                SaveXmlAttrbuteValue(stNode, "stc_test", "stc_max", (stcItem.STCMax > 90 ? 90 : stcItem.STCMax));
                SaveXmlAttrbuteValue(stNode, "stc_test", "uniformity_hor_max", stcItem.UniformityHorMax);
                SaveXmlAttrbuteValue(stNode, "stc_test", "uniformity_ver_max", stcItem.UniformityVerMax);
            }

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

                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "ranks_allow_overrun_num", mcapRawDataItem.RanksAllowOverrunNum);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "allow_overrun_num", mcapRawDataItem.AllowOverrunNum);
                SaveXmlAttrbuteValue(stNode, "mcap_rawdata_test", "allow_overrun_ratio", mcapRawDataItem.AllowOverrunRatio);

            }

            var vtItem = TestItemList.FirstOrDefault((t) => { return t.Name == "vt_test" ? true : false; }) as VTTestItem;
            if (null != vtItem)
            {
                SaveXmlAttrbuteValue(stNode, "vt_test", "vt_min", vtItem.VTTestMin);
                SaveXmlAttrbuteValue(stNode, "vt_test", "vt_max", vtItem.VTTestMax);
            }

            var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            if (null != baseItem)
            {
                SaveXmlAttrbuteValue(stNode, "base_test", "base_min", baseItem.BaseTestMin);
                SaveXmlAttrbuteValue(stNode, "base_test", "base_max", baseItem.BaseTestMax);
            }

            var noiseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "noise_test" ? true : false; }) as NoiseTestItem;
            if (null != baseItem)
            {
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_frames", noiseItem.NoiseTestFrames);
                SaveXmlAttrbuteValue(stNode, "noise_test", "noise_max", noiseItem.NoiseTestMax);
            }
            var miscItem = TestItemList.FirstOrDefault((t) => { return t.Name == "misc_test" ? true : false; }) as MISCTestItem;
            if (null != miscItem)
            {
                SaveXmlAttrbuteValue(stNode, "misc_test", "misc_mode", miscItem.MiscMode);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
