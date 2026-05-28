using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.Windows;
using System.Xml;
using SEMI.Util;
using SEMITestApp.Src.Util;

namespace SEMITestApp.Src.WinSet
{
    public class CommonSetMode : SettingMode
    {
//         public class StartKind
//         {
//             public int StartType { get; set; }
//             public string TypeName { get; set; }
//             public override string ToString()
//             {
//                 return TypeName;
//             }
//         }
//         public class UserFormat
//         {
//             public ushort FormatType { get; set; }
//             public string FormatName { get; set; }
//             public override string ToString()
//             {
//                 return FormatName;
//             }
//         }

        private ushort way_to_start = 1;
        public ushort WayToStart
        {
            get { return way_to_start; }
            set { if (value != way_to_start) { way_to_start = value; OnPropertyChanged("WayToStart"); } }
        }

//         private int way_to_start = 1;
//         public int WayToStart
//         {
//             get { return way_to_start; }
//             set { if (value != way_to_start) { way_to_start = value; SNVisible = way_to_start == 3 ? Visibility.Visible : Visibility.Collapsed; OnPropertyChanged("WayToStart"); } }
//         }

//         private Visibility snVisible = Visibility.Collapsed;
//         public Visibility SNVisible
//         {
//             get { return snVisible; }
//             set { if (value != snVisible) { snVisible = value; OnPropertyChanged("SNVisible"); } }
//         }

        private int snLen = 10;
        public int SNLen
        {
            get { return snLen; }
            set { if (value != snLen) { snLen = value; OnPropertyChanged("SNLen"); } }
        }

        private string userRecord = "";
        public string UserRecord
        {
            get { return userRecord; }
            set { if (value != userRecord) { userRecord = value; OnPropertyChanged("UserRecord"); } }
        }

        private string logPath = "";
        public string LogPath
        {
            get { return logPath; }
            set { if (value != logPath) { logPath = value; OnPropertyChanged("LogPath"); } }
        }

        private IList<SMDefinition> list_modes = new List<SMDefinition>()
        {
            new SMDefinition( 1, "Single Tp Test" ),
            new SMDefinition( 2, "Number 2" ),
            new SMDefinition( 3, "Number 3" ),
            new SMDefinition( 4, "Number 4" ),
            new SMDefinition( 5, "Number 5" ),
            new SMDefinition( 6, "Number 6" ),
            new SMDefinition( 7, "Number 7" ),
            new SMDefinition( 8, "Number 8" ),
        };
        public IList<SMDefinition> ListModes
        {
            get { return list_modes; }
        }

        private ushort testMode = 1;
        public ushort TestMode
        {
            get { return testMode; }
            set { if (value != testMode) { testMode = value; OnPropertyChanged("TestMode"); } }
        }

        private IList<SMDefinition> list_start_kind = new List<SMDefinition>()
        {
            new SMDefinition( 1, "Auto Start" ),
            new SMDefinition( 2, "Button/Signal" ),
            new SMDefinition( 3, "SN Trigger" ),
        };
        public IList<SMDefinition> ListStartKind
        {
            get { return list_start_kind; }
        }

        private ushort holdUp = 10;
        public ushort HoldUp
        {
            get { return holdUp; }
            set { if (value != holdUp) { holdUp = value; OnPropertyChanged("HoldUp"); } }
        }

        private ushort selectedFormat = 0;
        public ushort SelectedFormat
        {
            get { return selectedFormat; }
            set
            {
                if (value != selectedFormat)
                {
                    selectedFormat = value;
                    OnPropertyChanged("SelectedFormat");

                    /*OP_LIKE_EDO -> TCP/IP*/
                    if (3 == selectedFormat)
                    {
                        LinkType = 0x2;
                    }
                }
            }
        }

