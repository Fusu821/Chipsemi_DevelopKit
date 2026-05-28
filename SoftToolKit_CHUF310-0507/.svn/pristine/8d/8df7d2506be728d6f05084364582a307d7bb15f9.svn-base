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
using System.Threading.Tasks;

namespace SEMIDevelopKit.Src.WinSub
{
    public class Model7126 : ModelBase
    {
        private static byte[] cfgContent = new byte[2048];

        public Model7126()
        {
            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_RAWDATA, eChipTypeList.SM_IC_7126, this);
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
            if (touchPoint[0] != 0xEB)
            {
                int coeff = (touchPoint[0] == 0xF8) ? 6 : 5;
                int checksumPos = TouchMaxNum * coeff + 2;
                uint len = (uint)(TouchMaxNum * coeff + 2);
                ushort checksum = (ushort)((touchPoint[checksumPos + 1] << 8) | touchPoint[checksumPos]);
                ushort crc = SMCheckTools.CaculateCheckSumU816(touchPoint, len);
                crc = (ushort)((~crc) + 1);

                return (crc == checksum) ? new MCap710TouchReportData(touchPoint) : null;

                //if(touchPoint[0] == 0xF8)
                //{
                //    ushort checksum = (ushort)(touchPoint[(TouchMaxNum * 6 + 3)] << 8 | touchPoint[(TouchMaxNum * 6+ 2)]);
                //    uint len = (uint)((TouchMaxNum * 6) + 2);
                //    ushort crc = SMCheckTools.CaculateCheckSumU816(touchPoint, len);
                //    crc = (ushort)((~crc) + 1);
                //    if (crc == checksum)
                //    {
                //        return new MCap710TouchReportData(touchPoint);
                //    }
                //}
                //else
                //{
                //    ushort checksum = (ushort)(touchPoint[(TouchMaxNum * 5 + 3)] << 8 | touchPoint[(TouchMaxNum * 5 + 2)]);
                //    uint len = (uint)((TouchMaxNum * 5) + 2);
                //    ushort crc = SMCheckTools.CaculateCheckSumU816(touchPoint, len);
                //    crc = (ushort)((~crc) + 1);
                //    if (crc == checksum)
                //    {
                //        return new MCap710TouchReportData(touchPoint);
                //    }
                //}
                //return null;
            }

            return new MCap710TouchReportData(touchPoint);
        }

        public override bool InitializeOK()
        {

            System.Threading.Thread.Sleep(100);
            //MainViewModel.Intr.ReturnCode = SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);  //
            //System.Threading.Thread.Sleep(60);
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

            DisplayDataLen = (ushort)(((Rows * Cols + 3*Rows + 3*Cols) * 2 + 6 + 3) & 0xfffc);

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
            //        RawDataMatrix = new DataMatrix(Rows + 2, Cols + 2, Cols + 2, Rows + 2);
            //        RuningKernel.Instance().Pause(false);
            //    }
            //}

            if (Rows > 0 && Cols > 0)
            {
                if ((Rows) != WpfRawDispView.Rows || (Cols) != WpfRawDispView.Columns)
                {
                    RuningKernel.Instance().Pause(true);
                    //RawDataMatrix = new DataMatrix(Rows, Cols, Cols + 2, Rows + 2);

                    System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => { WpfRawDispView.WpfRawDataViewInit(Rows, Cols, 3, 3); }));
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
            return SMChip7126.BurnConfigBin(buffer, (ushort)len);
            //SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
            //System.Threading.Thread.Sleep(10);
            //Initialized = false;
        }
        public override uint GetFirmWareConfig(byte[] buffer, uint len)
        {
            return SMChip7126.GetFirmWareConfig(buffer, (ushort)len);
        }
        public override uint WritePram(byte[] buffer, uint len)
        {
            Mcap7126.TPWritePramAction item = new Mcap7126.TPWritePramAction(0, "Write Pram", 0x20000000, 0);
            return item.act(buffer, len);
        }

