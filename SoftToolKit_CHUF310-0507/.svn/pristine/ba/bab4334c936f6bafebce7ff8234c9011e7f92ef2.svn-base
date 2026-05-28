using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using SMInvokeBridge;
using System.Windows.Forms;
using SEMIDevelopKit.Src.Util;
using System.IO;
using MahApps.Metro.Controls.Dialogs;

namespace SEMIDevelopKit.Src.WinSub
{
    public class Model5562 : ModelBase
    {
        private static byte[] cfgContent = new byte[2048];

        public Model5562()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, eChipTypeList.SM_IC_5562, this);
        }

        public override void OnDisplayTypeChanged(ushort type)
        {
            SimulationPosition = 0;
            ReferenceData = dtType.MODE_RAWDATA == type ? 6000 : 100;

            //if (null == RawDataMatrix || (Rows + 1) != RawDataMatrix.RowNumber || (Cols + 1) != RawDataMatrix.ColNumber)
            //{
            //    RawDataMatrix = new DataMatrix(Rows, Cols, Cols, Rows);
            //}
            StcType = 0;

            ActionOnChannelNumChange();

            RuningKernel.Instance().Work.AddWorkTemporary(new Action(SwitchMode));
        }

        public override TouchReportData GenTouchReport(byte[] touchPoint)
        {
            ushort checksum = 0;
            ushort crc = 0;
            uint len = 0;

            if (touchPoint[0] == 0xf8)
            {
                checksum = (ushort)(touchPoint[(TouchMaxNum * 6 + 3)] << 8 | touchPoint[(TouchMaxNum * 6 + 2)]);

                len = (uint)((TouchMaxNum * 6) + 2);

                crc = SMCheckTools.CaculateCheckSumU816(touchPoint, len);
            
            }
            else if ((touchPoint[0] == 0xf0 )|| (touchPoint[0] == 0xff))
            {
                checksum = (ushort)(touchPoint[(TouchMaxNum * 5 + 3)] << 8 | touchPoint[(TouchMaxNum * 5 + 2)]);

                len = (uint)((TouchMaxNum * 5) + 2);

                crc = SMCheckTools.CaculateCheckSumU816(touchPoint, len);
            }

            crc = (ushort)((~crc) + 1) ;
            if (crc == checksum)
            {
                return new MCap550TouchReportData(touchPoint);
            }

            return null;          
        }

        public override bool InitializeOK()
        {
//             Rows = 40;
//             Cols = 32;

//             Rows = 31;
//             Cols = 17;
// 
            //Rows = 22;
            //Cols = 12;

            System.Threading.Thread.Sleep(100);
            MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);  //
            System.Threading.Thread.Sleep(60);
            //byte[] cfgContent = new byte[1000];
            MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(0x20000000 + 0x80, cfgContent, 2048);  //
            if (0 != MainViewModel.Intr.ReturnCode) return false;

            //if (cfgContent[0] == 0x72 && cfgContent[1] == 0x54)
            {
                uint uCheckSum = SMCheckTools.CaculateCheckSumU32(cfgContent, 2048);

                if ((cfgContent[0x33] & 0x01) > 0)
                {
                    xPixel = (cfgContent[0x09] << 8) + cfgContent[0x08];
                    yPixel = (cfgContent[0x07] << 8) + cfgContent[0x06];
                }
                else
                {
                    xPixel = (cfgContent[0x07] << 8) + cfgContent[0x06];
                    yPixel = (cfgContent[0x09] << 8) + cfgContent[0x08];
                }

                //if (0 == uCheckSum) //256 -> 512
                //if (0x00 == (cfgContent[0] & 0xf0))
                {
                    Rows = cfgContent[0x1a];
                    Cols = cfgContent[0x19];
                }

                TouchMaxNum = cfgContent[0x18];
            }

            //MainViewModel.Intr.WorkClk = (ushort)((cfgContent[2 * 2 + 1] << 8) + cfgContent[2 * 2 + 0]);

            DisplayDataLen = (ushort)(((Rows * Cols + Rows + Cols) * 2 + 6 + 3) & 0xfffc);

            //if (null == RawDataMatrix || (Rows + 1) != RawDataMatrix.RowNumber || (Cols + 1) != RawDataMatrix.ColNumber)
            //{
            //    RawDataMatrix = new DataMatrix(Rows, Cols, Cols, Rows);
            //}

            ActionOnChannelNumChange();

            MainViewModel.Intr.ReturnCode = 0;
            //DisplayDataLen = 1152;

            //RawDataMatrix = new DataMatrix(Rows, Cols, Refs);

            //System.Threading.Thread.Sleep(50);

            //RawDataMatrix = new DataMatrix(Rows, Cols, 0);