        private IList<SMDefinition> listformat = new List<SMDefinition>()
        {
            new SMDefinition( 0, "Default" ),
            new SMDefinition( 1, "Format-ID" ),
            new SMDefinition( 2, "Format-YY" ),
            new SMDefinition( 3, "Format-EDO" ),
            new SMDefinition( 4, "Format-HX" ),
            new SMDefinition( 5, "Format-Cloud" ),
            new SMDefinition( 6, "Format-VSN" ),
            new SMDefinition( 7, "Format-EMS_Hes" ),
            new SMDefinition( 8, "Format-EMS_Ofilm" ),
            new SMDefinition( 9, "Format-EMS_PBH" ),
            new SMDefinition( 10, "Format-XY" ),
            new SMDefinition( 11, "Format-Visionox" ),
            new SMDefinition( 12, "Format-JW" ),
            new SMDefinition( 13, "Format-ChuangWei" ),
            new SMDefinition( 14, "Format-MES_New_Hes" ),
            new SMDefinition( 15, "Format-MES_LS" ),
        };
        public IList<SMDefinition> ListFormat
        {
            get { return listformat; }
        }

        private ushort selectedHeatBeatVol = 0x00;
        public ushort SelectedHeatBeatVol
        {
            get { return selectedHeatBeatVol; }
            set { if (value != selectedHeatBeatVol) { selectedHeatBeatVol = value; OnPropertyChanged("SelectedHeatBeatVol"); } }
        }

        private IList<SMDefinition> listHeatbeatVol = new List<SMDefinition>()
        {
            new SMDefinition( 0x00, "OFF" ),
            new SMDefinition( 0x01, "0.1V" ),
            new SMDefinition( 0x20, "0.8V" ),
            new SMDefinition( 0x27, "1.0V" ),
            new SMDefinition( 0x2B, "1.1V" ),
        };
        public IList<SMDefinition> ListHeatbeatVol
        {
            get { return listHeatbeatVol; }
        }

        private IList<SMDefinition> linkTypeList = new List<SMDefinition>()
        {
            new SMDefinition( 0x0, "None" ),
            new SMDefinition( 0x1, "Com" ),
            new SMDefinition( 0x2, "TCP/IP" ),
        };
        public IList<SMDefinition> LinkTypeList
        {
            get { return linkTypeList; }
        }

        private ushort linkType = 0;
        public ushort LinkType
        {
            get{return linkType;}
            set{if(value != linkType){linkType = value; OnPropertyChanged("linkType");}}
        }

        private ushort portNum = 0;
        public ushort PortNum
        {
            get { return portNum; }
            set { if (value != portNum) { portNum = value; OnPropertyChanged("PortNum"); } }
        }

        private ushort portSource = 0;
        public ushort PortSource
        {
            get { return portSource; }
            set { if (value != portSource) { portSource = value; OnPropertyChanged("PortSource"); } }
        }

        private string ipAddr = "127.0.0.1";
        public string IpAddr
        {
            get { return ipAddr; }
            set { if (value != ipAddr) { ipAddr = value; OnPropertyChanged("IpAddr"); } }
        }

        private string lineID = "M1TPS0100";
        public string LineID
        {
            get { return lineID; }
            set { if (value != lineID) { lineID = value; OnPropertyChanged("LineID"); } }
        }
        private string lineIDCW = "";
        public string LineIDCW
        {
            get { return lineIDCW; }
            set { if (value != lineIDCW) { lineIDCW = value; OnPropertyChanged("LineIDCW"); } }
        }

        private string account = "C99999";
        public string Account
        {
            get { return account; }
            set { if (value != account) { account = value; OnPropertyChanged("Account"); } }
        }

        private string password = "123456";
        public string Password
        {
            get { return password; }
            set { if (value != password) { password = value; OnPropertyChanged("Password"); } }
        }

        private string device_ID = "";
        public string Device_ID
        {
            get { return device_ID; }
            set { if (value != device_ID) { device_ID = value; OnPropertyChanged("Device_ID"); } }
        }

        private string process_name = "";
        public string Process_name
        {
            get { return process_name; }
            set { if (value != process_name) { process_name = value; OnPropertyChanged("Process_name"); } }
        }