        //public override void ActionOnICChanged() 
        //{
        //    RuningKernel.Instance().StopRun();
        //    RuningKernel.Instance().StartRun();

        //    Initialized = false;

        //    Func<short[], bool> ackOnRawData = new Func<short[], bool>((t) =>
        //    {
        //        if (Refresh)
        //        {
        //            //Refresh = false;
        //            RuningKernel.Instance().Work.AddWorkTemporary(() => { Refresh = false; });

        //            int index = 0;
        //            for (int iRow = 0; iRow < Rows; iRow++)
        //            {
        //                for (int iCol = 0; iCol < Cols; iCol++)
        //                {
        //                    if (index * 2 >= DisplayDataLen) break;

        //                    if (null != RawDataMatrix)
        //                    {
        //                        RawDataMatrix[iRow][iCol] = t[index++];
        //                    }
        //                }
        //            }
        //            if (RawDataMatrix.RowNumber > Rows)
        //            {
        //                for (int iCol = 0; iCol < Cols; iCol++)
        //                {
        //                    if (index * 2 >= DisplayDataLen) break;

        //                    if (null != RawDataMatrix)
        //                    {
        //                        RawDataMatrix[Rows][iCol] = t[index++];
        //                    }
        //                }
        //            }

        //            if (RawDataMatrix.ColNumber > Cols)
        //            {
        //                for (int iRow = 0; iRow < Rows; iRow++)
        //                {
        //                    if (index * 2 >= DisplayDataLen) break;

        //                    if (null != RawDataMatrix)
        //                    {
        //                        RawDataMatrix[iRow][Cols] = t[index++];
        //                    }
        //                }

        //            }

        //            for (int iCol = 0; iCol < Cols; iCol++)
        //            {
        //                if (index * 2 >= DisplayDataLen) break;

        //                if (null != RawDataMatrix)
        //                {
        //                    RawDataMatrix[Rows + 1][iCol] = t[index++];
        //                }
        //            }
        //            for (int iCol = 0; iCol < Cols; iCol++)
        //            {
        //                if (index * 2 >= DisplayDataLen) break;

        //                if (null != RawDataMatrix)
        //                {
        //                    RawDataMatrix[Rows + 2][iCol] = t[index++];
        //                }
        //            }

        //            for (int iRow = 0; iRow < Rows; iRow++)
        //            {
        //                if (index * 2 >= DisplayDataLen) break;

        //                if (null != RawDataMatrix)
        //                {
        //                    RawDataMatrix[iRow][Cols + 1] = t[index++];
        //                }
        //            }

        //            for (int iRow = 0; iRow < Rows; iRow++)
        //            {
        //                if (index * 2 >= DisplayDataLen) break;

        //                if (null != RawDataMatrix)
        //                {
        //                    RawDataMatrix[iRow][Cols + 2] = t[index++];
        //                }
        //            }
        //        }
        //        return true;
        //    });

        //    Action ackOnRawDataN = new Action(() =>
        //    {
        //        if (Refresh)
        //        {
        //            Array.Copy(dataBuffer,WpfRawDispView.RawDataMatrix, DisplayDataLen);
        //            //Refresh = false;
        //            RuningKernel.Instance().Work.AddWorkTemporary(() => { Refresh = false; });
        //            System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => { WpfRawDispView.Refresh(); }));
        //        }
    
        //    });

        //    RuningKernel.Instance().Work.AddWorkPermanent(new Action(() =>
        //    {
        //        //if (MainViewModel.Intr.DisplayType > dtType.MODE_TOUCH)
        //        //    return;
        //        if (SimulationChecked) return;
        //        if (dtType.MODE_NONE == MainViewModel.Intr.DisplayType) return;

        //        bool tpLinked = false;
        //        if (MainViewModel.Intr.ReturnCode > 0)
        //        {
        //            tpLinked = SMChipBase.HaveTpLinked();
        //            Initialized = false;
        //        }
        //        else
        //        {
        //            tpLinked = true;
        //        }


