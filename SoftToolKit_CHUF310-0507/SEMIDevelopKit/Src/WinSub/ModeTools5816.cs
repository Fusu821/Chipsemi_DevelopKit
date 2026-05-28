using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.Windows;
using System.Threading;

namespace SEMIDevelopKit.Src.WinSub.Mcap5816
{
    public class TPWritePramAction : TPBurnAction
    {
        public TPWritePramAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = StartAddr, iLeft = count;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    //enter upgrade mode
                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_UPGRADE_MODE);

                    //download ramcode
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("write pram data, addr = 0x{0:X},  lenth = {1:D}", iAddr, count))));
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(iAddr, content, count);

                    //read pram
                    //Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("read pram data, addr = 0x{0:X},  lenth = {1:D}", iAddr, count))));
                    //iAddr = StartAddr; 
                    //iLeft = count;
                    //while (iLeft > 0)
                    //{
                    //    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X}", iAddr))));

                    //    uint iOnce = Math.Min(1024, iLeft);
                    //    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, onceBuffer, iOnce);

                    //    for (int index = 0; index < iOnce; index++)
                    //    {
                    //        if (onceBuffer[index] != content[iAddr - StartAddr + index])
                    //        {
                    //            Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("check pram fail, addr = 0x{0:X}", iAddr + index))));
                    //            return MainViewModel.Intr.ReturnCode;
                    //        }
                    //    }

                    //    iAddr += iOnce;
                    //    iLeft -= iOnce;
                    //    MainViewModel.Intr.ProcessValue = iAddr;
                    //}

                    //remap
                    byte[] byteRemap = new byte[] { 0x02, 0x40, 0x04, 0x12 };
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x40007000, byteRemap, 4);

                    //soft reset mcu
                    byte[] byteReset = new byte[] { 0x03, 0x40, 0x04, 0x12 };
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x40007000, byteReset, 4);

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));
                    Thread.Sleep(50);
                }
                catch(Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }
                
                return MainViewModel.Intr.ReturnCode;
            });
        }
    }

    public class TPReadPramAction : TPBurnAction
    {
        public TPReadPramAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = StartAddr;
                    uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessValue = 0;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X4}", iAddr))));
                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, content, iLeft);

                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        OnActionDone(content, Lengh);
                    }));
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }

                return MainViewModel.Intr.ReturnCode;
            });
        }
    }