        private bool needClickStart = false;
        public bool NeedClickStart
        {
            get { return needClickStart; }
            set { if (value != needClickStart) { needClickStart = value; OnPropertyChanged("NeedClickStart"); } }
        }

        private bool needRemoveIC = false;
        public bool NeedRemoveIC
        {
            get { return needRemoveIC; }
            set { if (value != needRemoveIC) { needRemoveIC = value; OnPropertyChanged("NeedRemoveIC"); } }
        }

        private string mesUrl = "";
        public string MesUrl
        {
            get { return mesUrl; }
            set { if (value != mesUrl) { mesUrl = value; OnPropertyChanged("MesUrl"); } }
        }
        private string mesUrlCW = "";
        public string MesUrlCW
        {
            get { return mesUrlCW; }
            set { if (value != mesUrlCW) { mesUrlCW = value; OnPropertyChanged("MesUrlCW"); } }
        }

        private string mesUrlHes = "";
        public string MesUrlHes
        {
            get { return mesUrlHes; }
            set { if (value != mesUrlHes) { mesUrlHes = value; OnPropertyChanged("MesUrlHes"); } }
        }

        private string mesUrlLS = "";
        public string MesUrlLS
        {
            get { return mesUrlLS; }
            set { if (value != mesUrlLS) { mesUrlLS = value; OnPropertyChanged("MesUrlLS"); } }
        }

        private string stepId = "";
        public string StepId
        {
            get { return stepId; }
            set { if (value != stepId) { stepId = value; OnPropertyChanged("StepId"); } }
        }

        private string testStepId = "";
        public string TestStepId
        {
            get { return testStepId; }
            set { if (value != testStepId) { testStepId = value; OnPropertyChanged("TestStepId"); } }
        }
        private string testStepIdCW = "";
        public string TestStepIdCW
        {
            get { return testStepIdCW; }
            set { if (value != testStepIdCW) { testStepIdCW = value; OnPropertyChanged("TestStepIdCW"); } }
        }
        private string subopNoHes = "";
        public string SubopNoHes
        {
            get { return subopNoHes; }
            set { if (value != subopNoHes) { subopNoHes = value; OnPropertyChanged("SubopNoHes"); } }
        }

        private string macAddress = "";
        public string MacAddress
        {
            get { return macAddress; }
            set { if (value != macAddress) { macAddress = value; OnPropertyChanged("MacAddress"); } }
        }
        private string macAddressCW = "";
        public string MacAddressCW
        {
            get { return macAddressCW; }
            set { if (value != macAddressCW) { macAddressCW = value; OnPropertyChanged("MacAddressCW"); } }
        }
        private string sNFilter = "";
        public string SNFilter
        {
            get { return sNFilter; }
            set { if (value != sNFilter) { sNFilter = value; OnPropertyChanged("SNFilter"); } }
        }
        private string fixtureId = "";
        public string FixtureId
        {
            get { return fixtureId; }
            set { if (value != fixtureId) { fixtureId = value; OnPropertyChanged("FixtureId"); } }
        }

        private string fixtureIdCW = "";
        public string FixtureIdCW
        {
            get { return fixtureIdCW; }
            set { if (value != fixtureIdCW) { fixtureIdCW = value; OnPropertyChanged("FixtureIdCW"); } }
        }

        private string userId = "";
        public string UserId
        {
            get { return userId; }
            set { if (value != userId) { userId = value; OnPropertyChanged("UserId"); } }
        }
        private string userIdCW = "";
        public string UserIdCW
        {
            get { return userIdCW; }
            set { if (value != userIdCW) { userIdCW = value; OnPropertyChanged("UserIdCW"); } }
        }

        private string machineNoHes = "";
        public string MachineNoHes
        {
            get { return machineNoHes; }
            set { if (value != machineNoHes) { machineNoHes = value; OnPropertyChanged("MachineNoHes"); } }
        }

        private string lotNoHes = "";
        public string LotNoHes
        {
            get { return lotNoHes; }
            set { if (value != lotNoHes) { lotNoHes = value; OnPropertyChanged("LotNoHes"); } }
        }

