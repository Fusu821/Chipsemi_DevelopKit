using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using LoadToolLibrary;
namespace SEMIDevelopKit.Src.WinSub
{
    /// <summary>
    /// ToolsFrame.xaml 的交互逻辑
    /// </summary>
    public partial class ToolsFrame : UserControl
    {
        private IDictionary<EnumTranslateType, string> dcTypeToPath = new Dictionary<EnumTranslateType, string>();
        public ToolsFrame()
        {
            InitializeComponent();

            this.DataContext = ModeTools.Singleton();
            LoadTool.LoadTools(panelLeft);
        }

        //private void PacketToSPI(string path)
        //{
        //    //Time [s],Packet ID,MOSI,MISO
        //    string backUp = "";
        //    string directory = System.IO.Path.GetDirectoryName(path);

        //    try
        //    {
        //        StreamReader srReaderFile = new StreamReader(path);
        //        string line = srReaderFile.ReadLine();
        //        if (0 != line.CompareTo("Time [s],Packet ID,MOSI,MISO"))
        //            return;

        //        int tickCnt = 0;
        //        byte lastAddrVal = 0;
        //        int lastPacketID = int.MaxValue;
        //        ModeTools.Singleton().ProtocalParsed = "";
        //        string strCommandTemp = "", strReadTemp = "";
        //        StringBuilder sb = new StringBuilder();

        //        while (!srReaderFile.EndOfStream)
        //        {
        //            line = srReaderFile.ReadLine();
        //            string[] stamp = line.Trim().Split(',');

        //            backUp = line;

        //            int stampID = 0;
        //            if ("" == stamp[1])
        //                stampID = 0;
        //            else
        //                stampID = int.Parse(stamp[1]);

        //            if (stampID != lastPacketID)
        //            {
        //                if (!string.IsNullOrEmpty(strReadTemp))
        //                {
        //                    strCommandTemp += string.Format("{0,-4:X} //", -tickCnt) + strReadTemp;
        //                    strReadTemp = "";
        //                }
        //                if (!string.IsNullOrEmpty(strCommandTemp))
        //                {
        //                    sb.AppendLine(strCommandTemp);
        //                    strCommandTemp = "";
        //                }
        //                strCommandTemp += "\r\n" + (ModeTools.Singleton().PacketTime ? stamp[0] + "\t" : "") + "w  ";
        //                tickCnt = 4;
        //                lastAddrVal = 0;
        //            }

        //            tickCnt--;
        //            if (tickCnt == 0)
        //            {
        //                lastAddrVal = byte.Parse(stamp[2].Replace("0x", ""), System.Globalization.NumberStyles.HexNumber);
        //                strCommandTemp += stamp[2].Replace("0x", "") + " ";
        //                strCommandTemp += ((lastAddrVal & 0x02) > 0) ? "r  " : "";
        //            }
        //            else if (tickCnt > 0)
        //            {
        //                strCommandTemp += stamp[2].Replace("0x", "") + " ";
        //            }
        //            else if (tickCnt < 0)
        //            {
        //                if ((lastAddrVal & 0x02) > 0) strReadTemp += stamp[3].Replace("0x", "") + " ";
        //                else strCommandTemp += stamp[3].Replace("0x", "") + " ";
        //            }

        //            lastPacketID = stampID;
        //        }
        //        srReaderFile.Close();


        //        if (!string.IsNullOrEmpty(strReadTemp))
        //        {
        //            strCommandTemp += string.Format("{0,-4:X} //", -tickCnt) + strReadTemp;
        //            strReadTemp = "";
        //        }
        //        if (!string.IsNullOrEmpty(strCommandTemp))
        //        {
        //            sb.AppendLine(strCommandTemp);
        //            strCommandTemp = "";
        //        }

        //        ModeTools.Singleton().ProtocalParsed = sb.ToString().Substring(2);

        //        //write text
        //        string fileName = System.IO.Path.GetFileNameWithoutExtension(path) + "_SPI.txt";
        //        StreamWriter sw = new StreamWriter(directory + "\\" + fileName, false, Encoding.Default);
        //        sw.Write(ModeTools.Singleton().ProtocalParsed);
        //        sw.Flush();
        //        sw.Close();
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.ToString());
        //    }
        //}

