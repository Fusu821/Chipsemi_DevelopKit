using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using System.IO;
using GDI = System.Drawing;
using System.Windows.Media;
using System.Windows;
using SMInvokeBridge;

namespace LibraryTools
{
    class DispalyView : ContentControl
    {
        public int width { get; set; }
        public int height { get; set; }

        public int XPixel { get; set; }
        public int YPixel { get; set; }

        public int LinesX = 10;
        public int LinesY = 10;

        public int LineSize = 1;

        public int GraghMode = 1;

        public int PointSize = 15;

        private TouchReportData lastTouch;

        private TPoint sLLastPoint;

        private WriteableBitmap bitmap = null;

        MemoryStream mos = new MemoryStream();

        private GDI.Pen[] pen = new GDI.Pen[]
        {
            new GDI.Pen(GDI.Color.Red, 1),
            new GDI.Pen(GDI.Color.Silver, 1),
            new GDI.Pen(GDI.Color.GreenYellow, 1),
            new GDI.Pen(GDI.Color.LightGreen, 1),
            new GDI.Pen(GDI.Color.Green, 1),
            new GDI.Pen(GDI.Color.DarkRed, 1),
            new GDI.Pen(GDI.Color.Gold, 1),
            new GDI.Pen(GDI.Color.LightSkyBlue, 1),
            new GDI.Pen(GDI.Color.Orange, 1),
            new GDI.Pen(GDI.Color.Blue, 1),
        };
        private GDI.Brush[] brush = new GDI.Brush[]
        {
            new GDI.SolidBrush(GDI.Color.Red),
            new GDI.SolidBrush(GDI.Color.Silver),
            new GDI.SolidBrush(GDI.Color.GreenYellow),
            new GDI.SolidBrush(GDI.Color.LightGreen),
            new GDI.SolidBrush(GDI.Color.Green),
            new GDI.SolidBrush(GDI.Color.DarkRed),
            new GDI.SolidBrush(GDI.Color.Gold),
            new GDI.SolidBrush(GDI.Color.LightSkyBlue),
            new GDI.SolidBrush(GDI.Color.Orange),
            new GDI.SolidBrush(GDI.Color.Blue),
        };

        public DispalyView()
        {

        }

        public void ViewWindowRefresh()
        {

            if (width <= 0 || height <= 0) return;

            if (bitmap == null)
            {
                this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);
            }
            else if (bitmap.Width != this.width || bitmap.Height != this.height)
            {
                this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);
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
                    ClearBitmap(backBufferGraphics);