        private string personHes = "";
        public string PersonHes
        {
            get { return personHes; }
            set { if (value != personHes) { personHes = value; OnPropertyChanged("PersonHes"); } }
        }

        private string resourceNoLS = "";
        public string ResourceNoLS
        {
            get { return resourceNoLS; }
            set { if (value != resourceNoLS) { resourceNoLS = value; OnPropertyChanged("ResourceNoLS"); } }
        }

        private string specCodeLS = "";
        public string SpecCodeLS
        {
            get { return specCodeLS; }
            set { if (value != specCodeLS) { specCodeLS = value; OnPropertyChanged("SpecCodeLS"); } }
        }

        private string operatorLS = "";
        public string OperatorLS
        {
            get { return operatorLS; }
            set { if (value != operatorLS) { operatorLS = value; OnPropertyChanged("OperatorLS"); } }
        }

        private string deviceNumLS = "";
        public string DeviceNumLS
        {
            get { return deviceNumLS; }
            set { if (value != deviceNumLS) { deviceNumLS = value; OnPropertyChanged(" DeviceNumLS"); } }
        }

        private string eqpId = "";
        public string EqpId
        {
            get { return eqpId; }
            set { if (value != eqpId) { eqpId = value; OnPropertyChanged("EqpId"); } }
        }
        private string eqpIdCW = "";
        public string EqpIdCW
        {
            get { return eqpIdCW; }
            set { if (value != eqpIdCW) { eqpIdCW = value; OnPropertyChanged("EqpIdCW"); } }
        }

        private bool simulationUp = false;
        public bool SimulationUp
        {
            get { return simulationUp; }
            set { if (value != simulationUp) { simulationUp = value; OnPropertyChanged("SimulationUp"); } }
        }
        private bool displayTestLS = false;
        public bool DisplayTestLS
        {
            get { return displayTestLS; }
            set { if (value != displayTestLS) { displayTestLS = value; OnPropertyChanged("DisplayTestLS"); } }
        }
        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if ("log-path-click" == strParam)
            {
                string DirectoryPath = GetWorkPath();
                if (FolderBrowserDialog.Active(ref DirectoryPath) == System.Windows.Forms.DialogResult.OK)
                {
                    LogPath = DirectoryPath;
                }
            }
        }

        private IList<SMDefinition> ftpServerList = new List<SMDefinition>()
        {
            new SMDefinition( 0x0, "None" ),
            new SMDefinition( 0x2, "FTP" ),
        };
        public IList<SMDefinition> FtpServerList
        {
            get { return ftpServerList; }
        }

        private ushort ftpType = 0;
        public ushort FtpType
        {
            get { return ftpType; }
            set { if (value != ftpType) { ftpType = value; OnPropertyChanged("FtpType"); } }
        }

        private string ftpIpAddr = "127.0.0.1";
        public string FtpIpAddr
        {
            get { return ftpIpAddr; }
            set { if (value != ftpIpAddr) { ftpIpAddr = value; OnPropertyChanged("FtpIpAddr"); } }
        }

        private ushort ftpPortNum = 21;
        public ushort FtpPortNum
        {
            get { return ftpPortNum; }
            set { if (value != ftpPortNum) { ftpPortNum = value; OnPropertyChanged("FtpPortNum"); } }
        }

        private string ftpAccount = "";
        public string FtpAccount
        {
            get { return ftpAccount; }
            set { if (value != ftpAccount) { ftpAccount = value; OnPropertyChanged("FtpAccount"); } }
        }

        private string ftpPassWord = "";
        public string FtpPassWord
        {
            get { return ftpPassWord; }
            set { if (value != ftpPassWord) { ftpPassWord = value; OnPropertyChanged("FtpPassWord"); } }
        }

        private string ftpRelativePath = "";
        public string FtpRelativePath
        {
            get { return ftpRelativePath; }
            set { if (value != ftpRelativePath) { ftpRelativePath = value; OnPropertyChanged("FtpRelativePath"); } }
        }

