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
using SEMIDevelopKit.Src.WinSub;
namespace SEMIDevelopKit.Src.Util
{
    public class TPoint
    {
        public ushort X;
        public ushort Y;
        public ushort Z;
        public byte   ID;
    }
    public class TouchReportData
    {
        protected byte[] report = null;
        protected TPoint[] points = new TPoint[ExportDeclares.SM_MAX_NUM_POINT];
        public TouchReportData(byte[] report)
        {
            this.report = new byte[report.Length];
            Array.Copy(report, this.report, report.Length);
        }
        public virtual byte TCnt { get;set; }
        public virtual ushort Msk { get; set; }
        public virtual bool Valid()
        {
            return false;
        }
        public virtual TouchReportData Colne()
        {
            return null;
        }

        public virtual TPoint Points(int index)
        {
            return null;
        }
        public override string ToString()
        {
            StringBuilder strRet = new StringBuilder();
            int len = report.Length;
            for (int index = 0; index < len; index++)
            {
                strRet.Append("0x" + report[index].ToString("X2") + ",");
            }
            strRet = strRet.Remove(strRet.Length - 1, 1);

            return strRet.ToString();
        }
    }

    public class SCapTouchReportData : TouchReportData
    {
        public SCapTouchReportData(byte[] report)
            :base(report)
        {
            for (int index = 0; index < 2; index++)
            {
                TPoint pt = new TPoint();
                pt.X = (ushort)((report[5 + index * 6] << 8) + report[4 + index * 6]);
                pt.Y = (ushort)((report[7 + index * 6] << 8) + report[6 + index * 6]);
                pt.Z = (byte)(report[8 + index * 6]);
                pt.ID = (byte)(report[9 + index * 6]);
                //if (pt.ID >= 2) continue;

                if (index < TCnt && pt.ID < 2)
                {
                    points[pt.ID] = pt;
                }
            }
        }

        public override byte TCnt { get { return (byte)(report[0] & 0x0f); } }
        public override ushort Msk { get { return (ushort)((report[3] << 8) + report[2]); } }

        public override bool Valid()
        {
            return TCnt <= 2;
        }
        public override TPoint Points(int id)
        {
            return points[id];
        }
        public override TouchReportData Colne()
        {
            return new SCapTouchReportData(report);
        }
    }

    public class MCapTouchReportData : TouchReportData
    {
        public MCapTouchReportData(byte[] report)
            : base(report)
        {
            for (int index = 0; index < ExportDeclares.SM_MAX_NUM_POINT; index++)
            {
                TPoint pt = new TPoint();
                pt.X = (ushort)(((report[5 + index * 5] & 0x0f) << 8) + report[2 + index * 5]);
                pt.Y = (ushort)(((report[5 + index * 5] & 0xf0) << 4) + report[3 + index * 5]);
                pt.Z = (ushort)(report[4 + index * 5]);
                pt.ID = (byte)(report[6 + index * 5] & 0x0f);

                if (index < TCnt && pt.ID < ExportDeclares.SM_MAX_NUM_POINT)
                {
                    points[pt.ID] = pt;
                }
            }
        }

        public override byte TCnt { get { return (byte)(report[1] & 0x0f); } }
        public override ushort Msk 
        { 
            get 
            { 
                ushort temp = 0;
                for (int index = 0; index < TCnt; index++)
                    temp |= (ushort)(0x0001 << index);
                return temp;
            }
        }

        public override bool Valid()
        {
            if (TCnt >= 0x0f) return false;
            if (0 == report[0]) return false;

            return true;
        }
        public override TPoint Points(int id)
        {
            return points[id];
        }
        public override TouchReportData Colne()
        {
            return new MCapTouchReportData(report);
        }
    }


    public class TickRate
    {
        private int tickCount = 0;
        private long systemTime = 0;
        private double dwRate = 0;

        public TickRate()
        {

        }
        public bool TickComplete()
        {
            if (++tickCount >= 100)
            {
                long current = DateTime.Now.Ticks;
                long dev = current - systemTime;
                dwRate = tickCount * 10000000 / (current - systemTime);
                tickCount = 0;
                systemTime = current;

                return true;
            }
            return false;
        }
        public double Rate { get { return dwRate; } }
    }
    /// <summary>
    ///
    ///     <MyNamespace:TouchDisplayView/>
    ///
    /// </summary>
    public class WpfDisplayView : FrameworkElement
    {
        public int width { get; set; }
        public int height { get; set; }
        private bool PendingClean = false;
        private WriteableBitmap bitmap = null;
        private TouchReportData lastTouch = null;
        private TickRate tickRate = new TickRate();

