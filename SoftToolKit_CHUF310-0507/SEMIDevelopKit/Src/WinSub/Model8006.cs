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
    public class Model8006 : ModelBase
    {
        private static byte[] cfgContent = new byte[2048];

        public Model8006()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, eChipTypeList.SM_IC_8006, this);
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
            return new MCap8006ReportData(touchPoint);
        }

        public override bool InitializeOK()
        {

            System.Threading.Thread.Sleep(100);
            MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);
            System.Threading.Thread.Sleep(60);
            if (0 != MainViewModel.Intr.ReturnCode) return false;

            MainViewModel.Intr.ReturnCode = SMChipBase.ReadCoreSpace(0x20000000 + 0x1c, cfgContent, 204);  //
            if (0 != MainViewModel.Intr.ReturnCode) return false;

            BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            BitValue misc = new BitValue((cfgContent[57 * 2 + 1] << 8) + cfgContent[57 * 2 + 0]);
            BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
            BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

            int vaChannel = tp_chain.MaskValue(0x3f0) >> 4;
            int realChannel = tp_chain.MaskValue(0xfc00) >> 10;
            Refs = realChannel - vaChannel;

            //swap xy
            //if (misc.Bit(3))
            //{
            //    xPixel = lcdy.UShortValue;
            //    yPixel = lcdx.UShortValue;
            //}
            //else
            //{
            //    xPixel = lcdx.UShortValue;
            //    yPixel = xPixel;//lcdy.UShortValue;
            //}
            xPixel = lcdx.UShortValue;
            //xPixel = 8192;
            yPixel = xPixel;//lcdy.UShortValue;

            Rows = 20;
            Cols = 2;

            DisplayDataLen = (ushort)(((Rows * Cols + Rows + Cols) * 2 + 6 + 3) & 0xfffc);

            //if (null == RawDataMatrix || (Rows + 1) != RawDataMatrix.RowNumber || (Cols + 1) != RawDataMatrix.ColNumber)
            //{
            //    RawDataMatrix = new DataMatrix(Rows, Cols, Cols, Rows);
            //}

            ActionOnChannelNumChange();

            MainViewModel.Intr.ReturnCode = 0;

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
            return SMChip8006.BurnConfigBin(buffer, (ushort)len);
            //SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
            //System.Threading.Thread.Sleep(10);
            //Initialized = false;
        }
        public override uint GetFirmWareConfig(byte[] buffer, uint len)
        {
            return SMChip8006.GetFirmWareConfig(buffer, (ushort)len);
        }
        public override uint WritePram(byte[] buffer, uint len)
        {
            Mcap5562.TPWritePramAction item = new Mcap5562.TPWritePramAction(0, "Write Pram", 0x20000000, 0);
            return item.act(buffer, len);
        }

        public override void SwitchMode()
        {
            uint iRetCode = 0;

            if (SimulationChecked) return;
          
            System.Threading.Thread.Sleep(200);
            SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);
            System.Threading.Thread.Sleep(60);
            
            iRetCode = SMChipBase.SwitchMode(MainViewModel.Intr.DisplayType, DisplayDataLen);
            if (0 != iRetCode)
            {
                SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                System.Threading.Thread.Sleep(1000);

                SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);
                System.Threading.Thread.Sleep(60);

                iRetCode = SMChipBase.SwitchMode(MainViewModel.Intr.DisplayType, DisplayDataLen);
            }

            MainViewModel.Intr.ReturnCode = iRetCode;
            //.....
            //Thread.Sleep(200);
        }

    }
}