        public override void XMLDataToView()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            TestMode = (ushort)GetXmlAttrbuteValue(stNode, "misc", "test_mode", 1);
            WayToStart = (ushort)GetXmlAttrbuteValue(stNode, "misc", "way_to_start", 1);
            SNLen = (int)GetXmlAttrbuteValue(stNode, "misc", "sn_length", 10);
            SelectedFormat = (ushort)GetXmlAttrbuteValue(stNode, "misc", "selected_format", 0);
            NeedClickStart = GetXmlAttrbuteValue(stNode, "misc", "need_click_start", 0) > 0 ? true : false;

            NeedRemoveIC = GetXmlAttrbuteValue(stNode, "misc", "need_remove_ic", 0) > 0 ? true : false;

            UserRecord = GetXmlAttrbuteString(stNode, "misc", "user_record");
            SelectedHeatBeatVol = (ushort)GetXmlAttrbuteValue(stNode, "misc", "heatbeat_voltage", 0x20);
            LogPath = GetXmlAttrbuteString(stNode, "misc", "log_path");
            HoldUp = (ushort)GetXmlAttrbuteValue(stNode, "misc", "hold_up", 10);
            SNFilter = GetXmlAttrbuteString(stNode, "misc", "snFilter");

            LinkType = (ushort)GetXmlAttrbuteValue(stNode, "online", "link_type", 0);
            PortNum = (ushort)GetXmlAttrbuteValue(stNode, "online", "port_num", 0);
            IpAddr = GetXmlAttrbuteString(stNode, "online", "ip_addr", "127.0.0.1");
            PortSource = (ushort)GetXmlAttrbuteValue(stNode, "online", "port_source", 0);

            FtpType = (ushort)GetXmlAttrbuteValue(stNode, "uploader", "ftp_type", 0);
            FtpPortNum = (ushort)GetXmlAttrbuteValue(stNode, "uploader", "port_num", 21);
            FtpIpAddr = GetXmlAttrbuteString(stNode, "uploader", "ip_addr", "127.0.0.1");
            FtpAccount = GetXmlAttrbuteString(stNode, "uploader", "account", "");
            FtpPassWord = GetXmlAttrbuteString(stNode, "uploader", "password", "");
            FtpRelativePath = GetXmlAttrbuteString(stNode, "uploader", "relative_path", "");

            //like_edo
            if (3 == SelectedFormat)
            {
                LineID = GetXmlAttrbuteString(stNode, "custom", "line_id");
                Account = GetXmlAttrbuteString(stNode, "custom", "account");
                Password = GetXmlAttrbuteString(stNode, "custom", "password");
            }

