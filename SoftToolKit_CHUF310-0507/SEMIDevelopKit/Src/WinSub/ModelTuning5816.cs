using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using SEMI.Util;
using System.IO;

namespace SEMIDevelopKit.Src.WinSub
{
    public partial class SMDevelopChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexTuningModel5816()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5816, "SEMIDevelopKit.Src.WinSub.ModelTuning5816", SEMI.Util.ChipReflex.SEMI_DEVLOP_TUNING);
        }
    }
    public class ModelTuning5816 : TuningViewModel
    {
        private byte[] bootContent = new byte[40 * 1024];
        private byte[] onceBuffer = new byte[1024];

        public ModelTuning5816()
        {
            tuningLists = new List<TuningNode>()
            {
                new TuningNode(){ ItemName="基本设置", LinkUri="BasicSetting.xaml", ItemNodes = new List<TuningNode>()
                {
                    new TuningNode(){ ItemName="触摸效果", LinkUri="Touch.xaml", ItemNodes = null },
                }},
                new TuningNode(){ ItemName="高级设置", LinkUri="ExtendSet.xaml", ItemNodes = new List<TuningNode>()
                {
                    new TuningNode(){ ItemName="滤波", LinkUri="Filter.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="映射关系", LinkUri="Mapping.xaml", ItemNodes = null },
                }},

//                 new TuningNode(){ ItemName="全览配置", LinkUri="OverView.xaml", ItemNodes = new List<TuningNode>()
//                 {
//                     new TuningNode(){ ItemName="基本信息", LinkUri="BasicSet.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="功能开关", LinkUri="Function.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="扫频参数", LinkUri="FreqScan.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="跳频相关", LinkUri="FreqHopping.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="阈值相关", LinkUri="Threshold.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="精度调整", LinkUri="Precision.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="按键相关", LinkUri="Keys.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="滤波相关", LinkUri="Filter.xaml", ItemNodes = null },
//                     new TuningNode(){ ItemName="其他设置", LinkUri="Others.xaml", ItemNodes = null },
//                 }},
               
            };
        }
        public override void OnInitialized(byte[] osBin)
        {

        }
        public override void OnButtonClicked(string ctrlName, byte[] osBin)
        {
            try
            {
                if ("btn_cfg_pc" == ctrlName)
                {
                    System.Windows.Forms.OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();
                    openFileDialog.Filter = "Bin File(*.bin)|*.bin";
                    openFileDialog.RestoreDirectory = true;
                    openFileDialog.FilterIndex = 1;
                   // openFileDialog.InitialDirectory = Directory.GetCurrentDirectory();
                    if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        string fileName = openFileDialog.FileName;

                        FileInfo fileInfo = new FileInfo(fileName);
                        long len = fileInfo.Length;

                        using (FileStream fs = new FileStream(fileName, FileMode.Open))
                        {
                            fs.Read(bootContent, 0, (int)len);
                            fs.Close();
                        }

                        bool bRet = CheckAppContent(bootContent, len);
                        //if (true == bRet)
                        {
                            ushort cfgAddr = (ushort)((bootContent[0x39] << 8) + bootContent[0x38]);
                            Array.Copy(bootContent, cfgAddr, BufferOS, 0, 256);
                            binFileLen = len;
                            new System.Threading.Thread(() =>
                            {
                                AnyTypeDataManager.RefreshAll();
                                TuningInfo = "Sync Cfg From File Success\r\n";
                            }).Start();
                        }
                    }
                }
                else if ("btn_pc_cfg" == ctrlName)
                {
                    uint checksumCalc = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(bootContent, (uint)binFileLen - 4);
                    uint checkSumMemr = (uint)((bootContent[binFileLen - 1] << 24) + (bootContent[binFileLen - 2] << 16) + (bootContent[binFileLen - 3] << 8) + (bootContent[binFileLen - 4] << 0));
                    if (checksumCalc != checkSumMemr || 0 == checksumCalc)
                    {
                        TuningInfo = "error, invalid boot content!!!\r\n";
                        return;
                    }

                    ushort checkSum = CalcCheckSum(BufferOS, 256 - 2);
                    BufferOS[256 - 2] = (byte)(checkSum >> 0);
                    BufferOS[256 - 1] = (byte)(checkSum >> 8);
                    ushort cfgAddr = (ushort)((bootContent[0x39] << 8) + bootContent[0x38]);
                    Array.Copy(BufferOS, 0, bootContent, cfgAddr, 256);
                    binFileLen = ((bootContent[0x35] << 8) + bootContent[0x34]) % (40 * 1024);
                    uint crc = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(bootContent, (uint)binFileLen - 4);
                    bootContent[binFileLen - 1] = (byte)(crc >> 24);
                    bootContent[binFileLen - 2] = (byte)(crc >> 16);
                    bootContent[binFileLen - 3] = (byte)(crc >> 8);
                    bootContent[binFileLen - 4] = (byte)(crc >> 0);

                    System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
                    saveFileDlg.OverwritePrompt = true;
                    saveFileDlg.Filter = "bin files (*.bin)|*.bin";
                    if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
                    {
                        string fileName = saveFileDlg.FileName;
                        FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                        BinaryWriter bw = new BinaryWriter(fs);
                        bw.Write(bootContent, 0, (int)BindFileLen);
                        bw.Close();
                    }
                }
                else if ("btn_tp_pc" == ctrlName)
                {
                    //long len = BindFileLen;
                    //byte[] content = new byte[256];
                    //uint iRet = SMChip5816.GetFirmWareConfig(content, 256);
                    uint iRet = 0;
                    uint iAddr = 0, iLeft = (uint)bootContent.Length;
                    MainViewModel.Intr.ProcessMax = iLeft;
                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        TuningInfo = "<---------->";
                        while (iLeft > 0)
                        {
                            uint iOnce = Math.Min(1024, iLeft);
                            iRet = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);
                            Array.Copy(onceBuffer, 0, bootContent, iAddr, iOnce);
                            if (iRet > 0) break;

                            iAddr += iOnce;
                            iLeft -= iOnce;
                            MainViewModel.Intr.ProcessValue = iAddr;
                        }

                        if (iRet > 0)
                        {
                            TuningInfo = string.Format("Read Cfg From Tp Faild, Err = {0}\r\n", iRet);
                        }
                        else
                        {
                            binFileLen = ((bootContent[0x35] << 8) + bootContent[0x34]) % (40 * 1024);
                            bool bRet = CheckAppContent(bootContent, binFileLen);
                            if (true == bRet)
                            {
                                ushort cfgAddr = (ushort)((bootContent[0x39] << 8) + bootContent[0x38]);
                                Array.Copy(bootContent, cfgAddr, BufferOS, 0, 256);
                                //binFileLen = len;
                                AnyTypeDataManager.RefreshAll();
                                TuningInfo = "Sync Cfg From Tp Success\r\n";
                            }
                        }

                        SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    });
                }
                else if ("btn_pc_tp" == ctrlName)
                {
                    uint iRet = 0;
                    ushort checkSum = CalcCheckSum(BufferOS, 256 - 2);
                    BufferOS[256 - 2] = (byte)(checkSum >> 0);
                    BufferOS[256 - 1] = (byte)(checkSum >> 8);
                    uint iAddr = 0, iLeft = (uint)bootContent.Length;
                    
                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        TuningInfo = "<---------->";

                        //get boot content from tp
                        MainViewModel.Intr.ProcessMax = iLeft;
                        while (iLeft > 0)
                        {
                            uint iOnce = Math.Min(1024, iLeft);
                            iRet = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);
                            Array.Copy(onceBuffer, 0, bootContent, iAddr, iOnce);
                            if (iRet > 0) break;

                            iAddr += iOnce;
                            iLeft -= iOnce;
                            MainViewModel.Intr.ProcessValue = iAddr;
                        }

                        //merge
                        binFileLen = ((bootContent[0x35] << 8) + bootContent[0x34]) % (40 * 1024);
                        ushort cfgAddr = (ushort)((bootContent[0x39] << 8) + bootContent[0x38]);
                        Array.Copy(BufferOS, 0, bootContent, cfgAddr, 256);
                        uint crc = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(bootContent, (uint)binFileLen - 4);
                        bootContent[binFileLen - 1] = (byte)(crc >> 24);
                        bootContent[binFileLen - 2] = (byte)(crc >> 16);
                        bootContent[binFileLen - 3] = (byte)(crc >> 8);
                        bootContent[binFileLen - 4] = (byte)(crc >> 0);

                        //write boot to tp
                        iRet = SMChip5816.EraseBurnSpace(0, 40 * 1024);
                        if (0 == iRet)
                        {
                            //iRet = SMChip5816.WriteBurnSpace(0, bootContent, (uint)BindFileLen, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);
                            iAddr = 0;
                            iLeft = (uint)BindFileLen;
                            MainViewModel.Intr.ProcessMax = iLeft;
                            while (iLeft > 0)
                            {
                                uint iOnce = Math.Min(1024, iLeft);
                                Array.Copy(bootContent, iAddr, onceBuffer, 0, iOnce);
                                iRet = SMChipBase.WriteBurnSpace(iAddr, onceBuffer, iOnce, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);
                                if (iRet > 0) break;

                                iAddr += iOnce;
                                iLeft -= iOnce;
                                MainViewModel.Intr.ProcessValue = iAddr;
                            }
                        }

                        if (iRet > 0)
                        {
                            TuningInfo = string.Format("Download Cfg Faild, Err = {0}\r\n", iRet);
                        }
                        else
                        {
                            TuningInfo = "Download Cfg Success\r\n";
                        }

                        SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    });
                }
                else if ("btn_ram_pc" == ctrlName)
                {
                    uint iRet = 0;
                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        TuningInfo = "<---------->";

                        //SMChip5816.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                        //System.Threading.Thread.Sleep(100);

                        iRet = SMChip5816.ReadCoreSpace(0x20000080, BufferOS, 256);
                        if (iRet > 0) return;

                        ushort checkSum = SMInvokeBridge.SMCheckTools.CaculateCheckSumU16(BufferOS, 256);
                        if (0 != checkSum)
                        {
                            TuningInfo = "Sync Cfg From CheckSum Error\r\n";
                            return;
                        }

                        AnyTypeDataManager.RefreshAll();
                        TuningInfo = "Sync Cfg From Ram Success\r\n";
                    });
                }
                else if ("btn_pc_ram" == ctrlName)
                {
                    byte[] checkReturn = new byte[16];
                    ushort checkSum = CalcCheckSum(BufferOS, 256 - 2);
                    BufferOS[256 - 2] = (byte)(checkSum >> 0);
                    BufferOS[256 - 1] = (byte)(checkSum >> 8);

                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        TuningInfo = "<---------->";

                        //SMChip5816.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                        //System.Threading.Thread.Sleep(100);

                        uint iRet = SMChip5816.SetConfigInFctMode(BufferOS, (ushort)256);
                        if (iRet > 0)
                        {
                            TuningInfo = string.Format("Update Cfg To Ram Faild, Err = {0}\r\n", iRet);
                        }
                        else
                        {

                            TuningInfo = "Update Cfg to Ram Success\r\n";
                        }
                    });
                }
            }
            catch (Exception ex)
            {
                TuningInfo = ex.ToString();
            }
        }
