using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.Globalization;
using System.IO;

namespace SEMIDevelopKit.Src.WinSub
{
    public class IOCommand
    {
        static byte[] write = new byte[1024 * 5];
        static byte[] read = new byte[1024 * 5];
        static IEnumerable<TResult> Map<T, TResult>(Func<T, TResult> func, IEnumerable<T> list)
        {
            foreach (var i in list)
            {
                yield return func(i);
            }
        }
        static T Reduce<T, U>(Func<U, T, T> func, IEnumerable<U> list, T acc)
        {
            foreach (var i in list)
            {
                acc = func(i, acc);
            }
            return acc;
        }
        public static uint DoCommand(string strCmd, ref string strResult)
        {
            try
            {
                string strContent = "", strMark = "";
                ushort valueWidth = 1, numStyle = (ushort)NumberStyles.HexNumber;
                MainViewModel.Intr.ReturnCode = 0;

                strCmd = strCmd.TrimStart();
                strCmd = strCmd.ToLower();

                if (0 == strCmd.Length)
                {
                    strResult = "\r\n";
                    return 0;
                }

                if ("//" == strCmd.Substring(0, 2))
                {
                    int iMark = strCmd.IndexOf("//");
                    strMark = strCmd.Substring(iMark);
                }
                else if (strCmd.Contains("//"))
                {
                    int iMark = strCmd.IndexOf("//");
                    strMark = strCmd.Substring(iMark);
                    strContent = strCmd.Substring(0, iMark).TrimEnd();
                }
                else
                {
                    strContent = strCmd.Replace("\r\n", "");
                    strContent = strContent.Replace("\r", "");
                }

                if (0 == strContent.IndexOf("enter_upgrade_mode"))
                {
                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_UPGRADE_MODE);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("reset_pin"))
                {
                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("power_level"))
                {
                    string temp = strContent.Replace("power_level", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    string[] arrParam = temp.Split(',');
                    uint[] usParam = new uint[6];
                    for (int index = 0; index < usParam.Length && index < arrParam.Length; index++)
                        usParam[index] = uint.Parse(arrParam[index], System.Globalization.NumberStyles.HexNumber);


                    byte[] retValue = new byte[16];
                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand((byte)cmdTypeID.CMD_MTK_SET_VOLTAGE, usParam[0], (byte)usParam[1], 0, retValue);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("run_ram_code"))
                {
                    string temp = strContent.Replace("run_ram_code", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    if (!System.IO.File.Exists(temp))
                        temp = System.Environment.CurrentDirectory + "\\XBin\\" + temp;
                    if (!System.IO.File.Exists(temp))
                    {
                        MainViewModel.Intr.ReturnCode = 2;
                        strMark = "File not exist!\r\n";
                    }
                    else 
                    {
                        using (FileStream fs = new FileStream(temp, FileMode.Open))
                        {
                            int lenth = (int)fs.Length;
                            byte[] fileContent = new byte[lenth];
                            fs.Read(fileContent, 0, lenth);
                            fs.Flush();
                            fs.Close();
                            var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                            MainViewModel.Intr.ReturnCode = mdBase.WritePram(fileContent, (uint)lenth);

                            strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                        }
                        
                    }
                }
                else if (0 == strContent.IndexOf("register_bit_set"))
                {
                    string temp = strContent.Replace("register_bit_set", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    string[] arrParam = temp.Split(',');
                    uint[] usParam = new uint[3];
                    for (int index = 0; index < usParam.Length && index < arrParam.Length; index++)
                        usParam[index] = uint.Parse(arrParam[index], System.Globalization.NumberStyles.HexNumber);

                    uint regData = 0;
                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadRegister(usParam[0], ref regData);
                    regData = regData & usParam[1];
                    regData = regData | usParam[2];
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteRegister(usParam[0], regData);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("write_register"))
                {
                    string temp = strContent.Replace("write_register", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    string[] arrParam = temp.Split(',');
                    uint[] usParam = new uint[3];
                    for (int index = 0; index < usParam.Length && index < arrParam.Length; index++)
                        usParam[index] = uint.Parse(arrParam[index], System.Globalization.NumberStyles.HexNumber);

                    //usParam[1] = ((usParam[1] & 0xFF) << 24) | ((usParam[1] >> 8) & 0xFF) << 16
                    //            | ((usParam[1] >> 16) & 0xFF) << 8 | (usParam[1] >> 24) & 0xFF;   
 
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteRegister(usParam[0], usParam[1]);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("read_register"))
                {
                    string temp = strContent.Replace("read_register", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    string[] arrParam = temp.Split(',');
                    uint[] usParam = new uint[3];
                    for (int index = 0; index < usParam.Length && index < arrParam.Length; index++)
                        usParam[index] = uint.Parse(arrParam[index], System.Globalization.NumberStyles.HexNumber);
                    uint value = 0;
                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadRegister(usParam[0], ref value);

                    strMark = "\t//";
                    strMark += string.Format("0x{0,-8:X8}", value);
                    strMark += string.Format("\t({0:D},{1:D})", (short)(value >> 16), (short)(value & 0xffff));
                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("write_pattern"))
                {
                    string temp = strContent.Replace("write_pattern", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    ushort pattern = ushort.Parse(temp, NumberStyles.HexNumber);
                    byte [] ptArray = new byte[]{(byte)(pattern >> 8), (byte)(pattern >> 0)};

                    for (int index = 0; index < 1024; index += 2)
                    {
                        Array.Copy(ptArray, 0, write, index, 2);
                    }
                        

                    for (int index = 0; index < 128; index++)
                    {
                        MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace((uint)index * 1024, write, 1024, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1); 
                    }
                }
                else if (0 == strContent.IndexOf("check_pattern"))
                {
                    string temp = strContent.Replace("check_pattern", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    ushort pattern = ushort.Parse(temp, NumberStyles.HexNumber);
                    byte[] ptArray = new byte[] { (byte)(pattern >> 8), (byte)(pattern >> 0) };

                    for (int index = 0; index < 1024; index += 2)
                    {
                        Array.Copy(ptArray, 0, write, index, 2);
                    }

                    bool checkPass = true;
                    for (int index = 0; index < 128; index++)
                    {
                        if (!checkPass) break;
                        MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace((uint)index * 1024, read, 1024);
                        for (int pos = 0; pos < 1024; pos++)
                        {
                            if (write[pos] != read[pos])
                            {
                                checkPass = false;
                                strMark = "\t//check fail at " + string.Format("0x{0,-4:X2}", (index * 1024 + pos));
                                break;
                            }
                        }
                    }
                    if (checkPass) strMark = "\t//check OK";
                }
                else if (0 == strContent.IndexOf("sync"))
                {
                    var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                    if (null != mdBase) mdBase.SwitchMode();

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (0 == strContent.IndexOf("invoke_command"))
                {
                    string temp = strContent.Replace("invoke_command", "").Trim();
                    temp = temp.Replace("(", "");
                    temp = temp.Replace(")", "");
                    temp = temp.Replace("0x", "");
                    string[] arrParam = temp.Split(',');
                    uint[] usParam = new uint[6];
                    byte[] retValue = new byte[16];
                    for (int index = 0; index < usParam.Length && index < arrParam.Length; index++)
                        usParam[index] = uint.Parse(arrParam[index], System.Globalization.NumberStyles.HexNumber);
                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand((byte)usParam[0], usParam[1], (ushort)usParam[2], (ushort)usParam[3], retValue);

                    strMark = "\t//";
                    for (int index = 0; index < 16; index++)
                        strMark += string.Format("{0,-4:X2}", retValue[index]);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if (strContent.IndexOf("mw") >= 0 || strContent.IndexOf("mr") >= 0)
                {
                    uint iWrite = 0, iRead = 0;
                    SubParse(strContent, ref iWrite, ref iRead, ref numStyle, ref valueWidth);

                    //#define           MTK_TXRX_BUF_MCAP                   0xc400
                    if (iWrite > 0)
                    {
                        MainViewModel.Intr.ReturnCode = SMCommBase.WriteToUsbMemory(0xc400, write, (ushort)iWrite);
                    }
                    if (iRead > 0)
                    {
                        MainViewModel.Intr.ReturnCode = SMCommBase.ReadFromUsbMemory(0xc400, read, (ushort)iRead);
                        strMark = GetFormatString(iRead, valueWidth, numStyle);
                    }
                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
//                 else if (strContent.IndexOf("dw") >= 0 || strContent.IndexOf("dr") >= 0)
//                 {
//                     uint iWrite = 0, iRead = 0;
//                     SubParse(strContent, ref iWrite, ref iRead, ref numStyle, ref valueWidth);
// 
//                     if (iWrite > 0)
//                     {
//                         MainViewModel.Intr.ReturnCode = SMChipBase.BSPRWrite(write, iWrite);
//                     }
//                     if (iRead > 0)
//                     {
//                         MainViewModel.Intr.ReturnCode = SMChipBase.BSPRRead(read, iRead);
//                         strMark = GetFormatString(iRead, valueWidth, numStyle);
//                     }
//   
//                     strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
//                 }
                else if (0 == strContent.IndexOf("d"))
                {
                    string temp = strContent.Replace("d", "").Trim();
                    int sleepTime = int.Parse(temp);
                    System.Threading.Thread.Sleep(sleepTime);
                }
                else if (strContent.IndexOf("sr") >= 0)
                {
                    uint iWrite = 0, iRead = 0;
                    SPI_SubParse(strContent, ref iWrite, ref iRead, ref numStyle, ref valueWidth);

                    ///do invoke
                    MainViewModel.Intr.ReturnCode = SMChipBase.BSPRWriteAndRead(write, iWrite, read, iRead);

                    strMark = GetFormatString(iRead, valueWidth, numStyle);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }
                else if(strContent.IndexOf("w") >= 0 || strContent.IndexOf("r") >= 0)
                {
                    uint iWrite = 0, iRead = 0;
                    SubParse(strContent, ref iWrite, ref iRead,  ref numStyle, ref valueWidth);

                    ///do invoke
                    MainViewModel.Intr.ReturnCode = SMChipBase.BSPRWriteAndRead(write, iWrite, read, iRead);

                    strMark = GetFormatString(iRead, valueWidth, numStyle);

                    strMark = (0 == MainViewModel.Intr.ReturnCode) ? strMark : " //Fail";
                }

                else
                {
                    if(string.IsNullOrEmpty(strMark)) strMark = " //unrecognizable command...";
                }

                strResult = strContent;
                if(!string.IsNullOrEmpty(""))
                    strResult += "\t";

                strResult += strMark + "\r\n";
            }
            catch(Exception ex)
            {
                ex.ToString();

                strResult = "unsuported cammand" + "//" + strCmd + "\r\n";
                //MainViewModel.Intr.ReturnCode = 1;
            }

            return MainViewModel.Intr.ReturnCode;
        }

        private static string GetFormatString(uint iRead, ushort valueWidth, ushort numStyle)
        {
            string strMark = "\t//";
            if (numStyle == (ushort)NumberStyles.Any) return Encoding.UTF8.GetString(read).Replace('\0', ' ');

            for (int index = 0; index < iRead; index += valueWidth)
            {
                uint val = 0;
                for (int iShift = 0; iShift < valueWidth; iShift++)
                {
                    val |= (uint)(read[index + iShift] << (iShift * 8));
                }

                string formater = "{" + string.Format("0, -{0}:{1}{2}", valueWidth * 4, (numStyle == (ushort)NumberStyles.HexNumber) ? "X" : "D", valueWidth * 2) + "}";
                strMark += string.Format(formater, (int)val);
            }
            return strMark;
        }

        private static void SubParse(string strContent, ref uint iWrite, ref uint iRead, ref ushort numStyle, ref ushort valueWidth)
        {
            Boolean wtDir = true;
            //uint iWrite = 0, iRead = 0;

            int iformat = strContent.IndexOf("-d");
            if (iformat > 0)
            {
                string strTemp = strContent.Substring(iformat + 2);
                numStyle = (ushort)NumberStyles.Integer;
                valueWidth = byte.Parse(strTemp);
                strContent = strContent.Substring(0, iformat);
            }
            iformat = strContent.IndexOf("-h");
            if (iformat > 0)
            {
                string strTemp = strContent.Substring(iformat + 2);
                numStyle = (ushort)NumberStyles.HexNumber;
                valueWidth = byte.Parse(strTemp);
                strContent = strContent.Substring(0, iformat);
            }
            iformat = strContent.IndexOf("-s");
            if (iformat > 0)
            {
                numStyle = (ushort)NumberStyles.Any;
                strContent = strContent.Substring(0, iformat);
            }


            StringBuilder strValue = new StringBuilder();
            foreach (var item in strContent)
            {
                if ('w' == item)
                {
                    wtDir = true;
                    strValue.Clear();
                }
                else if ('r' == item)
                {
                    wtDir = false;
                    strValue.Clear();
                }
                else
                {
                    if (' ' == item || '\t' == item || '\r' == item)
                    {
                        if (strValue.Length > 0)
                        {
                            string s = strValue.ToString().Trim();

                            if (wtDir)
                                write[iWrite++] = byte.Parse(strValue.ToString().Trim(), System.Globalization.NumberStyles.HexNumber);
                            else
                                iRead = uint.Parse(strValue.ToString().Trim(), System.Globalization.NumberStyles.HexNumber);

                            strValue.Clear();
                        }
                    }
                    else
                    {
                        strValue.Append(item);
                    }
                }
            }

            if (strValue.Length > 0)
            {
                if (wtDir)
                    write[iWrite++] = byte.Parse(strValue.ToString().Trim(), System.Globalization.NumberStyles.HexNumber);
                else
                    iRead = uint.Parse(strValue.ToString().Trim(), System.Globalization.NumberStyles.HexNumber);
            }
        }

        private static void SPI_SubParse(string strContent, ref uint iWrite, ref uint iRead, ref ushort numStyle, ref ushort valueWidth)
        {
            //Boolean wtDir = true;
            //uint iWrite = 0, iRead = 0;

            int iformat = strContent.IndexOf("-d");
            if (iformat > 0)
            {
                string strTemp = strContent.Substring(iformat + 2);
                numStyle = (ushort)NumberStyles.Integer;
                valueWidth = byte.Parse(strTemp);
                strContent = strContent.Substring(0, iformat);
            }
            iformat = strContent.IndexOf("-h");
            if (iformat > 0)
            {
                string strTemp = strContent.Substring(iformat + 2);
                numStyle = (ushort)NumberStyles.HexNumber;
                valueWidth = byte.Parse(strTemp);
                strContent = strContent.Substring(0, iformat);
            }
            iformat = strContent.IndexOf("-s");
            if (iformat > 0)
            {
                numStyle = (ushort)NumberStyles.Any;
                strContent = strContent.Substring(0, iformat);
            }

            var str = strContent.Split(new char[] { ' ', '\t', '\r' }, StringSplitOptions.RemoveEmptyEntries);

            if ((str[0] == "sr") && (str.Count() >= 6))
            {
                for (int i = 1; i < 5; i++ )
                {
                    write[iWrite++] = byte.Parse(str[i].ToString().Trim(), System.Globalization.NumberStyles.HexNumber);
                }

                iRead = uint.Parse(str[5].ToString().Trim(), System.Globalization.NumberStyles.HexNumber);
                           
            }
        }

    }
}