            if (7 == SelectedFormat)
            {
                Device_ID = GetXmlAttrbuteString(stNode, "customv2", "device_id");
                Process_name = GetXmlAttrbuteString(stNode, "customv2", "process_name");
                //Password = GetXmlAttrbuteString(stNode, "custom", "password");
            }
            if (8 == SelectedFormat)//ofilm
            {
                MesUrl = GetXmlAttrbuteString(stNode, "custom_ofilm", "mesUrl");
                StepId = GetXmlAttrbuteString(stNode, "custom_ofilm", "stepId");
                TestStepId = GetXmlAttrbuteString(stNode, "custom_ofilm", "testStepId");
                MacAddress = GetXmlAttrbuteString(stNode, "custom_ofilm", "macAddress");
                
            }
            if (9 == SelectedFormat)//pbh
            {

                MesUrl = GetXmlAttrbuteString(stNode, "custom_pbh", "mesUrl");
                FixtureId = GetXmlAttrbuteString(stNode, "custom_pbh", "fixtureId");
                TestStepId = GetXmlAttrbuteString(stNode, "custom_pbh", "testStepId");
                EqpId = GetXmlAttrbuteString(stNode, "custom_pbh", "station");
                UserId = GetXmlAttrbuteString(stNode, "custom_pbh", "userId");
                Password = GetXmlAttrbuteString(stNode, "custom_pbh", "passWord");
            }
            if (13 == SelectedFormat)//chuangwei
            {

                MesUrlCW = GetXmlAttrbuteString(stNode, "custom_chuangwei", "mesUrl");

                UserIdCW = GetXmlAttrbuteString(stNode, "custom_chuangwei", "userId");
                TestStepIdCW = GetXmlAttrbuteString(stNode, "custom_chuangwei", "processcode");
                LineIDCW = GetXmlAttrbuteString(stNode, "custom_chuangwei", "line_id");
                EqpIdCW = GetXmlAttrbuteString(stNode, "custom_chuangwei", "message");

                FixtureIdCW    = GetXmlAttrbuteString(stNode, "custom_chuangwei", "orderno");
                MacAddressCW   = GetXmlAttrbuteString(stNode, "custom_chuangwei", "macAddress");
                SimulationUp = GetXmlAttrbuteValue(stNode, "custom_chuangwei", "simulationUp", 0) > 0 ? true : false;
            }
            if (14 == SelectedFormat)//MES_NEW_Hes
            {
                MesUrlHes = GetXmlAttrbuteString(stNode, "custom_hes", "mesUrl");
                MachineNoHes = GetXmlAttrbuteString(stNode, "custom_hes", "machine_no");
                LotNoHes = GetXmlAttrbuteString(stNode, "custom_hes", "lot_no");
                SubopNoHes = GetXmlAttrbuteString(stNode, "custom_hes", "subop_no");
                PersonHes = GetXmlAttrbuteString(stNode, "custom_hes", "person");
            }
            if (15 == SelectedFormat)//MES_LS
            {
                MesUrlLS = GetXmlAttrbuteString(stNode, "custom_ls", "mesUrl");
                ResourceNoLS = GetXmlAttrbuteString(stNode, "custom_ls", "resource_no");
                SpecCodeLS = GetXmlAttrbuteString(stNode, "custom_ls", "special_code");
                OperatorLS = GetXmlAttrbuteString(stNode, "custom_ls", "operator");
                DeviceNumLS = GetXmlAttrbuteString(stNode, "custom_ls", "device_num");
                DisplayTestLS = GetXmlAttrbuteValue(stNode, "custom_ls", "display_test", 0) > 0 ? true : false;
            }
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);
            if (null == stNode) return;

            SaveXmlAttrbuteValue(stNode, "misc", "test_mode", TestMode);
            SaveXmlAttrbuteValue(stNode, "misc", "way_to_start", WayToStart);
            SaveXmlAttrbuteValue(stNode, "misc", "sn_length", SNLen);
            SaveXmlAttrbuteValue(stNode, "misc", "need_click_start", NeedClickStart ? 1 : 0);

            SaveXmlAttrbuteValue(stNode, "misc", "need_remove_ic", NeedRemoveIC ? 1 : 0);

            SaveXmlAttrbuteValue(stNode, "misc", "selected_format", SelectedFormat);
            SaveXmlAttrbuteString(stNode, "misc", "user_record", UserRecord);
            SaveXmlAttrbuteValue(stNode, "misc", "heatbeat_voltage", SelectedHeatBeatVol);
            SaveXmlAttrbuteValue(stNode, "misc", "log_path", LogPath);
            SaveXmlAttrbuteValue(stNode, "misc", "hold_up", HoldUp);
            SaveXmlAttrbuteString(stNode, "misc", "snFilter", SNFilter);

            SaveXmlAttrbuteValue(stNode, "online", "link_type", LinkType);
            SaveXmlAttrbuteValue(stNode, "online", "port_num", PortNum);
            SaveXmlAttrbuteString(stNode, "online", "ip_addr", IpAddr);
            SaveXmlAttrbuteValue(stNode, "online", "port_source", PortSource);

            SaveXmlAttrbuteValue(stNode, "uploader", "ftp_type", FtpType);
            SaveXmlAttrbuteValue(stNode, "uploader", "port_num", FtpPortNum);
            SaveXmlAttrbuteString(stNode, "uploader", "ip_addr", FtpIpAddr);
            SaveXmlAttrbuteString(stNode, "uploader", "account", FtpAccount);
            SaveXmlAttrbuteString(stNode, "uploader", "password", FtpPassWord);
            SaveXmlAttrbuteString(stNode, "uploader", "relative_path", FtpRelativePath);

            if (3 == SelectedFormat)
            {
                SaveXmlAttrbuteString(stNode, "custom", "line_id", LineID);
                SaveXmlAttrbuteString(stNode, "custom", "account", Account);
                SaveXmlAttrbuteString(stNode, "custom", "password", Password);
            }

            if (7 == SelectedFormat)
            {

                SaveXmlAttrbuteString(stNode, "customv2", "device_id", Device_ID);
                SaveXmlAttrbuteString(stNode, "customv2", "process_name", Process_name);
                //SaveXmlAttrbuteString(stNode, "custom", "password", Password)
            }

            if (8 == SelectedFormat)//ofilm
            {

                SaveXmlAttrbuteString(stNode, "custom_ofilm", "mesUrl", MesUrl);
                SaveXmlAttrbuteString(stNode, "custom_ofilm", "stepId", StepId);
                SaveXmlAttrbuteString(stNode, "custom_ofilm", "testStepId", TestStepId);
                SaveXmlAttrbuteString(stNode, "custom_ofilm", "macAddress", MacAddress);
            }
            if (9 == SelectedFormat)//pbh
            {

                SaveXmlAttrbuteString(stNode, "custom_pbh", "mesUrl", MesUrl);
                SaveXmlAttrbuteString(stNode, "custom_pbh", "fixtureId", FixtureId);
                SaveXmlAttrbuteString(stNode, "custom_pbh", "testStepId", TestStepId);
                SaveXmlAttrbuteString(stNode, "custom_pbh", "station", EqpId);
                SaveXmlAttrbuteString(stNode, "custom_pbh", "userId", UserId);
                SaveXmlAttrbuteString(stNode, "custom_pbh", "passWord", Password);
            }

            if (13 == SelectedFormat)//chuangwei
            {

                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "mesUrl", MesUrlCW);
                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "userId", UserIdCW);
                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "processcode", TestStepIdCW);
                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "line_id", LineIDCW);
                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "message", EqpIdCW);

                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "orderno", FixtureIdCW);
                SaveXmlAttrbuteString(stNode, "custom_chuangwei", "macAddress", MacAddressCW);
                SaveXmlAttrbuteValue(stNode, "custom_chuangwei", "simulationUp", SimulationUp ? 1 : 0);
 
            }
            if (14 == SelectedFormat)//MES_NEW_Hes
            {
                SaveXmlAttrbuteString(stNode, "custom_hes", "mesUrl", MesUrlHes);
                SaveXmlAttrbuteString(stNode, "custom_hes", "machine_no", MachineNoHes);
                SaveXmlAttrbuteString(stNode, "custom_hes", "lot_no", LotNoHes);
                SaveXmlAttrbuteString(stNode, "custom_hes", "subop_no", SubopNoHes);
                SaveXmlAttrbuteString(stNode, "custom_hes", "person", PersonHes);
            }
            if (15 == SelectedFormat)//MES_LS
            {
                SaveXmlAttrbuteString(stNode, "custom_ls", "mesUrl", MesUrlLS);
                SaveXmlAttrbuteString(stNode, "custom_ls", "resource_no", ResourceNoLS);
                SaveXmlAttrbuteString(stNode, "custom_ls", "special_code", SpecCodeLS);
                SaveXmlAttrbuteString(stNode, "custom_ls", "operator", OperatorLS);
                SaveXmlAttrbuteString(stNode, "custom_ls", "device_num", DeviceNumLS);
                SaveXmlAttrbuteValue(stNode, "custom_ls", "display_test", DisplayTestLS ? 1 : 0);
            }
            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
