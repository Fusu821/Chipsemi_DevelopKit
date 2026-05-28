using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class BasicSetMode3535 : TestItemSetMode3535
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
                fsdItem.FastClock = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "f_clk", 0x2502);
                fsdItem.SlowClock = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "s_clk", 0x3502);
                fsdItem.FSDCmpMax = (ushort)GetXmlAttrbuteValue(stNode, "fsd_test", "cmp_max", 9000);
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
            }

            var currentItem = TestItemList.FirstOrDefault((t) => { return t.Name == "current_test" ? true : false; }) as CurrentTestItem;
            if (null != currentItem)
            {
                //currentItem.Action = (ushort)GetXmlAttrbuteValue(stNode, "current_test", "action", 0x00);
                currentItem.WorkCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "work_current_min", -100);
                currentItem.WorkCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "work_current_max", 32);
                currentItem.SleepCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_min", -100);
                currentItem.SleepCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "sleep_current_max", 32);
                currentItem.DeltaCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "delta_current_min", -55);
                currentItem.DeltaCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "delta_current_max", 55);
                currentItem.ActiveCurrentMin = GetXmlAttrbuteValue(stNode, "current_test", "active_current_min", 10000);
                currentItem.ActiveCurrentMax = GetXmlAttrbuteValue(stNode, "current_test", "active_current_max", 14000);
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

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                mtkversionItem.MTKVersion = GetXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", 0x51030);
            }

            var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            if (null != baseItem)
            {
                baseItem.BaseMin = GetXmlAttrbuteValue(stNode, "base_test", "base_min", 3000);
                baseItem.BaseMax = GetXmlAttrbuteValue(stNode, "base_test", "base_max", 16000);
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

            var mtkversionItem = TestItemList.FirstOrDefault((t) => { return t.Name == "mtkversion_test" ? true : false; }) as MTKVersionTestItem;
            if (null != mtkversionItem)
            {
                SaveXmlAttrbuteValue(stNode, "mtkversion_test", "mtk_version", mtkversionItem.MTKVersion);
            }

            var baseItem = TestItemList.FirstOrDefault((t) => { return t.Name == "base_test" ? true : false; }) as BaseTestItem;
            if (null != baseItem)
            {
                SaveXmlAttrbuteValue(stNode, "base_test", "base_min", baseItem.BaseMin);
                SaveXmlAttrbuteValue(stNode, "base_test", "base_max", baseItem.BaseMax);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
