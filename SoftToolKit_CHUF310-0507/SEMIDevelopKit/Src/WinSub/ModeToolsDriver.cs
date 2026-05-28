using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.IO;
using System.Runtime.InteropServices;

namespace SEMIDevelopKit.Src.WinSub
{
    public enum DrvAssistType
    {
        MakeUDP = 0,
        CleanUp = 1,
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public class chsc_updfile_header
    {
        public uint sig;
        public ushort rc_burn_len;
        public ushort rc_short_len;
        public uint n_cfg;
        public uint n_match;
        public uint len_cfg;
        public uint len_boot;
        public void Clear()
        {
            rc_burn_len = 0;
            rc_short_len = 0;
            n_cfg = 0;
            n_match = 0;
            len_cfg = 0;
            len_boot = 0;
        }
    }
    public partial class ModeTools
    {
        private byte[] packetContent1 = new byte[50];
        private byte[] packetContent2 = new byte[400 * 1024];
        private byte[] packetContent3 = new byte[400 * 1024];
        private byte[] packetContent4 = new byte[10 * 1024];
        private string mAssistPath = "";
        private string mVidPid = "";
        private chsc_updfile_header mHeader = new chsc_updfile_header();

        private string drvAssistTips = "";
        public string DrvAssistTips
        {
            get { return drvAssistTips; }
            set { drvAssistTips = value; OnPropertyChanged("DrvAssistTips"); }
        }

        private DrvAssistType curSelAssist = DrvAssistType.MakeUDP;
        public DrvAssistType CurSelAssist
        {
            get { return curSelAssist; }
            set { if (value != curSelAssist) { curSelAssist = value; OnPropertyChanged("CurSelAssist"); } }
        }

        private Boolean burnCheck = false;
        public Boolean BurnCheck
        {
            get { return burnCheck; }
            set { if (burnCheck != value) { burnCheck = value; if (burnCheck) ShortCheck = false; OnPropertyChanged("BurnCheck"); } }
        }

        private Boolean shortCheck = false;
        public Boolean ShortCheck
        {
            get { return shortCheck; }
            set { if (shortCheck != value) { shortCheck = value; if (shortCheck) BurnCheck = false; OnPropertyChanged("ShortCheck"); } }
        }

        private Boolean multiVendorCheck = false;
        public Boolean MultiVendorCheck
        {
            get { return multiVendorCheck; }
            set { if (multiVendorCheck != value) { multiVendorCheck = value; OnPropertyChanged("MultiVendorCheck"); } }
        }

        private Boolean expandPid_Vid = false;
        public Boolean ExpandPid_Vid
        {
            get { return expandPid_Vid; }
            set { if (expandPid_Vid != value) { expandPid_Vid = value; OnPropertyChanged("ExpandPid_Vid"); } }
        }

        private string BytesToString(byte[] bytes, int len, ref int ipos)
        {
            StringBuilder szTemp = new StringBuilder();
            for (int index = 0; index < (int)len; index++)
            {
                szTemp.Append(string.Format("0x{0:X2},", bytes[index]));
                if ((ipos > 0) && ((ipos + 1) % 16) == 0)
                {
                    szTemp.Append("\r\n");
                }
                ipos++;
            }
            return szTemp.ToString();
        }