        //private void PacketToSPIx(string path)
        //{
        //    //Time [s],Packet ID,MOSI,MISO
        //    string directory = System.IO.Path.GetDirectoryName(path);

        //    try
        //    {
        //        StreamReader srReaderFile = new StreamReader(path);
        //        string line = srReaderFile.ReadLine();
        //        if (0 != line.CompareTo("Time [s],Packet ID,MOSI,MISO"))
        //            return;

        //        int lastPacketID = int.MaxValue;
        //        ModeTools.Singleton().ProtocalParsed = "";
        //        string strWriteTemp = "", strReadTemp = "";
        //        StringBuilder sb = new StringBuilder();

        //        while (!srReaderFile.EndOfStream)
        //        {
        //            line = srReaderFile.ReadLine();
        //            string[] stamp = line.Trim().Split(',');

        //            //backUp = line;

        //            int stampID = 0;
        //            if ("" == stamp[1])
        //                stampID = 0;
        //            else
        //                stampID = int.Parse(stamp[1]);

        //            if (stampID != lastPacketID)
        //            {
        //                if (!string.IsNullOrEmpty(strWriteTemp))
        //                {
        //                    sb.AppendLine(strWriteTemp);
        //                }
        //                if (!string.IsNullOrEmpty(strReadTemp))
        //                {
        //                    sb.AppendLine(strReadTemp);
        //                    sb.AppendLine("");
        //                }

        //                strWriteTemp = (ModeTools.Singleton().PacketTime ? stamp[0] + "\t" : "") + "w  ";
        //                strReadTemp =  (ModeTools.Singleton().PacketTime ? stamp[0] + "\t" : "") + "r  ";
        //            }

        //            strWriteTemp += stamp[2].Replace("0x", "") + " ";
        //            strReadTemp += stamp[3].Replace("0x", "") + " ";
        //            lastPacketID = stampID;
        //        }
        //        srReaderFile.Close();


        //        if (!string.IsNullOrEmpty(strWriteTemp))
        //        {
        //            sb.AppendLine(strWriteTemp);
        //        }
        //        if (!string.IsNullOrEmpty(strReadTemp))
        //        {
        //            sb.AppendLine(strReadTemp);
        //        }

        //        ModeTools.Singleton().ProtocalParsed = sb.ToString();

