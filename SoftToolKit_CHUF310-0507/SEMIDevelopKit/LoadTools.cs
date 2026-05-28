using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using Xceed.Wpf.AvalonDock.Layout;
using System.Windows;

namespace LoadToolLibrary
{
   public static class LoadTool
    {
       public static void LoadTools(LayoutAnchorablePane avalonPane)
       {
           string AppPathName = System.Windows.Forms.Application.StartupPath;
           try
           {
               var assembly = Assembly.LoadFrom(AppPathName + @"\LibraryTools.dll");
               var type = assembly.GetType("LibraryTools.Tools");
               dynamic lib = Activator.CreateInstance(type);
               var tools = lib.GetToolsMap();
               foreach (var tool in tools)
               {
                   LayoutAnchorable it = new LayoutAnchorable();
                   it.Title = tool.Key;
                   it.Content = tool.Value;
                   avalonPane.Children.Add(it);
               } 
           }
           catch (System.Exception ex)
           {
               MessageBox.Show(ex.ToString());
               MessageBox.Show("Not Found LibraryTools.dll");
           }
            
       }
    }
}
