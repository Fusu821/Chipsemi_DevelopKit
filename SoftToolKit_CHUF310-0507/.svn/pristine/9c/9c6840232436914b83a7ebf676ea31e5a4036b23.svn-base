using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Xml;
using SEMITestApp.Src.WinSub;
using SEMI.Util;

namespace SEMITestApp.Src.WinSet
{
    public class GraphSettingMode : SettingMode
    {
        public KeyPanel Kpanel { get; set; }
        public KeyPanel PhysicalKpanel { get; set; }
        private bool freepaintChecked = false;
        public bool FreePaintChecked
        {
            get { return freepaintChecked; }
            set { if (value != freepaintChecked) { freepaintChecked = value; OnPropertyChanged("FreePaintChecked"); } }
        }

        private bool freepaintOnce = true;
        public bool FreePaintOnce
        {
            get { return freepaintOnce; }
            set { if (value != freepaintOnce) { freepaintOnce = value; OnPropertyChanged("FreePaintOnce"); } }
        }

        private int freepaintLeftTime = 98;
        public int FreePaintLeftTime
        {
            get { return freepaintLeftTime; }
            set { if (value != freepaintLeftTime) { freepaintLeftTime = value; OnPropertyChanged("FreePaintLeftTime"); } }
        }

        public IList<SMDefinition> Typelist
        {
            get
            {
                return new List<SMDefinition>()
                {
                    new SMDefinition(0,   "default"),
                    new SMDefinition(1,   "feikong_sd"),
                    new SMDefinition(2,   "feikong"),
                    new SMDefinition(3,   "slider"),
                    new SMDefinition(4,   "knob"),
                    new SMDefinition(5,   "encoder"),
                };
            }
        }


        private ushort type = 0;
        public ushort Type
        {
            get { return type; }
            set
            {
                if (value != type)
                {
                    type = value;
                    OnPropertyChanged("Type");
                }
            }
        }

        private bool swichAddr = false;
        public bool SwichAddr
        {
            get { return swichAddr; }
            set { if (value != swichAddr) { swichAddr = value; OnPropertyChanged("SwichAddr"); } }
        }

        private int slaveAddr1 = 0xff;
        public int SlaveAddr1
        {
            get { return slaveAddr1; }
            set { if (value != slaveAddr1) { slaveAddr1 = value; OnPropertyChanged("SlaveAddr1"); } }
        }

        private int slaveAddr2 = 0xff;
        public int SlaveAddr2
        {
            get { return slaveAddr2; }
            set { if (value != slaveAddr2) { slaveAddr2 = value; OnPropertyChanged("SlaveAddr2"); } }
        }
        //private int slaveAddr3 = 0xff;
        //public int SlaveAddr3
        //{
        //    get { return slaveAddr3; }
        //    set { if (value != slaveAddr3) { slaveAddr3 = value; OnPropertyChanged("SlaveAddr3"); } }
        //}

        private bool buttonchecked = false;
        public bool ButtonChecked
        {
            get { return buttonchecked; }
            set { if (value != buttonchecked) { buttonchecked = value; OnPropertyChanged("ButtonChecked"); } }
        }

        private bool keyChannelInvalid = true;
        public bool KeyChannelInvalid
        {
            get { return keyChannelInvalid; }
            set { if (value != keyChannelInvalid) { keyChannelInvalid = value; OnPropertyChanged("KeyChannelInvalid"); } }
        }

        private int buttonMaxNg = 2;
        public int ButtonMaxNg
        {
            get { return buttonMaxNg; }
            set { if (value != buttonMaxNg) { buttonMaxNg = value; OnPropertyChanged("ButtonMaxNg"); } }
        }

        private int buttonLeftTime = 10;
        public int ButtonLeftTime
        {
            get { return buttonLeftTime; }
            set { if (value != buttonLeftTime) { buttonLeftTime = value; OnPropertyChanged("ButtonLeftTime"); } }
        }

        //private localKeyNum = 0;
        public int KeyNum
        {
            get { return keyNum; }
            set { keyNum = value; OnPropertyChanged("KeyNum"); }
        }
        public int PhysicalButtonNum
        {
            get { return physicalButtonNum; }
            set { physicalButtonNum = value; OnPropertyChanged("PhysicalButtonNum"); }
        }

        private int keythreshold = 0;
        public int KeyThr
        {
            get { return keythreshold; }
            set { keythreshold = value; OnPropertyChanged("KeyThr"); }
        }

        private bool linearlyTest = false;
        public bool LinearlyTest
        {
            get { return linearlyTest; }
            set { if (value != linearlyTest) { linearlyTest = value; OnPropertyChanged("LinearlyTest"); } }
        }

