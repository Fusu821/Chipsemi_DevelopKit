using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using SMInvokeBridge;

namespace SEMIDevelopKit.Src.WinSub
{
    public delegate bool WorkComplete();

    internal class Status
    {
        //主线程是否运行
        private static Boolean _run = false;
        public static Boolean Running { get { return _run; } set { _run = value; } }
        //主线程是否暂停
        private static Boolean _pause = false;
        public static Boolean Pausing { get { return _pause; } set { _pause = value; } }
    }

    #region 任务管理类 管理临时任务和常驻任务
    public class ProcessWork
    {
        private static readonly object Lock = new object();

        internal class TempWorkWrapper
        {
            Action actTemp = null;
            WorkComplete completeRoutine = null;
            public void Invoke()
            {
                if (null != actTemp) actTemp.Invoke();
            }
            public bool Completed()
            {
                if (null == completeRoutine) return true;
                return completeRoutine.Invoke();
            }
            public TempWorkWrapper(Action ack, WorkComplete routine)
            {
                actTemp = ack;
                completeRoutine = routine;
            }
        }
        public void Clear(bool bPerment = true)
        {
            lock (Lock)
            {
                listAckTemp.Clear();
                if (bPerment)
                {
                    ackPermanent = null;
                }
            }
        }
        public bool empty()
        {
            return listAckTemp.Count == 0;
        }
        public void AddWorkPermanent(Action persist)
        {
            lock (Lock)
            {
                ackPermanent += persist;
            }
        }
        public void AddWorkTemporary(Action temp, WorkComplete complte = null, bool topPriority = false)
        {
            lock (Lock)
            {
                if (topPriority) listAckTemp.Insert(0, new TempWorkWrapper(temp, complte));
                else listAckTemp.Add(new TempWorkWrapper(temp, complte));
            }
        }
        public void DoInvoke()
        {
            List<TempWorkWrapper> lsCopy = new List<TempWorkWrapper>();

            lock(Lock)
            {
                lsCopy.AddRange(listAckTemp);
                listAckTemp.Clear();
            }

            for (int counter = 0; counter < lsCopy.Count; )
            {
                lsCopy[counter].Invoke();

                if (lsCopy[counter].Completed())
                    lsCopy.RemoveAt(counter);
                else
                    counter++;
            }

            lock (Lock)
            {
                listAckTemp.AddRange(lsCopy);
            }

            if (null != ackPermanent) ackPermanent.Invoke();
        }
        private Action ackPermanent = null;
        private List<TempWorkWrapper> listAckTemp = new List<TempWorkWrapper>();
    }
    #endregion

    public class RuningKernel
    {
        private Boolean loopExited = false;
        protected ProcessWork runProcessWork = new ProcessWork();
        private static RuningKernel singleton = null;

        private System.Timers.Timer refreshTimer = new System.Timers.Timer();
        public System.Timers.Timer RefreshTimer { get { return refreshTimer; } }

        public ProcessWork Work { get { return runProcessWork; } }

        public static RuningKernel Instance()
        {
            if (singleton == null)
                singleton = new RuningKernel();

            return singleton;
        }
        public void StartRun()
        {
            if (Status.Running) return;

            //this.Work.Clear();

            Status.Running = true;
            Thread thread = new Thread(new ThreadStart(Run));
            thread.IsBackground = true;
            thread.Start();
        }

        public void StopRun()
        {
            loopExited = false;
            //Status.Running = false;
            runProcessWork.Clear();

            for (int index = 0; index < 30; index++)
            {
                if (loopExited) break;
                Thread.Sleep(50);
            }   
        }

        public void Pause(bool pause)
        {
            Status.Pausing = pause;
            Thread.Sleep(50);
        }

        public void Run()
        {
            while (Status.Running)
            {
                if (Status.Pausing && runProcessWork.empty())
                {
                    Thread.Sleep(300);
                    continue;
                }

                try
                {
                    runProcessWork.DoInvoke();
                }
                catch (Exception ex)
                {
                    ex.ToString();
                    //System.Windows.MessageBox.Show(ex.ToString());
                }
            }
            loopExited = true;
        }

    }
}
