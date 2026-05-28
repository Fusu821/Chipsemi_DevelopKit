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
        public void RegistReflexTuningModel7449()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7449, "SEMIDevelopKit.Src.WinSub.ModelTuning7449", SEMI.Util.ChipReflex.SEMI_DEVLOP_TUNING);
        }
    }
    public class ModelTuning7449 : TuningViewModel
    {
        public ModelTuning7449()
        {
            tuningLists = new List<TuningNode>()
            {
                new TuningNode(){ ItemName="全览配置", LinkUri="OverView.xaml", ItemNodes = new List<TuningNode>()
                {
                    new TuningNode(){ ItemName="基本信息", LinkUri="BasicSet.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="功能开关", LinkUri="Function.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="扫频参数", LinkUri="FreqScan.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="跳频相关", LinkUri="FreqHopping.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="阈值相关", LinkUri="Threshold.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="精度调整", LinkUri="Precision.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="按键相关", LinkUri="Keys.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="滤波相关", LinkUri="Filter.xaml", ItemNodes = null },
                    new TuningNode(){ ItemName="其他设置", LinkUri="Others.xaml", ItemNodes = null },
                }},
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
                    //openFileDialog.InitialDirectory = Directory.GetCurrentDirectory();
                    if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        string fileName = openFileDialog.FileName;

                        FileInfo fileInfo = new FileInfo(fileName);
                        long len = fileInfo.Length;
                        byte[] content = new byte[len];

                        using (FileStream fs = new FileStream(fileName, FileMode.Open))
                        {
                            fs.Read(content, 0, (int)len);
                            fs.Close();
                        }

                        bool bRet = CheckAppContent(content, len);
                        if (true == bRet)
                        {
                            Array.Copy(content, 0, BufferOS, 0, len);
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
                    ushort crc256 = CalcCheckSum(BufferOS, 254);
                    BufferOS[256 - 2] = (byte)(crc256 >> 0);
                    BufferOS[256 - 1] = (byte)(crc256 >> 8);

                    ushort checkSum = CalcCheckSum(BufferOS, BindFileLen - 2);
                    BufferOS[BindFileLen - 2] = (byte)(checkSum >> 0);
                    BufferOS[BindFileLen - 1] = (byte)(checkSum >> 8);

                    System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
                    saveFileDlg.OverwritePrompt = true;
                    saveFileDlg.Filter = "bin files (*.bin)|*.bin";
                    if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
                    {
                        string fileName = saveFileDlg.FileName;
                        FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                        BinaryWriter bw = new BinaryWriter(fs);
                        bw.Write(BufferOS, 0, (int)BindFileLen);
                        bw.Close();
                    }
                }
                else if ("btn_tp_pc" == ctrlName)
                {
                    long len = 512;
                    
                    //uint iRet = SMChip7449.GetFirmWareConfig(content, (ushort)BindFileLen);
                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_FW_BOOT_LOADER);

                        TuningInfo = "<---------->";
                        //byte[] content = new byte[len];
                        uint iRet = SMChip7449.GetFirmWareConfig(BufferOS, (ushort)len);
                        if (iRet > 0)
                        {
                            TuningInfo = string.Format("Read Cfg From Tp Faild, Err = {0}\r\n", iRet);
                        }
                        else
                        {
                            if (true == CheckAppContent(BufferOS, len))
                            {
                                //Array.Copy(content, 0, BufferOS, 0, len);
                                binFileLen = len;

                                AnyTypeDataManager.RefreshAll();
                                TuningInfo = "Sync Cfg From Tp Success\r\n";
                            }
//                             else if (true == CheckAppContent256(content, 256))
//                             {
//                                 Array.Copy(content, 0, BufferOS, 0, 256);
//                                 binFileLen = 256;
// 
//                                 AnyTypeDataManager.RefreshAll();
//                                 TuningInfo = "Sync Cfg 256 bytes From Tp Success\r\n";
//                             }
                            else
                            {
                                TuningInfo = "Sync Cfg From Tp Error\r\n";
                            }
                        }

                        SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    });
                }
                else if ("btn_pc_tp" == ctrlName)
                {
                    ushort crc256 = CalcCheckSum(BufferOS, 254);
                    BufferOS[256 - 2] = (byte)(crc256 >> 0);
                    BufferOS[256 - 1] = (byte)(crc256 >> 8);

                    ushort checkSum = CalcCheckSum(BufferOS, BindFileLen - 2);
                    BufferOS[BindFileLen - 2] = (byte)(checkSum >> 0);
                    BufferOS[BindFileLen - 1] = (byte)(checkSum >> 8);

                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_FW_BOOT_LOADER);

                        TuningInfo = "<---------->";
                        uint iRet = SMChip7449.BurnConfigBin(BufferOS, (ushort)BindFileLen);
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

                        //SMChip7449.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                        //System.Threading.Thread.Sleep(100);

                        iRet = SMChip7449.ReadCoreSpace(0x20000080, BufferOS, 512);
                        if (iRet > 0)
                        {
                            TuningInfo = string.Format("Read Cfg From Tp Faild, Err = {0}\r\n", iRet);
                        }
                        else
                        {
                            if (true == CheckAppContent(BufferOS, BindFileLen))
                            {
                                AnyTypeDataManager.RefreshAll();
                                TuningInfo = "Sync Cfg From Ram Success\r\n";
                            }
//                             else if (true == CheckAppContent256(BufferOS, 256))
//                             {
//                                 binFileLen = 256;
//                                 AnyTypeDataManager.RefreshAll();
//                                 TuningInfo = "Sync Cfg 256 bytes From Ram Success\r\n";
//                             }
                            else
                            {
                                TuningInfo = "Sync Cfg From Ram Error\r\n";
                            }
                        }
                    });
                }
                else if ("btn_pc_ram" == ctrlName)
                {
                    byte[] checkReturn = new byte[16];

                    ushort crc256 = CalcCheckSum(BufferOS, 254);
                    BufferOS[256 - 2] = (byte)(crc256 >> 0);
                    BufferOS[256 - 1] = (byte)(crc256 >> 8);

                    ushort checkSum = CalcCheckSum(BufferOS, BindFileLen - 2);
                    BufferOS[BindFileLen - 2] = (byte)(checkSum >> 0);
                    BufferOS[BindFileLen - 1] = (byte)(checkSum >> 8);

                    RuningKernel.Instance().Work.AddWorkTemporary(() =>
                    {
                        TuningInfo = "<---------->";

                        //SMChip7449.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                        //System.Threading.Thread.Sleep(100);

                        uint iRet = SMChip7449.SetConfigInFctMode(BufferOS, (ushort)BindFileLen);
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
            ushort uCheckSum = 0;
            for (int index = 0; index < binFileLen; index += 2)
                uCheckSum += (ushort)((content[index + 1] << 8) + content[index]);

            if (uCheckSum != 0) return false;

            //uCheckSum = (ushort)((content[binFileLen - 1] << 8) + content[binFileLen - 2]);
            //if (uCheckSum == 0) return false;

            if (0 == content[0] && 0 == content[1]) return false;

            return true;
        }

//         private bool CheckAppContent256(byte[] content, long binFileLen = 256)
//         {
//             ushort uCheckSum = 0;
//             for (int index = 0; index < binFileLen; index += 2)
//                 uCheckSum += (ushort)((content[index + 1] << 8) + content[index]);
// 
//             if (uCheckSum != 0) return false;
// 
//             return true;
//         }
        
    }
}