//         public override bool CheckAppFile(string fileName)
//         {
//             FileInfo fileInfo = new FileInfo(fileName);
//             long binFileLen = fileInfo.Length;
// 
//             byte[] tempBuffer = new byte[binFileLen];
//             using (FileStream fs = new FileStream(fileName, FileMode.Open))
//             {
//                 fs.Read(tempBuffer, 0, (int)binFileLen);
//                 fs.Close();
//             }
// 
//             return CheckAppContent(tempBuffer, binFileLen);
//         }
        public override void OnTuningValueChanged(string name, int addr, byte[] osBin)
        {

        }
        private bool CheckAppContent(byte[] content, long binFileLen)
        {
            //ushort uCheckSum = 0;
            //for (int index = 0; index < binFileLen; index += 2)
            //    uCheckSum += (ushort)((content[index + 1] << 8) + content[index]);

            //if (content[0] != 0x72) return false;
            //if (content[1] != 0x54) return false;
            //if (uCheckSum != 0) return false;

            if (0 == content[0] && 0 == content[1]) return false;

            uint crc = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(content, (uint)binFileLen - 4);
            uint checkSum = (uint)content[binFileLen - 1];
            checkSum = (checkSum << 8) + (uint)content[binFileLen - 2];
            checkSum = (checkSum << 8) + (uint)content[binFileLen - 3];
            checkSum = (checkSum << 8) + (uint)content[binFileLen - 4];

            return crc == checkSum;
        }
        
    }
}
