using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SMInvokeBridge;
using System.IO;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class SaveSetMode : SettingMode
    {
        private void SaveScapFactoryConfig(string exportPath)
        {
            StringBuilder szOut = new StringBuilder();

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define noise_frame", GetXmlAttrbuteString(stNode, "noise_test", "noise_frame")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define noise_max", GetXmlAttrbuteString(stNode, "noise_test", "noise_max")));
            szOut.AppendLine("");

            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define integral", GetXmlAttrbuteString(stNode, "os_test", "integral")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define scale_a", GetXmlAttrbuteString(stNode, "os_test", "scale_a")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define scale_b", GetXmlAttrbuteString(stNode, "os_test", "scale_b")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define os_clk", GetXmlAttrbuteString(stNode, "os_test", "os_clk")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define m1_ratio_lower_va", GetXmlAttrbuteString(stNode, "os_test", "m1_ratio_lower_va")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define m1_ratio_upper_va", GetXmlAttrbuteString(stNode, "os_test", "m1_ratio_upper_va")));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define m2_ratio", GetXmlAttrbuteString(stNode, "os_test", "m2_ratio")));
            szOut.AppendLine("");
            int addRow = GetKeys() > 0 ? 1 : 0;

            szOut.AppendLine("unsigned short os_base[] = {");
            for (int iRow = 0; iRow < GetRows() + addRow; iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("os_test");
                string tag = string.Format("os_base_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ",");
                    szOut.AppendLine(szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("unsigned short rawdata_min[] = {");
            for (int iRow = 0; iRow < GetRows() + addRow; iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("rawdata_test");
                string tag = string.Format("rawdata_min_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ",");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("unsigned short rawdata_max[] = {");
            for (int iRow = 0; iRow < GetRows() + addRow; iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("rawdata_test");
                string tag = string.Format("rawdata_max_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ",");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");



            StreamWriter sw = new StreamWriter(exportPath, false, Encoding.Default);
            sw.Write(szOut.ToString());
            sw.Flush();
            sw.Close();
        }

        private void SaveMcapFactoryConfig(string exportPath)
        {
            StringBuilder szOut = new StringBuilder();

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);


            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define MAX_TX_NUM_5472", 32));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define MAX_RX_NUM_5472", 40));
            szOut.AppendLine(string.Format("{0, -40}{1, -40}", "#define MAX_CAP_DATA_SIZE", "(MAX_TX_NUM_5472 * MAX_RX_NUM_5472 * 2)"));
            szOut.AppendLine(string.Format("{0, -40}{1, -40}", "#define SAVE_LOG_NAME", "\"/sdcard/chsc_factory_test_result.txt\""));
            szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define SHORT_TEST_THL", GetXmlAttrbuteString(stNode, "short_test", "short_tx_max")));
            //szOut.AppendLine(string.Format("{0, -40}{1, -6}", "#define RAWDATA_TEST_THL", 30));
            szOut.AppendLine("const short rawdata_min[] = {");
            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("mcap_rawdata_test");
                string tag = string.Format("mcap_rawdata_min_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ",");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("const short rawdata_max[] = {");
            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("mcap_rawdata_test");
                string tag = string.Format("mcap_rawdata_max_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ",");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            StreamWriter sw = new StreamWriter(exportPath, false, Encoding.Default);
            sw.Write(szOut.ToString());
            sw.Flush();
            sw.Close();
        }
        private void Save_scap_test_p_Config(string exportPath)
        {
            StringBuilder szOut = new StringBuilder();

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            szOut.AppendLine("#include "+'"'+"scap_test_p.h"+'"');
            szOut.AppendLine("");
            szOut.AppendLine("");

            //0sctrimt Test
            szOut.AppendLine("OsctrimtTestParameter OsctrimtTestP=");
            szOut.AppendLine("{");
            szOut.AppendLine(string.Format("  .tick_standard = {0, -6},", GetXmlAttrbuteString(stNode, "osctrim_test", "tick_standard")));
            szOut.AppendLine(string.Format("  .osctrim_min = {0, -6},", GetXmlAttrbuteString(stNode, "osctrim_test", "osctrim_min")));
            szOut.AppendLine(string.Format("  .osctrim_max = {0, -6},", GetXmlAttrbuteString(stNode, "osctrim_test", "osctrim_max")));
            szOut.AppendLine(string.Format("  .must_test = {0, -6},", GetXmlAttrbuteString(stNode, "osctrim_test", "must_test")));
            szOut.AppendLine("};");
            szOut.AppendLine("");
            szOut.AppendLine("");

            //rawdata test
            szOut.AppendLine("RawDataTestParameter RawDataTestP=");
            szOut.AppendLine("{");
            szOut.AppendLine(string.Format("  .selected = {0, -6},", GetXmlAttrbuteString(stNode, "rawdata_test", "selected")));
            szOut.AppendLine(string.Format("  .sync_length = {0, -6},", GetXmlAttrbuteValue(stNode, "mtkversion_test", "sync_length", 122)));
            szOut.AppendLine(string.Format("  .minValue = {0, -6},", GetXmlAttrbuteString(stNode, "rawdata_test", "rawdata_min")));
            szOut.AppendLine(string.Format("  .maxValue = {0, -6},", GetXmlAttrbuteString(stNode, "rawdata_test", "rawdata_max")));
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short rawdata_min[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("rawdata_test");
                string tag = string.Format("rawdata_min_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short rawdata_max[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("rawdata_test");
                string tag = string.Format("rawdata_max_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            //os test

            szOut.AppendLine("OSTestParameter OSTestP=");
            szOut.AppendLine("{");
            szOut.AppendLine(string.Format("  .selected = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "selected")));
            szOut.AppendLine(string.Format("  .integral_time = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "integral")));
            szOut.AppendLine(string.Format("  .scale_a = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "scale_a")));
            szOut.AppendLine(string.Format("  .scale_b = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "scale_b")));
            szOut.AppendLine(string.Format("  .os_clk = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "os_clk")));
            szOut.AppendLine(string.Format("  .m1_va_dn = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m1_ratio_lower_va")));
            szOut.AppendLine(string.Format("  .m1_va_up = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m1_ratio_upper_va")));
            szOut.AppendLine(string.Format("  .m1_ref_dn = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m1_ratio_lower_ref")));
            szOut.AppendLine(string.Format("  .m1_ref_up = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m1_ratio_upper_ref")));
            szOut.AppendLine(string.Format("  .m2_ratio = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m2_ratio")));
            szOut.AppendLine(string.Format("  .m3_level1 = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m3_delta_level1")));
            szOut.AppendLine(string.Format("  .m3_level2 = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m3_delta_level2")));
            szOut.AppendLine(string.Format("  .m3_va_max = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m3_delta_va_max")));
            szOut.AppendLine(string.Format("  .m3_ref_max = {0, -6},", GetXmlAttrbuteString(stNode, "os_test", "m3_delta_ref_max")));
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short os_base[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("os_test");
                string tag = string.Format("os_base_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            //Invalid
            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short Invalid[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("invalidnode");
                string tag = string.Format("invalid_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            //FSDBK test
            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("FSDBKTestParameter FSDBKTsetP =");
            szOut.AppendLine("{");
            szOut.AppendLine(string.Format("  .selected = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "selected")));
            szOut.AppendLine(string.Format("  .f_clk = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "f_clk")));
            szOut.AppendLine(string.Format("  .s_clk = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "s_clk")));
            szOut.AppendLine(string.Format("  .integral_time = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "integral")));
            szOut.AppendLine(string.Format("  .fsd_min = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fsd_min")));
            szOut.AppendLine(string.Format("  .triger_min = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "triger_min")));
            szOut.AppendLine(string.Format("  .triger_max = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "triger_max")));
            szOut.AppendLine(string.Format("  .slow_crt_min = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "slow_critical_min")));
            szOut.AppendLine(string.Format("  .slow_crt_max = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "slow_critical_max")));
            szOut.AppendLine(string.Format("  .fsd_bsd_min = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fsd_besides_min")));
            szOut.AppendLine(string.Format("  .fast_crt_max = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fast_critical_max")));
            szOut.AppendLine(string.Format("  .fb_base = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fb_base")));
            szOut.AppendLine(string.Format("  .fb_min = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fb_min")));
            szOut.AppendLine(string.Format("  .fb_max = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fb_max")));
            szOut.AppendLine(string.Format("  .scalecheck = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "scale_check")));
            szOut.AppendLine(string.Format("  .recheck = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "recheck")));
            szOut.AppendLine(string.Format("  .fbcheck = {0, -6},", GetXmlAttrbuteString(stNode, "fsdbk_test", "fbcheck")));
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_base[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_base_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_fast[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_fast_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_slow[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_slow_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_delta_max[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_delta_max_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_uniformity_left[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_uniformity_left_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_uniformity_right[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_uniformity_right_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("unsigned short fsd_deviation[48] = {");

            for (int iRow = 0; iRow < GetRows(); iRow++)
            {
                XmlNode itemTest = stNode.SelectSingleNode("fsdbk_test");
                string tag = string.Format("fsd_deviation_{0:D}", iRow);
                XmlNode nDetail = itemTest.SelectSingleNode(tag);
                if (null != nDetail)
                {
                    string szValue = nDetail.InnerXml;
                    szValue.Replace("\t", " ");
                    szValue = szValue.Replace("  ", " ");
                    szValue = szValue.Replace(" ", ", ");
                    szOut.AppendLine("    " + szValue);
                }
            }
            szOut.AppendLine("};");

            szOut.AppendLine("");
            szOut.AppendLine("");

            szOut.AppendLine("IC_Info ICInfo;");

            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("");
            szOut.AppendLine("");

            StreamWriter sw = new StreamWriter(exportPath, false, Encoding.Default);
            sw.Write(szOut.ToString());
            sw.Flush();
            sw.Close();

        }

        public override void OnCtrlClickCommand(object param)
        {
            if ("convert-config-click" == param.ToString())
            {
                try
                {
                    SaveFileDialog saveFileDialog = new SaveFileDialog();
                    saveFileDialog.Filter = "Text Files (*.h;)|*.h";
                    if (DialogResult.OK == saveFileDialog.ShowDialog())
                    {
                        string exportPath = saveFileDialog.FileName;
                        if (eChipTypeList.CLR_IC_TYPE_MCAP == eChipTypeList.GetSubType(SettingMode.selectedIC))
                        {
                            SaveMcapFactoryConfig(exportPath);
                        }
                        else
                        {
                            SaveScapFactoryConfig(exportPath);
                        }
                    }
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
            }
            if ("file-generation-click" == param.ToString())
            {
                try
                {
                    if (eChipTypeList.CLR_IC_TYPE_SCAP == eChipTypeList.GetSubType(SettingMode.selectedIC))
                    {
                        SaveFileDialog saveFileDialog = new SaveFileDialog();
                        saveFileDialog.FileName = "scap_test_p";
                        saveFileDialog.Filter = "Text Files (*.c;)|*.c";
                        if (DialogResult.OK == saveFileDialog.ShowDialog())
                        {

                            string exportPath = saveFileDialog.FileName;
                            Save_scap_test_p_Config(exportPath);
                        }
                    
                    }

                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
            
            }
        }
    }
}
