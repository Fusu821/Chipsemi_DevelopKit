using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Globalization;
using System.Windows.Input;
using System.ComponentModel;

namespace LibraryTools
{

    public class ModelToolCheckSum : INotifyPropertyChanged
    {
        private string checkSumDataInput = "";
        public string CheckSumDataInput
        {
            get { return checkSumDataInput; }
            set 
            { 
                checkSumDataInput = value;
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CheckSumDataInput"));
                //OnPropertyChanged("CheckSumDataInput");
            }
        }

        uint calcCheckSum = 0;
        public uint CalcCheckSum
        {
            get { return calcCheckSum; }
            set 
            {
                if (value != calcCheckSum)
                { 
                    calcCheckSum = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CalcCheckSum"));
                } 
            }
        }

        private CheckSumType curSelCheckSum = CheckSumType.CheckSumU16;
        public CheckSumType CurSelCheckSum
        {
            get { return curSelCheckSum; }
            set 
            { 
                if (value != curSelCheckSum)
                { 
                    curSelCheckSum = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CurSelCheckSum"));
                }
            }
        }

        public ICommand BtnCommand {get;set; }



        public event PropertyChangedEventHandler PropertyChanged;
    }
}
