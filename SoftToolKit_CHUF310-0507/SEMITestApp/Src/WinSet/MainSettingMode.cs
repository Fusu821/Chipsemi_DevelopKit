using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMITestApp.Src.Util;
using System.Xml;
using System.Collections.ObjectModel;
using System.IO;
using Microsoft.Win32;
using SMInvokeBridge;
using SEMI.Util;
using System.Windows;

namespace SEMITestApp.Src.WinSet
{
    public class MainSettingMode : SettingMode
    {
        private string xmlPath = "";
        public string XMLPath
        {
            get { return xmlPath; }
            set { if (value != xmlPath) { xmlPath = value; OnPropertyChanged("XMLPath"); } }
        }

        private IList<SMDefinition> icLists = new List<SMDefinition>();
        public IList<SMDefinition> ICLists
        {
            get { return icLists; }
            set { if (icLists != value) { icLists = value; OnPropertyChanged("ICLists"); } }
        }

        public ushort SelectedIC
        {
            get { return selectedIC; }
            set
            {
                if (value != selectedIC)
                {
                    selectedIC = value;
                    OnPropertyChanged("SelectedIC");

                    if (eChipTypeList.IsSameKind(selectedIC, eChipTypeList.SM_IC_5816))
                    {
                        CfgVisible = Visibility.Hidden;
                    }
                    else
                    {
                        CfgVisible = Visibility.Visible;
                    }

                    chipInfo = SMChipInfoChipReflex.Instance.GetSemiModuleByChipAndType(SMChipInfoChipReflex.SEMI_TEST_MAIN_SET, selectedIC) as BinInformation;
                }
            }
        }

        private IList<HexValue<byte>> slaveAddrList = new List<HexValue<byte>>() 
        { 
            new HexValue<byte>(0x5c),
            new HexValue<byte>(0x70),
        };
        public IList<HexValue<byte>> SlaveAddrList
        {
            get { return slaveAddrList; }
            set { if (value != slaveAddrList) { slaveAddrList = value; OnPropertyChanged("SlaveAddrList"); } }
        }

        private byte slaveAddr = 0x5c;
        public byte SlaveAddr
        {
            get { return slaveAddr; }
            set { if (value != slaveAddr) { slaveAddr = value; OnPropertyChanged("SlaveAddr"); } }
        }

        public IList<SMDefinition> VddVoltageList
        {
            get
            {
                return new List<SMDefinition>()
                {
                    new SMDefinition(0x8E,   "3.6V"),
                    new SMDefinition(0x81,   "3.3V"),
                    new SMDefinition(0x76,   "3.0V"),
                    new SMDefinition(0x6E,   "2.8V"),
                    new SMDefinition(0x68,   "2.6V"),
                    new SMDefinition(0x47,   "1.8V"),
                };
            }
        }


        private ushort vddVotage = 0x6E;
        public ushort VddVotage
        {
            get { return vddVotage; }
            set
            {
                if (value != vddVotage)
                {
                    vddVotage = value;
                    OnPropertyChanged("VddVotage");
                }
            }
        }

        public IList<SMDefinition> AgentList
        {
            get
            {
                return new List<SMDefinition>()
                {
                    new SMDefinition(0x01,   "MTK"),
                    new SMDefinition(0x07,   "HID"),
                };
            }
        }

        private ushort agent = 0x01;
        public ushort Agent
        {
            get { return agent; }
            set
            {
                if (value != agent)
                {
                    agent = value;
                    SMCommBase.MtkBoardReBoot((uint)agent);
                    OnPropertyChanged("Agent");
                    CLRLinkParam linkParam = new CLRLinkParam();
                    linkParam.LinkType = (byte)(agent & 0x0F);
                    linkParam.szIpAddress = "127.0.0.1"; 

                    bool bConnected = ExportDeclares.CLRHalLinkAndDoInit(linkParam);
                    //if (bConnected) DeviceStates = new byte[] { 1, 0, 0, 0 };
                    //else DeviceStates = new byte[ExportDeclares.MAX_DEVICE_NUMS];

                    SMChipBase.SetICTypeAndCreateComponent(selectedIC);
                }
            }
        }

        public IList<SMDefinition> IoVddVoltageList
        {
            get
            {
                return new List<SMDefinition>()
                {
                    new SMDefinition(0x8E,   "3.6V"),
                    new SMDefinition(0x81,   "3.3V"),
                    new SMDefinition(0x76,   "3.0V"),
                    new SMDefinition(0x6E,   "2.8V"),
                    new SMDefinition(0x68,   "2.6V"),
                    new SMDefinition(0x47,   "1.8V"),
                    new SMDefinition(0x2f,   "1.2V"),
                };
            }
        }

        private ushort ioVddVotage = 0x47;
        public ushort IoVddVotage
        {
            get { return ioVddVotage; }
            set
            {
                if (value != ioVddVotage)
                {
                    ioVddVotage = value;
                    OnPropertyChanged("IoVddVotage");
                }
            }
        }

//         public IList<SMDefinition> VIHVoltageList
//         {
//             get
//             {
//                 return new List<SMDefinition>()
//                 {
//                     new SMDefinition(0x29,   "1.6V"),
//                     new SMDefinition(0x25,   "1.4V"),
//                     new SMDefinition(0x20,   "1.2V"),
//                 };
//             }
//         }

        private float vihVotage = 1.3f;
        public float VIHVotage
        {
            get { return vihVotage; }
            set
            {
                if (value != vihVotage)
                {
                    vihVotage = value;
                    OnPropertyChanged("VIHVotage");
                }
            }
        }

        private IList<SMDefinition> i2cSpeedList = new List<SMDefinition>()
        {
            new SMDefinition(1,   "50k"),
            new SMDefinition(2,   "100k"),
            new SMDefinition(3,   "200k"),
            new SMDefinition(4,   "300k"),
            new SMDefinition(5,   "400k"),
            new SMDefinition(6,   "1M"),
        };
        public IList<SMDefinition> I2CSpeedList
        {
            get { return i2cSpeedList; }
            set
            {
                if (value != i2cSpeedList)
                {
                    i2cSpeedList = value;
                    OnPropertyChanged("I2CSpeedList");
                }
            }
        }

        private ushort i2cSpeed = 5;
        public ushort I2CSpeed
        {
            get { return i2cSpeed; }
            set { if (value != i2cSpeed) { i2cSpeed = value; OnPropertyChanged("I2CSpeed"); } }
        }

        private IList<SMDefinition> spiSpeedList = new List<SMDefinition>()
        {
            new SMDefinition(0x0000,   "18M"),
            new SMDefinition((1 << 3), "9M"),
            new SMDefinition((2 << 3), "4.5M"),
            new SMDefinition((3 << 3), "2.25M"),
            new SMDefinition((4 << 3), "1.125M"),
        };

