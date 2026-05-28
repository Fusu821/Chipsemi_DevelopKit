using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.Windows;
using System.Threading;

namespace SEMIDevelopKit.Src.WinSub.Scap3535
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
                    //byte[] onceBuffer = new byte[1024];
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                byte[] regHead1 = new byte[] { 0x05 };
                MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x602, regHead1, 1);
                byte[] regHead2 = new byte[] { 0x00 };
                MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x643, regHead2, 1);

                Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("write pram data, addr = 0x{0:X},  lenth = {1:D}", iAddr, count))));
                MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(iAddr, content, count);

                byte[] regHead3 = new byte[] { MainViewModel.Intr.SlaveAddr };
                MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x001, regHead3, 1);
                byte[] regHead4 = new byte[] { 0x88 };
                MainViewModel.Intr.ReturnCode = SMChipBase.WriteCoreSpace(0x602, regHead4, 1);

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));
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
                MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, content, len);

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

    public class TPWriteOtpAction : TPBurnAction
    {
        public TPWriteOtpAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = 0, iLeft = count;
                    //byte[] onceBuffer = new byte[1024];
                    uint checkSum = SMCheckTools.CaculateCheckSumEx(content, (ushort)count);
                    //checkSum = 0x59eff630;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;
                    while (iLeft > 0)
                    {
                        MainViewModel.Intr.ProcessValue = iAddr;
                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write flash data to  " + string.Format("0x{0:X}", iAddr))));

                    uint iOnce = Math.Min(1024, iLeft);
                    Array.Copy(content, iAddr, onceBuffer, 0, iOnce);
                    MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace(iAddr, onceBuffer, iOnce, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);

                    iAddr += iOnce;
                    iLeft -= iOnce;

                    if (MainViewModel.Intr.ReturnCode > 0)
                        break;
                }

                onceBuffer[0] = (byte)(checkSum >> 0);
                onceBuffer[1] = (byte)(checkSum >> 8);
                onceBuffer[2] = (byte)(checkSum >> 16);
                onceBuffer[3] = (byte)(checkSum >> 24);
                MainViewModel.Intr.ReturnCode = SMChipBase.WriteBurnSpace(iAddr, onceBuffer, 4, EnIoComplex.SM_OTP_W_CHK | EnIoComplex.SM_TLK_DATACHK_EX1);
                Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));

                Thread.Sleep(50);

                iAddr = 0;
                iLeft = count;
                MainViewModel.Intr.ProcessValue = 0;

                while (iLeft > 0)
                {
                    MainViewModel.Intr.ProcessValue = iAddr;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read otp data from  " + string.Format("0x{0:X}", iAddr))));

                    uint iOnce = Math.Min(1024, iLeft);
                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);

                    for (int index = 0; index < iOnce; index++)
                    {
                        if (onceBuffer[index] != content[iAddr + index])
                        {
                            Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("check otp fail, addr = 0x{0:X}", iAddr + index))));
                            return MainViewModel.Intr.ReturnCode;
                        }
                    }

                        iAddr += iOnce;
                        iLeft -= iOnce;
                    }
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

    public class TPReadOtpAction : TPBurnAction
    {
        public TPReadOtpAction(int typeVal, string typeName, uint start, uint len)
            : base(typeVal, typeName, start, len)
        {
            act = new Func<byte[], uint, uint>((content, count) =>
            {
                try
                {
                    uint iAddr = StartAddr;
                    uint iLeft = Lengh;
                    //byte[] onceBuffer = new byte[1024];
                    MainViewModel.Intr.ProcessValue = 0;
                    MainViewModel.Intr.ProcessMax = len;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));

                    while (iLeft > 0)
                    {
                        MainViewModel.Intr.ProcessValue = iAddr;
                        Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read otp data from  " + string.Format("0x{0:X}", iAddr))));

                        uint iOnce = Math.Min(1024, iLeft);
                        MainViewModel.Intr.ReturnCode = SMChipBase.ReadBurnSpace(iAddr, onceBuffer, iOnce);
                        Array.Copy(onceBuffer, 0, content, iAddr - StartAddr, iOnce);

                        iAddr += iOnce;
                        iLeft -= iOnce;
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
                    byte[] onceBuffer = new byte[1024];
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    var mdBase = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, MainViewModel.Intr.SelectedIC) as ModelBase;
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(string.Format("write config data,  lenth = {0:D}", count))));
                    MainViewModel.Intr.ReturnCode = mdBase.BurnConfigBin(content, count);

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("write finished...")));
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
        protected override void RefreshArgs()
        {
            RuningKernel.Instance().Pause(true);
            StartAddr = SMChip3535.FindLastCfgAddress();
            RuningKernel.Instance().Pause(false);
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
                    uint iAddr = 0xD6E0;
                    //uint iLeft = Lengh;
                    MainViewModel.Intr.ProcessValue = 0;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Clear()));
                    MainViewModel.Intr.ProcessMax = count;

                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add("read pram data from  " + string.Format("0x{0:X4}", iAddr))));
                    //SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                    //Thread.Sleep(1000);
                    MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(iAddr, content, 204);


                    //Application.Current.Dispatcher.Invoke(new Action(() =>
                    //{
                    //    OnActionDone(content, 204);
                    //}));

                    ushort cfg0 = (ushort)(content[0] & 0xff | (content[1] & 0xff) << 8);
                    ushort cfg1 = (ushort)(content[2] & 0xff | (content[3] & 0xff) << 8);
                    byte cfg_version = (byte)(cfg1>>10);


                    ushort p = (ushort)((cfg0 & 0x1ff));
                    ushort v = (ushort)((cfg0 >> 9));
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
