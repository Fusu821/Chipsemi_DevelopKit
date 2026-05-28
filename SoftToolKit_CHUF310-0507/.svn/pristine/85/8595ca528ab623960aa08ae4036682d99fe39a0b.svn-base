using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Win32;
using System.Windows;
using System.IO;

namespace LibraryTools
{
   

    class ToolMontageBinViewMode
    {
        public static uint CaculateCheckSumEx(byte[] buf, int length)
        {
            int k = 0;
            uint combChk = 0;
            ushort check = 0, checkEx = 0;

            for (k = 0; k < length; k++)
            {
                check += buf[k];
                checkEx += (ushort)(k * buf[k]);
            }
            combChk = (uint)(checkEx << 16) | check;

            return combChk;
        }

        private ModeToolMontageBin m_ModeToolMontageBin = new ModeToolMontageBin();
        public ModeToolMontageBin ModeToolMontageBin
        {
            get
            {
                return m_ModeToolMontageBin;
            }
        }

        public ToolMontageBinViewMode()
        {
            m_ModeToolMontageBin.ClickFristBinLoad = new Command()
            {
                DoExecute = obj =>
                {
                    FirstBinLoad_Click();
                }
            };
            m_ModeToolMontageBin.ClickSecondtBinLoad = new Command()
            {
                DoExecute = obj =>
                {
                    SecondtBinLoad_Click();
                }
            };

            m_ModeToolMontageBin.ClickGenerateBin = new Command()
            {
                DoExecute = obj =>
                {
                    GenerateBin_Click();
                }
            };
        }

        private void FirstBinLoad_Click()
        {
            try
            {
                OpenFileDialog dlg = new OpenFileDialog();
                dlg.DefaultExt = ".bin";
                dlg.Filter = "Bin file (.bin)|*.bin";
                Nullable<bool> result = dlg.ShowDialog();
                if (true == result)
                {
                    m_ModeToolMontageBin.FristBinPath = dlg.FileName;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void SecondtBinLoad_Click()
        {
            try
            {
                OpenFileDialog dlg = new OpenFileDialog();
                dlg.DefaultExt = ".bin";
                dlg.Filter = "Bin file (.bin)|*.bin";
                Nullable<bool> result = dlg.ShowDialog();
                if (true == result)
                {
                    m_ModeToolMontageBin.SecondBinPath = dlg.FileName;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

        }

        private void GenerateBin_Click()
        {
            try
            {
                if (!string.IsNullOrEmpty(m_ModeToolMontageBin.FristBinPath))
                {
                    FileInfo fileInfo = new FileInfo(m_ModeToolMontageBin.FristBinPath);
                    uint binFileLen = (uint)fileInfo.Length;
                    if (binFileLen > m_ModeToolMontageBin.AddressOffset)
                    {
                        MessageBox.Show("Frist bin greater than address offset");
                        return;
                    }
                    using (FileStream fs = new FileStream(m_ModeToolMontageBin.FristBinPath, FileMode.Open))
                    {
                        //bootContent = new byte[binFileLen];
                        fs.Read(m_ModeToolMontageBin.generatebincontent, 0, (int)binFileLen);
                        fs.Flush();
                        fs.Close();
                    }
                }

                if (!string.IsNullOrEmpty(m_ModeToolMontageBin.SecondBinPath))
                {
                    FileInfo fileInfo = new FileInfo(m_ModeToolMontageBin.SecondBinPath);
                    uint binFileLen = (uint)fileInfo.Length;
                    if ((binFileLen + m_ModeToolMontageBin.AddressOffset) > m_ModeToolMontageBin.generatebincontent.Count())
                    {
                        MessageBox.Show("Generate bin greater than maximum");
                        return;
                    }

                    m_ModeToolMontageBin.generatebinmaxsizenum = binFileLen + m_ModeToolMontageBin.AddressOffset;

                    using (FileStream fs = new FileStream(m_ModeToolMontageBin.SecondBinPath, FileMode.Open))
                    {
                        //bootContent = new byte[binFileLen];
                        fs.Read(m_ModeToolMontageBin.generatebincontent, (int)m_ModeToolMontageBin.AddressOffset, (int)binFileLen);
                        fs.Flush();
                        fs.Close();
                    }

                }
                var crc = CaculateCheckSumEx(m_ModeToolMontageBin.generatebincontent, (int)m_ModeToolMontageBin.generatebinmaxsizenum);

                m_ModeToolMontageBin.generatebincontent[(int)m_ModeToolMontageBin.generatebinmaxsizenum + 3] = (byte)((crc >> 24)& 0xff);
                m_ModeToolMontageBin.generatebincontent[(int)m_ModeToolMontageBin.generatebinmaxsizenum + 2] = (byte)((crc >> 16) & 0xff);
                m_ModeToolMontageBin.generatebincontent[(int)m_ModeToolMontageBin.generatebinmaxsizenum + 1] = (byte)((crc >> 8) & 0xff);
                m_ModeToolMontageBin.generatebincontent[(int)m_ModeToolMontageBin.generatebinmaxsizenum + 0] = (byte)(crc&0xff);

                System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
                saveFileDlg.OverwritePrompt = true;
                saveFileDlg.Filter = "bin files (*.bin)|*.bin";
                if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
                {
                    string fileName = saveFileDlg.FileName;
                    FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite);
                    BinaryWriter bw = new BinaryWriter(fs);
                    bw.Write(m_ModeToolMontageBin.generatebincontent, 0, (int)m_ModeToolMontageBin.generatebinmaxsizenum + 4);
                    bw.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

    }
}

