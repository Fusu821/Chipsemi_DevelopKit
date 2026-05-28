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

namespace SEMITestApp.Src.WinSub
{
    /// <summary>
    /// SinglePage.xaml 的交互逻辑
    /// </summary>
    public partial class SinglePage : Page
    {
        public SinglePage()
        {
            InitializeComponent();

            SinglePageViewMode sinModel = ViewModelManager.Instance().GetSinglePageViewMode();
            this.DataContext = sinModel;

            ViewModelManager.Instance().richTextSin = this.testMessage;

            Paragraph paragraph = new Paragraph();
           

            //Run runf = new Run()
            //{
            //    Text = "我是红色的Run",
            //    Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0))
            //};
            //paragraph.Inlines.Add(runf);
            //Run run = new Run()
            //{
            //    Text = "我是红色的Run",
            //    Background = new SolidColorBrush(Color.FromRgb(255, 0, 0))
            //};
            //paragraph.Inlines.Add(run);
            //Run run3 = new Run()
            //{
            //    Text = "我是...................................................\r\n回车换行",
            //    Background = new SolidColorBrush(Color.FromRgb(255, 0, 0))
            //};
            //paragraph.Inlines.Add(run3);

            //Hyperlink hyperlink = new Hyperlink();
            //hyperlink.Inlines.Add("我是博客园主页的链接");
            //hyperlink.MouseLeftButtonDown += ((s, arg) =>
            //{
            //    System.Diagnostics.Process proc = new System.Diagnostics.Process();
            //    proc.StartInfo.FileName = "http://www.cnblogs.com";
            //    proc.Start();
            //});
            //paragraph.Inlines.Add(hyperlink);

            //this.testMessage.Document.Blocks.Add(paragraph);

            //Paragraph paragraph2 = new Paragraph();
            //paragraph2.Inlines.Add(new Run { Text = "另取一行", Background = new SolidColorBrush(Color.FromRgb(0, 0, 255)) });
            //testMessage.Document.Blocks.Add(paragraph2);


            //testMessage.Document.Blocks.Clear();

            //int cc = testMessage.Document.Blocks.Count;

            ////Block blk = testMessage.Document.Blocks.First();
            


            //testMessage.Document.Blocks.Add(paragraph);
            //this.testMessage.Document.Blocks.Add(new Paragraph(new Run("add by run") { Foreground = Brushes.Blue }));
            //this.testMessage.Document.Blocks.Add(new Paragraph(new Run("add by run") { Foreground = Brushes.Red }));
        }
    }
}
