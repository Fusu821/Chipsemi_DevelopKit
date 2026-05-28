using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using SMInvokeBridge;
using SEMIDevelopKit.Src.Util;
using System.Windows.Markup;

namespace SEMIDevelopKit.Src.WinSub
{
    /// <summary>
    /// TuningFrame.xaml 的交互逻辑
    /// </summary>
    public partial class TuningFrame : UserControl
    {
        private IDictionary<string, Action<string>> mapRoleAction = new Dictionary<string, Action<string>>();
        //private TuningViewModel logic = null;

        public static readonly DependencyProperty ButtonCommandProperty =
             DependencyProperty.Register("ButtonCommand", typeof(RoutedCommand), typeof(TuningFrame), new PropertyMetadata(null));

        public RoutedCommand ButtonCommand
        {
            get { return (RoutedCommand)GetValue(ButtonCommandProperty); }
            set { SetValue(ButtonCommandProperty, value); }
        }

        public TuningFrame()
        {
            InitializeComponent();

            InitButtonAction();

            //LoadTuningPage();
        }

        public void ActionOnICChanged()
        {
            LoadTuningPage();
        }

        private void LoadTuningPage()
        {
            this.ButtonCommand = new RoutedCommand();
            var bin = new CommandBinding(this.ButtonCommand);
            bin.Executed += OnTuningButtonExecuted;
            this.CommandBindings.Add(bin);

            ushort icCode = MainViewModel.Intr.SelectedIC;
            string zipFolder = TuningViewModel.GetTuningDirectory();
            string packetName = eChipTypeList.GetIcName((ushort)(icCode & 0xff00));
            //UnZipTuningResource(zipFolder + packetName + ".zip", zipFolder, "123456");

            try
            {
                this.tuningGrid.Children.Clear();
                TuningViewModel.Instance = SMDevelopChipReflex.Instance.GetSemiModuleByChipAndType(SMDevelopChipReflex.SEMI_DEVLOP_TUNING, icCode) as TuningViewModel;
                TuningViewModel.Instance.ICKindName = packetName;
                TuningViewModel.Instance.ButtonCommand = ButtonCommand;
                TuningViewModel.Instance.Parse();
                this.DataContext = TuningViewModel.Instance;

                ParserContext pContext = new ParserContext();
                pContext.XamlTypeMapper = new XamlTypeMapper(new string[] { });
                pContext.XamlTypeMapper.AddMappingProcessingInstruction("clr-namespace:SEMIDevelopKit.Src.WinSub", "SEMIDevelopKit.Src.WinSub", "SEMIDevelopKit");
                pContext.XmlnsDictionary.Add("viewModel", "clr-namespace:SEMIDevelopKit.Src.WinSub");


                string fullPath = zipFolder + packetName + "\\MainTuningPage.xaml";
                using (System.IO.FileStream fs = new System.IO.FileStream(fullPath, System.IO.FileMode.Open))
                {
                    UserControl obj = XamlReader.Load(fs, pContext) as UserControl;
                    obj.DataContext = TuningViewModel.Instance;
                    this.tuningGrid.Children.Add((UIElement)obj);
                    TuningViewModel.Instance.OnInitialized(TuningViewModel.Instance.BufferOS);
                }
            }
            catch
            {
                TextBlock txtMessage = new TextBlock();
                txtMessage.Text = "UnSupported function, Please wait...";
                txtMessage.FontSize = 30;
                txtMessage.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
                txtMessage.TextAlignment = TextAlignment.Center;
                txtMessage.VerticalAlignment = System.Windows.VerticalAlignment.Center;
                this.tuningGrid.Children.Add((UIElement)txtMessage);
            }
        }

        private void OnTuningButtonExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            var btnClicked = e.OriginalSource as Button;
            if (null == btnClicked) return;

            var action = mapRoleAction.FirstOrDefault(c => 0 == c.Key.CompareTo(btnClicked.Name)).Value;
            if (null != action)
                action.Invoke(btnClicked.Name);
            else
                TuningViewModel.Instance.OnButtonClicked(btnClicked.Name, TuningViewModel.Instance.BufferOS);
        }

