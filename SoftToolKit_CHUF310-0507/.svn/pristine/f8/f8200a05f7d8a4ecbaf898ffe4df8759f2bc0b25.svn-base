using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using System.ComponentModel;
using SEMI.Util;

namespace SEMITestApp.Src.Util
{
    public class TestItem : NotifyBase
    {
        public int ID { get; set; }
        public String Name { get; set; }

        private Boolean bChecked = false;
        public Boolean Checked
        {
            get { return bChecked; }
            set { if (value != bChecked) { bChecked = value; OnPropertyChanged("Checked"); } }
        }

        public Boolean MustRequied { get; set; }

        public string ItemText { get; set; }
    }
    public class SDefinition
    {
        public SDefinition(ushort val, string name)
        {
            this.TypeName = name;
            this.TypeVal = val;
        }

        public string TypeName { get; set; }
        public ushort TypeVal { get; set; }
    }

    public class SMTestItemRef : SMTestItem, INotifyPropertyChanged
    {
        public SMTestItemRef() { }
        public SMTestItemRef(SMTestItem item)
        {
            this.testCode = item.testCode;
            this.testMark = item.testMark;
            this.testName = item.testName;
            this.testResult = item.testResult;
        }
        
        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string strPropertyInfo)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(strPropertyInfo));
            }
        }

        public int ItemCode
        {
            get { return testCode; }
            set { if (value != testCode) { testCode = value; OnPropertyChanged("ItemCode"); } }
        }

        public int ItemResult
        {
            get { return testResult; }
            set { if (value != testResult) { testResult = value; OnPropertyChanged("ItemResult"); } }
        }

        public string ItemName
        {
            get { return testName; }
            set { if (value != testName) { testName = value; OnPropertyChanged("ItemName"); } }
        }

        public string ItemMark
        {
            get { return testMark; }
            set { if (value != testMark) { testMark = value; OnPropertyChanged("ItemMark"); } }
        }

        public void Reset()
        {
            ItemResult = 0;
            ItemMark = "";
        }
    }
}
