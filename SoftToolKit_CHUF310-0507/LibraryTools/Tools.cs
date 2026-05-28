using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LibraryTools.BasicTools;
using System.Windows.Controls;
using System.Reflection;
namespace LibraryTools
{
    public class Tools
    {
        private static IDictionary<string,UserControl> dcToolsMap = new Dictionary<string, UserControl>();
        private static LoadConfig m_LoadConfig = new LoadConfig();
        private  void Init()
        {
            m_LoadConfig.AddToolsMap("ToolCheckSum");
            m_LoadConfig.AddToolsMap("ToolProtocal");
            m_LoadConfig.AddToolsMap("ToolFilterTransform");
            m_LoadConfig.AddToolsMap("ToolMontageBin");
            m_LoadConfig.AddToolsMap("ToolTouchFrame");    
            m_LoadConfig.ReadToolsCondig();
            var dc = m_LoadConfig.GetToolsMap();
            Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集       
            foreach(var item in dc.ToList() )
            {
                if (item.Value=="1")
                {
                    dynamic obj = assembly.CreateInstance("LibraryTools." + item.Key);
                    dcToolsMap.Add(item.Key.Replace("Tool", ""), obj);
                }
            }
        }
        public  IDictionary<string, UserControl> GetToolsMap()
        {
            if (dcToolsMap.Count==0)
            {
                Init();
            }
            return dcToolsMap;
        }

    }
}