        //        if (!tpLinked || !Initialized)
        //        {
        //            if (!tpLinked)
        //            {
        //                if (MainViewModel.Intr.NotReset != true) SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
        //                Thread.Sleep(120);
        //                tpLinked = SMChipBase.HaveTpLinked();
        //                if (!tpLinked) MainViewModel.Intr.ReturnCode = 0x0008;
        //            }

        //            if (tpLinked && InitializeOK())
        //            {
        //                SwitchMode();
        //                Initialized = true;
        //            }
        //        }
        //    }));

        //    RuningKernel.Instance().Work.AddWorkPermanent(new Action(() =>    //获取数据
        //    {
        //        //if (!Initialized) return;
        //        if (dtType.MODE_RAWDATA == MainViewModel.Intr.DisplayType || dtType.MODE_TWOICS_RAWDATA == MainViewModel.Intr.DisplayType || dtType.MODE_810ANALOG_RAW == MainViewModel.Intr.DisplayType)
        //        {
        //            MainViewModel.Intr.ReturnCode = SMChipBase.GetRawDataPoint(dataBuffer, DisplayDataLen);
        //            //MainViewModel.Intr.ReturnCode = SMChipBase.GetRawDataPoint(WpfRawDispView.RawDataMatrix, DisplayDataLen);
        //            if (0 == MainViewModel.Intr.ReturnCode)
        //                //ackOnRawData(dataBuffer);
        //                ackOnRawDataN();
        //            //System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Input, new Action(() => ackOnRawData(dataBuffer)));
        //            //else if (Initialized)
        //            //SwitchMode();
        //        }
        //        else if (dtType.MODE_DIFFER == MainViewModel.Intr.DisplayType)
        //        {
        //            MainViewModel.Intr.ReturnCode = SMChipBase.GetRawDataPoint(dataBuffer, DisplayDataLen);
        //            if (0 == MainViewModel.Intr.ReturnCode)
        //                //ackOnRawData(dataBuffer);
        //                ackOnRawDataN();
        //            //System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Input, new Action(() => ackOnRawData(dataBuffer)));
        //            //else if (Initialized)
        //            //    SwitchMode();
        //        }
        //        else if (dtType.MODE_BASE == MainViewModel.Intr.DisplayType)
        //        {
        //            MainViewModel.Intr.ReturnCode = SMChipBase.GetRawDataPoint(dataBuffer, DisplayDataLen);
        //            if (0 == MainViewModel.Intr.ReturnCode)
        //                //ackOnRawData(dataBuffer);
        //                ackOnRawDataN();
        //        }
        //        else if (dtType.MODE_TOUCH == MainViewModel.Intr.DisplayType || dtType.MODE_TWOICS_TOUCH == MainViewModel.Intr.DisplayType || dtType.MODE_810ANALOG_TOUCH == MainViewModel.Intr.DisplayType)
        //        {
        //            ushort len = 0;
        //            MainViewModel.Intr.ReturnCode = SMChipBase.GetTouchPoint(touchPoint, ref len);
        //            ModelTouch touchMode = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_TOUCH, MainViewModel.Intr.SelectedIC) as ModelTouch;
        //            TouchReportData rpt = GenTouchReport(touchPoint);
        //            System.Windows.Application.Current.Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Render, (Action)(() => touchMode.OnReport(rpt)));
        //        }
        //        else if (dtType.MODE_SIMULATE_RAW == MainViewModel.Intr.DisplayType)
        //        {
        //            if (SimulationChecked)
        //                MainViewModel.Intr.ReturnCode = GetSimullationRawData(dataBuffer);
        //            else
        //                MainViewModel.Intr.ReturnCode = SMChipBase.GetRawDataPoint(dataBuffer, DisplayDataLen);

