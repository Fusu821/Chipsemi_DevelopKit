using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows.Media;
using SEMITestApp.Src.Util;
using System.Windows;
using MahApps.Metro;
using SEMITestApp.Src.WinSub;
using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;
using SEMITestApp.Src.WinSet;
using SMInvokeBridge;
using SEMI.Util;
using System.Collections.ObjectModel;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Interop;

namespace SEMITestApp.Src
{
    class MainViewModel : CtrlEventDispacher
    {
        public string Name { get; set; }
        public List<AppThemeMenuData> AppThemes { get; set; }

        public MetroWindow view  = null;


        private IDictionary<int, string> dcContentMap = new Dictionary<int, string>()
        {
            { Definition.Mode_Singleton_Test, "Src/WinSub/SinglePage.xaml" },
            { Definition.Mode_Multiple2_Test, "Src/WinSub/MutiplePage.xaml" },
            { Definition.Mode_Multiple3_Test, "Src/WinSub/MutiplePage.xaml" },
            { Definition.Mode_Multiple4_Test, "Src/WinSub/MutiplePage.xaml" },
            { Definition.Mode_Multiple5_Test, "Src/WinSub/MutiplePage.xaml" },
            { Definition.Mode_Multiple6_Test, "Src/WinSub/MutiplePage.xaml" },
            { Definition.Mode_Multiple7_Test, "Src/WinSub/MutiplePage.xaml" },
            { Definition.Mode_Multiple8_Test, "Src/WinSub/MutiplePage.xaml" },
        };
        public IDictionary<int, string> ContentMap
        {
            get { return dcContentMap; }
            private set{dcContentMap = value;}
        }

        public MainViewModel(MetroWindow win)
        {
            view = win;

            this.AppThemes = ThemeManager.AppThemes
                                           .Select(a => new AppThemeMenuData()
                                           {
                                               Name = a.Name,
                                               BorderColorBrush = a.Resources["BlackColorBrush"] as Brush,
                                               ColorBrush = a.Resources["WhiteColorBrush"] as Brush
                                           })
                                           .ToList();

        }

        private ICommand changeAccentCommand;

        public ICommand ChangeAccentCommand
        {
            get { return this.changeAccentCommand ?? (changeAccentCommand = new SimpleCommand { CanExecuteDelegate = x => true, ExecuteDelegate = x => this.DoChangeTheme(x) }); }
        }

        protected virtual void DoChangeTheme(object sender)
        {
            var theme = ThemeManager.DetectAppStyle(Application.Current);
            var accent = ThemeManager.GetAccent(this.Name);
            ThemeManager.ChangeAppStyle(Application.Current, accent, theme.Item1);
        }

        private byte[] deviceStates = new byte[ExportDeclares.MAX_DEVICE_NUMS];
        public byte[] DeviceStates
        {
            get { return deviceStates; }
            set { if (value != deviceStates)
            { 
                deviceStates = value;    
                OnPropertyChanged("DeviceStates");
                ViewModelManager.Instance().OnDeviceStatusChange(deviceStates);

                SnDevices.Clear();
                for (int index = 0; index < ViewModelManager.Instance().TestMode; index++)
                {
                    if (1 == this.DeviceStates[index])
                    {
                        SnDevices.SnDeviceEnqueue(index);
                    }
                }
            } }
        }

        private string projectInfo = "";
        public string ProjectInfo
        {
            get { return projectInfo; }
            set { if (value != projectInfo) { projectInfo = value; OnPropertyChanged("ProjectInfo"); } }
        }

        private string softWareVersion = "";
        public string SoftWareVersion
        {
            get { return softWareVersion; }
            set { if (value != softWareVersion) { softWareVersion = value; OnPropertyChanged("SoftWareVersion"); } }
        }

        private string statisticText = "";
        public string StatisticText
        {
            get { return statisticText; }
            set { if (value != statisticText) { statisticText = value; OnPropertyChanged("StatisticText"); } }
        }

//         private string tipMessage = "";
//         public string TipMessage
//         {
//             get { return tipMessage; }
//             set { if (value != tipMessage) { tipMessage = value; OnPropertyChanged("TipMessage"); } }
//         }

        private string onLineState = "OffLine";
        public string OnLineState
        {
            get { return onLineState; }
            set
            {
                if (value != onLineState)
                {
                    onLineState = value; 
                    OnPropertyChanged("OnLineState");
                    if("OffLine" == onLineState)
                        OnLineStateForground = new SolidColorBrush(Color.FromArgb(255, 100, 15, 15));
                    else
                        OnLineStateForground = new SolidColorBrush(Color.FromArgb(255, 5, 250, 250));
                }
            }
        }

        private Brush onLineStateForground = new SolidColorBrush(Color.FromArgb(255, 100, 15, 15));
        public Brush OnLineStateForground
        {
            get{return onLineStateForground;}
            set{if(value != onLineStateForground){ onLineStateForground = value; OnPropertyChanged("OnLineStateForground"); }}
        }

        private Visibility signVisible = Visibility.Collapsed;
        public Visibility SignVisible
        {
            get { return signVisible; }
            set { if (value != signVisible) { signVisible = value; OnPropertyChanged("SignVisible"); } }
        }

