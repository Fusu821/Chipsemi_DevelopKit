using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.Windows;
using System.Threading;

namespace SEMIDevelopKit.Src.WinSub.Mcap8006
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
                    StartAddr = 0x20000000;
                    uint iAddr = StartAddr, iLeft = count;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    //enter upgrade mode
                    MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_ENTER_UPGRADE_MODE);

                    //download ramcode
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("write pram data, addr = 0x{0:X},  lenth = {1:D}", iAddr, count))));
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(iAddr, content, count);

                    //soft reset mcu
                    byte[] byteReset = new byte[] { 0xe4, 0xff, 0xff, 0x00 };
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

                    //MainViewModel.Intr.ReturnCode = SMChipBase.WriteRegister(0x40005008, 0x00000002);

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X4}", iAddr))));
                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, content, iLeft);

                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        OnActionDone(content, Lengh);
                    }));

                    //MainViewModel.Intr.ReturnCode = SMChipBase.WriteRegister(0x40005008, 0x00000022);
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
                    uint iAddr = StartAddr;
                    uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessValue = 0;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X4}", iAddr))));
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
