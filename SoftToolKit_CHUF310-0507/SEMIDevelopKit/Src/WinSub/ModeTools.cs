using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using System.Windows.Controls;
using System.Windows;
using Microsoft.Win32;
using System.IO;
using System.ComponentModel;
using SMInvokeBridge;
using System.Windows.Threading;
using System.Threading;
using System.Threading.Tasks;

namespace SEMIDevelopKit.Src.WinSub
{
    public partial class ModeTools : CtrlEventDispacher
    {
        CancellationTokenSource tokenSource = new CancellationTokenSource();
        private static ModeTools instance = null;
        byte[] mtkContent = new byte[800 * 1024];

        public static ushort DIR_WRITE_HIDE_TEXT_CTRL = 0x0000;
        public static ushort DIR_WRITE_SHOW_TEXT_CTRL = 0x0001;
        public static ushort DIR_READ_HIDE_PAPAM_CTRL = 0x0000;
        public static ushort DIR_READ_SHOW_PARAM_CTRL = 0x0010;

        public static ModeTools Singleton()
        {
            if (null == instance)
                instance = new ModeTools();

            return instance;
        }
        private ModeTools()
        {
            ActionOnICChanged();

            ModeCatch.Register(SMDevelopChipReflex.SEMI_DEVLOP_TOOLS, eChipTypeList.SM_CHIPALL, this);
        }

        public void ActionOnICChanged()
        {
            ListBurns.Clear();
            UserControl user = new UserControl()
            {
                Template = System.Windows.Application.Current.Resources["TpBurnTemplate"] as ControlTemplate,
                DataContext = GenDataContext(),
            };
            ListBurns.Add(user);
        }

