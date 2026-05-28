using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using SEMITestApp.Src.Util;
using Microsoft.Win32;
using System.Windows;
using System.IO;
using System.Globalization;
using System.Collections.ObjectModel;
using SEMI.Util;

using sz_value_pair = System.Collections.Generic.KeyValuePair<SRange, int>;
using System.Windows.Data;
using SMInvokeBridge;

namespace SEMITestApp.Src.WinSet
{
    public class BinInformation
    {
        public virtual int GetRows(byte[] cfgContent) { return 0; }

        public virtual int GetCols(byte[] cfgContent) { return 0; }

        public virtual int GetRefs(byte[] cfgContent) { return 0; }

        public virtual bool CheckBootValidation(byte[] bootContent) { return false; }

        public virtual bool CheckCfgValidation(byte[] cfgContent) { return false; }

        public virtual void CfgToView(MainSettingMode mode, byte[] cfgContent) { }

        public virtual void BootToView(MainSettingMode mode, byte[] bootContent) { }
    }

    public partial class SMChipInfoChipReflex : SEMI.Util.ChipReflex
    {
        protected static ChipReflex single = new SMChipInfoChipReflex();

        public static ChipReflex Instance
        {
            get { return single; }
        }

        static SMChipInfoChipReflex()
        {
            RegisterReflexModule();
        }

        public override Type TypeOfReflexObject(string objName)
        {
            return Type.GetType(objName);
        }

        private static void RegisterReflexModule()
        {
            Type type = typeof(SMChipInfoChipReflex);
            var methods = type.GetMethods();

            var reflexMethods = methods.Where(t => { return t.Name.Contains("RegistReflex") ? true : false; });

            reflexMethods.All((t) => { t.Invoke(SMChipInfoChipReflex.Instance, null); return true; });
        }
    }

    public class SettingMode : CtrlEventDispacher
    {
        public static XmlDocument xml = new XmlDocument();
        public static byte[] bootContent = null;
        public static byte[] cfgContent  = null;
        public static ushort selectedIC = 0;

        public static int keyNum = 0;
        public static int keyThr = 0;
        public static List<KeyValuePair<int, int>> listKeys = new List<KeyValuePair<int, int>>();
        public static List<int> listKeyChannels = new List<int>();
        protected static string workStation = "";

        protected static ushort selectedProtocal = 0;

        protected static BinInformation chipInfo = new BinInformation();

        public static int physicalButtonNum = 0;
        public static List<KeyValuePair<int, int>> physicalButtons = new List<KeyValuePair<int, int>>();

        public SettingMode()
        {
            
        }

        public virtual void XMLDataToView()
        {

        }

        public virtual void ViewToXMLData()
        {

        }

        protected static int rows = 0;

        protected static int cols = 0;

        public static int GetRows()
        {
            if (0 != rows) return rows;
            return chipInfo.GetRows(cfgContent);
        }

        public static int GetCols()
        {
            if (0 != cols) return cols;
            return chipInfo.GetCols(cfgContent);
        }

        public static int GetRefs()
        {
            return chipInfo.GetRefs(cfgContent);
        }

        public static int GetKeys()
        {
            return keyNum;
        }

        public static bool CheckBootValidation()
        {
            return chipInfo.CheckBootValidation(bootContent);
        }

        public static bool CheckCfgValidation()
        {
            return chipInfo.CheckCfgValidation(cfgContent);
        }

        public static ushort CaculateCheckSumU16(byte[] buf, int length)
        {
            ushort checkSum = 0;

            for (int index = 0; index < (length >> 1); index++)
            {
                ushort temp = (ushort)((buf[index * 2 + 1] << 8) + buf[index * 2 + 0]);
                checkSum += temp;
            }

            return checkSum;
        }

        public static uint CaculateCheckSumEx(byte[] buf, int length)
        {
            int k = 0;
            uint combChk = 0;
            ushort check = 0, checkEx = 0;

            for (k = 0; k < length; k++)
            {
                check += buf[k];
                checkEx += (ushort)(k * buf[k]);
            }
            combChk = (uint)(checkEx << 16) | check;

            return combChk;
        }