        //            if (0 == MainViewModel.Intr.ReturnCode)
        //            {
        //                FirmwareSimulate.FirmwareSimulation(SimulationPosition++, Cols, Rows, dataBuffer, diffBuffer, touchPoint);
        //                ackOnRawData(dataBuffer);
        //                ModelTouch touchMode = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_TOUCH, MainViewModel.Intr.SelectedIC) as ModelTouch;
        //                System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => touchMode.OnReport(GenTouchReport(touchPoint))));
        //                //touchMode.TouchData = GenTouchReport(touchPoint);
        //            }

        //        }
        //        else if (dtType.MODE_SIMULATE_DIFF == MainViewModel.Intr.DisplayType)
        //        {
        //            if (SimulationChecked)
        //                MainViewModel.Intr.ReturnCode = GetSimullationRawData(dataBuffer);
        //            else
        //                MainViewModel.Intr.ReturnCode = SMChipBase.GetRawDataPoint(dataBuffer, DisplayDataLen);

        //            if (0 == MainViewModel.Intr.ReturnCode)
        //            {
        //                FirmwareSimulate.FirmwareSimulation(SimulationPosition++, Cols, Rows, dataBuffer, diffBuffer, touchPoint);
        //                ackOnRawData(diffBuffer);
        //                ModelTouch touchMode = ModeCatch.GetModeByIdAndICType(SMDevelopChipReflex.SEMI_DEVLOP_TOUCH, MainViewModel.Intr.SelectedIC) as ModelTouch;
        //                System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => touchMode.OnReport(GenTouchReport(touchPoint))));
        //                //touchMode.TouchData = GenTouchReport(touchPoint);
        //            }
        //        }

        //        else
        //        {
        //            Thread.Sleep(100);
        //        }
        //    }));
        //}



        public override void saveTextData(string exportPath)
        {
            StringBuilder szOut = new StringBuilder();

            for (int index = 0; index < listCatchData.Count; index++)
            {
                szOut.Append("Frame:" + index.ToString() + "\r\n");
                short[] dataCopy = listCatchData[index];
                for (int iRow = 0; iRow < Rows + 1; iRow++)
                {
                    for (int iCol = 0; iCol < Cols; iCol++)
                    {
                        szOut.Append(string.Format("{0,-9:D}", dataCopy[iRow * Cols + iCol]));
                    }
                    if (RawDataMatrix.ColNumber > Cols)
                    {
                        szOut.Append(string.Format("{0,-9:D}", dataCopy[(Rows + 1) * Cols + iRow]));
                    }
                    szOut.Append("\r\n");
                }
                if (RawDataMatrix.RowExp > 0 && RawDataMatrix.ColExp > 0)
                {
                    szOut.Remove(szOut.Length - 8, 8);
                }

                szOut.Append("\r\n");
                szOut.Append("\r\n");

                for (int i = 0; i < 2; i++)
                {
                    szOut.Append(string.Format("TX{0,2:D}:", i+1));
                    for (int iCol = 0; iCol < Cols; iCol++)
                    {
                        szOut.Append(string.Format("{0,-9:D}", dataCopy[Rows * Cols + Cols + Rows + i * Cols + iCol]));
                    }
                    szOut.Append("\r\n");
                }
                for (int i = 0; i < 2; i++)
                {
                    szOut.Append(string.Format("RX{0,2:D}:", i + 1));
                    for (int iRow = 0; iRow < Rows; iRow++)
                    {
                        szOut.Append(string.Format("{0,-9:D}", dataCopy[Rows * Cols + Cols + Rows + 2 * Cols + i * Rows + iRow]));
                    }
                    szOut.Append("\r\n");
                }

                szOut.Append("\r\n");
            }
            listCatchData.Clear();

            StreamWriter sw = new StreamWriter(exportPath, false, Encoding.Default);
            sw.Write(szOut.ToString());
            sw.Flush();
            sw.Close();
        }