        private void InitButtonAction()
        {
            mapRoleAction.Clear();

            mapRoleAction["Save"] = (t) =>
            {
                TuningViewModel.Instance.OnButtonClicked(t, TuningViewModel.Instance.BufferOS);
            };

            mapRoleAction["Prev"] = (t) =>
            {
//                 TabControl tab = this.tuningGrid.GetElementByName("TabMain") as TabControl;
//                 if (null != tab)
//                 {
//                     int selectIndex = Math.Max(0, tab.SelectedIndex);
//                     while (selectIndex > 0)
//                     {
//                         selectIndex--;
//                         TabItem item = tab.Items[selectIndex] as TabItem;
//                         if (item.IsVisible) break;
//                     }
//                     tab.SelectedIndex = selectIndex;
// 
//                     logic.OnButtonClicked(t, TuningViewModel.GetInstance().BufferOS);
//                 }
            };

            mapRoleAction["Next"] = (t) =>
            {
//                 TabControl tab = this.tuningGrid.GetElementByName("TabMain") as TabControl;
//                 if (null != tab)
//                 {
//                     int selectIndex = Math.Min(tab.Items.Count - 1, tab.SelectedIndex);
//                     while (selectIndex < tab.Items.Count - 1)
//                     {
//                         selectIndex++;
//                         TabItem item = tab.Items[selectIndex] as TabItem;
//                         if (item.IsVisible) break;
//                     }
//                     tab.SelectedIndex = selectIndex;
// 
//                     logic.OnButtonClicked(t, TuningViewModel.GetInstance().BufferOS);
//                 }
            };

//             mapRoleAction["LoadBin"] = (t) =>
//             {
//                 Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
//                 openFileDialog.Filter = "Bin File(*.bin)|*.bin";
//                 openFileDialog.RestoreDirectory = true;
//                 openFileDialog.FilterIndex = 1;
//                 openFileDialog.InitialDirectory = Directory.GetCurrentDirectory();
//                 if (openFileDialog.ShowDialog() == true)
//                 {
//                     string fileName = openFileDialog.FileName;
// 
//                     bool bRet = TuningViewModel.Instance.CheckAppFile(fileName);
//                     if (true == bRet)
//                     {
//                         new System.Threading.Thread(() =>
//                         {
//                             TuningViewModel.Instance.LoadBinFromOutSite(fileName);
//                         }).Start();
// 
//                         //告知DLL  某个按钮触发了Click事件
//                         TuningViewModel.Instance.OnButtonClicked(t, TuningViewModel.Instance.BufferOS);
//                     }
//                 }
//             };

            mapRoleAction["Debug"] = (t) =>
            {
                string strDebugInfo = "";
                foreach (var item in AnyTypeDataManager.mapAnyData)
                {
                    AnyTypeData data = item.Value;
                    string strItem = "";
                    strItem += string.Format("{0,-26}", data.Name);
                    strItem += string.Format("{0,-10}", data.SType.ToString());
                    strItem += string.Format("0x{0:x4}   ", data.StartAddress.ToString());
                    strItem += string.Format("{0,-10}", data.ItemNum.ToString());
                    string strFormat = string.Format("{{0:X{0}}}, ", AnyTypeDataManager.mapItemSize[data.SType] * 2);
                    for (int index = 0; index < data.ItemNum; index++)
                    {
                        int value = 0;
                        for (int counter = 0; counter < AnyTypeDataManager.mapItemSize[data.SType]; counter++)
                        {
                            value = value << 8;
                            value += TuningViewModel.Instance.BufferOS[data.StartAddress + index * AnyTypeDataManager.mapItemSize[data.SType] + counter];
                        }
                        strItem += string.Format(strFormat, value);
                    }
                    strDebugInfo += strItem + "\r\n";
                }

                Microsoft.Win32.SaveFileDialog sfd = new Microsoft.Win32.SaveFileDialog();
                sfd.Filter = "(*.txt)|*.txt|(*.*)|*.*";
                sfd.AddExtension = true;
                sfd.RestoreDirectory = true;
                if (true == sfd.ShowDialog())
                {
                    using (FileStream fs = new FileStream(sfd.FileName, FileMode.Create))
                    {
                        StreamWriter sw = new StreamWriter(fs);
                        sw.Write(strDebugInfo);
                        sw.Flush();
                    }
                }

                //告知DLL  某个按钮触发了Click事件
                TuningViewModel.Instance.OnButtonClicked(t, TuningViewModel.Instance.BufferOS);
            };
        }

        private void UnZipTuningResource(string pathZip, string folder, string password)
        {
            try
            {
                string[] strDirs = System.IO.Directory.GetDirectories(folder);
                foreach (var dir in strDirs)
                    Directory.Delete(dir, true);

                UnZipClass.UnZip(pathZip, folder, password);

                if (System.IO.Directory.GetDirectories(folder).Length > 0)
                {
                    string xmlPath = System.IO.Directory.GetDirectories(folder)[0];
                    DirectoryInfo dir = new DirectoryInfo(xmlPath);
                    File.SetAttributes(xmlPath, dir.Attributes | FileAttributes.Hidden & ~FileAttributes.ReadOnly);
                }
            }
            catch
            {

            }
        }

    }
}
