using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;

namespace LibraryTools
{
    class TableData
    {

        public int index { get; set; }
        public Single time { get; set; }
        public Int64 data { get; set; }
        public TableData(int index, Single time, Int64 data)
        {
            this.index = index;
            this.time = time;
            this.data = data;
        }
    }
    class ModelToolFilterTransform : INotifyPropertyChanged
    {
        private List<string> sourcedata = new List<string>();
        public List<string> SourceData 
        {
            get
            {
                return sourcedata;
            }
        }
        private List<string> filterdata = new List<string>();
        public List<string> FilterData
        {
            get
            {
                return filterdata;
            }
        }
        public List<TableData> sourcetabledata = new List<TableData>();
        public List<TableData> SourceTableData
        {
            get
            {
                return sourcetabledata;
            }
        }
        private string displaycontent = "";
        public string DisplayContent
        {
            get
            {
                return displaycontent;
            }
            set
            {
                displaycontent = value;
                // OnPropertyChanged("ProtocalParsed"); 
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs("DisplayContent"));
            }
        }

        private string filtercriteria = "";
        public string FilterCriteria
        {
            get
            {
                return filtercriteria;
            }
            set
            {
                filtercriteria = value;
                //OnPropertyChanged("Pattern");
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs("FilterCriteria"));
            }
        }

        private EnumTransformType curTransformType = EnumTransformType.Transform_IICToCSv;
        public EnumTransformType CurTransformType
        {
            get
            {
                return curTransformType;
            }
            set
            {
                if (value != curTransformType)
                {
                    curTransformType = value;
                    //OnPropertyChanged("CurSelTranslate"); 
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CurTransformType"));
                }
            }
        }
        public ICommand ClickTransform { get; set; }
        public ICommand ClickFilter { get; set; }
        public event PropertyChangedEventHandler PropertyChanged;
    }
}
