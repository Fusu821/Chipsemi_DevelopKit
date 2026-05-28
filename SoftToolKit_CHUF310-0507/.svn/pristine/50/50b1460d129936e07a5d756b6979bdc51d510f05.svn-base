using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;
namespace LibraryTools
{
    class ModeToolMontageBin : INotifyPropertyChanged
    {
        public uint generatebinmaxsizenum = 0;

        //public byte[] generatebincontent = new byte[128 * 1024];
        public byte[] generatebincontent = Enumerable.Repeat((byte)0xff,1024 * 128).ToArray();
        private string fristBinPath = "";
        public string FristBinPath
        {
            get 
            {
                return fristBinPath;
            }
            set 
            {
                if (fristBinPath != value)
                {
                    fristBinPath = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("FristBinPath"));
                } 
            }
        }

        private string secondBinPath = "";
        public string SecondBinPath
        {
            get
            {
                return secondBinPath;
            }
            set
            {
                if (secondBinPath != value)
                {
                    secondBinPath = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("SecondBinPath"));
                }
            }
        }

        private uint addressoffset = 0x2000;
        public uint AddressOffset
        {
            get
            {
                return addressoffset;
            }
            set
            {
                if (addressoffset != value)
                {
                    addressoffset = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("AddressOffset"));
                }
            }
        }

        public ICommand ClickFristBinLoad { get; set; }
        public ICommand ClickSecondtBinLoad { get; set; }
        public ICommand ClickGenerateBin { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

    }
}
