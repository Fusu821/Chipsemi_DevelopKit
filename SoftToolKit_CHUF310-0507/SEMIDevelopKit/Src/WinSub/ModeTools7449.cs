using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.Windows;
using System.Threading;

namespace SEMIDevelopKit.Src.WinSub.Mcap7449
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
                    byte[] byteRemap = new byte[] { 0x00, 0x01, 0x00, 0x00 };
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x40007008, byteRemap, 4);

                    //soft reset mcu
                    byte[] byteReset = new byte[] { 0x5c, 0x00, 0x00, 0xc0 };
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x40007004, byteReset, 4);

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

    public class TPWriteConfigAction : TPBurnAction
    {
        public TPWriteConfigAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_FW_BOOT_LOADER);
                    Thread.Sleep(20);

                    uint iAddr = StartAddr, iLeft = count;
                    //byte[] onceBuffer = new byte[1024];
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("write config data,  lenth = {0:D}", count))));
                    MainViewModel.Intr.ReturnCode = mdBase.BurnConfigBin(content, count);

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));

                    SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("check data ok...")));
                    Thread.Sleep(50);
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

    public class TPReadConfigAction : TPBurnAction
    {
        public TPReadConfigAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_FW_BOOT_LOADER);
                    Thread.Sleep(20);

                    uint iAddr = StartAddr;
                    uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessValue = 0;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X4}", iAddr))));
                    MainViewModel.Intr.ReturnCode = mdBase.GetFirmWareConfig(content, len);

                    SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    Thread.Sleep(50);
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
                    SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_FW_BOOT_LOADER);
                    Thread.Sleep(20);

                    uint iAddr = (uint)(MainViewModel.Intr.Agent == 0x08 ? 0x2000 : 0);
                    uint iLeft = count;
                    uint copyAddr = 0;
                    uint checkSum = SMCheckTools.CaculateCheckSumEx(content, (ushort)count);
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;
                    while (iLeft > 0)
                    {
                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write flash data to  " + string.Format("0x{0:X}", iAddr))));

                        uint iOnce = Math.Min(1024, iLeft);
                        Array.Copy(content, copyAddr, onceBuffer, 0, iOnce);
                        MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace(iAddr, onceBuffer, iOnce, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);

                        iAddr += iOnce;
                        iLeft -= iOnce;
                        copyAddr += iOnce;
                        MainViewModel.Intr.ProcessValue = iAddr;
                    }

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));

                    if (0 == iLeft)
                    {
                        Thread.Sleep(50);

                        iAddr = (uint)(MainViewModel.Intr.Agent == 0x08 ? 0x2000 : 0);
                        iLeft = count;
                        copyAddr = 0;
                        MainViewModel.Intr.ProcessValue = 0;

                        while (iLeft > 0)
                        {
                            Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read flash data from  " + string.Format("0x{0:X}", iAddr))));

                            uint iOnce = Math.Min(1024, iLeft);
                            MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);

                            for (int index = 0; index < iOnce; index++)
                            {
                                if (onceBuffer[index] != content[copyAddr + index])
                                {
                                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("check flash fail, addr = 0x{0:X}", iAddr + index))));
                                    return MainViewModel.Intr.ReturnCode;
                                }
                            }

                            iAddr += iOnce;
                            iLeft -= iOnce;
                            copyAddr += iOnce;
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
                    SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_FW_BOOT_LOADER);
                    Thread.Sleep(20);

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

                    SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    Thread.Sleep(50);

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

                    SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);
                    Thread.Sleep(50);

                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_IDENTITY);

                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, content, 256);

                    //Application.Current.Dispatcher.Invoke(new Action(() =>
                    //{
                    //    OnActionDone(content, 204);
                    //}));

                    ushort p = (ushort)((content[3] << 8) + content[2]);
                    ushort v = (ushort)((content[5] << 8) + content[4]);

                    byte cfg_version = (byte)(content[1]);

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
