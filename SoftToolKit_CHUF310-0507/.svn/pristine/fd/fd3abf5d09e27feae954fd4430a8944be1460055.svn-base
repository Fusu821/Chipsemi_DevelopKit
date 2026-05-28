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

namespace LibraryTools
{

    class ToolTouchViewModel
    {
        private ModelToolTouch m_ModelToolTouch = new ModelToolTouch();

        public DispalyView m_DispalyView = new DispalyView();

        //public IC8006DisplayBase m_IC8006DisplayBase = new IC8006DisplayBase();

        //public IC810DisplayBase m_IC810DisplayBase = new IC810DisplayBase();

        private IDictionary<ushort, ICDisplayBase> dcICDisplayMap = new Dictionary<ushort, ICDisplayBase>
        {
            {0x0000, new IC8006DisplayBase()},
            {0x0001, new IC810DisplayBase()}
        };

        public int num = 0;
        public readonly int m_MaxSaveNum = 20000;

        private bool IsInitOK = false;

        private List<String> m_PointMsgS = new List<string>();

        public ModelToolTouch ModelToolTouch
        {
            get
            {
                return m_ModelToolTouch;
            }
        }

        public ICDisplayBase GetICDisplayBase()
        {

            return dcICDisplayMap[m_ModelToolTouch.SelectedIC];
        }

        public void PointMsgRefresh()
        {
            if ( num % 20 == 0)
            {
                var i = num > m_MaxSaveNum ? m_MaxSaveNum : num;
                var str = "";
                for (int m = i - 20; m < i; m ++ )
                {
                    str += m_PointMsgS[m]+"\n";
                }
                str = str.TrimEnd('\n', '\r');
                m_ModelToolTouch.AddListPacket(str);
                
            }
        }

        public void ToolTouchViewModelRefresh(int side)
        {
            ModelToolTouch.DisplayHeight = side;
            ModelToolTouch.DisplayWidth = side;

            m_DispalyView.height = side;
            m_DispalyView.width = side;

            m_DispalyView.ViewWindowRefresh();
            ModelToolTouch.Image = m_DispalyView.GetBitmap();  
        }

        //void Start()
        //{
        //    var ret = m_IC8006DisplayBase.ReadCfg();
        //    if (ret == false) return;

        //    m_DispalyView.XPixel = m_IC8006DisplayBase.XPixel;
        //    m_DispalyView.YPixel = m_IC8006DisplayBase.YPixel;

        //    ret = m_IC8006DisplayBase.SwitchTouchMode();
        //    if (ret == false) return;

        //    IsRun = true;

        //    while (IsRun)
        //    {
        //        ret = m_IC8006DisplayBase.GetTouchData();
        //        if (ret == false) return;
        //        var touch = new MCap8006ReportData(m_IC8006DisplayBase.touchBuff);
        //        System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => m_DispalyView.OnTouchReport(touch)));
        //        System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>
        //        {
        //            num++;
        //            if (m_PointMsgS.Count() > m_MaxSaveNum) m_PointMsgS.RemoveAt(0);
        //            m_PointMsgS.Add(num.ToString() + ":" + touch.GetPointString());
        //            PointMsgRefresh();
        //        })); 
        //    }

        
        //}


        public ToolTouchViewModel()
        {
            m_ModelToolTouch.ctrlClickCommand = new Command()
            {
                DoExecute = obj =>
                {
                    string strParam = obj as string;
                    if (strParam== "Start")
                    {
                        RuningKernel.Instance().StopRun();
                        RuningKernel.Instance().StartRun();

                        RuningKernel.Instance().Work.AddWorkPermanent(new Action(() =>
                        {
                            if (IsInitOK == true) return;

                            var ret = GetICDisplayBase().ReadCfg();
                            if (ret == false) return;

                            m_DispalyView.XPixel = GetICDisplayBase().XPixel;
                            m_DispalyView.YPixel = GetICDisplayBase().YPixel;

                            ret = GetICDisplayBase().SwitchTouchMode(ModelToolTouch.SelectedPackages);
                            if (ret == false) return;

                            IsInitOK = true;

                        }));

                        RuningKernel.Instance().Work.AddWorkPermanent(new Action(() =>
                        {
                            var ret = GetICDisplayBase().GetTouchData();
                            if (ret == false) return;
                            //var touch = new MCap8006ReportData(GetICDisplayBase().touchBuff);
                            var touch = GetICDisplayBase().GetTouchReportData();
                            if (touch == null) return;
                            System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() => m_DispalyView.OnTouchReport(touch)));
                            System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>
                            {
                                num++;
                                DateTime now = DateTime.Now;
                               
                                if (m_PointMsgS.Count() > m_MaxSaveNum) m_PointMsgS.RemoveAt(0);
                                m_PointMsgS.Add(now.ToString("HH:mm:ss.fff")+" "+ num.ToString() + ":" + touch.GetPointString());
                                PointMsgRefresh();
                            })); 

                        }));

                        //Start();
                    }
                    else if (strParam == "Stop")
                    {
                        
                        RuningKernel.Instance().StopRun();
                        IsInitOK = false;
                    }
                    else if (strParam == "Clear")
                    {
                       
                        RuningKernel.Instance().Work.AddWorkTemporary(new Action(() =>
                        {
                            System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>  m_DispalyView.ViewWindowRefresh()));

                        }),null,true);

                    }
                    else if (strParam == "Save")
                    {

                        RuningKernel.Instance().Work.AddWorkTemporary(new Action(() =>
                        {
                            System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(() =>
                            {
                                System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
                                saveFileDlg.OverwritePrompt = true;
                                saveFileDlg.Filter = "log files (*.log)|*.log";
                                if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
                                {
                                    string strFileName = saveFileDlg.FileName;
                                    System.IO.Stream stream = saveFileDlg.OpenFile();
                                    System.IO.StreamWriter sw = new System.IO.StreamWriter(stream, Encoding.ASCII);
                                    //str = "data string for dynamic catch\r\n";
                                    //sw.Write(str);
                                    //sw.WriteLine();
                                    foreach (var MsgS in m_PointMsgS)
                                    {
                                        sw.Write(MsgS);
                                        sw.WriteLine();
                                    }

                                    sw.Close();
                                    stream.Close();

                                    m_PointMsgS.Clear();
                                    m_ModelToolTouch.ListPacket.Clear();
                                    num = 0;


                                }

                            }));


                        }));

                    }



                }

            };

        }
    }
}
