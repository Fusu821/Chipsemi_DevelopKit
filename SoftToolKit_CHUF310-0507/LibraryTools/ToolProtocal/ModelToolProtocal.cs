using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;

namespace LibraryTools
{

    class ModelToolProtocal : INotifyPropertyChanged
    {
        private string protocalParsed = "";
        public string ProtocalParsed
        {
            get
            { 
                return protocalParsed;
            }
            set
            { 
                protocalParsed = value;
               // OnPropertyChanged("ProtocalParsed"); 
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs("ProtocalParsed"));
            }
        }

        private string pattern = "0x55aa:0x55aa:0:0x8000";
        public string Pattern
        {
            get
            {
                return pattern;
            }
            set
            {
                pattern = value; 
                //OnPropertyChanged("Pattern");
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs("Pattern"));
            }
        }

        private EnumTranslateType curSelTranslate = EnumTranslateType.Translate_PackToIIC;
        public EnumTranslateType CurSelTranslate
        {
            get 
            { 
                return curSelTranslate; 
            }
            set 
            { 
                if (value != curSelTranslate)               
                { 
                    curSelTranslate = value; 
                    //OnPropertyChanged("CurSelTranslate"); 
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CurSelTranslate"));
                } 
            }
        }

        private Boolean packetTime = false;
        public Boolean PacketTime
        {
            get 
            { 
                return packetTime;
            }
            set 
            { 
                if (value != packetTime) 
                { 
                    packetTime = value; 
                  //  OnPropertyChanged("PacketTime");
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("PacketTime"));
                } 
            }
        }

        public ICommand ClickShotCuts { get; set; }
        public ICommand ClickPattern { get; set; }
 
        public event PropertyChangedEventHandler PropertyChanged;
    }
}