        public void AssistGenPacket()
        {
            try
            {
                SMCheckTools.StructToBytes(mHeader, packetContent1);

                string binPath = mAssistPath + "\\chsc_auto_update_packet.bin";
                if (MultiVendorCheck) binPath = mAssistPath +"\\chsc_auto_update_packet_" + mVidPid + ".bin";
                using (FileStream fs = new FileStream(binPath, FileMode.Create))
                {
                    fs.SetLength(0);
                    int headerlen = 0;
                    if (ExpandPid_Vid)
                    {
                        headerlen = (int)(Marshal.SizeOf(mHeader) + 8 * mHeader.n_cfg);
                    }
                    else
                    {
                        headerlen = (int)(Marshal.SizeOf(mHeader) + 4 * mHeader.n_cfg);
                    }
                    fs.Write(packetContent1, 0, headerlen);
                    fs.Write(packetContent2, 0, (int)mHeader.len_cfg);
                    fs.Write(packetContent3, 0, (int)mHeader.len_boot);

                    if (mHeader.rc_burn_len > 0)
                    {
                        fs.Write(packetContent4, 0, (int)mHeader.rc_burn_len);
                    }
                    if (mHeader.rc_short_len > 0)
                    {
                        fs.Write(packetContent4, (int)mHeader.rc_burn_len, (int)mHeader.rc_short_len);
                    }

                    fs.Close();
                }

                string txtPath = mAssistPath + "\\fw_update_packet.h";
                if (MultiVendorCheck)  txtPath = mAssistPath + "\\fw_update_packet_" + mVidPid + ".h";
                using (StreamWriter sw = new StreamWriter(txtPath, false, Encoding.Default))
                {
                    int posix = 0;

                    string udp_name = "upd_data";
                    //sw.Write("static const unsigned char upd_data[] = {\r\n");
                    if (MultiVendorCheck) udp_name = "upd_data_" + mVidPid;

                    sw.Write(string.Format("static const unsigned char {0}[] = {{\r\n", udp_name));
                    int headerlen = 0;
                    if (ExpandPid_Vid)
                    {
                        headerlen = (int)(Marshal.SizeOf(mHeader) + 8 * mHeader.n_cfg);
                    }
                    else
                    {
                        headerlen = (int)(Marshal.SizeOf(mHeader) + 4 * mHeader.n_cfg);
                    }
                    sw.Write(BytesToString(packetContent1, headerlen, ref posix));
                    sw.Write(BytesToString(packetContent2, (int)mHeader.len_cfg, ref posix));
                    sw.Write(BytesToString(packetContent3, (int)mHeader.len_boot, ref posix));
                    sw.Write("\r\n};\r\n\r\n");

                    //if (MultiVendorCheck)
                    //    sw.Write(string.Format("static struct bin_code_chain   fw_{0} = {{1}, sizeof({2}), firmware_chain_header}};"), "upd_data_" + mVidPid, "upd_data_" + mVidPid, "upd_data_" + mVidPid);
                    //else
                    //    sw.Write("static const unsigned char upd_data[] = {\r\n");

                    sw.WriteLine("#ifdef firmware_chain_header");
                    sw.WriteLine(string.Format("static struct bin_code_chain   fw_{0} = {{{1}, sizeof({2}), firmware_chain_header}};", udp_name, udp_name, udp_name));
                    sw.WriteLine("#else");
                    sw.WriteLine(string.Format("static struct bin_code_chain   fw_{0} = {{{1}, sizeof({2}), NULL}};", udp_name, udp_name, udp_name));
                    sw.WriteLine("#endif\r\n");
                    sw.WriteLine("#undef  firmware_chain_header");
                    sw.WriteLine(string.Format("#define firmware_chain_header  &fw_{0}", udp_name));

                    sw.Flush();
                    sw.Close();
                }

                mVidPid = "";
                mAssistPath = "";
                DrvAssistTips = "";
                mHeader.Clear();
                BurnCheck = false;
                ShortCheck = false;

            }
            catch (Exception ex)
            {
                ex.ToString();
            }
        }

        public void OnAssist(string path)
        {
            if (DrvAssistType.MakeUDP == CurSelAssist)
            {
                MakeUpdatePacket(path);
            }
            else if (DrvAssistType.CleanUp == CurSelAssist)
            {

            }
        }

        private byte[] GetVidPid(byte[] cfg, int len)
        {
            byte[] vid_pid = new byte[8];

            if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5816, MainViewModel.Intr.SelectedIC))
            {
                byte[] configContent = new byte[256];
                ushort cfgAddr = (ushort)((cfg[0x39] << 8) + cfg[0x38]);
                Array.Copy(cfg, cfgAddr, configContent, 0, configContent.Length);
                if (0 == SMCheckTools.CaculateCheckSumU16(configContent, (uint)configContent.Length))
                {
                    Array.Copy(configContent, 1, vid_pid, 0, 5);

                    ushort vid = (ushort)((vid_pid[0x04] << 8) + vid_pid[0x03]);

                    if (!ExpandPid_Vid) vid = (ushort)(vid & 0x00ff);

                    ushort pid = (ushort)((vid_pid[0x02] << 8) + vid_pid[0x01]);
                    byte ver = vid_pid[0x00];

                    DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                    DrvAssistTips += string.Format("vid = {0:D}, pid = {1:D}, ver = 0x{2:X}\r\n", vid, pid, ver);
                    mVidPid = string.Format("v0x{0:x}_p0x{1:x}", vid, pid);
                }
            }
            else if (eChipTypeList.CLR_IC_TYPE_MCAP == eChipTypeList.GetSubType(MainViewModel.Intr.SelectedIC))
            {
                Array.Copy(cfg, 1, vid_pid, 0, 5);

                ushort vid = (ushort)((vid_pid[0x04] << 8) + vid_pid[0x03]);

                if (!ExpandPid_Vid) vid = (ushort)(vid & 0x00ff);

                ushort pid = (ushort)((vid_pid[0x02] << 8) + vid_pid[0x01]);
                byte ver = vid_pid[0x00];

                DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                DrvAssistTips += string.Format("vid = {0:D}, pid = {1:D}, ver = 0x{2:X}\r\n", vid, pid, ver);
                mVidPid = string.Format("v0x{0:x}_p0x{1:x}", vid, pid);
            }
            else
            {
                Array.Copy(cfg, 0, vid_pid, 0, 4);

                byte vid = (byte)((vid_pid[1] & 0xFE) >> 1);
                ushort pid = (ushort)(((vid_pid[0x01] & 0x01) << 8) + vid_pid[0x00]);
                byte ver = (byte)((vid_pid[0x03] & 0xFC) >> 2);

                DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                DrvAssistTips += string.Format("vid = {0:D}, pid = {1:D}, ver = 0x{2:X}\r\n", vid, pid, ver);
                mVidPid = string.Format("v0x{0:x}_p0x{1:x}", vid, pid);
            }



