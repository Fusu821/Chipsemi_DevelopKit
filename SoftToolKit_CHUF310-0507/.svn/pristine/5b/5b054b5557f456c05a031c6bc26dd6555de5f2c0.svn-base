using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using SMInvokeBridge;
using System.Windows.Forms;

namespace SEMIDevelopKit.Src.WinSub
{
    public class Model3536 : ModelBase
    {
        private byte[] cfgContent = new byte[204];

        public Model3536()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, eChipTypeList.SM_IC_3536, this);

            DisplayDataLen = 122;
        }

        public override bool InitializeOK()
        {
            //SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
            MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(0x9E00, cfgContent, 204); //SMChip3536.GetFirmWareConfig(cfgContent, 204);
            MainViewModel.Intr.WorkClk = (ushort)((cfgContent[2 * 2 + 1] << 8) + cfgContent[2 * 2 + 0]);

            BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            BitValue misc = new BitValue((cfgContent[57 * 2 + 1] << 8) + cfgContent[57 * 2 + 0]);
            BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
            BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

            int vaChannel = tp_chain.MaskValue(0x3f0) >> 4;
            int realChannel = tp_chain.MaskValue(0xfc00) >> 10;
            Refs = realChannel - vaChannel;

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
            //DisplayDataLen = (ushort)((Rows + addRow) * Cols * 2);
            //DisplayDataLen = 94;

            //RawDataMatrix = new DataMatrix(Rows, Cols, Refs);

            //if (null == RawDataMatrix || (Rows + (Refs > 0 ? 1 : 0)) != RawDataMatrix.RowNumber)
            //{
            //    RawDataMatrix = new DataMatrix(Rows, Cols, Refs);
            //}

            //sensor map
            Ic_2_Sensor_Map = new ushort[48];
            Sensor_2_Ic_Map = new ushort[48];
            for (int index = 0; index < 48; index++)
            {
                Ic_2_Sensor_Map[index] = (ushort)(cfgContent[22 + index]);
                if (Ic_2_Sensor_Map[index] > 0 && Ic_2_Sensor_Map[index] < 48)
                {
                    Sensor_2_Ic_Map[Ic_2_Sensor_Map[index] - 1] = (ushort)index;
                }
            }

            ActionOnChannelNumChange();

            return 0 == MainViewModel.Intr.ReturnCode;
        }

        public override uint BurnConfigBin(byte[] buffer, uint len)
        {
            return SMChip3536.BurnConfigBin(buffer, (ushort)len);
        }
        public override uint GetFirmWareConfig(byte[] buffer, uint len)
        {
            return SMChip3536.GetFirmWareConfig(buffer, (ushort)len);
        }
        public override uint GetScanFreq(ushort workClk, short[] buffer, byte scanCnt = 1)
        {
            return SMChip3536.GetFSDFastData(workClk, 1, buffer, (48 + 3) * 2, scanCnt);
        }
    }
}
