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
using GDI = System.Drawing;
using SMInvokeBridge;
namespace SEMITestApp.Src.Util
{
    public class TouchReportData
    {
        public int deviceID{ get; set; }
        public TouchReportData(int device)
        {
            deviceID = device;
        }
    }
    /// <summary>
    ///
    ///     <MyNamespace:TouchDisplayView/>
    ///
    /// </summary>
    public class TouchDisplayView : FrameworkElement
    {
        public int width { get; set; }
        public int height { get; set; }
        private int localDeviceID = 0;
        private WriteableBitmap bitmap = null;
        private System.IO.MemoryStream memory = new System.IO.MemoryStream();

        public static readonly DependencyProperty TouchReportDataProperty =
            DependencyProperty.Register("TouchReportData", typeof(TouchReportData), typeof(TouchDisplayView),
            new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.None, OnTouchReportDataPropertyChanged));

        public static TouchReportData GetTouchReportData(DependencyObject d)
        {
            return (TouchReportData)d.GetValue(TouchReportDataProperty);
        }

        public static void SetTouchReportData(DependencyObject d, TouchReportData value)
        {
            d.SetValue(TouchReportDataProperty, value);
        }

        private static void OnTouchReportDataPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            TouchDisplayView trendLine = (TouchDisplayView)d;
            TouchReportData latestTouch = (TouchReportData)e.NewValue;
            trendLine.localDeviceID = latestTouch.deviceID;
            if (null != trendLine)
            {
                //trendLine.OnDataArrived(latestTouch);
                trendLine.InvalidateVisual();
            }
            else
            {

            }
        }

        protected override void OnRender(DrawingContext dc)
        {
            this.width = (int)RenderSize.Width;
            this.height = (int)RenderSize.Height;
            if (width <= 0 || height <= 0) return;

            if (bitmap == null)
            {
                this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);
            }
            else if (bitmap.Width != this.width || bitmap.Height != this.height)
            {
                this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);
            }

            bitmap.Lock();

            using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
            bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
            bitmap.BackBuffer))
            {
                using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                {
                    backBufferGraphics.Clear(System.Drawing.Color.Black);

                    IntPtr hdc = backBufferGraphics.GetHdc();

                    MainWindow.SMComplexed.SetContextForGraphTest(localDeviceID, hdc, width, height);

                    backBufferGraphics.ReleaseHdc(hdc);

                    backBufferGraphics.Flush();
                    memory.SetLength(0);
                    backBufferBitmap.Save(memory, System.Drawing.Imaging.ImageFormat.Bmp);
                }
            }

            bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)bitmap.Width, (int)bitmap.Height));
            bitmap.Unlock();

            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.BeginInit();
            bitmapImage.StreamSource = memory;
            bitmapImage.EndInit();

            dc.DrawImage(bitmapImage, new Rect(0, 0, width, height));
            base.OnRender(dc);

            
        }
    }
}