        public override void saveTextDataNew(StringBuilder szOut)
        {
            szOut.Append("Frame:" + frames.ToString() + "\r\n");
            short[] dataCopy = queueCatchDataGet();
            for (int iRow = 0; iRow < Rows + 1; iRow++)
            {
                for (int iCol = 0; iCol < Cols; iCol++)
                {
                    szOut.Append(string.Format("{0,-9:D}", dataCopy[iRow * Cols + iCol]));
                }
                if (WpfRawDispView.Columns + WpfRawDispView.ColExp > Cols)
                {
                    szOut.Append(string.Format("{0,-9:D}", dataCopy[(Rows + 1) * Cols + iRow]));
                }
                szOut.Append("\r\n");
            }
            if (WpfRawDispView.RowExp > 0 && WpfRawDispView.ColExp > 0)
            {
                szOut.Remove(szOut.Length - 8, 8);
            }

            szOut.Append("\r\n");
            szOut.Append("\r\n");

            for (int i = 0; i < 2; i++)
            {
                szOut.Append(string.Format("TX{0,2:D}:", i + 1));
                for (int iCol = 0; iCol < Cols; iCol++)
                {
                    szOut.Append(string.Format("{0,-9:D}", dataCopy[Rows * Cols + Cols + Rows + i * (Cols + Rows) + iCol]));
                }
                szOut.Append("\r\n");

                szOut.Append(string.Format("RX{0,2:D}:", i + 1));
                for (int iRow = 0; iRow < Rows; iRow++)
                {
                    szOut.Append(string.Format("{0,-9:D}", dataCopy[Rows * Cols + Cols + Rows + i * (Cols + Rows) + Cols + iRow]));
                }
                szOut.Append("\r\n");
            }
            szOut.Append("\r\n");
        }

        //public override void OnCtrlClickCommand(object param)
        //{
        //    string strParam = param as string;
        //    if (null == strParam) return;

        //    if ("main-catch-checked" == strParam)
        //    {
        //        queueCatchData.Clear();

        //        string exportPath = "";

        //        frames = 0;

        //        try
        //        {
        //            SaveFileDialog saveFileDialog = new SaveFileDialog();
        //            saveFileDialog.Filter = "Text Files (*.txt;)|*.txt";//|Hex Files(*.bin;)|*.bin
        //            if (DialogResult.OK == saveFileDialog.ShowDialog())
        //            {
        //                exportPath = saveFileDialog.FileName;
        //                exportPath.EndsWith(".txt");
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            ex.ToString();
        //        }

        //        RuningKernel.Instance().Work.AddWorkTemporary(() =>
        //        {
        //            int matrixCells =  DisplayDataLen >> 1;
        //            short[] dataCopy = new short[matrixCells];
        //            Array.Copy(dataBuffer, dataCopy, matrixCells);

        //            queueCatchDataAdd(dataCopy);

        //        }, new WorkComplete(() =>
        //        {
        //            return CatchChecked ? false : true;
        //        }));

        //        Task task = new Task(() =>
        //        {
        //            StreamWriter sw = new StreamWriter(exportPath, true, Encoding.Default);
        //            while (CatchChecked || queueCatchDataCount() != 0)
        //            {
        //                if (queueCatchDataCount() != 0)
        //                {
        //                    StringBuilder szOut = new StringBuilder();

        //                    saveTextDataNew(szOut);

        //                    //szOut.Append("Frame:" + frames.ToString() + "\r\n");
        //                    //short[] dataCopy = queueCatchDataGet();
        //                    //for (int iRow = 0; iRow < RawDataMatrix.RowNumber; iRow++)
        //                    //{
        //                    //    for (int iCol = 0; iCol < Cols; iCol++)
        //                    //    {
        //                    //        szOut.Append(string.Format("{0,-9:D}", dataCopy[iRow * Cols + iCol]));
        //                    //    }
        //                    //    if (RawDataMatrix.ColNumber > Cols)
        //                    //    {
        //                    //        szOut.Append(string.Format("{0,-9:D}", dataCopy[RawDataMatrix.RowNumber * Cols + iRow]));
        //                    //    }
        //                    //    szOut.Append("\r\n");
        //                    //}
        //                    //if (RawDataMatrix.RowExp > 0 && RawDataMatrix.ColExp > 0)
        //                    //{
        //                    //    szOut.Remove(szOut.Length - 8, 8);
        //                    //}