        private int linearlyMaxNg = 6;
        public int LinearlyMaxNg
        {
            get { return linearlyMaxNg; }
            set { if (value != linearlyMaxNg) { linearlyMaxNg = value; OnPropertyChanged("LinearlyMaxNg"); } }
        }

        private int linearlyLeftTime = 20;
        public int LinearlyLeftTime
        {
            get { return linearlyLeftTime; }
            set { if (value != linearlyLeftTime) { linearlyLeftTime = value; OnPropertyChanged("LinearlyLeftTime"); } }
        }

        private int linearlyDistance = 36;
        public int LinearlyDistance
        {
            get { return linearlyDistance; }
            set { if (value != linearlyDistance) { linearlyDistance = value; OnPropertyChanged("LinearlyDistance"); } }
        }

        private int linearlyEdge = 30;
        public int LinearlyEdge
        {
            get { return linearlyEdge; }
            set { if (value != linearlyEdge) { linearlyEdge = value; OnPropertyChanged("LinearlyEdge"); } }
        }

        //         private Visibility vertialVisible = Visibility.Collapsed;
        //         public Visibility VerticalVisible
        //         {
        //             get { return vertialVisible; }
        //             set { if (value != vertialVisible) { vertialVisible = value; OnPropertyChanged("VerticalVisible"); } }
        //         }
        // 
        //         private Visibility horizontalVisible = Visibility.Visible;
        //         public Visibility HorizontalVisible
        //         {
        //             get { return horizontalVisible; }
        //             set { if (value != horizontalVisible) { horizontalVisible = value; OnPropertyChanged("HorizontalVisible"); } }
        //         }

        private int linearlyLenth = 30;
        public int LinearlyLenth
        {
            get { return linearlyLenth; }
            set { if (value != linearlyLenth) { linearlyLenth = value; OnPropertyChanged("LinearlyLenth"); } }
        }

        private bool linearlydirection = true;
        public bool LinearlyDirection
        {
            get { return linearlydirection; }
            set { if (value != linearlydirection) linearlydirection = value; LinearlyPostion = linearlydirection ? LinearlyPostion & 0x003F : LinearlyPostion & 0x0FC0; OnPropertyChanged("LinearlyDirection"); }//modify-lhl
        }

        private int linearlyPostion = 63;
        public int LinearlyPostion
        {
            get { return linearlyPostion; }
            set { if (value != linearlyPostion) { linearlyPostion = value; OnPropertyChanged("LinearlyPostion"); } }
        }

        private int linearlyUpperLimiteH1 = 0;
        public int LinearlyUpperLimiteH1
        {
            get { return linearlyUpperLimiteH1; }
            set { if (value != linearlyUpperLimiteH1) { linearlyUpperLimiteH1 = value; OnPropertyChanged("LinearlyUpperLimiteH1"); } }
        }

        private int linearlyLowerLimiteH1 = 0;
        public int LinearlyLowerLimiteH1
        {
            get { return linearlyLowerLimiteH1; }
            set { if (value != linearlyLowerLimiteH1) { linearlyLowerLimiteH1 = value; OnPropertyChanged("LinearlyLowerLimiteH1"); } }
        }

        private int linearlyUpperLimiteH2 = 0;
        public int LinearlyUpperLimiteH2
        {
            get { return linearlyUpperLimiteH2; }
            set { if (value != linearlyUpperLimiteH2) { linearlyUpperLimiteH2 = value; OnPropertyChanged("LinearlyUpperLimiteH2"); } }
        }

        private int linearlyLowerLimiteH2 = 0;
        public int LinearlyLowerLimiteH2
        {
            get { return linearlyLowerLimiteH2; }
            set { if (value != linearlyLowerLimiteH2) { linearlyLowerLimiteH2 = value; OnPropertyChanged("LinearlyLowerLimiteH2"); } }
        }

        private int linearlyUpperLimiteH3 = 0;
        public int LinearlyUpperLimiteH3
        {
            get { return linearlyUpperLimiteH3; }
            set { if (value != linearlyUpperLimiteH3) { linearlyUpperLimiteH3 = value; OnPropertyChanged("LinearlyUpperLimiteH3"); } }
        }

        private int linearlyLowerLimiteH3 = 0;
        public int LinearlyLowerLimiteH3
        {
            get { return linearlyLowerLimiteH3; }
            set { if (value != linearlyLowerLimiteH3) { linearlyLowerLimiteH3 = value; OnPropertyChanged("LinearlyLowerLimiteH3"); } }
        }

        private int linearlyUpperLimiteH4 = 0;
        public int LinearlyUpperLimiteH4
        {
            get { return linearlyUpperLimiteH4; }
            set { if (value != linearlyUpperLimiteH4) { linearlyUpperLimiteH4 = value; OnPropertyChanged("LinearlyUpperLimiteH4"); } }
        }

