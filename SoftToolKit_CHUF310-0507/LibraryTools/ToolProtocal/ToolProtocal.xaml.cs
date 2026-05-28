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

namespace LibraryTools
{
    /// <summary>
    /// ToolProtocal.xaml 的交互逻辑
    /// </summary>
    public partial class ToolProtocal : UserControl
    {
        public ToolProtocal()
        {
            InitializeComponent();
            this.DataContext = new ToolProtocalViewModel();
        }

        private void Grid_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effects = DragDropEffects.Link;
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }
        }

        private void Grid_Drop(object sender, DragEventArgs e)
        {
            string path = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
            //string directory = System.IO.Path.GetDirectoryName(path);
            var t_ToolProtocalViewModel = this.DataContext as ToolProtocalViewModel;
            if (t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate == EnumTranslateType.Translate_PackToIIC)
            {
                t_ToolProtocalViewModel.PacketToIIC(path);
            }
            else if (t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate == EnumTranslateType.Translate_PackToSPI)
            {
                t_ToolProtocalViewModel.PacketToSPI(path);
            }
            else if (t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate == EnumTranslateType.Translate_HexToTxt)
            {
                t_ToolProtocalViewModel.PacketHexToText(path);
            }
            else if (t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate == EnumTranslateType.Translate_TxtToHex)
            {
                t_ToolProtocalViewModel.PacketTextToHex(path);
            }
            else if (t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate == EnumTranslateType.Translate_PackToSPIx)
            {
                t_ToolProtocalViewModel.PacketToSPIx(path);
            }
            else if (t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate == EnumTranslateType.Translate_PackToUSART)
            {
                t_ToolProtocalViewModel.PacketToUSART(path);
            }

            t_ToolProtocalViewModel.dcTypeToPath[t_ToolProtocalViewModel.ModelToolProtocal.CurSelTranslate] = path;
        }
    }
}
