using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SEMIDevelopKit.Src.WinSub
{
    public enum EnumTranslateType
    {
        Translate_PackToIIC = 0,
        Translate_PackToSPI = 1,
        Translate_HexToTxt  = 10,
        Translate_TxtToHex  = 11,
        Translate_PackToSPIx = 20,
    }
    public partial class ModeTools
    {
        private string protocalParsed = "";
        public string ProtocalParsed
        {
            get { return protocalParsed; }
            set { protocalParsed = value; OnPropertyChanged("ProtocalParsed"); }
        }

        private string pattern = "0x55aa:0x55aa:0:0x8000";
        public string Pattern
        {
            get { return pattern; }
            set { pattern = value; OnPropertyChanged("Pattern"); }
        }

        private EnumTranslateType curSelTranslate = EnumTranslateType.Translate_PackToIIC;
        public EnumTranslateType CurSelTranslate
        {
            get { return curSelTranslate; }
            set { if (value != curSelTranslate) { curSelTranslate = value; OnPropertyChanged("CurSelTranslate"); } }
        }

        private Boolean packetTime = false;
        public Boolean PacketTime
        {
            get { return packetTime; }
            set { if (value != packetTime) { packetTime = value; OnPropertyChanged("PacketTime"); } }
        }
    }
}
