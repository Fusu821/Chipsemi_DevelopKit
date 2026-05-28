using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using SEMI.Util;

namespace LibraryTools
{
    class ModelToolTouch : INotifyPropertyChanged
    {
        private double displayWidth = 100;
        public double DisplayWidth
        {
            get { return displayWidth; }
            set 
            {
                if (value != displayWidth)
                {
                    displayWidth = value; OnPropertyChanged("DisplayWidth"); 
                } 
            }
        }
        private double displayHeight = 100;
        public double DisplayHeight
        {
            get { return displayHeight; }
            set 
            { 
                if (value != displayHeight)
                {
                    displayHeight = value; OnPropertyChanged("DisplayHeight"); 
                } 
            }
        }
        private ImageSource _image;
        public ImageSource Image
        {
            get { return _image; }
            set
            {
                _image = value;
                OnPropertyChanged("Image");
            }
        }
        private BindingList<String> _ListPacket = new BindingList<String>();
        public BindingList<String> ListPacket
        {
            get { return _ListPacket; }
            set
            {
                if (value != _ListPacket)
                {
                    _ListPacket = value;
                   OnPropertyChanged("ListPacket");
                }
            }
        }

        public void AddListPacket(String msg)
        {
            if(ListPacket.Count()>200) ListPacket.RemoveAt(0);

            ListPacket.Add(msg);
            
        }

        private IList<SMDefinition> icType = new List<SMDefinition>()
        {
            new SMDefinition(0x0000,   "IC8006"), 
            new SMDefinition(0x0001,   "IC810"), 
        };

        public IList<SMDefinition> ICType
        {
            get { return icType; }
            private set { }
        }

        private ushort selectedIC = 0x0000;
        public ushort SelectedIC
        {
            get { return selectedIC; }
            set 
            {
                if (value != selectedIC)
                {
                    selectedIC = value; OnPropertyChanged("SelectedIC"); 
                } 
            }
        }

        private IList<SMDefinition> packages = new List<SMDefinition>()
        {
            new SMDefinition(5,   "5"), 
            new SMDefinition(6,   "6"), 
            new SMDefinition(7,   "7"), 
            new SMDefinition(8,   "8"), 
            new SMDefinition(9,   "9"), 
            new SMDefinition(10,   "10"), 

        };

        public IList<SMDefinition> Packages
        {
            get { return packages; }
            private set { }
        }

        private ushort selectedPackages = 10;
        public ushort SelectedPackages
        {
            get { return selectedPackages; }
            set
            {
                if (value != selectedPackages)
                {
                    selectedPackages = value; OnPropertyChanged("SelectedPackages");
                }
            }
        }
        
        public ICommand ctrlClickCommand { get; set; }
        //public ICommand Start { get; set; }
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
