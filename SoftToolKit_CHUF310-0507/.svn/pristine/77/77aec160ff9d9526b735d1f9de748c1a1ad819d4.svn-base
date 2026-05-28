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
    public class ModelToolRawData : INotifyPropertyChanged
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

        private int iReferenceData = 12000;
        public int ReferenceData
        {
            get { return iReferenceData; }
            set { if (value != iReferenceData) { iReferenceData = value; OnPropertyChanged("ReferenceData"); } }
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
        public ICommand ctrlClickCommand { get; set; }
        //public ICommand Start { get; set; }
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
