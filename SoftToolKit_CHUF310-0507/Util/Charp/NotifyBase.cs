using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Windows.Input;

namespace SEMITestApp.Src.Util
{
    public class NotifyBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string strPropertyInfo)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(strPropertyInfo));
            }
        }
    }

    public class CtrlEventDispacher : NotifyBase 
    {
        public ICommand ctrlClickCommand { get; private set; }

        public ICommand ctrlLoadedEvent { get; private set; }

        public CtrlEventDispacher()
        {
            ctrlClickCommand = new DelegateCommand(OnCtrlClickCommand, CanCtrlClick);

            ctrlLoadedEvent = new DelegateCommand(OnCtrlLoadedEvent, CanCtrlLoaded);
        }

        private bool CanCtrlClick(object param)
        {
            return true;
        }
        private bool CanCtrlLoaded(object param)
        {
            return true;
        }
        public virtual void OnCtrlLoadedEvent(object param)
        {
            
        }
        public virtual void OnCtrlClickCommand(object param)
        {

        }
    }
}