        public IList<SMDefinition> SPISpeedList
        {
            get { return spiSpeedList; }
            private set { }
        }

        private ushort spiSpeed = 3 << 3;
        public ushort SPISpeed
        {
            get { return spiSpeed; }
            set { if (value != spiSpeed) { spiSpeed = value; OnPropertyChanged("SPISpeed"); } }
        }

        private IList<SMDefinition> protocalList = new List<SMDefinition>()
        {
            new SMDefinition(0, "IIC"),
            new SMDefinition(1, "SPI"),
        };
        public IList<SMDefinition> ProtocalList
        {
            get { return protocalList; }
            set { if (protocalList != value) { protocalList = value; OnPropertyChanged("ProtocalList"); } }
        }

        //private ushort selectedProtocal = 0;
        public ushort SelectedProtocal
        {
            get { return selectedProtocal; }
            set
            {
                if (value != selectedProtocal)
                {
                    selectedProtocal = value;
                    OnPropertyChanged("SelectedProtocal");
                }
            }
        }


        public int StationIndex { get; set; }

        private ObservableCollection<string> workStationList = new ObservableCollection<string>();
        public ObservableCollection<string> WorkStationList
        {
            get { return workStationList; }
            set { if (value != workStationList) { workStationList = value; OnPropertyChanged("WorkStationList"); } }
        }

        private string flyoutStation = "";
        public string FlyoutStation
        {
            get { return flyoutStation; }
            set { if (value != null && value != flyoutStation) { flyoutStation = value.Trim(); OnPropertyChanged("FlyoutStation"); } }
        }

        //         public string flyoutSelected = "";
        //         public string FlyoutSelected
        //         {
        //             get { return flyoutSelected; }
        //             set { if (value != flyoutSelected) { flyoutSelected = value; OnPropertyChanged("FlyoutSelected"); } }
        //         }

        public string WorkStation
        {
            get { return workStation; }
            set { if (value != workStation) { workStation = value; OnPropertyChanged("WorkStation"); } }
        }

        private string projectName = "";
        public string ProjectName
        {
            get { return projectName; }
            set { if (value != projectName) { projectName = value; OnPropertyChanged("ProjectName"); } }
        }

        private string configBinPath = "";
        public string ConfigBinPath
        {
            get { return configBinPath; }
            set { if (value != configBinPath) { configBinPath = value; OnPropertyChanged("ConfigBinPath"); } }
        }

        private string bootBinPath = "";
        public string BootBinPath
        {
            get { return bootBinPath; }
            set { if (value != bootBinPath) { bootBinPath = value; OnPropertyChanged("BootBinPath"); } }
        }

        private uint bootCrc = 0;
        public uint BootCrc
        {
            get { return bootCrc; }
            set { if (bootCrc != value) { bootCrc = value; OnPropertyChanged("BootCrc"); } }
        }

        private uint bootLoaderCrc = 0;
        public uint BootLoaderCrc
        {
            get { return bootLoaderCrc; }
            set { if (bootLoaderCrc != value) { bootLoaderCrc = value; OnPropertyChanged("BootLoaderCrc"); } }
        }

        private uint configCrc = 0;
        public uint ConfigCrc
        {
            get { return configCrc; }
            set { if (configCrc != value) { configCrc = value; OnPropertyChanged("ConfigCrc"); } }
        }

        private ushort workClk = 0x2602;
        public ushort WorkClk
        {
            get { return workClk; }
            set { if (value != workClk) { workClk = value; OnPropertyChanged("WorkClk"); } }
        }

        private bool filteroff = false;
        public bool FilterOff
        {
            get { return filteroff; }
            set { if (value != filteroff) { filteroff = value; OnPropertyChanged("FilterOff"); } }
        }

        private bool usrDef = false;
        public bool UsrDef
        {
            get { return usrDef; }
            set { if (value != usrDef) { usrDef = value; OnPropertyChanged("UsrDef"); } }
        }

        private ushort xPixel = 0;
        public ushort XPixel
        {
            get { return xPixel; }
            set { if (value != xPixel) { xPixel = value; OnPropertyChanged("XPixel"); } }
        }

        private ushort yPixel = 0;
        public ushort YPixel
        {
            get { return yPixel; }
            set { if (value != yPixel) { yPixel = value; OnPropertyChanged("YPixel"); } }
        }

        public int Rows
        {
            get { return rows; }
            set { if (value != rows) { rows = value; OnPropertyChanged("Rows"); } }
        }

        public int Cols
        {
            get { return cols; }
            set { if (value != cols) { cols = value; OnPropertyChanged("Cols"); } }
        }

        private Visibility cfgVisible = Visibility.Visible;
        public Visibility CfgVisible
        {
            get { return cfgVisible; }
            set { if (value != cfgVisible) { cfgVisible = value; OnPropertyChanged("CfgVisible"); } }
        }

//         private uint standardTicks = 60 * 1000;
//         public uint StandardTicks
//         {
//             get { return standardTicks; }
//             set { if (value != standardTicks) { standardTicks = value; OnPropertyChanged("StandardTicks"); } }
//         }

        private ushort va_Width = 1;
        public ushort VA_Width
        {
            get { return va_Width; }
            set { if (value != va_Width) { va_Width = value; OnPropertyChanged("VA_Width"); } }
        }

        private ushort x_Pitch = 1;
        public ushort X_Pitch
        {
            get { return x_Pitch; }
            set { if (value != x_Pitch) { x_Pitch = value; OnPropertyChanged("X_Pitch"); } }
        }

        private ushort x_Row = 1;
        public ushort X_Row
        {
            get { return x_Row; }
            set { if (value != x_Row) { x_Row = value; OnPropertyChanged("X_Row"); } }
        }

        private ushort va_Height = 1;
        public ushort VA_Height
        {
            get { return va_Height; }
            set { if (value != va_Height) { va_Height = value; OnPropertyChanged("VA_Height"); } }
        }

        private ushort y_Pitch = 1;
        public ushort Y_Pitch
        {
            get { return y_Pitch; }
            set { if (value != y_Pitch) { y_Pitch = value; OnPropertyChanged("Y_Pitch"); } }
        }

        private ushort y_Col = 1;
        public ushort Y_Col
        {
            get { return y_Col; }
            set { if (value != y_Col) { y_Col = value; OnPropertyChanged("Y_Col"); } }
        }