            return vid_pid;
        }

        private void GetBootVersion(byte[] boot, int len)
        {
            if (eChipTypeList.CLR_IC_TYPE_MCAP == eChipTypeList.GetSubType(MainViewModel.Intr.SelectedIC))
            {
                if ((eChipTypeList.SM_IC_5562 == (MainViewModel.Intr.SelectedIC)) || (eChipTypeList.SM_IC_570 == (MainViewModel.Intr.SelectedIC)))
                {
                    ushort flag = (ushort)((boot[0x33] << 8) + boot[0x32]);
    
                    ushort bootVer = flag == 0x6274 ? (ushort)((boot[0x3f + 0x2000] << 8) + boot[0x3e + 0x2000]) : (ushort)((boot[0x3f] << 8) + boot[0x3e]);
                                        
                    DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                    DrvAssistTips += string.Format("boot len = {0:D}, version = 0x{1:X}\r\n", len, bootVer);

                    DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                    DrvAssistTips += "boot add success...\r\n";

                }
                else
                {
                    ushort bootVer = (ushort)((boot[0x3f] << 8) + boot[0x3e]);
                    DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                    DrvAssistTips += string.Format("boot len = {0:D}, version = 0x{1:X}\r\n", len, bootVer);

                    DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                    DrvAssistTips += "boot add success...\r\n";
                }

            }
            else
            {
                ushort bootVer = (ushort)((boot[0x05] << 8) + boot[0x04]);
                uint check_sum = SMCheckTools.CaculateCheckSumEx(packetContent3, mHeader.len_boot);

                DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                DrvAssistTips += string.Format("boot len = {0:D}, version = 0x{1:X}, checksum = 0x{2:X}\r\n", len, bootVer, check_sum);

                packetContent3[mHeader.len_boot++] = (byte)(check_sum >> 0);
                packetContent3[mHeader.len_boot++] = (byte)(check_sum >> 8);
                packetContent3[mHeader.len_boot++] = (byte)(check_sum >> 16);
                packetContent3[mHeader.len_boot++] = (byte)(check_sum >> 24);

                DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                DrvAssistTips += "boot add success...\r\n";
            }
        }

        private void MakeUpdateConfig(byte[] tempContent, long binFileLen)
        {
            bool areayExist = mHeader.n_cfg > 0;
            int stp = 0;
            for (int cnt = 0; cnt < mHeader.n_cfg; cnt++)
            {
                areayExist = true;
                for (int index = 0; index < 4/*binFileLen*/; index++)
                {
                    if (packetContent2[stp + index] != tempContent[index])
                    {
                        areayExist = false;
                        break;
                    }
                }
                stp += (int)binFileLen;
                if (areayExist) break;
            }
            if (!areayExist)
            {
                byte[] vid_pid_ver = GetVidPid(tempContent, 4);

                if (ExpandPid_Vid)
                {
                    Array.Copy(vid_pid_ver, 0, packetContent1, Marshal.SizeOf(mHeader) + mHeader.n_cfg * 8, 8);
                }
                else
                {
                    Array.Copy(vid_pid_ver, 0, packetContent1, Marshal.SizeOf(mHeader) + mHeader.n_cfg * 4, 4);
                }
                mHeader.n_cfg++;
                mHeader.n_match++;
                mHeader.len_cfg += (uint)binFileLen;
                //mHeader.match = (uint)((vid_pid_ver[3] << 24) + (vid_pid_ver[2] << 16) + (vid_pid_ver[1] << 8) + (vid_pid_ver[0] << 0));
                Array.Copy(tempContent, 0, packetContent2, stp, binFileLen);

                //AssistGenPacket(fileInfo.DirectoryName, mHeader);
            }
            else
            {
                DrvAssistTips += eChipTypeList.GetIcName(MainViewModel.Intr.SelectedIC) + "\t";
                DrvAssistTips += "config aready exist!!!\r\n";
            }
        }