        private int linearlyLowerLimiteH4 = 0;
        public int LinearlyLowerLimiteH4
        {
            get { return linearlyLowerLimiteH4; }
            set { if (value != linearlyLowerLimiteH4) { linearlyLowerLimiteH4 = value; OnPropertyChanged("LinearlyLowerLimiteH4"); } }
        }

        private int linearlyUpperLimiteH5 = 0;
        public int LinearlyUpperLimiteH5
        {
            get { return linearlyUpperLimiteH5; }
            set { if (value != linearlyUpperLimiteH5) { linearlyUpperLimiteH5 = value; OnPropertyChanged("LinearlyUpperLimiteH5"); } }
        }

        private int linearlyLowerLimiteH5 = 0;
        public int LinearlyLowerLimiteH5
        {
            get { return linearlyLowerLimiteH5; }
            set { if (value != linearlyLowerLimiteH5) { linearlyLowerLimiteH5 = value; OnPropertyChanged("LinearlyLowerLimiteH5"); } }
        }


        private int linearlyUpperLimiteH6 = 0;
        public int LinearlyUpperLimiteH6
        {
            get { return linearlyUpperLimiteH6; }
            set { if (value != linearlyUpperLimiteH6) { linearlyUpperLimiteH6 = value; OnPropertyChanged("LinearlyUpperLimiteH6"); } }
        }

        private int linearlyLowerLimiteH6 = 0;
        public int LinearlyLowerLimiteH6
        {
            get { return linearlyLowerLimiteH6; }
            set { if (value != linearlyLowerLimiteH6) { linearlyLowerLimiteH6 = value; OnPropertyChanged("LinearlyLowerLimiteH6"); } }
        }

        //
        private int linearlyUpperLimiteV1 = 0;
        public int LinearlyUpperLimiteV1
        {
            get { return linearlyUpperLimiteV1; }
            set { if (value != linearlyUpperLimiteV1) { linearlyUpperLimiteV1 = value; OnPropertyChanged("LinearlyUpperLimiteV1"); } }
        }

        private int linearlyLowerLimiteV1 = 0;
        public int LinearlyLowerLimiteV1
        {
            get { return linearlyLowerLimiteV1; }
            set { if (value != linearlyLowerLimiteV1) { linearlyLowerLimiteV1 = value; OnPropertyChanged("LinearlyLowerLimiteV1"); } }
        }

        private int linearlyUpperLimiteV2 = 0;
        public int LinearlyUpperLimiteV2
        {
            get { return linearlyUpperLimiteV2; }
            set { if (value != linearlyUpperLimiteV2) { linearlyUpperLimiteV2 = value; OnPropertyChanged("LinearlyUpperLimiteV2"); } }
        }

        private int linearlyLowerLimiteV2 = 0;
        public int LinearlyLowerLimiteV2
        {
            get { return linearlyLowerLimiteV2; }
            set { if (value != linearlyLowerLimiteV2) { linearlyLowerLimiteV2 = value; OnPropertyChanged("LinearlyLowerLimiteV2"); } }
        }

        private int linearlyUpperLimiteV3 = 0;
        public int LinearlyUpperLimiteV3
        {
            get { return linearlyUpperLimiteV3; }
            set { if (value != linearlyUpperLimiteV3) { linearlyUpperLimiteV3 = value; OnPropertyChanged("LinearlyUpperLimiteV3"); } }
        }

        private int linearlyLowerLimiteV3 = 0;
        public int LinearlyLowerLimiteV3
        {
            get { return linearlyLowerLimiteV3; }
            set { if (value != linearlyLowerLimiteV3) { linearlyLowerLimiteV3 = value; OnPropertyChanged("LinearlyLowerLimiteV3"); } }
        }

        private int linearlyUpperLimiteV4 = 0;
        public int LinearlyUpperLimiteV4
        {
            get { return linearlyUpperLimiteV4; }
            set { if (value != linearlyUpperLimiteV4) { linearlyUpperLimiteV4 = value; OnPropertyChanged("LinearlyUpperLimiteV4"); } }
        }

        private int linearlyLowerLimiteV4 = 0;
        public int LinearlyLowerLimiteV4
        {
            get { return linearlyLowerLimiteV4; }
            set { if (value != linearlyLowerLimiteV4) { linearlyLowerLimiteV4 = value; OnPropertyChanged("LinearlyLowerLimiteV4"); } }
        }

        private int linearlyUpperLimiteV5 = 0;
        public int LinearlyUpperLimiteV5
        {
            get { return linearlyUpperLimiteV5; }
            set { if (value != linearlyUpperLimiteV5) { linearlyUpperLimiteV5 = value; OnPropertyChanged("LinearlyUpperLimiteV5"); } }
        }