//             byte[] header = new byte[0x32];
//             MainViewModel.Intr.ReturnCode = SMChip5472.ReadBurnSpace(0x20000000, header, 0x32);
// 
//             rawdataAddr = 0x20000000 + ((uint)(header[0x21] << 16) + header[0x20]);
//             differAddr = 0x20000000 + ((uint)(header[0x23] << 16) + header[0x22]);
//             baseAddr = 0x20000000 + ((uint)(header[0x25] << 16) + header[0x24]);

            //byte[] cfgContent = new byte[204];
            //MainViewModel.Intr.ReturnCode = SMChip3536.GetFirmWareConfig(cfgContent, 204);
            //MainViewModel.Intr.WorkClk = (ushort)((cfgContent[2 * 2 + 1] << 8) + cfgContent[2 * 2 + 0]);

            //BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            //int vaChannel = tp_chain.MaskValue(0x3f0) >> 4;
            //int realChannel = tp_chain.MaskValue(0xfc00) >> 10;
            //Refs = realChannel - vaChannel;
            //if (tp_chain.Bit(3))
            //{
            //    Rows = 4;
            //    Cols = (tp_chain.MaskValue(0x03f0) >> 4) >> 2;
            //}
            //else
            //{
            //    Rows = 2;
            //    Cols = (tp_chain.MaskValue(0x03f0) >> 4) >> 1;
            //}

            //int addRow = Refs > 0 ? 1 : 0;
            //DisplayDataLen = (ushort)((Rows + addRow) * Cols * 2);

            //RawDataMatrix = new DataMatrix(Rows, Cols, Refs);

            //BitValue misc = new BitValue((cfgContent[57 * 2 + 1] << 8) + cfgContent[57 * 2 + 0]);
            //BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
            //BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

            ////swap xy
            //if (misc.Bit(3))
            //{
            //    xPixel = lcdy.UShortValue;
            //    yPixel = lcdx.UShortValue;
            //}
            //else
            //{
            //    xPixel = lcdx.UShortValue;
            //    yPixel = lcdy.UShortValue;
            //}

            ////sensor map
            //Ic_2_Sensor_Map = new ushort[48];
            //Sensor_2_Ic_Map = new ushort[48];
            //for (int index = 0; index < 48; index++)
            //{
            //    Ic_2_Sensor_Map[index] = (ushort)(cfgContent[22 + index]);
            //    if (Ic_2_Sensor_Map[index] > 0 && Ic_2_Sensor_Map[index] < 48)
            //    {
            //        Sensor_2_Ic_Map[Ic_2_Sensor_Map[index] - 1] = (ushort)index;
            //    }
            //}

            return 0 == MainViewModel.Intr.ReturnCode;
        }

        public override void ActionOnChannelNumChange()
        {
            //if (Rows > 0 && Cols > 0)
            //{
            //    if (null == RawDataMatrix || (Rows + 1) != RawDataMatrix.RowNumber || (Cols + 1) != RawDataMatrix.ColNumber)
            //    {
            //        RuningKernel.Instance().Pause(true);
            //        RawDataMatrix = new DataMatrix(Rows, Cols, Cols, Rows);
            //        RuningKernel.Instance().Pause(false);
            //    }
            //}

            if (Rows > 0 && Cols > 0)
            {
                if ((Rows) != WpfRawDispView.Rows || (Cols) != WpfRawDispView.Columns)
                {
                    RuningKernel.Instance().Pause(true);
                    //RawDataMatrix = new DataMatrix(Rows, Cols, Cols + 2, Rows + 2);

                    System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => { WpfRawDispView.WpfRawDataViewInit(Rows, Cols, 1, 1); }));
                    RuningKernel.Instance().Pause(false);
                }
            }
        }

        public override uint GetSimullationRawData(short[] dataBuffer)
        {
            if (listSimulation.Count <= SimulationPosition)
                return 1;
            if (SimulationPosition >= SimulationStop)
                return 1;

            System.Threading.Thread.Sleep(SimulationSpeed);

            short[,] oneFrame = listSimulation[SimulationPosition];

            int index = 0;
            for (int iRow = 0; iRow < Rows + 1; iRow++)
            {
                for (int iCol = 0; iCol < Cols; iCol++)
                {
                    dataBuffer[index++] = oneFrame[iRow, iCol];
                }
            }
            for (int iRow = 0; iRow < Rows; iRow++)
            {
                dataBuffer[index++] = oneFrame[iRow, Cols];
            }

            //SimulationPosition++;
            DisplayDataLen = (ushort)(((Rows * Cols + Rows + Cols) * 2 + 6 + 3) & 0xfffc);
            //if (null == RawDataMatrix || (Rows + 1) != RawDataMatrix.RowNumber || (Cols + 1) != RawDataMatrix.ColNumber)
            //{
            //    RawDataMatrix = new DataMatrix(Rows, Cols, Cols, Rows);
            //}
            ActionOnChannelNumChange();

            return 0;
        }

        public override uint BurnConfigBin(byte[] buffer, uint len)
        {
            return SMChip5562.BurnConfigBin(buffer, (ushort)len);
            //SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
            //System.Threading.Thread.Sleep(10);
            //Initialized = false;
        }
        public override uint GetFirmWareConfig(byte[] buffer, uint len)
        {
            return SMChip5562.GetFirmWareConfig(buffer, (ushort)len);
        }
        public override uint WritePram(byte[] buffer, uint len)
        {
            Mcap5562.TPWritePramAction item = new Mcap5562.TPWritePramAction(0, "Write Pram", 0x20000000, 0);
            return item.act(buffer, len);
        }
 
    }
}