        public static void DeleteXmlNodeArray(XmlNode parent, string node, string key)
        {
            if (null == parent) return;
            if (string.IsNullOrEmpty(node)) return;

            XmlNode tNode = parent.SelectSingleNode(node);
            if (null == tNode) return;

            XmlNodeList listNode = tNode.ChildNodes;
            int childCnt = listNode.Count;
            for (int index = 0; index < childCnt; index++)
            {
                string subName = string.Format("{0}_{1}", key, index);
                XmlNode child = tNode.SelectSingleNode(subName);
                if (null != child) tNode.RemoveChild(child);
            }
        }

        public static string GetXmlAttrbuteString(XmlNode parent, string node, string key, string defRet = "")
        {
            if (null == parent) return defRet;
            XmlNode children = parent.SelectSingleNode(node);
            if (null == children) return defRet;
            if (null == children.Attributes[key]) return defRet;

            return children.Attributes[key].Value;
        }

        public static int GetXmlAttrbuteValue(XmlNode parent, string node, string key, int defRet = 0)
        {
            string ret = GetXmlAttrbuteString(parent, node, key, defRet.ToString());
            if (ret.Contains("0x"))
                return int.Parse(ret.Replace("0x", ""), NumberStyles.HexNumber);
            else
                return int.Parse(ret);
        }

        public static float GetXmlAttrbuteFloatValue(XmlNode parent, string node, string key, float defRet = 0)
        {
            string ret = GetXmlAttrbuteString(parent, node, key, defRet.ToString());
            return float.Parse(ret);
        }

        public static void SaveXmlAttrbuteString(XmlNode parent, string node, string key, string val)
        {
            XmlNode sub = parent.SelectSingleNode(node);
            if(null == sub)
            {
                sub = xml.CreateElement(node);
                parent.AppendChild(sub);
            }

            XmlAttribute attr = sub.Attributes[key];
            if (null == attr)
            {
                attr = xml.CreateAttribute(key);
                sub.Attributes.Append(attr);
            }
            if (0 != val.CompareTo(attr.Value))
            {
                DeleteXmlNodeArray(parent, node, key);
            }
            attr.Value = val;
        }

        public static void SaveXmlAttrbuteValue<T>(XmlNode parent, string node, string key, T val, string format = null)
        {
            string strValue = "";
            if (string.IsNullOrEmpty(format))
            {
                strValue = val.ToString();
            }
            else
            {
                strValue = string.Format(format, val);
            }
            SaveXmlAttrbuteString(parent, node, key, strValue);
        }

        public static bool LoadXml(string path)
        {
            try
            {
                xml.RemoveAll();
                xml.Load(path);
            }
            catch (Exception ex)
            {
                ex.ToString();
                return false;
            }

            return true;
        }

        public static bool SaveXml(string path)
        {
            try
            {
                int endIndex = path.LastIndexOf('\\');
                string dir = path.Substring(0, endIndex);
                if (false == System.IO.Directory.Exists(dir))
                    System.IO.Directory.CreateDirectory(dir);

                xml.Save(path);
            }
            catch (Exception ex)
            {
                ex.ToString();
                return false;
            }

            return true;
        }

        public static string GetWorkPath()
        {
            string strWorkPath = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            int index = strWorkPath.LastIndexOf("\\");
            strWorkPath = strWorkPath.Substring(0, index - 0);
            index = strWorkPath.LastIndexOf("\\");
            strWorkPath = strWorkPath.Substring(0, index + 1);
            return strWorkPath;
        }

        public virtual void ResolveXmlSetting()
        {

        }

        public virtual void ResolveCfgSetting()
        {

        }

        public void CreateNewXmlDoc()
        {
            xml = new XmlDocument();
            XmlDeclaration dec = xml.CreateXmlDeclaration("1.0", "utf-8", "yes");
            xml.AppendChild(dec);

            XmlElement tester = xml.CreateElement("semitester");
            xml.AppendChild(tester);

//             XmlElement common = xml.CreateElement("common");
//             tester.AppendChild(common);
        }
    }

}