        private int linearlyLowerLimiteV5 = 0;
        public int LinearlyLowerLimiteV5
        {
            get { return linearlyLowerLimiteV5; }
            set { if (value != linearlyLowerLimiteV5) { linearlyLowerLimiteV5 = value; OnPropertyChanged("LinearlyLowerLimiteV5"); } }
        }


        private int linearlyUpperLimiteV6 = 0;
        public int LinearlyUpperLimiteV6
        {
            get { return linearlyUpperLimiteV6; }
            set { if (value != linearlyUpperLimiteV6) { linearlyUpperLimiteV6 = value; OnPropertyChanged("LinearlyUpperLimiteV6"); } }
        }

        private int linearlyLowerLimiteV6 = 0;
        public int LinearlyLowerLimiteV6
        {
            get { return linearlyLowerLimiteV6; }
            set { if (value != linearlyLowerLimiteV6) { linearlyLowerLimiteV6 = value; OnPropertyChanged("LinearlyLowerLimiteV6"); } }
        }

/*******************************************************************************/
        private bool explinearlyTest = false;
        public bool ExpLinearlyTest
        {
            get { return explinearlyTest; }
            set { if (value != explinearlyTest) { explinearlyTest = value; OnPropertyChanged("ExpLinearlyTest"); } }
        }

        private int explinearlyMaxNg = 6;
        public int ExpLinearlyMaxNg
        {
            get { return explinearlyMaxNg; }
            set { if (value != explinearlyMaxNg) { explinearlyMaxNg = value; OnPropertyChanged("ExpLinearlyMaxNg"); } }
        }

        private int explinearlyLeftTime = 20;
        public int ExpLinearlyLeftTime
        {
            get { return explinearlyLeftTime; }
            set { if (value != explinearlyLeftTime) { explinearlyLeftTime = value; OnPropertyChanged("ExpLinearlyLeftTime"); } }
        }

        private int explinearlyDistance = 36;
        public int ExpLinearlyDistance
        {
            get { return explinearlyDistance; }
            set { if (value != explinearlyDistance) { explinearlyDistance = value; OnPropertyChanged("ExpLinearlyDistance"); } }
        }

        private int explinearlyEdge = 30;
        public int ExpLinearlyEdge
        {
            get { return explinearlyEdge; }
            set { if (value != explinearlyEdge) { explinearlyEdge = value; OnPropertyChanged("ExpLinearlyEdge"); } }
        }

        private int explinearlyLenth = 30;
        public int ExpLinearlyLenth
        {
            get { return explinearlyLenth; }
            set { if (value != explinearlyLenth) { explinearlyLenth = value; OnPropertyChanged("ExpLinearlyLenth"); } }
        }

        private int explinearlyPostion = 0;
        public int ExpLinearlyPostion
        {
            get { return explinearlyPostion; }
            set { if (value != explinearlyPostion) { explinearlyPostion = value; OnPropertyChanged("ExpLinearlyPostion"); } }
        }

        private int explinearlyUpperLimiteH1 = 0;
        public int ExpLinearlyUpperLimiteH1
        {
            get { return explinearlyUpperLimiteH1; }
            set { if (value != explinearlyUpperLimiteH1) { explinearlyUpperLimiteH1 = value; OnPropertyChanged("ExpLinearlyUpperLimiteH1"); } }
        }

        private int explinearlyLowerLimiteH1 = 0;
        public int ExpLinearlyLowerLimiteH1
        {
            get { return explinearlyLowerLimiteH1; }
            set { if (value != explinearlyLowerLimiteH1) { explinearlyLowerLimiteH1 = value; OnPropertyChanged("ExpLinearlyLowerLimiteH1"); } }
        }

        private int explinearlyUpperLimiteH2 = 0;
        public int ExpLinearlyUpperLimiteH2
        {
            get { return explinearlyUpperLimiteH2; }
            set { if (value != explinearlyUpperLimiteH2) { explinearlyUpperLimiteH2 = value; OnPropertyChanged("ExpLinearlyUpperLimiteH2"); } }
        }

        private int explinearlyLowerLimiteH2 = 0;
        public int ExpLinearlyLowerLimiteH2
        {
            get { return explinearlyLowerLimiteH2; }
            set { if (value != explinearlyLowerLimiteH2) { explinearlyLowerLimiteH2 = value; OnPropertyChanged("ExpLinearlyLowerLimiteH2"); } }
        }

        private int explinearlyUpperLimiteH3 = 0;
        public int ExpLinearlyUpperLimiteH3
        {
            get { return explinearlyUpperLimiteH3; }
            set { if (value != explinearlyUpperLimiteH3) { explinearlyUpperLimiteH3 = value; OnPropertyChanged("ExpLinearlyUpperLimiteH3"); } }
        }

