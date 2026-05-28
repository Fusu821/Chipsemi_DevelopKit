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
using System.Threading;

namespace SEMIDevelopKit.Src.WinSub
{
    public class Model810 : ModelBase
    {
        private static byte[] cfgContent = new byte[2048];

        public Model810()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, eChipTypeList.SM_IC_810, this);
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

           return new MCap810ReportData(touchPoint);
                    
        }

        public override bool InitializeOK()
        {
            if (dtType.MODE_810ANALOG_TOUCH == MainViewModel.Intr.DisplayType || dtType.MODE_810ANALOG_RAW == MainViewModel.Intr.DisplayType)
            {
                xPixel = yPixel = 8192;
            }
            else
            {
                MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
   
                MainViewModel.Intr.ReturnCode = GetFirmWareConfig(cfgContent, 448);
                if (0 != MainViewModel.Intr.ReturnCode) return false;

                xPixel = (2 * (cfgContent[0x9a * 2] + (cfgContent[0x9a * 2 + 1] << 8))) + 1;
                yPixel = xPixel;
            }

            
            Rows = 10;
            Cols = 8;
                
            TouchMaxNum = 6;
           
            DisplayDataLen = (ushort)(((Rows * Cols + Rows + Cols) * 2 + 6 + 3) & 0xfffc);

            ActionOnChannelNumChange();

            MainViewModel.Intr.ReturnCode = 0;

            //MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);

            return true;
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
            return SMChip810.BurnConfigBin(buffer, (ushort)len);
        }
        public override uint GetFirmWareConfig(byte[] buffer, uint len)
        {
            return SMChip810.GetFirmWareConfig(buffer, (ushort)len);
        }
        public override uint WritePram(byte[] buffer, uint len)
        {

            return 0;
        }
    }
}
