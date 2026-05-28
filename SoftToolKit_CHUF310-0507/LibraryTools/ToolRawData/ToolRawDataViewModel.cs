using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using System.Windows.Media;
using GDI = System.Drawing;
using System.Threading;
using System.Threading.Tasks;
using SMInvokeBridge;

namespace LibraryTools
{

    public class ToolRawDataViewModel
    {
        private ModelToolRawData m_ModelToolRawData = new ModelToolRawData();

        //public DispalyRawDataView m_DispalyRawDataView = new DispalyRawDataView();
        public WpfRawDataView m_WpfRawDataView = new WpfRawDataView();

        int Rows;
        int Cols ;
        int DisplayDataLen;

        //Thread thread;

        private static object _lockObj = new object();

       Boolean res = false;

        public ModelToolRawData ModelToolRawData
        {
            get
            {
                return m_ModelToolRawData;
            }
        }

        //public void ToolTouchViewModelRefresh(int rows, int columns, int cellWidth, int cellHeight)
        //{
        //    ModelToolRawData.DisplayHeight = rows * cellHeight;
        //    ModelToolRawData.DisplayWidth = columns * cellWidth;

        //    m_DispalyRawDataView.Rows = rows;
        //    m_DispalyRawDataView.Columns = columns;
        //    m_DispalyRawDataView.CellWidth = cellWidth;
        //    m_DispalyRawDataView.CellHeight = cellHeight;
        //    m_DispalyRawDataView.ViewWindowRefresh();
        //    m_ModelToolRawData.Image = m_DispalyRawDataView.GetBitmap();  
        //}
     void DoWork()
    {
        while (true)
         {
             if (res == true)
            {
                System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>
                {
                    //DateTime now = DateTime.Now;
                    //string custom1 = "1.||" + now.ToString("mm:ss.fff") + "||";

                    SMChipBase.GetRawDataPoint(m_WpfRawDataView.RawDataMatrix, (ushort)DisplayDataLen);

                    //for (uint iRow = 0; iRow < m_WpfRawDataView.Rows; iRow++)
                    //{
                    //    for (uint iCol = 0; iCol < m_WpfRawDataView.Columns; iCol++)
                    //    {
                    //        m_WpfRawDataView.RawDataMatrix[iRow * m_WpfRawDataView.Columns + iCol] = (short)(m_WpfRawDataView.RawDataMatrix[iRow * m_WpfRawDataView.Columns + iCol] + 50);
                    //    }
                    //}

                    //now = DateTime.Now;
                    //custom1 += now.ToString("mm:ss.fff") + "||";

                    m_WpfRawDataView.Refresh();

                    //now = DateTime.Now;
                    //custom1 += now.ToString("mm:ss.fff") + "||";



                    //Console.WriteLine(custom1);

                }));

                lock (_lockObj)
                {
                    res = false;
                }
           
            }

         }

       
    }

        public ToolRawDataViewModel()
        {
            ModelToolRawData.ctrlClickCommand = new Command()
            {
                DoExecute = obj =>
                {
                    string strParam = obj as string;

                    if (strParam == "Set")
                    {
                        //RuningKernel.Instance().StopRun();
                        //RuningKernel.Instance().StartRun();

                        //RuningKernel.Instance().Work.AddWorkTemporary(new Action(() =>
                        //{
                        //    System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>
                        //    {
                               
                        //    }));
                        //}), null, true);

                        //ToolTouchViewModelRefresh(80, 60, 45, 20);
                        byte[] cfgContent = new byte[2048];
                        SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
                        Thread.Sleep(200);
                        SMChipBase.ReadCoreSpace(0x20000000 + 0x80, cfgContent, 2048);

                        Rows = cfgContent[0x1a];
                        Cols = cfgContent[0x19];

                        DisplayDataLen = (ushort)(((Rows * Cols + 3 * Rows + 3 * Cols) * 2 + 6 + 3) & 0xfffc);

                        m_WpfRawDataView.WpfRawDataViewInit(Rows, Cols, 1, 1);
                        m_ModelToolRawData.ReferenceData = 100;

                        SMChipBase.SwitchMode(1, (ushort)DisplayDataLen);

                        //thread = new Thread(DoWork);
                        //thread.Start();

                        //Task task = new Task(() =>
                        //{

                        //});
                        //task.Start();


                       
                    }
                    else if (strParam == "Start")
                    {
                        RuningKernel.Instance().StopRun();
                        RuningKernel.Instance().StartRun();

                        RuningKernel.Instance().Work.AddWorkPermanent(new Action(() =>
                        {
                            SMChipBase.GetRawDataPoint(m_WpfRawDataView.RawDataMatrix, (ushort)DisplayDataLen);

                            System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>
                            {
                                //DateTime now = DateTime.Now;
                                //string custom1 = "1.||" + now.ToString("mm:ss.fff") + "||";

                                

                                //for (uint iRow = 0; iRow < m_WpfRawDataView.Rows; iRow++)
                                //{
                                //    for (uint iCol = 0; iCol < m_WpfRawDataView.Columns; iCol++)
                                //    {
                                //        m_WpfRawDataView.RawDataMatrix[iRow * m_WpfRawDataView.Columns + iCol] = (short)(m_WpfRawDataView.RawDataMatrix[iRow * m_WpfRawDataView.Columns + iCol] + 50);
                                //    }
                                //}

                                //now = DateTime.Now;
                                //custom1 += now.ToString("mm:ss.fff") + "||";

                                m_WpfRawDataView.Refresh();

                                //now = DateTime.Now;
                                //custom1 += now.ToString("mm:ss.fff") + "||";



                                //Console.WriteLine(custom1);

                            }));

                            //for (uint iRow = 0; iRow < m_WpfRawDataView.Rows; iRow++)
                            //{
                            //    for (uint iCol = 0; iCol < m_WpfRawDataView.Columns; iCol++)
                            //    {
                            //        m_WpfRawDataView.RawDataMatrix[iRow * m_WpfRawDataView.Columns + iCol] = (short)(m_WpfRawDataView.RawDataMatrix[iRow * m_WpfRawDataView.Columns + iCol] - 50);
                            //    }
                            //}

                            //lock (_lockObj)
                            //{
                            //    res = true;
                            //}

                            //m_WpfRawDataView.Refresh();

                           Thread.Sleep(20);
                          

                        }));

                            
                            //for (uint iRow = 0; iRow < m_DispalyRawDataView.Rows; iRow++)
                            //{
                            //    for (uint iCol = 0; iCol < m_DispalyRawDataView.Columns; iCol++)
                            //    {
                            //        m_DispalyRawDataView.RawDataMatrix[iRow, iCol] = (short)(m_DispalyRawDataView.RawDataMatrix[iRow, iCol] + 2);
                            //    }
                            //}
                            //m_DispalyRawDataView.Refresh();

                           
                        
                    }

                }

            };
        }
    }
}
