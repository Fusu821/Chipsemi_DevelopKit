using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using SMInvokeBridge;
using System.Windows.Forms;

namespace SEMIDevelopKit.Src.WinSub
{
    public class Model3535 : ModelBase
    {
        private byte[] cfgContent = new byte[204];

        public Model3535()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, eChipTypeList.SM_IC_3535, this);
        }

        public override bool InitializeOK()
        {
            uint lastOtpAddr = SMChip3535.FindLastCfgAddress();
            if (lastOtpAddr <= 0x5000 || lastOtpAddr >= 0x7f80)
                return false;

            MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(0xD6E0, cfgContent, 204); //SMChip3535.GetFirmWareConfig(lastOtpAddr, cfgContent, 204);
            MainViewModel.Intr.WorkClk = (ushort)((cfgContent[2 * 2 + 1] << 8) + cfgContent[2 * 2 + 0]);

            BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            int vaChannel = tp_chain.MaskValue(0x3f0) >> 4;
            int realChannel = tp_chain.MaskValue(0xfc00) >> 10;
            Refs = realChannel - vaChannel;
            if (tp_chain.Bit(3))
            {
                Rows = 4;
                Cols = (tp_chain.MaskValue(0x03f0) >> 4) >> 2;
            }
            else
            {
                Rows = 2;
                Cols = (tp_chain.MaskValue(0x03f0) >> 4) >> 1;
            }

            int addRow = Refs > 0 ? 1 : 0;
            DisplayDataLen = (ushort)((Rows + addRow) * Cols * 2);

            //RawDataMatrix = new DataMatrix(Rows, Cols, Refs);
            ActionOnChannelNumChange();

            BitValue misc = new BitValue((cfgContent[57 * 2 + 1] << 8) + cfgContent[57 * 2 + 0]);
            BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
            BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

            //swap xy
            if (misc.Bit(3))
            {
                xPixel = lcdy.UShortValue;
                yPixel = lcdx.UShortValue;
            }
            else
            {
                xPixel = lcdx.UShortValue;
                yPixel = lcdy.UShortValue;
            }

            //sensor map
            Ic_2_Sensor_Map = new ushort[48];
            Sensor_2_Ic_Map = new ushort[48];
            byte[] channeIndex = new byte[]{0, 8, 16, 26};
            for (int iGroup = 0; iGroup < 4; iGroup++)
            {
                byte whichGroup = 0;
                int iGroupStart = iGroup + 14;
                uint iGroupInfo = (uint)((cfgContent[iGroupStart * 4 + 3] << 24) | (cfgContent[iGroupStart * 4 + 2] << 16) | (cfgContent[iGroupStart * 4 + 1] << 8) | (cfgContent[iGroupStart * 4 + 0] << 0));
                for (int iter = 0; iter < 10; iter++)
                {
                    if (iter < 8)
                    {
                        whichGroup = (byte)(iGroupInfo & 0x03);
                        iGroupInfo = iGroupInfo >> 2;
                    }
                    else
                    {
                        whichGroup = (byte)((iGroupInfo & 0x01) > 0 ? 3 : 2);
                    }

                    if (cfgContent[30 + iGroup * 10 + iter] > 0)
                    {
                        byte channelStart = channeIndex[whichGroup];
                        Ic_2_Sensor_Map[channelStart + iter] = cfgContent[30 + iGroup * 10 + iter];
                        Sensor_2_Ic_Map[cfgContent[30 + iGroup * 10 + iter] - 1] = (ushort)(channelStart + iter);
                    }
                }
            }

            return 0 == MainViewModel.Intr.ReturnCode;
        }
        public override uint BurnConfigBin(byte[] buffer, uint len)
        {
            uint retCode = 0;
            uint lastAddr = SMChip3535.FindLastCfgAddress();
            if (lastAddr > 0x5000)
            {
                byte[] lastConfg = new byte[256];
                retCode = SMChip3535.GetFirmWareConfig(lastAddr, lastConfg, 204);
                if (Enumerable.SequenceEqual(buffer, lastConfg))
                    return retCode;

                retCode = SMChip3535.BurnConfigBin(lastAddr - 256, buffer, (ushort)len);
            }
            else
            {
                retCode = 1;
            }

            return retCode;
        }
        public override uint GetFirmWareConfig(byte[] buffer, uint len)
        {
            uint lastAddr = SMChip3535.FindLastCfgAddress();
            return SMChip3535.GetFirmWareConfig(lastAddr, buffer, (ushort)len);
        }
        public override uint GetScanFreq(ushort workClk, short[] buffer, byte scanCnt = 1)
        {
            return SMChip3535.GetFSDFastData(workClk, 1, buffer, 0x50, scanCnt);
        }
    }
}
