using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LibraryTools.BasicTools
{
    public  class LoadConfig
    {
        private IDictionary<string, string> dcToolsConfigMap = new Dictionary<string, string>();

        public void AddToolsMap(string Key)
        {
            dcToolsConfigMap.Add(Key,"");
        }
        public bool RemoveToolsMap(string Key)
        {
           return dcToolsConfigMap.Remove(Key);
        }
        public IDictionary<string, string> GetToolsMap()
        {
            return dcToolsConfigMap;
        }
        //读取配置文件
        [System.Runtime.InteropServices.DllImport("kernel32")]
        public static extern int GetPrivateProfileString(string section, string key, string def, System.Text.StringBuilder retVal, int size, string filePath);
        //更改配置文件
        [System.Runtime.InteropServices.DllImport("kernel32")]
        public static extern int WritePrivateProfileString(string Section, string Key, string Value, string iniFilePath);
        string sPath = System.Windows.Forms.Application.StartupPath + @"\Tools\Tools.ini";

        //public String ReadIni(string key)//读取函数
        //{
        //    StringBuilder temp = new StringBuilder();
        //    // string key = "TimeLimit";
        //    GetPrivateProfileString("TimeLimitConfig", key, "1", temp, 255, sPath);
        //    string str1 = temp.ToString();
        //    //int data = int.Parse(str1);
        //    return str1;
        //}

        //public void WriteIni(string key, string Value)//更改函数
        //{

        //    WritePrivateProfileString("TimeLimitConfig", key, Value, sPath);
        //}

        public void ReadToolsCondig()
        {
          foreach (var item in dcToolsConfigMap.ToList())
          {
              StringBuilder temp = new StringBuilder();
              var ret = GetPrivateProfileString("ToolsConfig", item.Key, "1", temp, 255, sPath);
              dcToolsConfigMap[item.Key] = temp.ToString();      
                      
          }
        }
    }
}