        private int explinearlyLowerLimiteH3 = 0;
        public int ExpLinearlyLowerLimiteH3
        {
            get { return explinearlyLowerLimiteH3; }
            set { if (value != explinearlyLowerLimiteH3) { explinearlyLowerLimiteH3 = value; OnPropertyChanged("ExpLinearlyLowerLimiteH3"); } }
        }

        private int explinearlyUpperLimiteH4 = 0;
        public int ExpLinearlyUpperLimiteH4
        {
            get { return explinearlyUpperLimiteH4; }
            set { if (value != explinearlyUpperLimiteH4) { explinearlyUpperLimiteH4 = value; OnPropertyChanged("ExpLinearlyUpperLimiteH4"); } }
        }

        private int explinearlyLowerLimiteH4 = 0;
        public int ExpLinearlyLowerLimiteH4
        {
            get { return explinearlyLowerLimiteH4; }
            set { if (value != explinearlyLowerLimiteH4) { explinearlyLowerLimiteH4 = value; OnPropertyChanged("ExpLinearlyLowerLimiteH4"); } }
        }

        private int explinearlyUpperLimiteH5 = 0;
        public int ExpLinearlyUpperLimiteH5
        {
            get { return explinearlyUpperLimiteH5; }
            set { if (value != explinearlyUpperLimiteH5) { explinearlyUpperLimiteH5 = value; OnPropertyChanged("ExpLinearlyUpperLimiteH5"); } }
        }

        private int explinearlyLowerLimiteH5 = 0;
        public int ExpLinearlyLowerLimiteH5
        {
            get { return explinearlyLowerLimiteH5; }
            set { if (value != explinearlyLowerLimiteH5) { explinearlyLowerLimiteH5 = value; OnPropertyChanged("ExpLinearlyLowerLimiteH5"); } }
        }

        private int explinearlyUpperLimiteV1 = 0;
        public int ExpLinearlyUpperLimiteV1
        {
            get { return explinearlyUpperLimiteV1; }
            set { if (value != explinearlyUpperLimiteV1) { explinearlyUpperLimiteV1 = value; OnPropertyChanged("ExpLinearlyUpperLimiteV1"); } }
        }

        private int explinearlyLowerLimiteV1 = 0;
        public int ExpLinearlyLowerLimiteV1
        {
            get { return explinearlyLowerLimiteV1; }
            set { if (value != explinearlyLowerLimiteV1) { explinearlyLowerLimiteV1 = value; OnPropertyChanged("ExpLinearlyLowerLimiteV1"); } }
        }

        private int explinearlyUpperLimiteV2 = 0;
        public int ExpLinearlyUpperLimiteV2
        {
            get { return explinearlyUpperLimiteV2; }
            set { if (value != explinearlyUpperLimiteV2) { explinearlyUpperLimiteV2 = value; OnPropertyChanged("ExpLinearlyUpperLimiteV2"); } }
        }

        private int explinearlyLowerLimiteV2 = 0;
        public int ExpLinearlyLowerLimiteV2
        {
            get { return explinearlyLowerLimiteV2; }
            set { if (value != explinearlyLowerLimiteV2) { explinearlyLowerLimiteV2 = value; OnPropertyChanged("ExpLinearlyLowerLimiteV2"); } }
        }

        private int explinearlyUpperLimiteV3 = 0;
        public int ExpLinearlyUpperLimiteV3
        {
            get { return explinearlyUpperLimiteV3; }
            set { if (value != explinearlyUpperLimiteV3) { explinearlyUpperLimiteV3 = value; OnPropertyChanged("ExpLinearlyUpperLimiteV3"); } }
        }

        private int explinearlyLowerLimiteV3 = 0;
        public int ExpLinearlyLowerLimiteV3
        {
            get { return explinearlyLowerLimiteV3; }
            set { if (value != explinearlyLowerLimiteV3) { explinearlyLowerLimiteV3 = value; OnPropertyChanged("ExpLinearlyLowerLimiteV3"); } }
        }

        private int explinearlyUpperLimiteV4 = 0;
        public int ExpLinearlyUpperLimiteV4
        {
            get { return explinearlyUpperLimiteV4; }
            set { if (value != explinearlyUpperLimiteV4) { explinearlyUpperLimiteV4 = value; OnPropertyChanged("ExpLinearlyUpperLimiteV4"); } }
        }

        private int explinearlyLowerLimiteV4 = 0;
        public int ExpLinearlyLowerLimiteV4
        {
            get { return explinearlyLowerLimiteV4; }
            set { if (value != explinearlyLowerLimiteV4) { explinearlyLowerLimiteV4 = value; OnPropertyChanged("ExpLinearlyLowerLimiteV4"); } }
        }