        //                    //szOut.Append("\r\n");

        //                    sw.Write(szOut.ToString());
        //                    sw.Flush();


        //                    frames++;
        //                }
        //            }
        //            sw.Close();
        //        });
        //        task.Start();


        //    }
        //    else if ("main-stopcatch-unchecked" == strParam)
        //    {
        //        //try
        //        //{
        //        //    SaveFileDialog saveFileDialog = new SaveFileDialog();
        //        //    saveFileDialog.Filter = "Text Files (*.txt;)|*.txt|Hex Files(*.bin;)|*.bin";
        //        //    if (DialogResult.OK == saveFileDialog.ShowDialog())
        //        //    {
        //        //        string exportPath = saveFileDialog.FileName;

        //        //        if (exportPath.EndsWith(".txt"))
        //        //        {
        //        //            saveTextData(exportPath);
        //        //        }
        //        //        else 
        //        //        {
        //        //            saveHexData(exportPath);
        //        //        }
        //        //    }
        //        //}
        //        //catch (Exception ex)
        //        //{
        //        //    ex.ToString();
        //        //}
        //    }
        //    else if ("simulation-path-click" == strParam)
        //    {
        //        try
        //        {
        //            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
        //            openFileDialog.Filter = "Txt File(*.txt)|*.txt";
        //            openFileDialog.RestoreDirectory = true;
        //            openFileDialog.FilterIndex = 1;
        //            openFileDialog.InitialDirectory = Directory.GetCurrentDirectory();
        //            if (openFileDialog.ShowDialog() == true)
        //            {
        //                SimulationPath = openFileDialog.FileName;

        //                RuningKernel.Instance().Pause(true);

        //                listSimulation.Clear();
        //                using (FileStream fs = new FileStream(SimulationPath, FileMode.Open))
        //                {
        //                    RuningKernel.Instance().Pause(true);
        //                    using (StreamReader sr = new StreamReader(fs))
        //                    {
        //                        string strLine = "";
        //                        int iRow = 0, iCol = 0;
        //                        short[,] oneFrame = null;

        //                        while (null != (strLine = sr.ReadLine()))
        //                        {
        //                            if (strLine.Contains("Frame"))
        //                            {
        //                                if (null == oneFrame)
        //                                {
        //                                    oneFrame = new short[50, 50];
        //                                    continue;
        //                                }
        //                                else
        //                                {
        //                                    listSimulation.Add(oneFrame);
        //                                    oneFrame = new short[50, 50];
        //                                    iRow = 0;
        //                                    continue;
        //                                }
        //                            }

        //                            string[] line = strLine.Trim().Split(' ');
        //                            line = line.Where((t) =>
        //                            {
        //                                return string.IsNullOrEmpty(t) ? false : true;
        //                            }).ToArray();
        //                            if (line.Length <= 2) continue;
        //                            for (iCol = 0; iCol < line.Length; iCol++)
        //                            {
        //                                oneFrame[iRow, iCol] = short.Parse(line[iCol]);
        //                            }
        //                            iRow++;
        //                        }

        //                        listSimulation.Add(oneFrame);

        //                        Rows = iRow - 1; Cols = iCol;
        //                    }
        //                    fs.Close();
        //                }
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            ex.ToString();
        //        }
        //        finally
        //        {
        //            SimulationPosition = 0;
        //            SimulationStop = SimulationMax = listSimulation.Count;
        //            RuningKernel.Instance().Pause(false);
        //        }
        //    }
        //    else if ("simulation-next-click" == strParam)
        //    {
        //        SimulationStop++;
        //    }
        //    else if ("main-catch-analyze-checked" == strParam)
        //    {
        //        queueCatchData.Clear();