        private void MakeUpdatePacket(string path)
        {
            try
            {
                //SMCheckTools.BytesToStruct(mHeader, packetContent1);
                mHeader.sig = 0x43534843;
                //mHeader.resv = 0;

                FileInfo fileInfo = new FileInfo(path);
                long binFileLen = fileInfo.Length;
                mAssistPath = fileInfo.DirectoryName;
                using (FileStream fs = new FileStream(path, FileMode.Open))
                {
                    byte[] tempContent = new byte[binFileLen];
                    fs.Read(tempContent, 0, (int)binFileLen);
                    fs.Flush();
                    fs.Close();

                    if (BurnCheck)
                    {
                        mHeader.rc_burn_len = (ushort)tempContent.Length;
                        Array.Copy(tempContent, 0, packetContent4, 0, tempContent.Length);
                        DrvAssistTips += "burn ramcode code add success...\r\n";
                    }
                    else if (ShortCheck)
                    {
                        mHeader.rc_short_len = (ushort)tempContent.Length;
                        Array.Copy(tempContent, 0, packetContent4, mHeader.rc_burn_len, tempContent.Length);
                        DrvAssistTips += "short ramcode code add success...\r\n";
                    }
                    else
                    {
                        if (binFileLen <= 512 && 0 == SMCheckTools.CaculateCheckSumU16(tempContent, (uint)binFileLen))
                        {
                            MakeUpdateConfig(tempContent, binFileLen);
                        }
                        else if (binFileLen > 512)
                        {
                            if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5816, MainViewModel.Intr.SelectedIC))
                            {
                                //5816 boot config merge
                                uint crc = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(tempContent, (uint)binFileLen - 4);
                                uint crcFile = (uint)((tempContent[binFileLen - 1] << 24) + (tempContent[binFileLen - 2] << 16) + (tempContent[binFileLen - 3] << 8) + (tempContent[binFileLen - 4] << 0));
                                if (crc == crcFile)
                                {
                                    MakeUpdateConfig(tempContent, binFileLen);
                                }
                                else
                                {
                                    DrvAssistTips += "invalid bin file!!!\r\n";
                                }
                            }
                            else if (binFileLen == 2 * 1024 && (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5562, MainViewModel.Intr.SelectedIC)|| (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_570, MainViewModel.Intr.SelectedIC))&& (0 == SMCheckTools.CaculateCheckSumU32(tempContent, (uint)binFileLen))))
                            {
                                MakeUpdateConfig(tempContent, binFileLen);
                            }
                            else if (eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5472, MainViewModel.Intr.SelectedIC) || eChipTypeList.IsSameKind(eChipTypeList.SM_IC_7449, MainViewModel.Intr.SelectedIC)
                                || eChipTypeList.IsSameKind(eChipTypeList.SM_IC_5562, MainViewModel.Intr.SelectedIC)
                                 || eChipTypeList.IsSameKind(eChipTypeList.SM_IC_570, MainViewModel.Intr.SelectedIC))
                            {
                                uint crc = SMInvokeBridge.SMCheckTools.CaculateCheckSumEx(tempContent, (uint)binFileLen - 4);
                                uint crcFile = (uint)((tempContent[binFileLen - 1] << 24) + (tempContent[binFileLen - 2] << 16) + (tempContent[binFileLen - 3] << 8) + (tempContent[binFileLen - 4] << 0));
                                if (crc == crcFile)
                                {
                                    mHeader.len_boot = (uint)binFileLen;
                                    Array.Copy(tempContent, packetContent3, binFileLen);

                                    GetBootVersion(packetContent3, (int)binFileLen);
                                    mAssistPath = fileInfo.DirectoryName;
                                }
                                else
                                {
                                    DrvAssistTips += "invalid bin file!!!\r\n";
                                }
                            }
                            else
                            {
                                ushort bootlen = (ushort)((tempContent[7] << 8) + tempContent[6]);
                                if (bootlen == binFileLen)
                                {
                                    mHeader.len_boot = (uint)binFileLen;
                                    Array.Copy(tempContent, packetContent3, binFileLen);

                                    GetBootVersion(packetContent3, (int)binFileLen);
                                    mAssistPath = fileInfo.DirectoryName;
                                }
                                else
                                {
                                    DrvAssistTips += "invalid bin file!!!\r\n";
                                }
                            }
                        }
                        else
                        {
                            DrvAssistTips += "fail to parse bin file!!!\r\n";
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                DrvAssistTips += ex.ToString();
                DrvAssistTips += "\r\n";
            }


            //             if (eChipTypeList.IsSameKind(MainViewModel.Intr.SelectedIC, eChipTypeList.SM_IC_5448))
            //             {
            // 
            //             }
        }
    }
}