        //        //write text
        //        string fileName = System.IO.Path.GetFileNameWithoutExtension(path) + "_SPIx.txt";
        //        StreamWriter sw = new StreamWriter(directory + "\\" + fileName, false, Encoding.Default);
        //        sw.Write(ModeTools.Singleton().ProtocalParsed);
        //        sw.Flush();
        //        sw.Close();
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.ToString());
        //    }
        //}

        //private Dictionary<string, int[]> Keytitles = new Dictionary<string, int[]>() { { "Time[s]", new int[] { -1, 1 } }, { "Packet ID", new int[] { -1, 1 } }, { "Address", new int[] { -1, 1 } }, { "Read/Write", new int[] { -1, 1 } }, { "Data", new int[] { -1, 1 } }, { "ACK/NAK", new int[] { -1, 0 } }, };
        //private List<string[]> SplitinFormation = new List<string[]>();
        //private void PacketToIIC(string path)
        //{
        //    string directory = System.IO.Path.GetDirectoryName(path);
        //    SplitinFormation.Clear();
        //    try
        //    {
        //        StreamReader srReaderFile = new StreamReader(path);
        //        string line = srReaderFile.ReadLine();
        //        string[] title = line.Trim().Split(',');
        //        if (title.Count()<4)
        //        {
        //            return;
        //        }
        //        else
        //        {

        //            foreach (var Keytitle in Keytitles.ToList())
        //            {
        //                for (int i = 0; i < title.Count();i++)
        //                {
        //                    if (Keytitle.Key == title[i])
        //                   {
        //                       Keytitles[Keytitle.Key][0] = i;
        //                       break;
        //                   }
        //                }
        //            }
        //        }

        //        foreach (var Keytitle in Keytitles)
        //        {
        //           if ((Keytitle.Value[1]) == 1 && (Keytitle.Value[0]==-1))
        //          {
        //            return;
        //          }
        //        }
        //        int readCnt = 0;
        //        ModeTools.Singleton().ProtocalParsed = "";
        //        string strReadTemp = "", strWriteTemp = "";
        //        StringBuilder sb = new StringBuilder();             
        //        while (!srReaderFile.EndOfStream)
        //        {

        //            string t_CurrentLine = srReaderFile.ReadLine();
        //            string[] t_Currentstamp = t_CurrentLine.Trim().Split(',');
        //            SplitinFormation.Add(t_Currentstamp);
                   
        //        }

        //        for (int i = 0; i < SplitinFormation.Count();i++ )
        //        {
        //            var stamp = SplitinFormation[i];
        //            if ("Write" == stamp[Keytitles["Read/Write"][0]])
        //            {
        //                if (i + 1 < SplitinFormation.Count())
        //                {
        //                    if ((stamp[Keytitles["Packet ID"][0]] == SplitinFormation[i + 1][Keytitles["Packet ID"][0]]))
        //                    {
        //                        strWriteTemp += "\r\n" + (ModeTools.Singleton().PacketTime ? stamp[Keytitles["Time[s]"][0]] + "\t" : "") + "w  ";
        //                        strWriteTemp += stamp[Keytitles["Data"][0]].Replace("0x", "") + " ";

        //                        readCnt = 0;
        //                        strReadTemp += SplitinFormation[i + 1][Keytitles["Data"][0]].Replace("0x", "") + " ";
        //                        string[] Cntstamp = strReadTemp.Trim().Split(' ');
        //                        readCnt = Cntstamp.Count();
        //                        i++;
        //                    }
        //                    else
        //                    {
        //                        strWriteTemp += "\r\n" + (ModeTools.Singleton().PacketTime ? stamp[Keytitles["Time[s]"][0]] + "\t" : "") + "w  ";
        //                        strWriteTemp += stamp[Keytitles["Data"][0]].Replace("0x", "") + " ";
        //                    }
        //                }
        //                else
        //                {
        //                    strWriteTemp += "\r\n" + (ModeTools.Singleton().PacketTime ? stamp[Keytitles["Time[s]"][0]] + "\t" : "") + "w  ";
        //                    strWriteTemp += stamp[Keytitles["Data"][0]].Replace("0x", "") + " ";
        //                }                                    
        //            }
        //            else if ("Read" == stamp[Keytitles["Read/Write"][0]])//读取读指令
        //            {
        //                readCnt = 0;
        //                strReadTemp += stamp[Keytitles["Data"][0]].Replace("0x", "") + " ";
        //                string[] Cntstamp = strReadTemp.Trim().Split(' ');
        //                readCnt = Cntstamp.Count();
        //            }

        //            if (strWriteTemp != "" && strReadTemp != "")
        //            {
        //                sb.AppendLine(strWriteTemp + " r  " + String.Format("{0,-4:X}", readCnt) + " //" + strReadTemp);
        //            }
        //            else if (strWriteTemp != "" )
        //            {
        //                sb.AppendLine(strWriteTemp);
        //            }
        //            else if (strReadTemp != "")
        //            {
        //                sb.AppendLine(" r  " + String.Format("{0,-4:X}", readCnt) + " //" + strReadTemp);
        //            }
        //            strWriteTemp = "";
        //            strReadTemp = "";
        //        }

        //        srReaderFile.Close();

        //        ModeTools.Singleton().ProtocalParsed = sb.ToString().Substring(2);

        //        //write text
        //        string fileName = System.IO.Path.GetFileNameWithoutExtension(path) + "_I2C.txt";
        //        StreamWriter sw = new StreamWriter(directory + "\\" + fileName, false, Encoding.Default);
        //        sw.Write(ModeTools.Singleton().ProtocalParsed);
        //        sw.Flush();
        //        sw.Close();
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.ToString());
        //    }
        //}

        //private void PacketHexToText(string TextSrc)
        //{
        //    try
        //    {
        //        string directory = System.IO.Path.GetDirectoryName(TextSrc);

        //        byte[] bootContent = new byte[96 * 1024];
        //        FileInfo fileInfo = new FileInfo(TextSrc);
        //        uint binFileLen = (uint)fileInfo.Length;
        //        using (FileStream fs = new FileStream(TextSrc, FileMode.Open))
        //        {
        //            fs.Read(bootContent, 0, (int)binFileLen);
        //            fs.Flush();
        //            fs.Close();
        //        }

        //        StringBuilder szTemp = new StringBuilder();
        //        for (int index = 0; index < (int)binFileLen; index++)
        //        {
        //            szTemp.Append(string.Format("0x{0:X2},", bootContent[index]));
        //            if ((index > 0) && ((index + 1) % 16) == 0)
        //            {
        //                szTemp.Append("\r\n");
        //            }
        //        }

        //        string fileName = System.IO.Path.GetFileNameWithoutExtension(TextSrc) + ".txt";
        //        StreamWriter sw = new StreamWriter(directory + "\\" + fileName, false, Encoding.Default);
        //        sw.Write(szTemp.ToString());
        //        sw.Flush();
        //        sw.Close();
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.ToString());
        //    }
        //}

        //private void PacketTextToHex(string TextSrc)
        //{
        //    try
        //    {
        //        string directory = System.IO.Path.GetDirectoryName(TextSrc);

        //        List<byte> lsContent = new List<byte>();

        //        StreamReader sr = new StreamReader(TextSrc, Encoding.Default);
        //        string text = sr.ReadToEnd();
        //        sr.Close();

        //        string[] txtArray = text.Split(',');
        //        for (int index = 0; index < txtArray.Length; index++)
        //        {
        //            string temp = txtArray[index].Trim();
        //            temp = temp.Replace("0x", "");
        //            temp = temp.Replace("0X", "");
        //            if (!string.IsNullOrEmpty(temp)) lsContent.Add(Convert.ToByte(temp, 16));
        //        }

        //        string fileName = System.IO.Path.GetFileNameWithoutExtension(TextSrc) + ".bin";
        //        using (FileStream fs = new FileStream(directory + "\\" + fileName, FileMode.Create))
        //        {
        //            fs.Write(lsContent.ToArray(), 0, lsContent.Count);
        //            fs.Flush();
        //            fs.Close();
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.ToString());
        //    }
        //}

        //private void ParserView_Drop(object sender, DragEventArgs e)
        //{
        //    string path = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
        //    //string directory = System.IO.Path.GetDirectoryName(path);

        //    if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_PackToIIC)
        //    {
        //        PacketToIIC(path);
        //    }
        //    else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_PackToSPI)
        //    {
        //        PacketToSPI(path);
        //    }
        //    else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_HexToTxt)
        //    {
        //        PacketHexToText(path);
        //    }
        //    else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_TxtToHex)
        //    {
        //        PacketTextToHex(path);
        //    }
        //    else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_PackToSPIx)
        //    {
        //        PacketToSPIx(path);
        //    }

        //    dcTypeToPath[ModeTools.Singleton().CurSelTranslate] = path;
        //}

        private void ParserView_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effects = DragDropEffects.Link;
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }
        }

        //private void Pattern_Click(object sender, RoutedEventArgs e)
        //{
        //    string szPattern = ModeTools.Singleton().Pattern;

        //    if (string.IsNullOrEmpty(szPattern)) return;

        //    try
        //    {
        //        //0x55aa:0x55aa:0:0x8000
        //        //0x0001:0xffff:1:0x8000
        //        string[] vec = szPattern.Trim().Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries);
        //        if (4 == vec.Length)
        //        {
        //            uint uf = uint.Parse(vec[0].Replace("0x", ""), System.Globalization.NumberStyles.HexNumber);
        //            uint ut = uint.Parse(vec[1].Replace("0x", ""), System.Globalization.NumberStyles.HexNumber);
        //            uint us = uint.Parse(vec[2].Replace("0x", ""), System.Globalization.NumberStyles.HexNumber);
        //            uint uc = uint.Parse(vec[3].Replace("0x", ""), System.Globalization.NumberStyles.HexNumber);

        //            if (uc > 64 * 1024) uc = 64 * 1024;

        //            byte[] pattern = new byte[uc * 2];
        //            uint udata = uf;
        //            for (int index = 0; index < uc; index++)
        //            {
        //                pattern[index * 2 + 0] = (byte)(udata >> 8);
        //                pattern[index * 2 + 1] = (byte)(udata & 0xff);
        //                udata += us;
        //                if (udata > ut) udata = uf;
        //            }

        //            System.Windows.Forms.SaveFileDialog saveFileDialog = new System.Windows.Forms.SaveFileDialog();
        //            saveFileDialog.Filter = "Text Files (*.bin;)|*.bin";
        //            if (System.Windows.Forms.DialogResult.OK == saveFileDialog.ShowDialog())
        //            {
        //                //write text
        //                using (FileStream fs = new FileStream(saveFileDialog.FileName, FileMode.Create))
        //                {
        //                    fs.Write(pattern, 0, pattern.Length);
        //                    fs.Flush();
        //                    fs.Close();
        //                }
        //            }
        //        }
        //    }
        //    catch
        //    {

        //    }
        //}

        //private void ShortCuts_Click(object sender, RoutedEventArgs e)
        //{
        //    if (dcTypeToPath.ContainsKey(ModeTools.Singleton().CurSelTranslate))
        //    {
        //        string path = dcTypeToPath[ModeTools.Singleton().CurSelTranslate];
        //        try
        //        {
        //            if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_PackToIIC)
        //            {
        //                PacketToIIC(path);
        //            }
        //            else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_PackToSPI)
        //            {
        //                PacketToSPI(path);
        //            }
        //            else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_HexToTxt)
        //            {
        //                PacketHexToText(path);
        //            }
        //            else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_TxtToHex)
        //            {
        //                PacketTextToHex(path);
        //            }
        //            else if (ModeTools.Singleton().CurSelTranslate == EnumTranslateType.Translate_PackToSPIx)
        //            {
        //                PacketToSPIx(path);
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            ex.ToString();
        //        }
        //    }
        //}

        private void AssistView_Drop(object sender, DragEventArgs e)
        {
            string path = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();

            ModeTools.Singleton().OnAssist(path);
        }

        private void AssistGenPacket_Click(object sender, RoutedEventArgs e)
        {
            ModeTools.Singleton().AssistGenPacket();
        }

        //private void CheckSumCalc_Click(object sender, RoutedEventArgs e)
        //{
        //    try
        //    {
        //        string input = ModeTools.Singleton().CheckSumDataInput.Replace(',', ' ');
        //        string[] inputArray = input.Split(' ');
        //        var ls = inputArray.Select((t) =>
        //        {
        //            t = t.Replace("0x", "").Trim();
        //            return byte.Parse(t, System.Globalization.NumberStyles.HexNumber);
        //        });
        //        var inputData = ls.ToArray();
        //        if (ModeTools.Singleton().CurSelCheckSum == CheckSumType.CheckSumU816)
        //        {
        //            ModeTools.Singleton().CalcCheckSum = SMInvokeBridge.SMCheckTools.CaculateCheckSumU816(inputData, (uint)inputData.Length);
        //        }
        //        else if (ModeTools.Singleton().CurSelCheckSum == CheckSumType.CheckSumU16)
        //        {
        //            ModeTools.Singleton().CalcCheckSum = SMInvokeBridge.SMCheckTools.CaculateCheckSumU16(inputData, (uint)inputData.Length);
        //        }
        //        else if (ModeTools.Singleton().CurSelCheckSum == CheckSumType.CheckSumEx)
        //        {
        //            ModeTools.Singleton().CalcCheckSum = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(inputData, (uint)inputData.Length);
        //        }
        //        else if (ModeTools.Singleton().CurSelCheckSum == CheckSumType.CheckSumU8)
        //        {
        //            ModeTools.Singleton().CalcCheckSum = SMInvokeBridge.SMCheckTools.CaculateCheckSumU8(inputData, (uint)inputData.Length);
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        ex.ToString();
        //    }
        //}
    }
}