        private string signText = "Sign-In";
        public string SignText
        {
            get { return signText; }
            set { if (value != signText) { signText = value; OnPropertyChanged("SignText"); } }
        }

        private string lineText = "On-Line";
        public string LineText
        {
            get { return lineText; }
            set { if (value != lineText) { lineText = value; OnPropertyChanged("LineText"); } }
        }

        public void OnLineUpdate(int operation)
        {
            HwndSource hwndSource = PresentationSource.FromVisual(view) as HwndSource;
            if (0 == MainWindow.SMComplexed.OnLine((byte)operation, hwndSource.Handle))
            {
                if (1 == operation)
                {
                    LineText = "Off-Line";
                    OnLineState = "OnLine";
                    SignVisible = Visibility.Visible;
                }
                else
                {
                    LineText = "On-Line";
                    OnLineState = "OffLine";
                    SignVisible = Visibility.Collapsed;
                }
            }
            else
            {
                view.Dispatcher.Invoke((Action)(() =>
                {
                    view.ShowMessageAsync("warning", MainWindow.SMComplexed.GetOnLineMessageInfo(), MessageDialogStyle.Affirmative);
                }));
            }
        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if("main-sigletp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Singleton_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if("main-number2tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple2_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-number3tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple3_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if("main-number4tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple4_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-number4tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple4_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-number5tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple5_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-number6tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple6_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-number7tp-click" == strParam)
            {
                ViewModelManager.Instance().TestMode = Definition.Mode_Multiple7_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-number8tp-click" == strParam)
            {
                 ViewModelManager.Instance().TestMode = Definition.Mode_Multiple8_Test;
                FrameContent = dcContentMap[ViewModelManager.Instance().TestMode];
            }
            else if ("main-flayout-click" == strParam)
            {
                ((MainWindow)view).ShowFlyout();
            }
            else if ("online-line-click" == strParam)
            {
                int operation = ("On-Line" == LineText) ? 1 : 0;

                OnLineUpdate(operation);
            }
            else if ("online-sign-click" == strParam)
            {
                if ("Sign-In" == SignText)
                {
                    Task<LoginDialogData> task = view.ShowLoginAsync("Account Check", "Enter your password",
                    new LoginDialogSettings { ColorScheme = view.MetroDialogOptions.ColorScheme, InitialUsername = "C99999" });

                    task.ContinueWith(t =>
                    {
                        LoginDialogData login = t.Result as LoginDialogData;
                        if (null == login) return;
                        if (0 == MainWindow.SMComplexed.Sign(1, "", login.Username, login.Password))
                        {
                            view.Dispatcher.Invoke((Action)(() =>
                            {
                                SignText = "Sign-Out";
                                OnLineState = "OnLine" + "-" + login.Username;
                                ((MainWindow)view).ShowFlyout();
                            }));
                        }
                        else
                        {
                            view.ShowMessageAsync("warning", MainWindow.SMComplexed.GetOnLineMessageInfo(), MessageDialogStyle.Affirmative);
                        }
                    });
                }
                else
                {
                    SignText = "Sign-In";
                    OnLineState = "OnLine" + "-";
                }
            }
            else if("main-login-click" == strParam)
            {
                Task<LoginDialogData> task = view.ShowLoginAsync("Login", "Enter your password",
                   new LoginDialogSettings { ColorScheme = view.MetroDialogOptions.ColorScheme, InitialUsername = "admin" });

                task.ContinueWith(t =>
                {
                    LoginDialogData login = t.Result as LoginDialogData;
                    if (null == login) return;
                    if(login.Password == "admin")
                    {
                        //develop
                    }
                    else if(login.Password == "fae")
                    {
                        view.Dispatcher.Invoke((Action)(() => {

                            MainWindow.SMComplexed.GameOver( 0 );
                            new SettingFrame() { Owner = view }.ShowDialog();

                            MainWindow.SMComplexed.GameOver( 1 );
                            MainWindow.SMComplexed.ReloadXmlConfig();
                            ((MainWindow)view).InitMainTestView();

                            List<SMTestItem> listItems = new List<SMTestItem>();
                            MainWindow.SMComplexed.GetAllTestItemLists(0, listItems);
                            ViewModelManager.Instance().InitializeListView(listItems);
                            
                        }));   
                    }
                });

                //LoginDialogData result = await view.ShowLoginAsync("Authentication", "Enter your credentials",
                //    new LoginDialogSettings { ColorScheme = view.MetroDialogOptions.ColorScheme, InitialUsername = "MahApps" });
                //if (result == null)
                //{
                //    User pressed cancel 
                //}
                //else
                //{
                //    MessageDialogResult messageResult = await view.ShowMessageAsync("Authentication Information",
                //        String.Format("Username: {0}\nPassword: {1}", result.Username, result.Password));
                //}
            }
        }

        public override void OnCtrlLoadedEvent(object param)
        {
            
        }

        private string frameContent = "Src/WinSub/SinglePage.xaml";
        //private string frameContent = "Src/WinSub/MutiplePage.xaml";
        public string FrameContent
        {
            get { return frameContent; }
            set { if (value != frameContent) { frameContent = value; OnPropertyChanged("FrameContent"); } }
        }
    }
}
