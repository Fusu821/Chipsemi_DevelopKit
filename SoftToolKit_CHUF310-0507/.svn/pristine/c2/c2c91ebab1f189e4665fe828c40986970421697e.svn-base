using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SEMIDevelopKit.Src.WinSub
{
    public enum CheckSumType
    {
        CheckSumU816 = 0,
        CheckSumU16 = 1,
        CheckSumEx = 10,
        CheckSumU8 = 20,
    }
    public partial class ModeTools
    {
        private string checkSumDataInput = "";
        public string CheckSumDataInput
        {
            get { return checkSumDataInput; }
            set { checkSumDataInput = value; OnPropertyChanged("CheckSumDataInput"); }
        }

        uint calcCheckSum = 0;
        public uint CalcCheckSum
        {
            get { return calcCheckSum; }
            set { if (value != calcCheckSum) { calcCheckSum = value; OnPropertyChanged("CalcCheckSum"); } }
        }

        private CheckSumType curSelCheckSum = CheckSumType.CheckSumU16;
        public CheckSumType CurSelCheckSum
        {
            get { return curSelCheckSum; }
            set { if (value != curSelCheckSum) { curSelCheckSum = value; OnPropertyChanged("CurSelCheckSum"); } }
        }
    }
}