                    backBufferGraphics.Flush();
                }
            }

            this.bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
            this.bitmap.Unlock();

        }

        private void ClearBitmap(GDI.Graphics backBufferGraphics)
        {

            double xDelta = (double)width / (LinesX);
            double yDelta = (double)height / (LinesY);

            backBufferGraphics.Clear(GDI.Color.Black);

            for (int iCol = 0; iCol < LinesX; iCol++)
            {
                GDI.Point pt1 = new GDI.Point((int)(xDelta * (iCol + 1)), 0);
                GDI.Point pt2 = new GDI.Point((int)(xDelta * (iCol + 1)), height);
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Gray, 1), pt1, pt2);
            }
            for (int iRow = 0; iRow < LinesY; iRow++)
            {
                GDI.Point pt1 = new GDI.Point(0, (int)(yDelta * (iRow + 1)));
                GDI.Point pt2 = new GDI.Point(width, (int)(yDelta * (iRow + 1)));
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Gray, 1), pt1, pt2);
            }

            backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.GreenYellow, 1), 0, 0,
                width, height);
            backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.GreenYellow, 1), (width - width / 2) / 2, (height - height / 2) / 2,
            width / 2, height / 2);

        }

        public void OnTouchReport(TouchReportData touch)
        {
            if (touch.DrawMode == DrawModes.SingleLineMode)
            {
                if (touch == null) return;
                if (null == this.bitmap) return;
                if (0 == touch.TCnt && null == sLLastPoint) return;

                if (null == sLLastPoint) { sLLastPoint = touch.FirstPoint(); }

                this.bitmap.Lock();

                using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
                this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
                this.bitmap.BackBuffer))
                {
                    using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                    {
                        backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                        backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;

                        if (1 == GraghMode)
                            DrawSingleLineMode(backBufferGraphics, touch);
                        else
                            DrawInPointMode(backBufferGraphics, touch);

                        sLLastPoint = touch.LastPoint();

                        backBufferGraphics.Flush();
                        mos.SetLength(0);
                        backBufferBitmap.Save(mos, System.Drawing.Imaging.ImageFormat.Bmp);
                    }
                }

                this.bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
                this.bitmap.Unlock();

            }
            else if (touch.DrawMode == DrawModes.MultiLineMode)
            {
                if (touch == null) return;
                if (null == this.bitmap) return;
                if (0 == touch.TCnt && null == lastTouch) return;

                if (null == lastTouch) { lastTouch = touch.Colne(); return; }

                this.bitmap.Lock();

                using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
                this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
                this.bitmap.BackBuffer))
                {
                    using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                    {
                        backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                        backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;

                        if (1 == GraghMode)
                            DrawMultiLineMode(backBufferGraphics, touch);
                        else
                            DrawInPointMode(backBufferGraphics, touch);

                        lastTouch = touch;

                        backBufferGraphics.Flush();
                        mos.SetLength(0);
                        backBufferBitmap.Save(mos, System.Drawing.Imaging.ImageFormat.Bmp);
                    }
                }

                this.bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
                this.bitmap.Unlock();
            }
            

        }

        private void DrawInLineMode(GDI.Graphics backBufferGraphics, TouchReportData touch)
        {
            if (touch.DrawMode == DrawModes.SingleLineMode)
            {
                DrawSingleLineMode(backBufferGraphics, touch);
            
            }
            else if (touch.DrawMode == DrawModes.MultiLineMode)
            {
                DrawMultiLineMode(backBufferGraphics, touch);
            }
            
        }

        private void DrawSingleLineMode(GDI.Graphics backBufferGraphics, TouchReportData touch)
        {
            var lastPt = sLLastPoint;

            var sllPoint = touch.GetSLPoints();

            foreach (var thisPt in sllPoint)
            {
                if (lastPt==null)
                {

                }
                else
                {
                    GDI.Point ptScreen = new GDI.Point();
                    GDI.Point lastScreen = new GDI.Point();
                    GDI.Rectangle rcTp = new GDI.Rectangle(0, 0, XPixel, YPixel);
                    GDI.Rectangle rcScreen = new GDI.Rectangle(0, 0, (int)width, (int)height);

                    SMChipBase.SMScreenXYChange(lastPt.X, lastPt.Y, ref lastScreen, rcTp, rcScreen);
                    SMChipBase.SMScreenXYChange(thisPt.X, thisPt.Y, ref ptScreen, rcTp, rcScreen);

                    pen[0].Width = LineSize;
                    backBufferGraphics.DrawLine(pen[0], lastScreen, ptScreen);
                    backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.White, LineSize),
                        lastScreen.X - LineSize / 2, lastScreen.Y - LineSize / 2, LineSize, LineSize);
                    backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.White, LineSize),
                        ptScreen.X - LineSize / 2, ptScreen.Y - LineSize / 2, LineSize, LineSize);
                    
                }

                lastPt = thisPt;
            
            }

        }

        private void  DrawMultiLineMode(GDI.Graphics backBufferGraphics, TouchReportData touch)
        {
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
                    GDI.Rectangle rcTp = new GDI.Rectangle(0, 0, XPixel, YPixel);
                    GDI.Rectangle rcScreen = new GDI.Rectangle(0, 0, (int)width, (int)height);

                    SMChipBase.SMScreenXYChange(lastPt.X, lastPt.Y, ref lastScreen, rcTp, rcScreen);
                    SMChipBase.SMScreenXYChange(thisPt.X, thisPt.Y, ref ptScreen, rcTp, rcScreen);

                    pen[ptId].Width = LineSize;
                    backBufferGraphics.DrawLine(pen[ptId], lastScreen, ptScreen);
                    backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.White, LineSize),
                        lastScreen.X - LineSize / 2, lastScreen.Y - LineSize / 2, LineSize, LineSize);
                    backBufferGraphics.DrawEllipse(new GDI.Pen(GDI.Color.White, LineSize),
                        ptScreen.X - LineSize / 2, ptScreen.Y - LineSize / 2, LineSize, LineSize);
                }
            }
        }




        private void DrawInPointMode(GDI.Graphics backBufferGraphics, TouchReportData touch)
        {
            ClearBitmap(backBufferGraphics);

            for (int ptId = 0; ptId < ExportDeclares.SM_MAX_NUM_POINT; ptId++)
            {
                //TPoint lastPt = lastTouch.Points(ptId);
                TPoint thisPt = touch.Points(ptId);

                if (null == thisPt) continue;

                GDI.Point ptScreen = new GDI.Point();
                GDI.Rectangle rcTp = new GDI.Rectangle(0, 0, XPixel, YPixel);
                GDI.Rectangle rcScreen = new GDI.Rectangle(0, 0, (int)width, (int)height);
                SMChipBase.SMScreenXYChange(thisPt.X, thisPt.Y, ref ptScreen, rcTp, rcScreen);

                
                backBufferGraphics.FillEllipse(brush[ptId], ptScreen.X - PointSize / 2,
                    ptScreen.Y - PointSize / 2, PointSize, PointSize);
                backBufferGraphics.DrawEllipse(pen[ptId], ptScreen.X - (PointSize + thisPt.Z) / 2, ptScreen.Y - (PointSize + thisPt.Z) / 2,
                    PointSize + thisPt.Z, PointSize + thisPt.Z);
        
                string strPixel = thisPt.X.ToString() + "," + thisPt.Y.ToString() + "," + thisPt.Z.ToString();

                GDI.Font text = new GDI.Font("Arial", PointSize, GDI.FontStyle.Bold);
                GDI.SizeF size = backBufferGraphics.MeasureString(strPixel, text);
                backBufferGraphics.DrawString(strPixel, text, brush[ptId],
                    new GDI.PointF(ptScreen.X - size.Width / 2, ptScreen.Y + PointSize / 2));
            }

        }

        public WriteableBitmap GetBitmap()
        {
            return bitmap;
        }
    }
}