        //        string exportPath = "";

        //        frames = 0;

        //        try
        //        {
        //            SaveFileDialog saveFileDialog = new SaveFileDialog();
        //            saveFileDialog.Filter = "Text Files (*.txt;)|*.txt|Hex Files(*.bin;)|*.bin";
        //            if (DialogResult.OK == saveFileDialog.ShowDialog())
        //            {
        //                exportPath = saveFileDialog.FileName;
        //                exportPath.EndsWith(".txt");
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            ex.ToString();
        //        }

        //        RuningKernel.Instance().Work.AddWorkTemporary(() =>
        //        {
        //            if (null == RawDataMatrix) return;
        //            //DataMatrix mx = new DataMatrix(RawDataMatrix.RowNumber, RawDataMatrix.ColNumber);
        //            int matrixCells =  DisplayDataLen >> 1;
        //            short[] dataCopy = new short[matrixCells];
        //            Array.Copy(dataBuffer, dataCopy, matrixCells);

        //            queueCatchDataAdd(dataCopy);

        //        }, new WorkComplete(() =>
        //        {
        //            return CatchAnalyzeChecked ? false : true;
        //        }));

        //        Task task = new Task(() =>
        //        {
        //            StreamWriter sw = new StreamWriter(exportPath, true, Encoding.Default);
        //            while (CatchAnalyzeChecked || queueCatchDataCount() != 0)
        //            {
        //                if (queueCatchDataCount() != 0)
        //                {
        //                    StringBuilder szOut = new StringBuilder();

        //                    saveTextDataNew(szOut);

        //                    //szOut.Append("Frame:" + frames.ToString() + "\r\n");
        //                    //short[] dataCopy = queueCatchDataGet();
        //                    //for (int iRow = 0; iRow < RawDataMatrix.RowNumber; iRow++)
        //                    //{
        //                    //    for (int iCol = 0; iCol < Cols; iCol++)
        //                    //    {
        //                    //        szOut.Append(string.Format("{0,-9:D}", dataCopy[iRow * Cols + iCol]));
        //                    //    }
        //                    //    if (RawDataMatrix.ColNumber > Cols)
        //                    //    {
        //                    //        szOut.Append(string.Format("{0,-9:D}", dataCopy[RawDataMatrix.RowNumber * Cols + iRow]));
        //                    //    }
        //                    //    szOut.Append("\r\n");
        //                    //}
        //                    //if (RawDataMatrix.RowExp > 0 && RawDataMatrix.ColExp > 0)
        //                    //{
        //                    //    szOut.Remove(szOut.Length - 8, 8);
        //                    //}

        //                    //szOut.Append("\r\n");

        //                    sw.Write(szOut.ToString());
        //                    sw.Flush();


        //                    frames++;
        //                }
        //            }
        //            sw.Close();
        //        });
        //        task.Start();
        //    }
        //    else if ("main-stopcatch-analyze-unchecked" == strParam)
        //    {
        //        //try
        //        //{
        //        //    SaveFileDialog saveFileDialog = new SaveFileDialog();
        //        //    saveFileDialog.Filter = "Text Files (*.txt;)|*.txt|Hex Files(*.bin;)|*.bin";
        //        //    if (DialogResult.OK == saveFileDialog.ShowDialog())
        //        //    {
        //        //        string exportPath = saveFileDialog.FileName;

        //        //        if (exportPath.EndsWith(".txt"))
        //        //        {
        //        //            saveTextData(exportPath);
        //        //        }
        //        //        else
        //        //        {
        //        //            saveHexData(exportPath);
        //        //        }
        //        //    }
        //        //}
        //        //catch (Exception ex)
        //        //{
        //        //    ex.ToString();
        //        //}
        //    }
        //}


    }
}