        public object GenDataContext()
        {
            TPBurning burn = new TPBurning();
            if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_3535, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Scap3535.TPWriteOtpAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Otp", 0, 0),
                    new Scap3535.TPReadOtpAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Otp", 0, 32 * 1024),
                    new Scap3535.TPWritePramAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x8000, 0),
                    new Scap3535.TPReadPramAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x8000, 32),
                    new Scap3535.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0xD6E0, 0),
                    new Scap3535.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0xD6E0, 204),
                    new Scap3535.TPReadPID_VID((8 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID", 0xD6E0, 204),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_3536, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Scap3536.TPWriteFlashAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Scap3536.TPReadFlashAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32 * 1024),
                    new Scap3536.TPWritePramAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x8000, 0),
                    new Scap3536.TPReadPramAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x8000, 32),
                    new Scap3536.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x8000, 0),
                    new Scap3536.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x8000, 204),
                    new Scap3536.TPEraseFlashAction((7 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Erase Flash", 0, 64 * 1024),
                    new Scap3536.TPReadPID_VID((8 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID", 0x9E00, 204),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5816, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap5816.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap5816.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap5816.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Mtp", 0, 0),
                    new Mcap5816.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Mtp", 0, 32),
                    //new Mcap5816.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x9F00, 0),
                    new Mcap5816.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x0000, 256),
                    new Mcap5816.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Mtp", 0, 40 * 1024 + 256),
                    //new Mcap5816.TPOSCCHAction((8 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Hidden Area Change", 0xA000,256),
                     new Mcap5816.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 256),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5472, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap5472.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap5472.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap5472.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap5472.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32),
                    new Mcap5472.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x18000, 0),
                    new Mcap5472.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x18000, 512),
                    new Mcap5472.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 128 * 1024),
                    new Mcap5472.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 512),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5562, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap5562.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap5562.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap5562.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap5562.TPWriteAppAction((8 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write App", 0x2000, 0),
                    new Mcap5562.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32),
                    new Mcap5562.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x32000, 0),
                    new Mcap5562.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x32000, 2048),
                    new Mcap5562.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 128 * 1024),
                    
                    new Mcap5562.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 2*1024),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_7126, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap7126.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap7126.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap7126.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap7126.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32),
                    new Mcap7126.TPWriteAppAction((8 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write App", 0x2000, 0),
                    new Mcap7126.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x32000, 0),
                    new Mcap7126.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x32000, 2048),
                    new Mcap7126.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 128 * 1024),
                    new Mcap7126.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 2*1024),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_7449, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap7449.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap7449.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap7449.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap7449.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32),
                    new Mcap7449.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x18000, 0),
                    new Mcap7449.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x18000, 512),
                    new Mcap7449.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 128 * 1024),
                    new Mcap7449.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 512),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_8006, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap8006.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap8006.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap8006.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap8006.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32),
                    new Mcap8006.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x7000, 204),
                    new Mcap8006.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x7000, 204),
                    new Mcap8006.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 20 * 1024),
                    //new Mcap7449.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 512),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_810, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    //new Mcap810.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    //new Mcap810.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap810.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap810.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 576),
                    new Mcap810.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x40, 448),
                    new Mcap810.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x40, 448),
                    new Mcap810.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 576),
                    //new Mcap7449.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 512),
                };
            }
            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_570, MainViewModel.Intr.SelectedIC))
            {
                burn.ListBurnType = new List<TPBurnAction>()
                {
                    new Mcap570.TPWritePramAction((1 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Pram", 0x20000000, 0),
                    new Mcap570.TPReadPramAction((2 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Pram", 0x20000000, 32),
                    new Mcap570.TPWriteFlashAction((3 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Flash", 0, 0),
                    new Mcap570.TPWriteAppAction((8 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write App", 0x2000, 0),
                    new Mcap570.TPReadFlashAction((4 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Flash", 0, 32),
                    new Mcap570.TPWriteConfigAction((5 << 8) + DIR_WRITE_SHOW_TEXT_CTRL, "Write Config", 0x32000, 0),
                    new Mcap570.TPReadConfigAction((6 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Read Config", 0x32000, 2048),
                    new Mcap570.TPEraseFlashAction((7 << 8) + DIR_READ_SHOW_PARAM_CTRL, "Erase Flash", 0, 128 * 1024),
                    new Mcap570.TPReadPID_VID((9 << 8) + DIR_READ_HIDE_PAPAM_CTRL, "Read PID-VID",0x20000080, 2*1024),
                };
            }

            return burn;
        }

        private bool executeChecked = false;
        public bool ExecuteChecked
        {
            get { return executeChecked; }
            set { if (value != executeChecked) { executeChecked = value; OnPropertyChanged("ExecuteChecked"); } }
        }

        private int selectedBurn = 0;
        public int SelectedBurn
        {
            get { return selectedBurn; }
            set { if (value != selectedBurn) { selectedBurn = value; OnPropertyChanged("SelectedBurn"); } }
        }

        private BindingList<UserControl> listBurns = new BindingList<UserControl>();
        public BindingList<UserControl> ListBurns
        {
            get { return listBurns; }
            set { if (value != listBurns) { listBurns = value; OnPropertyChanged("ListBurns"); } }
        }

        private bool loopChecked = false;
        public bool LoopChecked
        {
            get { return loopChecked; }
            set { if (value != loopChecked) { loopChecked = value; OnPropertyChanged("LoopChecked"); } }
        }

        private string mtkTextBinPath = "";
        public string MtkTextBinPath
        {
            get { return mtkTextBinPath; }
            set { if (mtkTextBinPath != value) { mtkTextBinPath = value; OnPropertyChanged("MtkTextBinPath"); } }
        }

        private int mtkBinSize = 0x32000;
        public int MtkBinSize
        {
            get { return mtkBinSize; }
            set { if (mtkBinSize != value) { mtkBinSize = value; OnPropertyChanged("MtkBinSize"); } }
        }

        private BindingList<string> listBurnResult = new BindingList<string>()
        {
        };
        public BindingList<string> ListBurnResult
        {
            get { return listBurnResult; }
            set { if (value != listBurnResult) { listBurnResult = value; OnPropertyChanged("ListBurnResult"); } }
        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if ("tool-add-click" == strParam)
            {
                UserControl user = new UserControl()
                {
                    Template = System.Windows.Application.Current.Resources["TpBurnTemplate"] as ControlTemplate,
                    DataContext = GenDataContext(),
                };
                ListBurns.Add(user);
            }
            else if ("tool-up-click" == strParam)
            {
                if (SelectedBurn >= 1 && SelectedBurn <= listBurns.Count - 1)
                {
                    int newIndex = SelectedBurn - 1;
                    var item = listBurns[SelectedBurn];
                    listBurns.RemoveAt(SelectedBurn);
                    listBurns.Insert(newIndex, item);
                    SelectedBurn = newIndex;
                }
            }
            else if ("tool-down-click" == strParam)
            {
                if (SelectedBurn >= 0 && SelectedBurn <= listBurns.Count - 2)
                {
                    int newIndex = SelectedBurn + 1;
                    var item = listBurns[SelectedBurn];
                    listBurns.RemoveAt(SelectedBurn);
                    listBurns.Insert(newIndex, item);
                    SelectedBurn = newIndex;
                }
            }
            else if ("tool-delete-click" == strParam)
            {
                if (SelectedBurn >= 0 && SelectedBurn <= listBurns.Count - 1)
                {
                    listBurns.RemoveAt(SelectedBurn);
                }
            }
            else if ("burn-execute-click" == strParam)
            {
                SelectedBurn = 0;
                foreach (var item in ListBurns)
                {
                    TPBurning burn = item.DataContext as TPBurning;
                    if (null == burn) continue;

                    burn.DoBurn();
                }
            }
            else if ("stop-execute-click" == strParam)
            {

            }
            else if ("loop-execute-click" == strParam)
            {
                int totalCnt = 0;
                tokenSource = new CancellationTokenSource();
                var token = tokenSource.Token;
                //token.IsCancellationRequested = 
                var task = Task.Factory.StartNew(() =>
                {
                    while (!token.IsCancellationRequested)
                    {
                        SelectedBurn = 0;
                        foreach (var item in ListBurns)
                        {
                            TPBurning burn = null;
                            Application.Current.Dispatcher.Invoke(new Action(() => burn = item.DataContext as TPBurning));

                            if (null == burn)
                                continue;
                            if (token.IsCancellationRequested)
                                break;

                            burn.DoBurnAndWait();

                            Application.Current.Dispatcher.BeginInvoke(new Action(() => ListBurnResult.Add("Total Count = " + (++totalCnt).ToString())));
                        }
                    }
                }, token);

                token.Register(() =>
                {
                    Application.Current.Dispatcher.BeginInvoke(new Action(() => ListBurnResult.Add("user canceled, Total Count = " + totalCnt.ToString())));
                });
            }
            else if ("loop-stop-click" == strParam)
            {
                tokenSource.Cancel();
            }
            else if ("mtk-bin-click" == strParam)
            {
                try
                {
                    OpenFileDialog dlg = new OpenFileDialog();
                    dlg.DefaultExt = ".bin";
                    dlg.Filter = "Bin file (.bin)|*.bin";
                    Nullable<bool> result = dlg.ShowDialog();
                    if (true == result)
                    {
                        MtkTextBinPath = dlg.FileName;
                    }
                }
                catch (Exception ex)
                {
                    ModeTools.Singleton().ListBurnResult.Add(ex.Message);
                }
            }
            else if ("mtk-download-click" == strParam)
            {
                try
                {
                    if (!string.IsNullOrEmpty(MtkTextBinPath))
                    {
                        FileInfo fileInfo = new FileInfo(MtkTextBinPath);
                        uint binFileLen = (uint)fileInfo.Length;
                        //byte[] mtkContent = new byte[64 * 1024];
                        using (FileStream fs = new FileStream(MtkTextBinPath, FileMode.Open))
                        {
                            //bootContent = new byte[binFileLen];
                            fs.Read(mtkContent, 0, (int)binFileLen);
                            fs.Flush();
                            fs.Close();
                        }

                        RuningKernel.Instance().Work.AddWorkTemporary(() =>
                        {
                            MainViewModel.Intr.ReturnCode = SMCommBase.PrepareMtkBoardUpgrade();
                            if (0 == MainViewModel.Intr.ReturnCode)
                            {
                                Thread.Sleep(200);

                                RuningKernel.Instance().Work.AddWorkTemporary(() =>
                                {
                                    MainViewModel.Intr.ProcessMax = binFileLen;
                                    MainViewModel.Intr.ReturnCode = SMCommBase.UpgradeMtkBoard(mtkContent, (uint)binFileLen, (byte devNo, int pos, int maxPos) =>
                                    {
                                        MainViewModel.Intr.ProcessValue = (uint)pos;
                                    });
                                    if (0 == MainViewModel.Intr.ReturnCode)
                                    {
                                        System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                                        {
                                            MessageBox.Show("\r\nUpgrade MTK Board Success");
                                        }));
                                    }
                                    else
                                    {
                                        System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                                        {
                                            MessageBox.Show("\r\nUpgrade MTK Board Failed");
                                        }));
                                    }
                                });
                            }
                            else
                            {
                                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                                {
                                    MessageBox.Show("\r\nUpgrade MTK Board Failed");
                                }));
                                return;
                            }
                        });
                    }
                }
                catch (Exception ex)
                {
                    ModeTools.Singleton().ListBurnResult.Add(ex.Message);
                }
            }
            else if ("mtk-bin-read-click" == strParam)
            {
                RuningKernel.Instance().Work.AddWorkTemporary(() =>
                {
                    //MainViewModel.Intr.ReturnCode = SMCommBase.PrepareMtkBoardUpgrade();
                    MainViewModel.Intr.ReturnCode = 0;
                    if (0 == MainViewModel.Intr.ReturnCode)
                    {
                        System.Threading.Thread.Sleep(200);

                        RuningKernel.Instance().Work.AddWorkTemporary(() =>
                        {
                            uint len = (uint)MtkBinSize;
                            MainViewModel.Intr.ProcessMax = len;
                            MainViewModel.Intr.ReturnCode = SMCommBase.ReadMtkBoard(mtkContent, len, (byte devNo, int pos, int maxPos) =>
                            {
                                MainViewModel.Intr.ProcessValue = (uint)pos;
                            });
                            if (0 == MainViewModel.Intr.ReturnCode)
                            {
                                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                                {
                                    System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
                                    saveFileDlg.OverwritePrompt = true;
                                    saveFileDlg.Filter = "bin files (*.bin)|*.bin";
                                    if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
                                    {
                                        string fileName = saveFileDlg.FileName;
                                        FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                                        BinaryWriter bw = new BinaryWriter(fs);
                                        bw.Write(mtkContent, 0, (int)len);
                                        bw.Close();
                                    }
                                }));
                            }
                            else
                            {
                                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                                {
                                    MessageBox.Show("\r\nRead MTK Board Failed");
                                }));
                            }
                        });
                    }
                    else
                    {
                        System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                        {
                            MessageBox.Show("\r\nRead MTK Board Failed");
                        }));
                        return;
                    }
                });
            
            }
        }

    }

    public class TPBurnAction : SMDefinition
    {
        private uint iStartAddr = 0;
        public uint Lengh { get; set; }
        public bool SaveBurnResult { get; set; }
        public Func<byte[], uint, uint> act = null;
        protected byte[] onceBuffer = new byte[1024];
        public uint StartAddr 
        {
            set { iStartAddr = value; }
            get
            {
                RefreshArgs();
                return iStartAddr;
            }
        }
        public TPBurnAction(int typeVal, string typeName, uint start, uint len)
            : base((ushort)typeVal, typeName)
        {
            StartAddr = start;
            Lengh = len;
        }

        protected virtual void RefreshArgs()
        {

        }
        protected void OnActionDone(byte[] content, uint count)
        {
            if (SaveBurnResult)
            {
                System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
                saveFileDlg.OverwritePrompt = true;
                saveFileDlg.Filter = "bin files (*.bin)|*.bin";
                if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
                {
                    string fileName = saveFileDlg.FileName;
                    FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                    BinaryWriter bw = new BinaryWriter(fs);
                    bw.Write(content, 0, (int)count);
                    bw.Close();
                }
            }
            else
            {
                string lines = "";
                int iLeft = (int)count, iOnce = 16;
                while (iLeft > 0)
                {
                    lines = String.Format("{0,-7:X4}", count - iLeft);
                    iOnce = Math.Min(16, iLeft);

                    
                    for (int index = 0; index < iOnce; index++)
                    {
                        //string temp = String.Format("0x{0:x2}", content[count - iLeft + index]);
                        //lines += String.Format("{0,-10} ", temp);
                        //lines += content[count - iLeft + index].ToString("X2");
                        lines += string.Format("0x{0,-3:X2}", content[count - iLeft + index]);
                    }

                    ModeTools.Singleton().ListBurnResult.Add(lines);

                    iLeft -= iOnce;
                }
            }
        }
    }

    public class TPBurning : CtrlEventDispacher
    {
        uint binFileLen = 0;
        byte[] bootContent = new byte[248 * 1024];
        public TPBurning()
        {
        }
        private string textSrc = "";
        public string TextSrc
        {
            get { return textSrc; }
            set { if (value != textSrc) { textSrc = value; OnPropertyChanged("TextSrc"); } }
        }

        private uint burnStartAddr = 0;
        public uint BurnStartAddr
        {
            get { return burnStartAddr; }
            set { if (value != burnStartAddr) { burnStartAddr = value; OnPropertyChanged("BurnStartAddr"); } }
        }

        private ushort rwUnit = 1;
        public ushort RWUnit
        {
            get { return rwUnit; }
            set { if (value != rwUnit) { rwUnit = value; OnPropertyChanged("RWUnit"); } }
        }
        private IList<SMDefinition> listUnit = new List<SMDefinition>()
        {
            new SMDefinition(1, "byte"),
            new SMDefinition(1024, "1K"),
            new SMDefinition(4096, "4K"),
        };
        public IList<SMDefinition> ListUnit
        {
            get { return listUnit; }
            set { if (value != listUnit) { listUnit = value; OnPropertyChanged("ListUnit"); } }
        }

        private uint burnLengh = 0;
        public uint BurnLengh
        {
            get { return burnLengh; }
            set { if (value != burnLengh) { burnLengh = value; OnPropertyChanged("BurnLengh"); } }
        }

        private ushort selectedBurnType = (1 << 8) + 0x0001;
        public ushort SelectedBurnType
        {
            get { return selectedBurnType; }
            set
            {
                if (value != selectedBurnType)
                {
                    selectedBurnType = value;
                    OnPropertyChanged("SelectedBurnType");

                    var item = ListBurnType.FirstOrDefault(t => t.TypeVal == selectedBurnType);

                    BurnStartAddr = item.StartAddr;
                    BurnLengh = item.Lengh / RWUnit;
                }
            }
        }

        private bool saveBurnResult = false;
        public bool SaveBurnContent
        {
            get { return saveBurnResult; }
            set { if (saveBurnResult != value) { saveBurnResult = value; OnPropertyChanged("SaveBurnContent"); } }
        }

        public void DoBurn()
        {
            try
            {
                var item = ListBurnType.FirstOrDefault(t => t.TypeVal == selectedBurnType);
                item.Lengh = BurnLengh * RWUnit;
                item.SaveBurnResult = SaveBurnContent;
                if ((item.TypeVal & ModeTools.DIR_READ_SHOW_PARAM_CTRL) > 0)
                    item.StartAddr = BurnStartAddr;

                if (!string.IsNullOrEmpty(TextSrc))
                {
                    FileInfo fileInfo = new FileInfo(TextSrc);
                    binFileLen = (uint)fileInfo.Length;
                    using (FileStream fs = new FileStream(TextSrc, FileMode.Open))
                    {
                        //bootContent = new byte[binFileLen];
                        fs.Read(bootContent, 0, (int)binFileLen);
                        fs.Flush();
                        fs.Close();
                    }
                }

                RuningKernel.Instance().Work.AddWorkTemporary(() => 
                {
                    MainViewModel.Intr.RaiseException = true;
                    item.act(bootContent, binFileLen);
                    MainViewModel.Intr.RaiseException = false;
                },() =>
                {
                    ModeTools.Singleton().ExecuteChecked = false;
                    ModeTools.Singleton().SelectedBurn = ModeTools.Singleton().SelectedBurn + 1;

                    return true;
                });
            }
            catch (Exception ex)
            {
                ModeTools.Singleton().ListBurnResult.Insert(0, ex.ToString());
            }
        }

        public void DoBurnAndWait()
        {
            try
            {
                var item = ListBurnType.FirstOrDefault(t => t.TypeVal == selectedBurnType);
                item.StartAddr = BurnStartAddr;
                item.Lengh = BurnLengh * RWUnit;
                item.SaveBurnResult = SaveBurnContent;

                bool actionFinished = false;
                RuningKernel.Instance().Work.AddWorkTemporary(() =>
                {
                    MainViewModel.Intr.RaiseException = true;
                    var rst = item.act(bootContent, binFileLen);
                    MainViewModel.Intr.RaiseException = false;

                    if (rst > 0) ModeTools.Singleton().LoopChecked = false;
                }, () =>
                {
                    actionFinished = true;
                    ModeTools.Singleton().SelectedBurn = ModeTools.Singleton().SelectedBurn + 1;
                    return true;
                });

                for (int index = 0; index < 100; index++)
                {
                    if (actionFinished)
                        break;
                    Thread.Sleep(200);
                }
            }
            catch (Exception ex)
            {
                ModeTools.Singleton().LoopChecked = false;
                Application.Current.Dispatcher.BeginInvoke(new Action(() => ModeTools.Singleton().ListBurnResult.Add(ex.ToString())));
            }
        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if ("burn-load-click" == strParam)
            {
                try
                {
                    OpenFileDialog dlg = new OpenFileDialog();
                    dlg.DefaultExt = ".bin";
                    dlg.Filter = "Bin file (.bin)|*.bin";
                    Nullable<bool> result = dlg.ShowDialog();
                    if (true == result)
                        TextSrc = dlg.FileName;
                }
                catch (Exception ex)
                {
                    ModeTools.Singleton().ListBurnResult.Add(ex.ToString());
                }

                try
                {
                    if (!string.IsNullOrEmpty(TextSrc))
                    {
                        FileInfo fileInfo = new FileInfo(TextSrc);
                        binFileLen = (uint)fileInfo.Length;
                        using (FileStream fs = new FileStream(TextSrc, FileMode.Open))
                        {
                            //bootContent = new byte[binFileLen];
                            fs.Read(bootContent, 0, (int)binFileLen);
                            fs.Flush();
                            fs.Close();
                        }
                    }
                }
                catch (Exception ex)
                {
                    ModeTools.Singleton().ListBurnResult.Add(ex.ToString());
                }
            }
            else if ("item-execute-click" == strParam)
            {
                this.DoBurn();
            }
        }
//        private IList<TPBurnAction> listBurnType = new List<TPBurnAction>()
//         {
//             new TPWriteFlashAction(0x0001, "Write Flash", 0, 0),
//             new TPReadFlashAction(0x0100, "Read Flash", 0, 32 * 1024),
//             new TPWritePramAction(0x0002, "Write Pram", 0x8000, 0),
//             new TPReadPramAction(0x0200, "Read Pram", 0x8000, 32),
//             new TPWriteConfigAction(0x0004, "Write Config", 0x8000, 0),
//             new TPReadConfigAction(0x0400, "Read Config", 0x8000, 204),
//             new TPEraseFlashAction(0x0800, "Erase Flash", 0, 64 * 1024),
//         };
        private IList<TPBurnAction> listBurnType = null;
        public IList<TPBurnAction> ListBurnType
        {
            get { return listBurnType; }
            set { if (value != listBurnType) { listBurnType = value; OnPropertyChanged("ListBurnType"); } }
        }
    }
}