        public MainSettingMode()
        {
            byte icType = eChipTypeList.CLR_IC_TYPE_ALL;
            int count = eChipTypeList.Count(icType);
            for (int index = 0; index < count; index++)
            {
                SMDefinition node = new SMDefinition(eChipTypeList.GetIcCodeByIndex(index, icType), eChipTypeList.GetIcNameByIndex(index, icType));
                icLists.Add(node);
            }

            bool bOK = LoadXml(GetWorkPath() + "config\\semichip_ctp_config.xml");

            if (bOK)
            {
                ResolveXmlSetting();
            }
            else
            {
                CreateNewXmlDoc();
            }
        }

        public void BootToView()
        {
            if (!File.Exists(GetWorkPath() + BootBinPath)) return;
            if (null == bootContent)
            {
                FileInfo fileInfo = new FileInfo(GetWorkPath() + BootBinPath);
                long binFileLen = fileInfo.Length;
                bootContent = new byte[binFileLen];
                using (FileStream fs = new FileStream(GetWorkPath() + BootBinPath, FileMode.Open))
                {
                    fs.Read(bootContent, 0, (int)binFileLen);
                    fs.Flush();
                    fs.Close();
                }
            }

            if (CheckBootValidation())
            {
                chipInfo.BootToView(this, bootContent);
            }
        }

        public void CfgToView()
        {
            if (!File.Exists(GetWorkPath() + ConfigBinPath)) return;
            if (null == cfgContent)
            {
                FileInfo fileInfo = new FileInfo(GetWorkPath() + ConfigBinPath);
                long binFileLen = fileInfo.Length;
                cfgContent = new byte[binFileLen];
                using (FileStream fs = new FileStream(GetWorkPath() + ConfigBinPath, FileMode.Open))
                {
                    fs.Read(cfgContent, 0, (int)binFileLen);
                    fs.Flush();
                    fs.Close();
                }
            }

            if (CheckCfgValidation())
            {
                chipInfo.CfgToView(this, cfgContent);
            }
        }

        public override void XMLDataToView()
        {
            string selectedIcName = GetXmlAttrbuteString(xml, "semitester", "ic_type", "CHSC6440");
            SelectedIC = eChipTypeList.GetIcCode(selectedIcName);

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");

            WorkStationList.Clear();
            for (int index = 0; index < 20; index++)
            {
                string workstations = String.Format("{0}_{1}", "station", index);
                string ws = GetXmlAttrbuteString(smTesterNode, "stations", workstations);
                if (string.IsNullOrEmpty(ws)) break;

                WorkStationList.Add(ws);
            }

            SelectedProtocal = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "protocal", 0);
            VddVotage = (byte)GetXmlAttrbuteValue(smTesterNode, "common", "vdd_votage", 0x6E);
            IoVddVotage = (byte)GetXmlAttrbuteValue(smTesterNode, "common", "iovdd_votage", 0x47);

            Agent = (byte)GetXmlAttrbuteValue(smTesterNode, "common", "agent", 0x01);

