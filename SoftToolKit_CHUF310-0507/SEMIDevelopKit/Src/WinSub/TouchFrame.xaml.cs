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

namespace SEMIDevelopKit.Src.WinSub
{
    /// <summary>
    /// TouchFrame.xaml 的交互逻辑
    /// </summary>
    public partial class TouchFrame : UserControl
    {
        private ModelTouch viewModel = new ModelTouch();
        public TouchFrame()
        {
            InitializeComponent();

            viewModel.DispView = FindName("dispTouch") as SEMIDevelopKit.Src.Util.WpfDisplayView;
            this.DataContext = viewModel;
        }

        private void Clear_Click(object sender, RoutedEventArgs e)
        {
            viewModel.ListPacket.Clear();
            viewModel.LocalListPacket.Clear();
        }
        private void SetPoint_Click(object sender, RoutedEventArgs e)
        {
            viewModel.ShowCoordinate = true;
            viewModel.ListPacket.Clear();

            viewModel.ShowPackets = true;

            //foreach (var item in viewModel.LocalListPacket)
            //    viewModel.ListPacket.Add(new ModelTouch.ReportPacket(viewModel.TouchPacketToString(item)));
        }
        private void SetDataPacket_Click(object sender, RoutedEventArgs e)
        {
            viewModel.ShowCoordinate = false;
            viewModel.ListPacket.Clear();

            viewModel.ShowPackets = true;

            //foreach (var item in viewModel.LocalListPacket)
            //    viewModel.ListPacket.Insert(0, new ModelTouch.ReportPacket(viewModel.TouchPacketToString(item)));
        }
        private void SaveLog_Click(object sender, RoutedEventArgs e)
        {
            string str = "";
            System.Windows.Forms.SaveFileDialog saveFileDlg = new System.Windows.Forms.SaveFileDialog();
            saveFileDlg.OverwritePrompt = true;
            saveFileDlg.Filter = "log files (*.log)|*.log";
            if (System.Windows.Forms.DialogResult.OK == saveFileDlg.ShowDialog())
            {
                string strFileName = saveFileDlg.FileName;
                System.IO.Stream stream = saveFileDlg.OpenFile();
                System.IO.StreamWriter sw = new System.IO.StreamWriter(stream, Encoding.ASCII);
                //str = "data string for dynamic catch\r\n";
                //sw.Write(str);
                //sw.WriteLine();
                foreach (var Elem in viewModel.LocalListPacket)
                {
                    str = viewModel.TouchPacketToString(Elem);

                    sw.Write(str);
                    sw.WriteLine();
                }

                sw.Close();
                stream.Close();
            }
        }
    }
}