        private GDI.Pen[] pen = new GDI.Pen[]
        {
            new GDI.Pen(GDI.Color.Blue, 1),
            new GDI.Pen(GDI.Color.Red, 1),
            new GDI.Pen(GDI.Color.GreenYellow, 1),
            new GDI.Pen(GDI.Color.LightGreen, 1),
            new GDI.Pen(GDI.Color.Green, 1),
            new GDI.Pen(GDI.Color.DarkRed, 1),
            new GDI.Pen(GDI.Color.Gold, 1),
            new GDI.Pen(GDI.Color.LightSkyBlue, 1),
            new GDI.Pen(GDI.Color.Orange, 1),
            new GDI.Pen(GDI.Color.Silver, 1),
        };
        private GDI.Brush[] brush = new GDI.Brush[]
        {
            new GDI.SolidBrush(GDI.Color.Blue),
            new GDI.SolidBrush(GDI.Color.Red),
            new GDI.SolidBrush(GDI.Color.GreenYellow),
            new GDI.SolidBrush(GDI.Color.LightGreen),
            new GDI.SolidBrush(GDI.Color.Green),
            new GDI.SolidBrush(GDI.Color.DarkRed),
            new GDI.SolidBrush(GDI.Color.Gold),
            new GDI.SolidBrush(GDI.Color.LightSkyBlue),
            new GDI.SolidBrush(GDI.Color.Orange),
            new GDI.SolidBrush(GDI.Color.Silver),
        };

        public static readonly DependencyProperty TouchProperty =
            DependencyProperty.Register("Touch", typeof(TouchReportData), typeof(WpfDisplayView),
            new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.None, OnTouchPropertyChanged));

        public static TouchReportData GetTouch(DependencyObject d)
        {
            return (TouchReportData)d.GetValue(TouchProperty);
        }

        public static void SetTouch(DependencyObject d, TouchReportData value)
        {
            d.SetValue(TouchProperty, value);
        }

        private static void OnTouchPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDisplayView trendLine = (WpfDisplayView)d;
            TouchReportData latestTouch = (TouchReportData)e.NewValue;
            if (null != trendLine)
            {
                trendLine.OnTouchReport(latestTouch);
            }
            else
            {

            }
        }

        public static readonly DependencyProperty XLinesProperty =
            DependencyProperty.Register("XLines", typeof(int), typeof(WpfDisplayView),
            new FrameworkPropertyMetadata(10, FrameworkPropertyMetadataOptions.None, OnXLinesPropertyChanged));

        public static int GetXLines(DependencyObject d)
        {
            return (int)d.GetValue(XLinesProperty);
        }

        public static void SetXLines(DependencyObject d, int value)
        {
            d.SetValue(XLinesProperty, value);
        }

        private static void OnXLinesPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDisplayView trendLine = (WpfDisplayView)d;
            int xLines = (int)e.NewValue;
            if (null != trendLine)
            {
                
            }
            else
            {

            }
        }

        public static readonly DependencyProperty YLinesProperty =
            DependencyProperty.Register("YLines", typeof(int), typeof(WpfDisplayView),
            new FrameworkPropertyMetadata(10, FrameworkPropertyMetadataOptions.None, OnYLinesPropertyChanged));

        public static int GetYLines(DependencyObject d)
        {
            return (int)d.GetValue(YLinesProperty);
        }

        public static void SetYLines(DependencyObject d, int value)
        {
            d.SetValue(YLinesProperty, value);
        }

        private static void OnYLinesPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfDisplayView trendLine = (WpfDisplayView)d;
            int yLines = (int)e.NewValue;
            if (null != trendLine)
            {

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

            ModelTouch viewModel = this.DataContext as ModelTouch;
            if (0 == ModelBase.YPixel) return;
            viewModel.DisplayWidth = height * ModelBase.XPixel / ModelBase.YPixel;
            

            if (bitmap == null)
            {
                this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);
                PendingClean = true;
            }
            else if (bitmap.Width != this.width || bitmap.Height != this.height)
            {
                this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);
                PendingClean = true;
            }

            WriteableBitmap nBitMap = this.bitmap.CloneCurrentValue();

