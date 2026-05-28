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
     public class DispalyRawDataView : ContentControl
    {

        public int Rows { get; set; }
        public int Columns { get; set; }

        public int CellWidth = 40;
        public int CellHeight = 20;

        private int width { get; set; }
        private int height { get; set; }

        public short[,] RawDataMatrix = new short[100, 100]; 

        public int PointSize = 8;//8

        private WriteableBitmap bitmap = null;

        MemoryStream mos = new MemoryStream();

        GDI.Font text = new GDI.Font("Arial",8 , GDI.FontStyle.Regular);//

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
            new GDI.SolidBrush(GDI.Color.Black),
        };

        private GDI.Brush Black = new GDI.SolidBrush(GDI.Color.Black);

        public DispalyRawDataView()
        {

        }

        public void ViewWindowRefresh()
        {
            width = Columns * CellWidth;
            height = Rows * CellHeight;

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

            backBufferGraphics.Clear(GDI.Color.White);

            for (int iCol = 0; iCol < Columns; iCol++)
            {
                GDI.Point pt1 = new GDI.Point((int)(CellWidth * (iCol + 1)), 0);
                GDI.Point pt2 = new GDI.Point((int)(CellWidth * (iCol + 1)), height);
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Black, 1), pt1, pt2);
            }
            for (int iRow = 0; iRow < Rows; iRow++)
            {
                GDI.Point pt1 = new GDI.Point(0, (int)(CellHeight * (iRow + 1)));
                GDI.Point pt2 = new GDI.Point(width, (int)(CellHeight * (iRow + 1)));
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Black, 1), pt1, pt2);
            }

        }

        private void SetCell(GDI.Graphics backBufferGraphics, UInt32 row, UInt32 column)
        {

            //Brush brush = new SolidBrush(Color.FromArgb(100, 0, 0, 255)); 
            backBufferGraphics.FillRectangle(brush[column * row % 10], column * CellWidth + 1, row * CellHeight, CellWidth - 2, CellHeight - 2); // 5, 5

            string strPixel = RawDataMatrix[row, column].ToString("D5");

           
            GDI.SizeF size = backBufferGraphics.MeasureString(strPixel, text);
            backBufferGraphics.DrawString(strPixel, text, brush[10],
                new GDI.PointF(column * CellWidth + (CellWidth / 2) - (size.Width / 2), (row * CellHeight) + (CellHeight / 2) - (size.Height / 2)));
            
        }

        public void Refresh()
        {
            //DateTime now = DateTime.Now;
            //string custom1 = "2.||" + now.ToString("mm:ss.fff")+"||";

            int CellWidthC = (CellWidth / 2) - 17;
            int CellHeightC = (CellHeight / 2) - 6;

            int CellWidthCC = (CellWidth / 2) - 4;
            int CellHeightCC = (CellHeight / 2) - 4;
            this.bitmap.Lock();

            using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
            this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
            this.bitmap.BackBuffer))
            {
                using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                {
                    backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                    backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;
                    //ClearBitmap(backBufferGraphics);
                    for (uint iRow = 0; iRow < Rows; iRow++)
                    {
                        for (uint iCol = 0; iCol < Columns; iCol++)
                        {

                            //if (iRow == 0 && iCol==0)
                            //{
                            //    now = DateTime.Now;
                            //    custom1 += now.ToString("mm:ss.fff")+"||";
                            //}

                            //SetCell(backBufferGraphics, iRow, iCol);

                            //backBufferGraphics.FillRectangle(brush[(iRow * Columns + iCol) % 10], iCol * CellWidth + CellWidthCC, iRow * CellHeight + CellHeightCC, 8, 8); // 7, 7  CellWidth - 2, CellHeight - 2
                            backBufferGraphics.FillRectangle(brush[(iRow * Columns + iCol) % 10], iCol * CellWidth + 1, iRow * CellHeight + 1, CellWidth - 2, CellHeight - 2); // 7, 7  CellWidth - 2, CellHeight - 2

                            string strPixel = RawDataMatrix[iRow, iCol].ToString("D5");


                            //GDI.SizeF size = backBufferGraphics.MeasureString(strPixel, text);
                            //backBufferGraphics.DrawString(strPixel, text, Black,new GDI.PointF(iCol * CellWidth + CellWidthC, (iRow * CellHeight) + CellHeightC));
                            backBufferGraphics.DrawString(strPixel, text, Black,iCol * CellWidth + CellWidthC, (iRow * CellHeight) + CellHeightC);

                            //if (iRow * Columns + iCol==1000)
                            //{
                            //    now = DateTime.Now;
                            //    custom1 += now.ToString("mm:ss.fff") + "||"; 
                            //}

                        }
                    }

                    //now = DateTime.Now;
                    //custom1 += now.ToString("mm:ss.fff") + "||"; 

                    backBufferGraphics.Flush();
                    mos.SetLength(0);
                    backBufferBitmap.Save(mos, System.Drawing.Imaging.ImageFormat.Bmp);
                }
            }

            this.bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
            this.bitmap.Unlock();

            //now = DateTime.Now;
            //custom1 += now.ToString("mm:ss.fff") + "||";
            //Console.WriteLine(custom1);
        }

        public WriteableBitmap GetBitmap()
        {
            return bitmap;
        }
    }
}