        private int explinearlyUpperLimiteV5 = 0;
        public int ExpLinearlyUpperLimiteV5
        {
            get { return explinearlyUpperLimiteV5; }
            set { if (value != explinearlyUpperLimiteV5) { explinearlyUpperLimiteV5 = value; OnPropertyChanged("ExpLinearlyUpperLimiteV5"); } }
        }

        private int explinearlyLowerLimiteV5 = 0;
        public int ExpLinearlyLowerLimiteV5
        {
            get { return explinearlyLowerLimiteV5; }
            set { if (value != linearlyLowerLimiteV5) { explinearlyLowerLimiteV5 = value; OnPropertyChanged("ExpLinearlyLowerLimiteV5"); } }
        }

        private int explinearlyDiagLength = 20;
        public int ExpLinearlyDiagLength
        {
            get { return explinearlyDiagLength; }
            set { if (value != explinearlyDiagLength) { explinearlyDiagLength = value; OnPropertyChanged("ExpLinearlyDiagLength"); } }
        }

        private int explinearlyDiagWidth = 10;
        public int ExpLinearlyDiagWidth
        {
            get { return explinearlyDiagWidth; }
            set { if (value != explinearlyDiagWidth) { explinearlyDiagWidth = value; OnPropertyChanged("ExpLinearlyDiagWidth"); } }
        }
/*******************************************************************************/

        private bool xy_reverse = false;
        public bool XY_Reverse
        {
            get { return xy_reverse; }
            set { if (value != xy_reverse) { xy_reverse = value; OnPropertyChanged("XY_Reverse"); } }
        }
        private bool x_reverse = false;
        public bool X_Reverse
        {
            get { return x_reverse; }
            set { if (value != x_reverse) { x_reverse = value; OnPropertyChanged("X_Reverse"); } }
        }
        private bool y_reverse = false;
        public bool Y_Reverse
        {
            get { return y_reverse; }
            set { if (value != y_reverse) { y_reverse = value; OnPropertyChanged("Y_Reverse"); } }

        }
        
