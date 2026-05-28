using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.IO;
using System.Text.RegularExpressions;

namespace LibraryTools
{

    class ToolFilterTransformViewModel
    {
        private ModelToolFilterTransform m_ModelToolFilterTransform = new ModelToolFilterTransform();
        public ModelToolFilterTransform ModelToolFilterTransform 
        {
            get
            {
                return m_ModelToolFilterTransform;
            }
        }

        public ToolFilterTransformViewModel()
        {
           m_ModelToolFilterTransform.ClickFilter = new Command()
           {
               DoExecute = obj =>
              {
                  ClickFilter();
              }

           };
            m_ModelToolFilterTransform.ClickTransform = new Command()
            {
                DoExecute = obj =>
                {
                    ClickTransform();
                }
            };
        }

        public void DisplayContent(string path)
        {
            try
            {
                m_ModelToolFilterTransform.DisplayContent="";
                m_ModelToolFilterTransform.SourceData.Clear();
                StreamReader srReaderFile = new StreamReader(path);
                string line = srReaderFile.ReadLine();
                while (!srReaderFile.EndOfStream)
                {
                   var nextline= srReaderFile.ReadLine();
                   m_ModelToolFilterTransform.SourceData.Add(nextline);//把文本读取到内存里  
                   m_ModelToolFilterTransform.DisplayContent += nextline;//把内存显示到界面上
                   m_ModelToolFilterTransform.DisplayContent += "\r\n";
                }
                srReaderFile.Close();
                //foreach (var nextline in m_ModelToolFilterTransform.MemoryData)//把内存显示到界面上
                //{
                   
                //}
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void ClickFilter()
        {
            m_ModelToolFilterTransform.DisplayContent = "";
            m_ModelToolFilterTransform.FilterData.Clear();
            var tFilterCriteria = Regex.Replace(m_ModelToolFilterTransform.FilterCriteria, @"\s", "");
            if (tFilterCriteria=="")
            {
                foreach (var line in m_ModelToolFilterTransform.SourceData)
                {

                    m_ModelToolFilterTransform.DisplayContent += line;
                    m_ModelToolFilterTransform.DisplayContent += "\r\n";
                }
            }
            else
            {
                foreach (var line in m_ModelToolFilterTransform.SourceData)
                {
                    if (line == "")
                    {
                        continue;
                    }
                    var s = Regex.Replace(line, @"\s", "");

                    var index = s.IndexOf(Regex.Replace(m_ModelToolFilterTransform.FilterCriteria, @"\s", ""));
                    if (index == -1)
                    {
                        continue;
                    }
                    m_ModelToolFilterTransform.DisplayContent += s;
                    m_ModelToolFilterTransform.DisplayContent += "\r\n";
                    m_ModelToolFilterTransform.FilterData.Add(s);
                }

            }
         
        }
        private Single timebase = 0;
        private bool firsttime = false;
        private void ClickTransform()
        {
           m_ModelToolFilterTransform.DisplayContent = "";
           m_ModelToolFilterTransform.DisplayContent = "Close-OSC-Cap-Curve,,,,";
           m_ModelToolFilterTransform.DisplayContent += "\r\n";
           m_ModelToolFilterTransform.DisplayContent = "num,time(ms),data";
           m_ModelToolFilterTransform.DisplayContent += "\r\n";
           firsttime = true;
           m_ModelToolFilterTransform.SourceTableData.Clear();
           foreach (var line in m_ModelToolFilterTransform.FilterData)
           {
               string[] arr = line.Split(new char[] { 'w','r','/' }, StringSplitOptions.RemoveEmptyEntries);
               if (arr.Length!=4)
               {
                   continue;
               }
               if (firsttime == true)
               {
                   firsttime = false;
                   timebase = Convert.ToSingle(arr[0]);
               }
              
               TableDataAdd(arr);
           }
           foreach (var td in m_ModelToolFilterTransform.SourceTableData)
           {
               string s = Convert.ToString(td.index) + "," + Convert.ToString(td.time) + "," + Convert.ToString(td.data);
               m_ModelToolFilterTransform.DisplayContent += s;
               m_ModelToolFilterTransform.DisplayContent += "\r\n";
           }
           if (m_ModelToolFilterTransform.SourceTableData!=null)
           {
               System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
               saveFileDlg.OverwritePrompt = true;
               saveFileDlg.Filter = "csv files (*.csv)|*.csv";
               if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
               {
                   string fileName = saveFileDlg.FileName;
                   FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                   BinaryWriter bw = new BinaryWriter(fs);
                   bw.Write(m_ModelToolFilterTransform.DisplayContent);
                   bw.Close();
               }
           }
        
        }
        private static int index = 0;
        private void TableDataAdd(string[] arr)
        {
            try
            {
                var t_time = ((Convert.ToSingle(arr[0])) - timebase) * 1000;
                t_time = Convert.ToSingle(Math.Round(t_time, 1));
                var t_num = Convert.ToInt32(arr[2]);
                var t_byte = StringToBytes(arr[3]);
                Int64 data = 0;
                if (t_num == 4)
                {
                    data = System.BitConverter.ToInt32(t_byte, 0);
                }
                else if(t_num == 8)
                {
                    data = System.BitConverter.ToInt64(t_byte, 0);
                }
                else
                {
                    return;
                }         
                var t_TData = new TableData(index, t_time, data);
                m_ModelToolFilterTransform.SourceTableData.Add(t_TData);
                index++;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());	
            }
          
        }

        private byte[] StringToBytes(string s)
        {
	        int sLen = s.Length;
	        int bytesLen = sLen / 2;
	        byte[] bytes = new byte[bytesLen];
	        int position = 0;
	        for(int i = 0; i < bytesLen; i++)
	        {
	            string abyte = s.Substring(position, 2);
                bytes[i] = Convert.ToByte(abyte, 16);
	            position += 2;
	        }
	        return bytes;
        }

 }
}