//             nBitMap.Lock();
// 
//             using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
//             this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
//             nBitMap.BackBuffer))
//             {
//                 using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
//                 {
//                     backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
//                     backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;
//                     ClearBitmap(backBufferGraphics);
// 
//                     backBufferGraphics.Flush();
//                 }
//             }
// 
//             nBitMap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
//             nBitMap.Unlock();

            dc.DrawImage(nBitMap, new Rect(0, 0, width, height));
            base.OnRender(dc);
        }

        private void ClearScreen()
        {
            ModelTouch viewModel = this.DataContext as ModelTouch;

            if (!viewModel.ClearScreen) return;

            this.bitmap.Lock();

            using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
                this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
                this.bitmap.BackBuffer))
            {
                using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                {
                    if (viewModel.ClearScreen)
                    {
                        PendingClean = true;
                        viewModel.ClearScreen = false;
                        ClearBitmap(backBufferGraphics);
                        backBufferGraphics.Flush();
                    }
                }
            }
            this.bitmap.AddDirtyRect(new Int32Rect(0, 0, width, height));
            this.bitmap.Unlock();
        }

        public void OnTouchReport(TouchReportData touch)
        {
            //if (touch.TCnt > 10) return;
            if (!touch.Valid()) return;
            if (null == this.bitmap) return;
            if (0 == touch.TCnt && null == lastTouch) return;

            ModelTouch viewModel = this.DataContext as ModelTouch;
            viewModel.ReportPacketToCatch(touch);
            if (null == lastTouch) { lastTouch = touch.Colne(); return; }
            

            //viewModel.ReportPacketToCatch(new SEMIDevelopKit.Src.WinSub.ModelTouch.ReportPacket(TouchPacketToString(touch)));
            

            if (touch.TCnt == 0 /*&& (byte)lastTouch.Msk == 0*/)
            {
                lastTouch = null;
                PendingClean = true;
                return;
            }

//             ushort lastPacketCnt = 0, thisPacketCnt = 0;
//             lastPacketCnt = (ushort)((lastTouch.Report[83] << 8) + lastTouch.Report[82]);
//             thisPacketCnt = (ushort)((touch.Report[83] << 8) + touch.Report[82]);
//             if (thisPacketCnt - lastPacketCnt > 1)
//             {
//                 int index = 0;
//             }


            ClearScreen();

           

            if (tickRate.TickComplete())
            {
                viewModel.ReportRate = (uint)tickRate.Rate;
            }

            this.bitmap.Lock();

            using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
                this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
                this.bitmap.BackBuffer))
            {
                using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                {
                    backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                    backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;

//                     if (touch.TCnt <= 0)
//                     {
//                         
//                     }
//                     else
//                     {
                        if (PendingClean && viewModel.GraphOnce)
                        {
                            //backBufferGraphics.Clear(m_backColor);
                            //backBufferGraphics.FillEllipse(new GDI.SolidBrush(GDI.Color.Black), 0, 0, width, height);
                            ClearBitmap(backBufferGraphics);
                            PendingClean = false;
                        }

                        if (1 == viewModel.GraghMode)
                            DrawInLineMode(backBufferGraphics, touch);
                        else
                            DrawInPointMode(backBufferGraphics, touch);

                        string strRate = viewModel.ReportRate.ToString();
                        GDI.Font textFont = new GDI.Font("Arial", viewModel.PointSize * 1.2f, GDI.FontStyle.Bold);
                        GDI.SizeF sizeF = backBufferGraphics.MeasureString(strRate, textFont);
                        backBufferGraphics.FillRectangle(new GDI.SolidBrush(GDI.Color.Black), 0, 0, sizeF.Width, sizeF.Height);
                        backBufferGraphics.DrawString(strRate, textFont, new GDI.SolidBrush(GDI.Color.Red), new GDI.PointF(0, 0));

                        lastTouch = touch.Colne();
                   //}

                    backBufferGraphics.Flush();
                }
            }

            this.bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
            this.bitmap.Unlock();

            this.InvalidateVisual();
        }

        private void DrawInLineMode(GDI.Graphics backBufferGraphics, TouchReportData touch)
        {
            ModelTouch viewModel = this.DataContext as ModelTouch;
            for (int ptId = 0; ptId < ExportDeclares.SM_MAX_NUM_POINT; ptId++)
            {
                TPoint lastPt = lastTouch.Points(ptId);
                TPoint thisPt = touch.Points(ptId);

                if (null == lastPt && null == thisPt)
                {
                    //no point
                }
                else if ((null == lastPt) && (thisPt.ID < ExportDeclares.SM_MAX_NUM_POINT))
                {
                    //event dowm
                }
                else if ((lastPt.ID < ExportDeclares.SM_MAX_NUM_POINT) && (null == thisPt))
                {
                    //event up
                }
                else
                {
                    GDI.Point ptScreen = new GDI.Point();
                    GDI.Point lastScreen = new GDI.Point();
                    GDI.Rectangle rcTp = new GDI.Rectangle(0, 0, ModelBase.XPixel, ModelBase.YPixel);
                    GDI.Rectangle rcScreen = new GDI.Rectangle(0, 0, (int)width, (int)height);

                    SMChipBase.SMScreenXYChange(lastPt.X, lastPt.Y, ref lastScreen, rcTp, rcScreen);
                    SMChipBase.SMScreenXYChange(thisPt.X, thisPt.Y, ref ptScreen, rcTp, rcScreen);

                    pen[ptId].Width = viewModel.LineSize;
                    backBufferGraphics.DrawLine(pen[ptId], lastScreen, ptScreen);
                    backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.White, viewModel.LineSize),
                        lastScreen.X - viewModel.LineSize / 2, lastScreen.Y - viewModel.LineSize / 2, viewModel.LineSize, viewModel.LineSize);
                    backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.White, viewModel.LineSize),
                        ptScreen.X - viewModel.LineSize / 2, ptScreen.Y - viewModel.LineSize / 2, viewModel.LineSize, viewModel.LineSize);
                }
            }
        }

        private void DrawInPointMode(GDI.Graphics backBufferGraphics, TouchReportData touch)
        {
            ModelTouch viewModel = this.DataContext as ModelTouch;
            ClearBitmap(backBufferGraphics);

            for (int ptId = 0; ptId < ExportDeclares.SM_MAX_NUM_POINT; ptId++)
            {
                //TPoint lastPt = lastTouch.Points(ptId);
                TPoint thisPt = touch.Points(ptId);

                if (null == thisPt) continue;

                GDI.Point ptScreen = new GDI.Point();
                GDI.Rectangle rcTp = new GDI.Rectangle(0, 0, ModelBase.XPixel, ModelBase.YPixel);
                GDI.Rectangle rcScreen = new GDI.Rectangle(0, 0, (int)width, (int)height);
                SMChipBase.SMScreenXYChange(thisPt.X, thisPt.Y, ref ptScreen, rcTp, rcScreen);

                if (0 == viewModel.DrawType)
                    backBufferGraphics.FillRectangle(brush[ptId], ptScreen.X - viewModel.PointSize / 2,
                        ptScreen.Y - viewModel.PointSize / 2, viewModel.PointSize, viewModel.PointSize);
                else
                    backBufferGraphics.FillEllipse(brush[ptId], ptScreen.X - viewModel.PointSize / 2,
                        ptScreen.Y - viewModel.PointSize / 2, viewModel.PointSize, viewModel.PointSize);

                string strPixel = thisPt.X.ToString() + "," + thisPt.Y.ToString();

                GDI.Font text = new GDI.Font("Arial", viewModel.PointSize, GDI.FontStyle.Bold);
                GDI.SizeF size = backBufferGraphics.MeasureString(strPixel, text);
                backBufferGraphics.DrawString(strPixel, text, brush[ptId],
                    new GDI.PointF(ptScreen.X - size.Width / 2, ptScreen.Y + viewModel.PointSize / 2));
            }
        }

        private void ClearBitmap(GDI.Graphics backBufferGraphics)
        {
            ModelTouch viewModel = this.DataContext as ModelTouch;

            double xDelta = (double)width / (viewModel.LinesX);
            double yDelta = (double)height / (viewModel.LinesY);

            backBufferGraphics.Clear(GDI.Color.Black);

            for (int iCol = 0; iCol < viewModel.LinesX; iCol++)
            {
                GDI.Point pt1 = new GDI.Point((int)(xDelta * (iCol + 1)), 0);
                GDI.Point pt2 = new GDI.Point((int)(xDelta * (iCol + 1)), height);
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Gray, 1), pt1, pt2);
            }
            for (int iRow = 0; iRow < viewModel.LinesY; iRow++)
            {
                GDI.Point pt1 = new GDI.Point(0, (int)(yDelta * (iRow + 1)));
                GDI.Point pt2 = new GDI.Point(width, (int)(yDelta * (iRow + 1)));
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Gray, 1), pt1, pt2);
            }
        }

//         private string TouchPacketToString(TouchReportData touch)
//         {
//             StringBuilder strRet = new StringBuilder();
//             ModelTouch viewModel = this.DataContext as ModelTouch;
//             if (viewModel.ShowCoordinate)
//             {
//                 if (touch.TCnt == 0) return "None";
//                 int pointNumber = 0;
//                 for (int index = 0; index < touch.TCnt; index++)
//                 {
//                     if (index >= 10) break;
//                     if (touch.Points(index).X == 0xffff) continue;
//                     if (touch.Points(index).Y == 0xffff) continue;
//                     strRet.Append("P" + (++pointNumber).ToString() + "(" + index.ToString() + "," + touch.Points(index).X.ToString() + "," + touch.Points(index).Y.ToString() + ") ");
//                 }
//             }
//             else
//             {
//                 int len = touch.Report.Length;
//                 for (int index = 0; index < len; index++)
//                 {
//                     strRet.Append("0x" + touch.Report[index].ToString("X2") + ",");
//                 }
//                 strRet = strRet.Remove(strRet.Length - 1, 1);
//             }
//             return strRet.ToString();
//         }
    }
}