        public override void XMLDataToView()
        {
            KeyNum = SettingMode.keyNum;
            Kpanel.ClearKeyControl();
            if (Kpanel.IsKeyControlEmpty()==true)
            {
                for (int i = 0; i < KeyNum; i++)
                {
                    var key = new KeyControl();
                    var t_caption_x = "key" + Convert.ToString(i + 1) + "_x";
                    key.SetXCaptionAndValue(t_caption_x, listKeys[i].Key);
                    var t_caption_y = "key" + Convert.ToString(i + 1) + "_y";
                    key.SetYCaptionAndValue(t_caption_y, listKeys[i].Value);
                    Kpanel.AddKeyControl(key);

                }
            }
            PhysicalButtonNum = SettingMode.physicalButtonNum;
            PhysicalKpanel.ClearKeyControl();
            if (PhysicalKpanel.IsKeyControlEmpty() == true)
            {
                for (int i = 0; i < PhysicalButtonNum; i++)
                {
                    var key = new KeyControl();
                    var t_caption_x = "Button" + Convert.ToString(i + 1) + "_x";
                    key.SetXCaptionAndValue(t_caption_x, physicalButtons[i].Key);
                    var t_caption_y = "Button" + Convert.ToString(i + 1) + "_y";
                    key.SetYCaptionAndValue(t_caption_y, physicalButtons[i].Value);
                    PhysicalKpanel.AddKeyControl(key);

                }
            }
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            //free paint
            FreePaintChecked = GetXmlAttrbuteValue(stNode, "freepaint_test", "selected", 0) > 0;
            FreePaintLeftTime = (int)GetXmlAttrbuteValue(stNode, "freepaint_test", "limited_time", 98);
            FreePaintOnce = GetXmlAttrbuteValue(stNode, "freepaint_test", "once", 1) > 0;

            SwichAddr = GetXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_selected", 0) > 0;
            SlaveAddr1 = GetXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_slaveAddr1", 0xff);
            SlaveAddr2 = GetXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_slaveAddr2", 0xff);
            //SlaveAddr3 = GetXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_slaveAddr3", 0xff);
            Type = (ushort)GetXmlAttrbuteValue(stNode, "freepaint_test", "line_type", 0);

            XY_Reverse = GetXmlAttrbuteValue(stNode, "freepaint_test", "xy_reverse", 0) > 0;
            X_Reverse = GetXmlAttrbuteValue(stNode, "freepaint_test", "x_reverse", 0) > 0;
            Y_Reverse = GetXmlAttrbuteValue(stNode, "freepaint_test", "y_reverse", 0) > 0;

            //button test
            ButtonChecked = GetXmlAttrbuteValue(stNode, "button_test", "selected", 0) > 0;
            ButtonMaxNg = (int)GetXmlAttrbuteValue(stNode, "button_test", "max_ng", 4);
            ButtonLeftTime = (int)GetXmlAttrbuteValue(stNode, "button_test", "limited_time", 10);
            KeyThr = (int)GetXmlAttrbuteValue(stNode, "button_test", "key_thr", 0);
            if (0 == KeyThr) KeyThr = SettingMode.keyThr;

            KeyChannelInvalid = GetXmlAttrbuteValue(stNode, "button_test", "key_channel_invalid", 1) > 0;

            //linearly test
            LinearlyTest = GetXmlAttrbuteValue(stNode, "linearly_test", "selected", 0) > 0;
            LinearlyMaxNg = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "max_ng", 6);
            LinearlyLeftTime = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "limited_time", 10);
            LinearlyDistance = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "distance", 36);
            LinearlyEdge = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "edge", 30);
            LinearlyPostion = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "postion", 0);
            LinearlyLenth = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lenth", 36);
            LinearlyDirection = GetXmlAttrbuteValue(stNode, "linearly_test", "linearly_direction", 1) > 0;
            LinearlyUpperLimiteH1 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h1", 0);
            LinearlyLowerLimiteH1 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h1", 0);
            LinearlyUpperLimiteH2 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h2", 0);
            LinearlyLowerLimiteH2 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h2", 0);
            LinearlyUpperLimiteH3 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h3", 0);
            LinearlyLowerLimiteH3 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h3", 0);
            LinearlyUpperLimiteH4 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h4", 0);
            LinearlyLowerLimiteH4 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h4", 0);
            LinearlyUpperLimiteH5 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h5", 0);
            LinearlyLowerLimiteH5 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h5", 0);
            LinearlyUpperLimiteH6 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h6", 0);
            LinearlyLowerLimiteH6 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h6", 0);

            LinearlyUpperLimiteV1 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v1", 0);
            LinearlyLowerLimiteV1 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v1", 0);
            LinearlyUpperLimiteV2 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v2", 0);
            LinearlyLowerLimiteV2 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v2", 0);
            LinearlyUpperLimiteV3 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v3", 0);
            LinearlyLowerLimiteV3 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v3", 0);
            LinearlyUpperLimiteV4 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v4", 0);
            LinearlyLowerLimiteV4 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v4", 0);
            LinearlyUpperLimiteV5 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v5", 0);
            LinearlyLowerLimiteV5 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v5", 0);
            LinearlyUpperLimiteV6 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v6", 0);
            LinearlyLowerLimiteV6 = (int)GetXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v6", 0);

            //exp linearly test
            ExpLinearlyTest = GetXmlAttrbuteValue(stNode, "exp_linearly_test", "selected", 0) > 0;
            ExpLinearlyMaxNg = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "max_ng", 6);
            ExpLinearlyLeftTime = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "limited_time", 10);
            ExpLinearlyDistance = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "distance", 36);
            ExpLinearlyEdge = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "edge", 30);
            ExpLinearlyPostion = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "postion", 0);
            ExpLinearlyLenth = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lenth", 36);
            ExpLinearlyUpperLimiteH1 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h1", 0);
            ExpLinearlyLowerLimiteH1 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h1", 0);
            ExpLinearlyUpperLimiteH2 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h2", 0);
            ExpLinearlyLowerLimiteH2 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h2", 0);
            ExpLinearlyUpperLimiteH3 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h3", 0);
            ExpLinearlyLowerLimiteH3 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h3", 0);
            ExpLinearlyUpperLimiteH4 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h4", 0);
            ExpLinearlyLowerLimiteH4 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h4", 0);
            ExpLinearlyUpperLimiteH5 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h5", 0);
            ExpLinearlyLowerLimiteH5 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h5", 0);

            ExpLinearlyUpperLimiteV1 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v1", 0);
            ExpLinearlyLowerLimiteV1 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v1", 0);
            ExpLinearlyUpperLimiteV2 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v2", 0);
            ExpLinearlyLowerLimiteV2 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v2", 0);
            ExpLinearlyUpperLimiteV3 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v3", 0);
            ExpLinearlyLowerLimiteV3 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v3", 0);
            ExpLinearlyUpperLimiteV4 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v4", 0);
            ExpLinearlyLowerLimiteV4 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v4", 0);
            ExpLinearlyUpperLimiteV5 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v5", 0);
            ExpLinearlyLowerLimiteV5 = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v5", 0);

            ExpLinearlyDiagLength = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "diagnol_length", 20);
            ExpLinearlyDiagWidth = (int)GetXmlAttrbuteValue(stNode, "exp_linearly_test", "diagnol_width", 10);
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            XmlNode stNode = smTesterNode.SelectSingleNode(workStation);

            //free paint
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "selected", FreePaintChecked ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "once", FreePaintOnce ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "limited_time", FreePaintLeftTime);

            SaveXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_selected", SwichAddr ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_slaveAddr1", SlaveAddr1);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_slaveAddr2", SlaveAddr2);
            //SaveXmlAttrbuteValue(stNode, "freepaint_test", "swaddr_slaveAddr3", SlaveAddr3);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "line_type", Type);

            SaveXmlAttrbuteValue(stNode, "freepaint_test", "xy_reverse", XY_Reverse ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "x_reverse", X_Reverse ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "freepaint_test", "y_reverse", Y_Reverse ? 1 : 0);

            //button test
            SaveXmlAttrbuteValue(stNode, "button_test", "selected", ButtonChecked ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "button_test", "max_ng", ButtonMaxNg);
            SaveXmlAttrbuteValue(stNode, "button_test", "limited_time", ButtonLeftTime);
            KeyThr = (KeyThr > 255) ? 255 : KeyThr;
            SaveXmlAttrbuteValue(stNode, "button_test", "key_thr", KeyThr);

            SaveXmlAttrbuteValue(stNode, "button_test", "key_channel_invalid", KeyChannelInvalid ? 1 : 0);

            //Linearly Test
            SaveXmlAttrbuteValue(stNode, "linearly_test", "selected", LinearlyTest ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "max_ng", LinearlyMaxNg);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "limited_time", LinearlyLeftTime);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "distance", LinearlyDistance);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "edge", LinearlyEdge);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lenth", LinearlyLenth);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "postion", LinearlyPostion);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "linearly_direction", LinearlyDirection ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h1", LinearlyUpperLimiteH1);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h1", LinearlyLowerLimiteH1);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h2", LinearlyUpperLimiteH2);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h2", LinearlyLowerLimiteH2);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h3", LinearlyUpperLimiteH3);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h3", LinearlyLowerLimiteH3);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h4", LinearlyUpperLimiteH4);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h4", LinearlyLowerLimiteH4);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h5", LinearlyUpperLimiteH5);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h5", LinearlyLowerLimiteH5);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_h6", LinearlyUpperLimiteH6);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_h6", LinearlyLowerLimiteH6);

            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v1", LinearlyUpperLimiteV1);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v1", LinearlyLowerLimiteV1);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v2", LinearlyUpperLimiteV2);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v2", LinearlyLowerLimiteV2);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v3", LinearlyUpperLimiteV3);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v3", LinearlyLowerLimiteV3);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v4", LinearlyUpperLimiteV4);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v4", LinearlyLowerLimiteV4);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v5", LinearlyUpperLimiteV5);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v5", LinearlyLowerLimiteV5);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "upper_limite_v6", LinearlyUpperLimiteV6);
            SaveXmlAttrbuteValue(stNode, "linearly_test", "lower_limite_v6", LinearlyLowerLimiteV6);

            //Exp Linearly Test
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "selected", ExpLinearlyTest ? 1 : 0);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "max_ng", ExpLinearlyMaxNg);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "limited_time", ExpLinearlyLeftTime);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "distance", ExpLinearlyDistance);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "edge", ExpLinearlyEdge);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lenth", ExpLinearlyLenth);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "postion", ExpLinearlyPostion);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h1", ExpLinearlyUpperLimiteH1);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h1", ExpLinearlyLowerLimiteH1);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h2", ExpLinearlyUpperLimiteH2);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h2", ExpLinearlyLowerLimiteH2);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h3", ExpLinearlyUpperLimiteH3);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h3", ExpLinearlyLowerLimiteH3);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h4", ExpLinearlyUpperLimiteH4);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h4", ExpLinearlyLowerLimiteH4);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_h5", ExpLinearlyUpperLimiteH5);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_h5", ExpLinearlyLowerLimiteH5);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v1", ExpLinearlyUpperLimiteV1);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v1", ExpLinearlyLowerLimiteV1);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v2", ExpLinearlyUpperLimiteV2);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v2", ExpLinearlyLowerLimiteV2);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v3", ExpLinearlyUpperLimiteV3);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v3", ExpLinearlyLowerLimiteV3);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v4", ExpLinearlyUpperLimiteV4);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v4", ExpLinearlyLowerLimiteV4);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "upper_limite_v5", ExpLinearlyUpperLimiteV5);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "lower_limite_v5", ExpLinearlyLowerLimiteV5);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "diagnol_length", ExpLinearlyDiagLength);
            SaveXmlAttrbuteValue(stNode, "exp_linearly_test", "diagnol_width", ExpLinearlyDiagWidth);

            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }
    }
}