            VIHVotage = (float)GetXmlAttrbuteFloatValue(smTesterNode, "common", "vih_votage", 1.3f);
            I2CSpeed = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "i2c_speed", 5);
            SPISpeed = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "spi_speed", 3 << 3);

            SlaveAddr = (byte)GetXmlAttrbuteValue(smTesterNode, "common", "i2c_addr", 0x5c);
            WorkStation = GetXmlAttrbuteString(smTesterNode, "common", "work_station");
            ProjectName = GetXmlAttrbuteString(smTesterNode, "common", "project_name");
            ConfigBinPath = GetXmlAttrbuteString(smTesterNode, "common", "configure_bin");
            BootBinPath = GetXmlAttrbuteString(smTesterNode, "common", "boot_bin");

            BootCrc = (uint)GetXmlAttrbuteValue(smTesterNode, "firmware", "boot_crc");
            BootLoaderCrc = (uint)GetXmlAttrbuteValue(smTesterNode, "firmware", "boot_loader_crc");
            ConfigCrc = (uint)GetXmlAttrbuteValue(smTesterNode, "firmware", "config_crc");
            WorkClk = (ushort)GetXmlAttrbuteValue(smTesterNode, "firmware", "w_clk", 0x2602);
            FilterOff = GetXmlAttrbuteValue(smTesterNode, "firmware", "filter_off", 0) > 0;
            Rows = GetXmlAttrbuteValue(smTesterNode, "firmware", "rows", 0);
            Cols = GetXmlAttrbuteValue(smTesterNode, "firmware", "cols", 0);
            UsrDef = GetXmlAttrbuteValue(smTesterNode, "firmware", "usr_def", 0) > 0;

            VA_Width = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "VA_Width", 1);
            X_Pitch = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "X_Pitch", 1);

            VA_Height = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "VA_Height", 1);
            Y_Pitch = (ushort)GetXmlAttrbuteValue(smTesterNode, "common", "Y_Pitch", 1);

            X_Row = X_Pitch == 0 ? (ushort)0 : (ushort)(VA_Width / X_Pitch);
            Y_Col = Y_Pitch == 0 ? (ushort)0 : (ushort)(VA_Height / Y_Pitch);

            //boot bin
            BootToView();

            //cfg bin
            CfgToView();
        }

        public override void ViewToXMLData()
        {
            SaveXmlAttrbuteString(xml, "semitester", "ic_type", eChipTypeList.GetIcName(SelectedIC));
            //if (string.IsNullOrEmpty(WorkStation)) 

            XmlNode smTesterNode = xml.SelectSingleNode("semitester");

            XmlNode stationNode = smTesterNode.SelectSingleNode("stations");
            if (null != stationNode) smTesterNode.RemoveChild(stationNode);
            for (int index = 0; index < WorkStationList.Count; index++)
            {
                string workstations = String.Format("{0}_{1}", "station", index);
                SaveXmlAttrbuteString(smTesterNode, "stations", workstations, WorkStationList[index]);
            }

            SaveXmlAttrbuteValue(smTesterNode, "common", "protocal", SelectedProtocal);
            SaveXmlAttrbuteValue(smTesterNode, "common", "vdd_votage", VddVotage, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "common", "agent", Agent, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "common", "iovdd_votage", IoVddVotage, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "common", "vih_votage", VIHVotage);

            SaveXmlAttrbuteValue(smTesterNode, "common", "i2c_speed", I2CSpeed);
            SaveXmlAttrbuteValue(smTesterNode, "common", "spi_speed", SPISpeed);

            SaveXmlAttrbuteValue(smTesterNode, "common", "i2c_addr", SlaveAddr, "0x{0:X}");
            SaveXmlAttrbuteString(smTesterNode, "common", "work_station", WorkStation);
            SaveXmlAttrbuteString(smTesterNode, "common", "project_name", ProjectName);
            SaveXmlAttrbuteString(smTesterNode, "common", "configure_bin", ConfigBinPath);
            SaveXmlAttrbuteString(smTesterNode, "common", "boot_bin", BootBinPath);

            SaveXmlAttrbuteValue(smTesterNode, "firmware", "boot_crc", (int)BootCrc, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "firmware", "boot_loader_crc", (int)BootLoaderCrc, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "firmware", "config_crc", (int)ConfigCrc, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "firmware", "w_clk", WorkClk, "0x{0:X}");
            SaveXmlAttrbuteValue(smTesterNode, "firmware", "rows", Rows);
            SaveXmlAttrbuteValue(smTesterNode, "firmware", "cols", Cols);
            SaveXmlAttrbuteValue(smTesterNode, "firmware", "usr_def", UsrDef ? 1: 0);
            //SaveXmlAttrbuteValue(smTesterNode, "firmware", "standard_ticks", (int)StandardTicks);

            SaveXmlAttrbuteValue(smTesterNode, "common", "VA_Width", VA_Width);
            SaveXmlAttrbuteValue(smTesterNode, "common", "X_Pitch", X_Pitch);
            SaveXmlAttrbuteValue(smTesterNode, "common", "VA_Height", VA_Height);
            SaveXmlAttrbuteValue(smTesterNode, "common", "Y_Pitch", Y_Pitch);

            if (null == smTesterNode.SelectSingleNode(WorkStation))
            {
                XmlNode stNode = xml.CreateElement(WorkStation);
                smTesterNode.AppendChild(stNode);
            }

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }

        private IDictionary<string, Action<MainSettingMode>> mapAct = new Dictionary<string, Action<MainSettingMode>>()
        {
            {
                "load-config-click", new Action<MainSettingMode>((t) =>
                {
                    OpenFileDialog dlg = new OpenFileDialog();
                    dlg.DefaultExt = ".xml";
                    dlg.Filter = "XML documents (.xml)|*.xml";
                    Nullable<bool> result = dlg.ShowDialog();

                    if (true == result)
                    {
                        LoadXml(dlg.FileName);
                        SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
                    }

                    t.XMLDataToView();
                })
            },

            {
                "maintain-station-click", new Action<MainSettingMode>((t) =>
                {
                    SettingFrame.ExternInterface.ShowFlyout(t);
                })
            },

            {
                "add-station-click", new Action<MainSettingMode>((t) =>
                {
                    if (!String.IsNullOrEmpty(t.FlyoutStation) && !t.WorkStationList.Contains(t.FlyoutStation))
                    {
                        t.WorkStationList.Add(t.FlyoutStation);
                        t.FlyoutStation = "";
                    }
                })
            },

            {
                "delete-station-click", new Action<MainSettingMode>((t) =>
                {
                    if (!String.IsNullOrEmpty(t.FlyoutStation))
                    {
                        t.WorkStationList.Remove(t.FlyoutStation);

                        XmlNode smTesterNode = xml.SelectSingleNode("semitester");
                        XmlNode rmNode = smTesterNode.SelectSingleNode(t.FlyoutStation);
                        if (null != rmNode)
                        {
                            smTesterNode.RemoveChild(rmNode);
                        }
                        t.FlyoutStation = "";
                    } 
                })
            },

            {
                "edit-station-click", new Action<MainSettingMode>((t) =>
                {
                    if (!String.IsNullOrEmpty(t.FlyoutStation))
                    {
                        int rmIter = t.StationIndex;
                        string cgStation = t.FlyoutStation;
                        if (t.StationIndex >= 0 && t.StationIndex < t.WorkStationList.Count())
                        {
                            string station = t.WorkStationList.ElementAt(rmIter);
                            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
                            XmlNode rmNode = smTesterNode.SelectSingleNode(station);
                            if (null != rmNode)
                            {
                                XmlNode stNode = xml.CreateElement(cgStation);
                                for (int index = 0; index < rmNode.ChildNodes.Count; index++)
                                {
                                    stNode.AppendChild(rmNode.ChildNodes.Item(index));
                                }
                                smTesterNode.RemoveChild(rmNode);
                                smTesterNode.AppendChild(stNode);

                                t.WorkStationList.RemoveAt(rmIter);
                                t.WorkStationList.Insert(rmIter, cgStation);

                                if (null == t.WorkStation)
                                {
                                    t.WorkStation = cgStation;
                                }
                            }
                        }
                    } 
                })
            },

            {
                "load-bootbin-click", new Action<MainSettingMode>((t) =>
                {
                    OpenFileDialog dlg = new OpenFileDialog();
                    dlg.DefaultExt = ".bin";
                    dlg.Filter = "bin documents (.bin)|*.bin";
                    Nullable<bool> result = dlg.ShowDialog();

                    if (true == result)
                    {
                        FileInfo fileInfo = new FileInfo(dlg.FileName);
                        long binFileLen = fileInfo.Length;
                        using (FileStream fs = new FileStream(dlg.FileName, FileMode.Open))
                        {
                            bootContent = new byte[binFileLen];
                            fs.Read(bootContent, 0, (int)binFileLen);
                            fs.Flush();
                            fs.Close();
                        }

                        string catPath = String.Format("{0}{1}_{2}_boot.bin", "user/", eChipTypeList.GetIcName(t.SelectedIC), t.ProjectName);
                        t.BootBinPath = catPath;

                        if (false == System.IO.Directory.Exists(GetWorkPath() + "user/"))
                            System.IO.Directory.CreateDirectory(GetWorkPath() + "user/");
                        using (FileStream fs = new FileStream(GetWorkPath() + catPath, FileMode.Create))
                        {
                            fs.Write(bootContent, 0, bootContent.Length);
                            fs.Flush();
                            fs.Close();
                        }

                        t.BootToView();

//                         if (CheckBootValidation())
//                         {
//                              
//                         }
                    }
                })
            },

             {
                "load-cfgbin-click", new Action<MainSettingMode>((t) =>
                {
                    OpenFileDialog dlg = new OpenFileDialog();
                    dlg.DefaultExt = ".bin";
                    dlg.Filter = "bin documents (.bin)|*.bin";
                    Nullable<bool> result = dlg.ShowDialog();

                    if (true == result)
                    {
                        FileInfo fileInfo = new FileInfo(dlg.FileName);
                        long binFileLen = fileInfo.Length;
                        using (FileStream fs = new FileStream(dlg.FileName, FileMode.Open))
                        {
                            cfgContent = new byte[binFileLen];
                            fs.Read(cfgContent, 0, (int)binFileLen);
                            fs.Flush();
                            fs.Close();
                        }

                        string catPath = String.Format("{0}{1}_{2}_cfg.bin", "user/", eChipTypeList.GetIcName(t.SelectedIC), t.ProjectName);
                        t.ConfigBinPath = catPath;

                        if (false == System.IO.Directory.Exists(GetWorkPath() + "user/"))
                            System.IO.Directory.CreateDirectory(GetWorkPath() + "user/");
                        using (FileStream fs = new FileStream(GetWorkPath() + catPath, FileMode.Create))
                        {
                            fs.Write(cfgContent, 0, cfgContent.Length);
                            fs.Flush();
                            fs.Close();
                        }

                        t.CfgToView();

//                         if (CheckCfgValidation())
//                         {
//                             
//                         }
                    }
                })
            },
        };

        public override void ResolveXmlSetting()
        {
            //XMLPath = xml.BaseURI.Replace("file:///", "");

            XmlNode root = xml.SelectSingleNode("semitester");

            if (null != root.Attributes["ic_type"])
            {
                string selectedIcName = root.Attributes["ic_type"].Value;
                SelectedIC = ICLists.FirstOrDefault((t) => { return t.TypeName == selectedIcName ? true : false; }).TypeVal;
            }
        }

        public override void ResolveCfgSetting()
        {

        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;
            if (!mapAct.ContainsKey(strParam)) return;

            //ViewToXMLData();

            try
            {
                mapAct[strParam].Invoke(this);
            }
            catch (Exception ex)
            {
                ex.ToString();
            }

            //ResolveXmlSetting();

            //XMLDataToView();
        }
    }

    public partial class SMChipInfoChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexScapBinInformation()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3535, "SEMITestApp.Src.WinSet.ScapBinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3536, "SEMITestApp.Src.WinSet.ScapBinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
        }
    }
    public class ScapBinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent)
        {
            //wasim
            //return 4;
            if (null == cfgContent) return 0;
            if (cfgContent.Length < 204) return 0;

            //huawei special case 
            if (7 == (cfgContent[0x6B] >> 4)) return 6;

            BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            if (tp_chain.Bit(3))
            {
                return 4;
            }
            else
            {
                return 2;
            }
        }

        public override int GetCols(byte[] cfgContent)
        {
            //wasim 
            //return 10;
            if (null == cfgContent) return 0;
            if (cfgContent.Length < 204) return 0;

            //huawei special case 
            if (7 == (cfgContent[0x6B] >> 4)) return 6;

            BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            if (tp_chain.Bit(3))
            {
                return (tp_chain.MaskValue(0xf300) >> 10) >> 2;
            }
            else
            {
                return (tp_chain.MaskValue(0x03f0) >> 4) >> 1;
            }
        }

        public override int GetRefs(byte[] cfgContent)
        {
            BitValue tp_chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
            int vaChannel = tp_chain.MaskValue(0x3f0) >> 4;
            int realChannel = tp_chain.MaskValue(0xfc00) >> 10;
            return realChannel - vaChannel;
        }

        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valided = true;
            if (null != bootContent)
            {
                ushort bootLen = (ushort)((bootContent[7] << 8) + bootContent[6]);
                if (bootContent.Length != bootLen)
                {
                    valided = false;
                    MessageBox.Show("boot file lengh is invalid");
                }
            }
            else
            {
                valided = false;
                MessageBox.Show("boot file lengh is invalid");
            }

            return valided;
        }

        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valided = true;

            if (null != cfgContent)
            {
                int len = cfgContent.Length;
                if (len > 256) valided = false;
                if (len < 64) valided = false;
                if ((len & 1) > 0) valided = false;

                ushort checkSum = 0;
                int haftLen = len >> 1;
                for (int index = 0; index < haftLen; index++)
                {
                    checkSum += (ushort)((cfgContent[index * 2 + 1] << 8) + cfgContent[index * 2 + 0]);
                }

                if (checkSum != 0) valided = false;
            }
            else
            {
                valided = false;
            }

            if (!valided)
            {
                MessageBox.Show("cfg file is invalid");
            }

            return valided;
        }

        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
                mode.ConfigCrc = SettingMode.CaculateCheckSumEx(cfgContent, cfgLen);

                BitValue misc = new BitValue((cfgContent[57 * 2 + 1] << 8) + cfgContent[57 * 2 + 0]);
                BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
                BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

                //swap xy
                if (misc.Bit(3))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                BitValue chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
                SettingMode.keyNum = chain.MaskValue(0x07);
                SettingMode.keyThr = cfgContent[48 * 2 + 1];
                //9 keys... very important
                int vaChannel = chain.MaskValue(0x3f0) >> 4;
                int realChannel = chain.MaskValue(0xfc00) >> 10;
                if (realChannel - vaChannel > SettingMode.keyNum) SettingMode.keyNum = realChannel - vaChannel;

                SettingMode.listKeys.Clear();
                if (SettingMode.keyNum > 4)
                {
                    int ys = 40 + 0 + 4;
                    BitValue y = new BitValue((cfgContent[ys * 2 + 1] << 8) + cfgContent[ys * 2 + 0]);
                    for (int cnt = 0; cnt < SettingMode.keyNum; cnt++)
                    {
                        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(cnt + 1, y.IntValue);
                        SettingMode.listKeys.Add(pairs);
                    }
                }
                //else if (SettingMode.keyNum > 4)
                //{
                //    int ys = 40 + 0 + 4;
                //    BitValue y = new BitValue((cfgContent[ys * 2 + 1] << 8) + cfgContent[ys * 2 + 0]);

                //    int[] key_x = new int[15];
                //    key_x[0] = cfgContent[40 * 2 + 0] & 0x0f;
                //    key_x[1] = (cfgContent[40 * 2 + 0] & 0xf0) >> 4;
                //    key_x[2] = cfgContent[40 * 2 + 1] & 0x0f;
                //    key_x[3] = (cfgContent[40 * 2 + 1] & 0xf0) >> 4;
                //    key_x[4] = cfgContent[41 * 2 + 0] & 0x0f;
                //    key_x[5] = (cfgContent[41 * 2 + 0] & 0xf0) >> 4;
                //    key_x[6] = cfgContent[41 * 2 + 1] & 0x0f;
                //    key_x[7] = (cfgContent[41 * 2 + 1] & 0xf0) >> 4;
                //    key_x[8] = cfgContent[42 * 2 + 0] & 0x0f;
                //    key_x[9] = (cfgContent[42 * 2 + 0] & 0xf0) >> 4;
                //    key_x[10] = cfgContent[42 * 2 + 1] & 0x0f;
                //    key_x[11] = (cfgContent[42 * 2 + 1] & 0xf0) >> 4;
                //    key_x[12] = cfgContent[43 * 2 + 0] & 0x0f;
                //    key_x[13] = (cfgContent[43 * 2 + 0] & 0xf0) >> 4;
                //    key_x[14] = cfgContent[43 * 2 + 1] & 0x0f;

                //    for (int index = 0; index < SettingMode.keyNum && index < 15; index++)
                //    {
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(key_x[index], y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }
                //}
                else
                {
                    for (int index = 0; index < SettingMode.keyNum; index++)
                    {
                        int xs = 40 + index + 0, ys = 40 + 0 + 4;
                        BitValue x = new BitValue((cfgContent[xs * 2 + 1] << 8) + cfgContent[xs * 2 + 0]);
                        BitValue y = new BitValue((cfgContent[ys * 2 + 1] << 8) + cfgContent[ys * 2 + 0]);
                        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                        SettingMode.listKeys.Add(pairs);
                    }
                }

                mode.Rows = mode.UsrDef ? mode.Rows : GetRows(cfgContent);
                mode.Cols = mode.UsrDef ? mode.Cols : GetCols(cfgContent);
            }
        }

        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                ushort bootLen = (ushort)((bootContent[7] << 8) + bootContent[6]);
                mode.BootCrc = SettingMode.CaculateCheckSumEx(bootContent, bootLen);
            }
        }
    }

    public partial class SMChipInfoChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexMcapBinInformation()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5472, "SEMITestApp.Src.WinSet.McapBinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5816, "SEMITestApp.Src.WinSet.CH5816BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5562, "SEMITestApp.Src.WinSet.CH5562BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7449, "SEMITestApp.Src.WinSet.CH7449BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_8006, "SEMITestApp.Src.WinSet.CH8006BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_810, "SEMITestApp.Src.WinSet.CH810BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_7126, "SEMITestApp.Src.WinSet.CH7126BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_570, "SEMITestApp.Src.WinSet.CH570BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_310, "SEMITestApp.Src.WinSet.CH310BinInformation", SEMI.Util.ChipReflex.SEMI_TEST_MAIN_SET);
        }
    }
    public class McapBinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1a]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x19]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            ushort uCheckSum = SettingMode.CaculateCheckSumU16(cfgContent, cfgLen);
            if (0 == uCheckSum)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                mode.BootCrc = crc;
            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
                mode.ConfigCrc = SettingMode.CaculateCheckSumEx(cfgContent, cfgLen);

                BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                if (msic.Bit(1))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                SettingMode.keyNum = cfgContent[0x52];
                SettingMode.listKeys.Clear();
                SettingMode.listKeyChannels.Clear();
                if (SettingMode.keyNum > 5)
                {
                    //int ys = 40 + 0 + 4;
                    BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                    for (int cnt = 0; cnt < SettingMode.keyNum; cnt++)
                    {
                        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(cnt + 1, y.IntValue);
                        SettingMode.listKeys.Add(pairs);
                        SettingMode.listKeyChannels.Add(cfgContent[0x64 + cnt]);
                    }
                }
                else
                {
                    for (int index = 0; index < SettingMode.keyNum; index++)
                    {
                        if ((cfgContent[0x53] & 0x02) > 0)
                        {
                            BitValue x = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                            BitValue y = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                            KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                            SettingMode.listKeys.Add(pairs);
                        }
                        else
                        {
                            BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                            BitValue x = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                            KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                            SettingMode.listKeys.Add(pairs);
                        }

                        SettingMode.listKeyChannels.Add(cfgContent[0x64 + index]);
                    }
                }

            }
        }
    }

    public class CH7449BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1a]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x19]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            ushort uCheckSum = SettingMode.CaculateCheckSumU16(cfgContent, cfgLen);
            if (0 == uCheckSum)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                mode.BootCrc = crc;
            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
                mode.ConfigCrc = SettingMode.CaculateCheckSumEx(cfgContent, cfgLen);

                BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                if (msic.Bit(1))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                SettingMode.keyNum = cfgContent[0x52];
                SettingMode.listKeys.Clear();
                SettingMode.listKeyChannels.Clear();
                if (SettingMode.keyNum > 5)
                {
                    //int ys = 40 + 0 + 4;
                    BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                    for (int cnt = 0; cnt < SettingMode.keyNum; cnt++)
                    {
                        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(cnt + 1, y.IntValue);
                        SettingMode.listKeys.Add(pairs);
                        SettingMode.listKeyChannels.Add(cfgContent[0x64 + cnt]);
                    }
                }
                else
                {
                    for (int index = 0; index < SettingMode.keyNum; index++)
                    {
                        if ((cfgContent[0x53] & 0x02) > 0)
                        {
                            BitValue x = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                            BitValue y = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                            KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                            SettingMode.listKeys.Add(pairs);
                        }
                        else
                        {
                            BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                            BitValue x = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                            KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                            SettingMode.listKeys.Add(pairs);
                        }

                        SettingMode.listKeyChannels.Add(cfgContent[0x64 + index]);
                    }
                }

                SettingMode.physicalButtonNum = cfgContent[0x188];
                SettingMode.physicalButtons.Clear();
                for (int index = 0; index < SettingMode.physicalButtonNum; index++)
                {
                    BitValue y = new BitValue((cfgContent[0x18a] << 8) + cfgContent[0x189]);
                    BitValue x = new BitValue((cfgContent[0x18d + index * 2 + index] << 8) + cfgContent[0x18c + index * 2 + index]);
                    KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                    SettingMode.physicalButtons.Add(pairs);  
                }
            }
        }
    }

    public class CH5562BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1a]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x19]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            uint uCheckSum = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);
           
            if (uCheckSum == 0)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                var flag = (ushort)((bootContent[51]<<8)|(bootContent[50]));
                if (0x6274 == flag)
                {
                    var bootlaoderlen = (ushort)((bootContent[0x35] << 8) | (bootContent[0x34]));
                    mode.BootLoaderCrc = (uint)((bootContent[bootlaoderlen - 1] << 24) + (bootContent[bootlaoderlen - 2] << 16) + (bootContent[bootlaoderlen - 3] << 8) + (bootContent[bootlaoderlen - 4] << 0));
                    mode.BootCrc = (uint)((bootContent[bootLen - 5] << 24) + (bootContent[bootLen - 6] << 16) + (bootContent[bootLen - 7] << 8) + (bootContent[bootLen - 8] << 0));
                }
                else
                {
                    uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                    mode.BootCrc = crc;
                    mode.BootLoaderCrc = 0;
                }
                    

            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
        
                mode.ConfigCrc = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

                BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                if (msic.Bit(1))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                //SettingMode.keyNum = cfgContent[0x52];
                //SettingMode.listKeys.Clear();
                //SettingMode.listKeyChannels.Clear();
                //for (int index = 0; index < SettingMode.keyNum; index++)
                //{
                //    if ((cfgContent[0x53] & 0x02) > 0)
                //    {
                //        BitValue x = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue y = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }
                //    else
                //    {
                //        BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue x = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }

                //    SettingMode.listKeyChannels.Add(cfgContent[0x64 + index]);
                //}
            }
        }
    }

    public class CH570BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1a]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x19]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            uint uCheckSum = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

            if (uCheckSum == 0)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                var flag = (ushort)((bootContent[51] << 8) | (bootContent[50]));
                if (0x6274 == flag)
                {
                    var bootlaoderlen = (ushort)((bootContent[0x35] << 8) | (bootContent[0x34]));
                    mode.BootLoaderCrc = (uint)((bootContent[bootlaoderlen - 1] << 24) + (bootContent[bootlaoderlen - 2] << 16) + (bootContent[bootlaoderlen - 3] << 8) + (bootContent[bootlaoderlen - 4] << 0));
                    mode.BootCrc = (uint)((bootContent[bootLen - 5] << 24) + (bootContent[bootLen - 6] << 16) + (bootContent[bootLen - 7] << 8) + (bootContent[bootLen - 8] << 0));
                }
                else
                {
                    uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                    mode.BootCrc = crc;
                    mode.BootLoaderCrc = 0;
                }


            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;

                mode.ConfigCrc = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

                BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                if (msic.Bit(1))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                //SettingMode.keyNum = cfgContent[0x52];
                //SettingMode.listKeys.Clear();
                //SettingMode.listKeyChannels.Clear();
                //for (int index = 0; index < SettingMode.keyNum; index++)
                //{
                //    if ((cfgContent[0x53] & 0x02) > 0)
                //    {
                //        BitValue x = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue y = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }
                //    else
                //    {
                //        BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue x = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }

                //    SettingMode.listKeyChannels.Add(cfgContent[0x64 + index]);
                //}
            }
        }
    }

    public class CH7126BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1a]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x19]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            uint uCheckSum = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

            if (uCheckSum == 0)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                var flag = (ushort)((bootContent[51] << 8) | (bootContent[50]));
                if (0x6274 == flag)
                {
                    var bootlaoderlen = (ushort)((bootContent[0x35] << 8) | (bootContent[0x34]));
                    mode.BootLoaderCrc = (uint)((bootContent[bootlaoderlen - 1] << 24) + (bootContent[bootlaoderlen - 2] << 16) + (bootContent[bootlaoderlen - 3] << 8) + (bootContent[bootlaoderlen - 4] << 0));
                    mode.BootCrc = (uint)((bootContent[bootLen - 5] << 24) + (bootContent[bootLen - 6] << 16) + (bootContent[bootLen - 7] << 8) + (bootContent[bootLen - 8] << 0));
                }
                else
                {
                    uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                    mode.BootCrc = crc;
                    mode.BootLoaderCrc = 0;
                }


            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;

                mode.ConfigCrc = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

                BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                if (msic.Bit(1))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                //SettingMode.keyNum = cfgContent[0x52];
                //SettingMode.listKeys.Clear();
                //SettingMode.listKeyChannels.Clear();
                //for (int index = 0; index < SettingMode.keyNum; index++)
                //{
                //    if ((cfgContent[0x53] & 0x02) > 0)
                //    {
                //        BitValue x = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue y = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }
                //    else
                //    {
                //        BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue x = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }

                //    SettingMode.listKeyChannels.Add(cfgContent[0x64 + index]);
                //}
            }
        }
    }

    public class CH8006BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return 2; }
        public override int GetCols(byte[] cfgContent) { return 2; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valided = true;

            if (null != cfgContent)
            {
                int len = cfgContent.Length;
                if (len > 256) valided = false;
                if (len < 64) valided = false;
                if ((len & 1) > 0) valided = false;

                ushort checkSum = 0;
                int haftLen = len >> 1;
                for (int index = 0; index < haftLen; index++)
                {
                    checkSum += (ushort)((cfgContent[index * 2 + 1] << 8) + cfgContent[index * 2 + 0]);
                }

                if (checkSum != 0) valided = false;
            }
            else
            {
                valided = false;
            }

            if (!valided)
            {
                MessageBox.Show("cfg file is invalid");
            }

            return valided;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                mode.BootCrc = crc;
            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
                mode.ConfigCrc = SettingMode.CaculateCheckSumEx(cfgContent, cfgLen);

                BitValue misc = new BitValue((cfgContent[57 * 2 + 1] << 8) + cfgContent[57 * 2 + 0]);
                BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
                BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

                //swap xy
                //if (misc.Bit(3))
                //{
                //    mode.XPixel = lcdy.UShortValue;
                //    mode.YPixel = mode.XPixel;//lcdx.UShortValue;
                //}
                //else
                //{
                //    mode.XPixel = lcdx.UShortValue;
                //    mode.YPixel = mode.XPixel;//lcdy.UShortValue;
                //}
                mode.XPixel = lcdx.UShortValue;
                mode.YPixel = mode.XPixel;//lcdy.UShortValue;

                BitValue chain = new BitValue((cfgContent[35 * 2 + 1] << 8) + cfgContent[35 * 2 + 0]);
                SettingMode.keyNum = 0;
                SettingMode.keyThr = 0;
                //9 keys... very important
                int vaChannel = chain.MaskValue(0x3f0) >> 4;
                int realChannel = chain.MaskValue(0xfc00) >> 10;

                SettingMode.listKeys.Clear();

                mode.Rows = mode.UsrDef ? mode.Rows : GetRows(cfgContent);
                mode.Cols = mode.UsrDef ? mode.Cols : GetCols(cfgContent);
                
            }
        }
    }

    public class CH810BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return 2; }
        public override int GetCols(byte[] cfgContent) { return 2; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint checkSum = MainSettingMode.CaculateCheckSumU16(bootContent, bootLen);

            if (checkSum == 0 && bootLen==64)
            {
                valid = true;
            }
            else
            {
                valid = false;
            }

            if (!valid)
            {
                var str = String.Format("boot file crc is invalid checkSum={0},bootLen={1}", checkSum, bootLen);
                MessageBox.Show(str);
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valided = true;
            ushort checkSum = 0;
            int len = 0;

            if (null != cfgContent)
            {
                len = cfgContent.Length;

                checkSum = MainSettingMode.CaculateCheckSumU16(cfgContent, len);

                if (checkSum == 0 && len == 448)
                {
                    valided = true;
                }
                else
                {
                    valided = false;
                } 
            }
            else
            {
                valided = false;
            }

            if (!valided)
            {
                var str = String.Format("cfg file is invalid CheckSum={0},CfgLen={1}", checkSum, len);
                MessageBox.Show(str);
            }

            return valided;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                uint crc = (uint)(MainSettingMode.CaculateCheckSumU16(bootContent, bootLen));
                mode.BootCrc = crc;
            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {

            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
                mode.ConfigCrc = SettingMode.CaculateCheckSumU16(cfgContent, cfgLen);

                ushort res = (ushort)((cfgContent[0xb1 * 2 + 1] << 8) + cfgContent[0xb1 * 2 + 0]);
                mode.XPixel = (ushort)(res * 2 + 1);
                mode.YPixel = mode.XPixel;//lcdy.UShortValue;
    
                SettingMode.keyNum = 0;
                SettingMode.keyThr = 0;

                //int vaChannel = 4;
                //int realChannel = 4;

                SettingMode.listKeys.Clear();

                mode.Rows = mode.UsrDef ? mode.Rows : GetRows(cfgContent);
                mode.Cols = mode.UsrDef ? mode.Cols : GetCols(cfgContent);

            }
        }
    }

    public class CH310BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1a]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x19]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            uint uCheckSum = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

            if (uCheckSum == 0)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                var flag = (ushort)((bootContent[51] << 8) | (bootContent[50]));
                if (0x6274 == flag)
                {
                    var bootlaoderlen = (ushort)((bootContent[0x35] << 8) | (bootContent[0x34]));
                    mode.BootLoaderCrc = (uint)((bootContent[bootlaoderlen - 1] << 24) + (bootContent[bootlaoderlen - 2] << 16) + (bootContent[bootlaoderlen - 3] << 8) + (bootContent[bootlaoderlen - 4] << 0));
                    mode.BootCrc = (uint)((bootContent[bootLen - 5] << 24) + (bootContent[bootLen - 6] << 16) + (bootContent[bootLen - 7] << 8) + (bootContent[bootLen - 8] << 0));
                }
                else
                {
                    uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                    mode.BootCrc = crc;
                    mode.BootLoaderCrc = 0;
                }


            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;

                mode.ConfigCrc = SMCheckTools.CaculateCheckSumU32(cfgContent, cfgLen);

                BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                if (msic.Bit(1))
                {
                    mode.XPixel = lcdy.UShortValue;
                    mode.YPixel = lcdx.UShortValue;
                }
                else
                {
                    mode.XPixel = lcdx.UShortValue;
                    mode.YPixel = lcdy.UShortValue;
                }

                //SettingMode.keyNum = cfgContent[0x52];
                //SettingMode.listKeys.Clear();
                //SettingMode.listKeyChannels.Clear();
                //for (int index = 0; index < SettingMode.keyNum; index++)
                //{
                //    if ((cfgContent[0x53] & 0x02) > 0)
                //    {
                //        BitValue x = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue y = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }
                //    else
                //    {
                //        BitValue y = new BitValue((cfgContent[0x55] << 8) + cfgContent[0x54]);
                //        BitValue x = new BitValue((cfgContent[0x57 + index * 2] << 8) + cfgContent[0x56 + index * 2]);
                //        KeyValuePair<int, int> pairs = new KeyValuePair<int, int>(x.IntValue, y.IntValue);
                //        SettingMode.listKeys.Add(pairs);
                //    }

                //    SettingMode.listKeyChannels.Add(cfgContent[0x64 + index]);
                //}
            }
        }
    }

    public class CH5816BinInformation : BinInformation
    {
        public override int GetRows(byte[] cfgContent) { return cfgContent[0x1c]; }
        public override int GetCols(byte[] cfgContent) { return cfgContent[0x1b]; }
        public override bool CheckBootValidation(byte[] bootContent)
        {
            bool valid = false;
            int bootLen = bootContent.Length;
            uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
            uint checkSum = MainSettingMode.CaculateCheckSumEx(bootContent, bootLen - 4);

            if (checkSum == crc)
            {
                ushort cfgAddr = (ushort)((bootContent[0x39] << 8) | bootContent[0x38]);
                byte[] cfgContent = new byte[256];
                Array.Copy(bootContent, cfgAddr, cfgContent, 0, cfgContent.Length);
                return CheckCfgValidation(cfgContent);
                //valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("boot file crc is invalid");
            }

            return valid;
        }
        public override bool CheckCfgValidation(byte[] cfgContent)
        {
            bool valid = false;

            ushort cfgLen = (ushort)cfgContent.Length;
            ushort uCheckSum = SettingMode.CaculateCheckSumU16(cfgContent, cfgLen);

            if (0 == uCheckSum)
            {
                valid = true;
            }
            else
            {
                valid = false;
                MessageBox.Show("cfg file is invalid");
            }

            return valid;
        }
        public override void BootToView(MainSettingMode mode, byte[] bootContent)
        {
            if (null != bootContent)
            {
                //ushort bootLen = (ushort)((bootContent[4] << 8) + bootContent[3]);
                //ushort bootLen = (ushort)(bootContent.Length);
                int bootLen = bootContent.Length;
                uint crc = (uint)((bootContent[bootLen - 1] << 24) + (bootContent[bootLen - 2] << 16) + (bootContent[bootLen - 3] << 8) + (bootContent[bootLen - 4] << 0));
                mode.BootCrc = crc;

                ushort cfgAddr = (ushort)((bootContent[0x39] << 8) | bootContent[0x38]);
                SettingMode.cfgContent = new byte[256];
                Array.Copy(bootContent, cfgAddr, SettingMode.cfgContent, 0, SettingMode.cfgContent.Length);

                CfgToView(mode, SettingMode.cfgContent);
            }
        }
        public override void CfgToView(MainSettingMode mode, byte[] cfgContent)
        {
            if (null != cfgContent)
            {
                ushort cfgLen = (ushort)cfgContent.Length;
                mode.ConfigCrc = SettingMode.CaculateCheckSumEx(cfgContent, cfgLen);

                //BitValue msic = new BitValue(cfgContent[0x0f]);
                BitValue lcdx = new BitValue((cfgContent[7] << 8) + cfgContent[6]);
                BitValue lcdy = new BitValue((cfgContent[9] << 8) + cfgContent[8]);

                mode.XPixel = lcdx.UShortValue;
                mode.YPixel = lcdy.UShortValue;
                mode.Rows = GetRows(cfgContent);
                mode.Cols = GetCols(cfgContent);

                SettingMode.keyNum = 0;
            }
        }
    }
}