//     public class TPWriteConfigAction : TPBurnAction
//     {
//         public TPWriteConfigAction(int typeVal, string typeName, uint start, uint len)
//             : base(typeVal, typeName, start, len)
//         {
//             act = new Func<byte[], uint, uint>((content, count) =>
//             {
//                 try
//                 {
//                     uint iAddr = StartAddr, iLeft = count;
//                     //byte[] onceBuffer = new byte[1024];
//                     Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
//                     MainViewModel.Intr.ProcessMax = count;
// 
//                     var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
//                     Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("write config data,  lenth = {0:D}", count))));
//                     MainViewModel.Intr.ReturnCode = mdBase.BurnConfigBin(content, count);
// 
//                     Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));
//                     Thread.Sleep(50);
//                 }
//                 catch (Exception ex)
//                 {
//                     Application.Current.Dispatcher.Invoke(new Action(() =>
//                     {
//                         MessageBox.Show(ex.Message);
//                     }));
//                 }
// 
//                 return MainViewModel.Intr.ReturnCode;
//             });
//         }
//     }

    public class TPReadConfigAction : TPBurnAction
    {
        public TPReadConfigAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = StartAddr;
                    uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessValue = 0;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from core space" /*+ string.Format("0x{0:X4}", iAddr)*/)));
                    MainViewModel.Intr.ReturnCode = mdBase.GetFirmWareConfig(content, len);

                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        OnActionDone(content, Lengh);
                    }));
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }

                return MainViewModel.Intr.ReturnCode;
            });
        }
    }

    public class TPWriteFlashAction : TPBurnAction
    {
        public TPWriteFlashAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = 0, iLeft = count;
                    uint checkSum = SMCheckTools.CaculateCheckSumEx(content, (ushort)count);
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    MainViewModel.Intr.ReturnCode = SMChipBase.EraseBurnSpace(0, 40 * 1024);

                    while (iLeft > 0)
                    {
                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write flash data to  " + string.Format("0x{0:X}", iAddr))));

                        uint iOnce = Math.Min(1024, iLeft);
                        Array.Copy(content, iAddr, onceBuffer, 0, iOnce);
                        MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace(iAddr, onceBuffer, iOnce, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);

                        iAddr += iOnce;
                        iLeft -= iOnce;
                        MainViewModel.Intr.ProcessValue = iAddr;
                    }

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));

                    if (0 == iLeft)
                    {
                        Thread.Sleep(50);

                        iAddr = 0;
                        iLeft = count;
                        MainViewModel.Intr.ProcessValue = 0;

                        while (iLeft > 0)
                        {
                            Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read flash data from  " + string.Format("0x{0:X}", iAddr))));

                            uint iOnce = Math.Min(1024, iLeft);
                            MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);

                            for (int index = 0; index < iOnce; index++)
                            {
                                if (onceBuffer[index] != content[iAddr + index])
                                {
                                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("check flash fail, addr = 0x{0:X}", iAddr + index))));
                                    return MainViewModel.Intr.ReturnCode;
                                }
                            }

                            iAddr += iOnce;
                            iLeft -= iOnce;
                            MainViewModel.Intr.ProcessValue = iAddr;
                        }
                        SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("check data ok...")));
                        Thread.Sleep(50);
                    }
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }

                return MainViewModel.Intr.ReturnCode;
            });
        }
    }

    public class TPReadFlashAction : TPBurnAction
    {
        public TPReadFlashAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = StartAddr;
                    uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessMax = iLeft;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));

                    while (iLeft > 0)
                    {
                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read flash data from  " + string.Format("0x{0:X}", iAddr))));

                        uint iOnce = Math.Min(1024, iLeft);
                        MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);
                        Array.Copy(onceBuffer, 0, content, iAddr - StartAddr, iOnce);

                        iAddr += iOnce;
                        iLeft -= iOnce;
                        MainViewModel.Intr.ProcessValue = iAddr;
                    }

                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        OnActionDone(content, Lengh);
                    }));
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }

                return MainViewModel.Intr.ReturnCode;
            });
        }
    }

    public class TPEraseFlashAction : TPBurnAction
    {
        public TPEraseFlashAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ReturnCode = SMChipBase.EraseBurnSpace(StartAddr, Lengh);
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("erase flash from 0x{0:X}, len = 0x{1:X}, ok...", StartAddr, Lengh))));
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }

                return MainViewModel.Intr.ReturnCode;
            });
        }
    }
    //public class TPOSCCHAction : TPBurnAction
    //{
    //    public TPOSCCHAction(int typeVal, string typeName, uint start, uint len)
    //        : base(typeVal, typeName, start, len)
    //    {
    //        act = new Func<byte[], uint, uint>((content, count) =>
    //        {
    //            try
    //            {
    //                uint iAddr = 0xa000;
    //                uint iLeft = 256;
    //                MainViewModel.Intr.ProcessMax = iLeft;
    //                //byte[] read_0xa000_buf = new byte[256];
    //                byte[] read_0xa000_buf = Enumerable.Repeat((byte)0xff, 256).ToArray();
    //                Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    
    //                MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(40*1024, read_0xa000_buf, 240);
    //                if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read hidden area data success")));
    //                Array.Copy(read_0xa000_buf, 0, content, 0, 240);
                    
    //                var crc= SMCheckTools.CaculateCheckSumEx(read_0xa000_buf, 20);
    //                var crc1 = read_0xa000_buf[20] << 0 | read_0xa000_buf[21] << 8 | read_0xa000_buf[22] << 16 | read_0xa000_buf[23] << 24;
    //                if (crc == crc1)
    //                {
    //                    read_0xa000_buf[0] = 0xb0;//24m
    //                    read_0xa000_buf[1] = 0x50;//32k
    //                    read_0xa000_buf[2] = (byte)(~(uint)(read_0xa000_buf[0]));
    //                    read_0xa000_buf[3] = (byte)(~(uint)(read_0xa000_buf[1]));
    //                    var crc2 = SMCheckTools.CaculateCheckSumEx(read_0xa000_buf, 20);
    //                    read_0xa000_buf[20] = (byte)(crc2 & 0xff);
    //                    read_0xa000_buf[21] = (byte)((crc2>>8) & 0xff);
    //                    read_0xa000_buf[22] = (byte)((crc2>>16) & 0xff);
    //                    read_0xa000_buf[23] = (byte)((crc2>>24) & 0xff);
    //                    for (int k = 1; k < 10; k++ )
    //                    {
    //                        for (int index = 0; index < 24; index++)
    //                        {
    //                            read_0xa000_buf[k * 24 + index] = read_0xa000_buf[index];
    //                        }

    //                    }
    //                    byte[] read_fw_buf = new byte[40 * 1024];
    //                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(0, read_fw_buf, 40 * 1024);
    //                    if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read main area data success")));

    //                    MainViewModel.Intr.ReturnCode = SMChipBase.EraseBurnSpace(0, 40 * 1024 + 256);
    //                    if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("erase flash success")));

    //                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace(0, read_fw_buf, 40 * 1024, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);
    //                    if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write main area data success")));

    //                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace(40 * 1024, read_0xa000_buf, 256, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);
    //                    if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write hidden area data success")));

    //                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_FW_SUM);
    //                    if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(0x20002400, read_0xa000_buf, 8);
    //                    if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;
    //                    uint fw_crc = (uint)(read_0xa000_buf[0]<<24|read_0xa000_buf[1]<<16|read_0xa000_buf[2]<<8|read_0xa000_buf[4]<<0);
    //                    if (fw_crc == StartAddr)
    //                    {
    //                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("FW CRC PASS")));
    //                    }
    //                    else
    //                    {
    //                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("FW CRC NG")));
    //                    }




    //                    //MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(40 * 1024, read_0xa000_buf, 256);
    //                    //if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    //Array.Copy(read_0xa000_buf, 0, content, 0, 256);

    //                    //Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("------------------------")));

    //                    //MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(0x9f00, read_0xa000_buf, 256);
    //                    //if (MainViewModel.Intr.ReturnCode != 0) return MainViewModel.Intr.ReturnCode;

    //                    //Array.Copy(read_0xa000_buf, 0, content, 256, 256);
    //                    //Application.Current.Dispatcher.Invoke(new Action(() =>
    //                    //{
    //                    //    OnActionDone(content, Lengh);
    //                    //}));
    //                }
                                
    //            }
    //            catch (Exception ex)
    //            {
    //                Application.Current.Dispatcher.Invoke(new Action(() =>
    //                {
    //                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("change hidden area data fail!!!!!!!")));
    //                    MessageBox.Show(ex.Message);
    //                }));
    //            }

    //            return MainViewModel.Intr.ReturnCode;
    //        });
    //    }
    //}

    public class TPReadPID_VID : TPBurnAction
    {
        public TPReadPID_VID(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = 0x20000000 + 0x80;
                    //uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessValue = 0;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X4}", iAddr))));
                    SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);

                    Thread.Sleep(100);

                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_IDENTITY);

                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, content, 256);


                    //Application.Current.Dispatcher.Invoke(new Action(() =>
                    //{
                    //    OnActionDone(content, 204);
                    //}));

                    ushort p = (ushort)((content[3] << 8) + content[2]);
                    ushort v = (ushort)((content[5] << 8) + content[4]);

                    byte cfg_version = (byte)(content[1] );

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("Cfg Version   " + "H: " + string.Format("0x{0:X4}", cfg_version) + ", D: " + string.Format("{0:D}", cfg_version))));
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("PID  " + "H: " + string.Format("0x{0:X4}", p) + ", D: " + string.Format("{0:D}", p))));
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("VID  " + "H: " + string.Format("0x{0:X4}", v) + ", D: " + string.Format("{0:D}", v))));

                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        MessageBox.Show(ex.Message);
                    }));
                }

                return MainViewModel.Intr.ReturnCode;
            });
        }
    }

}
