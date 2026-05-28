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
using System.Windows.Input;
using System.Drawing.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SEMIDevelopKit.Src.Util
{
    public class WpfRawDataView : ContentControl
    {
        public int Rows { get; set; }
        public int Columns { get; set; }

        private uint cellWidth = 42;
        public uint CellWidth
        {
            get{ return cellWidth;}
            set { cellWidth = value; }
        }

        private uint cellHeight = 20;
        public uint CellHeight
        {
            get { return cellHeight; }
            set { cellHeight = value; }
        }

        int screenWidth = Screen.PrimaryScreen.Bounds.Width;
        int screenHeight = Screen.PrimaryScreen.Bounds.Height;

        public int RowExp { get; set; }
        public int ColExp { get; set; }

        private int RowsAll { get; set; }
        private int ColumnsAll { get; set; }

        public short[] RawDataMatrix = new short[100 * 100];

        private WriteableBitmap bitmap = null;
        MemoryStream mos = new MemoryStream();
        private Image img = new Image();

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

        private GDI.Brush[] brushArgb = new GDI.Brush[]
        {
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0x90,0xff,0x90)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0x90,0xEE,0x90)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0xC1,0xFF,0xC1)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0xF0,0xF8,0xFF)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0xf4,0xf4,0xf4)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0xFF,0xA0,0x7A)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0xFF,0x7F,0x50)),
            new GDI.SolidBrush(GDI.Color.FromArgb(0xff,0xCD,0x5C,0x5C)),
            new GDI.SolidBrush(GDI.Color.FromArgb(255,178, 34, 34)),
        };

        GDI.Font ftext = new GDI.Font("Arial", 12.0f, GDI.FontStyle.Regular, GDI.GraphicsUnit.Pixel);

        private GDI.Brush Black = new GDI.SolidBrush(GDI.Color.Black);
        private GDI.Brush Gold = new GDI.SolidBrush(GDI.Color.Gold);


        public int[] backColorRule = new int[8 * 2];
        public int Reference
        {
            get { return (int)GetValue(ReferenceProperty); }
            set { SetValue(ReferenceProperty, value); }
        }

        public static readonly DependencyProperty ReferenceProperty = DependencyProperty.Register("Reference", typeof(int), typeof(WpfRawDataView), new PropertyMetadata(12000, OnReferencePropertyChanged));
        private static void OnReferencePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WpfRawDataView dataView = d as WpfRawDataView;
            dataView.Reference = (int)e.NewValue;

            int ruleHarfLevel = dataView.backColorRule.Length / 2;

            //int[] colorLevel = new int[8] { 0x90FF90, 0x90EE90, 0xC1FFC1, 0xF0F8FF, 0xf4f4f4, 0xFFA07A, 0xFF7F50, 0xCD5C5C };

            for (int index = 0; index < dataView.backColorRule.Length; index+=2)
            {
                dataView.backColorRule[index / 2] = dataView.Reference + 100 * (index - ruleHarfLevel);
                //dataView.backColorRule[index + 1] = colorLevel[index / 2];
            }
        }

        public WpfRawDataView()
        {
            this.Content = img;

            //if (screenWidth > 2300 && screenHeight > 1400)
            //{
            //    ftext = new GDI.Font("Arial", 6.0f, GDI.FontStyle.Regular, GDI.GraphicsUnit.Pixel);
            //}

            TransformGroup transformGroup = new TransformGroup();

            // 创建 ScaleTransform 对象并设置初始缩放比例
            scaleTransform = new ScaleTransform();
            scaleTransform.ScaleX = 1;
            scaleTransform.ScaleY = 1;

            // 创建 TranslateTransform 对象
            translateTransform = new TranslateTransform();

            // 将 ScaleTransform 和 TranslateTransform 添加到 TransformGroup 中
            transformGroup.Children.Add(scaleTransform);
            transformGroup.Children.Add(translateTransform);
            this.RenderTransform = transformGroup;

            //this.MouseWheel += new MouseWheelEventHandler(Grid_MouseWheel);
            this.MouseRightButtonDown += new MouseButtonEventHandler(Grid_MouseKeyDown);
            this.MouseLeftButtonDown += new MouseButtonEventHandler(WpfDataGrid_MouseLeftButtonDown);
            //this.MouseLeftButtonUp += new MouseButtonEventHandler(WpfDataGrid_MouseLeftButtonUp);
            //this.MouseMove += new MouseEventHandler(WpfDataGrid_MouseMove);
        }


        public void WpfRawDataViewInit(int rows, int columns, int rowexp = 0, int colexp = 0)
        {

            this.Rows = rows;
            this.Columns = columns;
            this.RowExp = rowexp;
            this.ColExp = colexp;

            this.RowsAll = (Rows + RowExp + 1);
            this.ColumnsAll = (Columns + ColExp + 1);

            this.Width = (int)(ColumnsAll * CellWidth);
            this.Height = (int)(RowsAll * CellHeight);

            if (this.Width <= 0 || this.Height <= 0) return;

            if (bitmap == null)
            {
                this.bitmap = new WriteableBitmap((int)this.Width, (int)this.Height, 96, 96, PixelFormats.Bgr24, null);
            }
            else if (bitmap.Width != this.Width || bitmap.Height != this.Height)
            {
                this.bitmap = new WriteableBitmap((int)this.Width, (int)this.Height, 96, 96, PixelFormats.Bgr24, null);
            }

            this.bitmap.Lock();

            using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap((int)this.Width, (int)this.Height,
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

            img.Source = bitmap;
            this.Content = img;

        }

        private void ClearBitmap(GDI.Graphics backBufferGraphics)
        {

            backBufferGraphics.Clear(GDI.Color.White);

            for (int iCol = 0; iCol < ColumnsAll; iCol++)
            {
                GDI.Point pt1 = new GDI.Point((int)(CellWidth * (iCol + 1)), 0);
                GDI.Point pt2 = new GDI.Point((int)(CellWidth * (iCol + 1)), (int)this.Height);
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Black, 1), pt1, pt2);

                backBufferGraphics.FillRectangle(Gold, (iCol + 1) * CellWidth + 1, 1, CellWidth - 2, CellHeight - 2);

                String txt = iCol < Columns ? string.Format("Col{0:D2}", iCol) : "EXP";
                GDI.SizeF size = backBufferGraphics.MeasureString(txt, ftext);
                backBufferGraphics.DrawString(txt, ftext, Black,
                    (iCol + 1) * CellWidth + (CellWidth / 2) - (size.Width / 2),(CellHeight / 2) - (size.Height / 2));
            }
            for (int iRow = 0; iRow < RowsAll; iRow++)
            {
                GDI.Point pt1 = new GDI.Point(0, (int)(CellHeight * (iRow + 1)));
                GDI.Point pt2 = new GDI.Point((int)this.Width, (int)(CellHeight * (iRow + 1)));
                backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Black, 1), pt1, pt2);

                backBufferGraphics.FillRectangle(Gold, 1, (iRow + 1) * CellHeight + 1, CellWidth - 2, CellHeight - 2);

                String txt = iRow < Rows ? string.Format("Row{0:D2}", iRow) : "EXP";
                GDI.SizeF size = backBufferGraphics.MeasureString(txt, ftext);
                backBufferGraphics.DrawString(txt, ftext, Black,
                    (CellWidth / 2) - (size.Width / 2), ((iRow + 1) * CellHeight) + (CellHeight / 2) - (size.Height / 2));
            }

        }


        public void Refresh()
        {
            try
            {
                if (this.RowExp == 0 || this.ColExp == 0) return;

                uint CellWidthC = (CellWidth / 2);
                uint CellHeightC = (CellHeight / 2);

                this.bitmap.Lock();

                using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap((int)this.Width, (int)this.Height,
                this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
                this.bitmap.BackBuffer))
                {
                    using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                    {
                        backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                        backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;

                        short value = 0;
                        int index = 0;
                        string strPixel = "";
                        //int left = 0;
                        //int right = 7;
                        float fillWidth = CellWidth - 2;
                        float fillHeight = CellHeight - 2;
                        GDI.SizeF size;

                        for (uint iRow = 0; iRow < Rows + RowExp; iRow++)
                        {
                            for (uint iCol = 0; iCol < Columns + ColExp; iCol++)
                            {
                                if (iRow < Rows && iCol < Columns)
                                {
                                    value = RawDataMatrix[iRow * Columns + iCol];
                                }
                                else if (iCol >= Columns)
                                {
                                    value = RawDataMatrix[Rows * Columns + (iCol - Columns) * (Rows + Columns) + Columns + iRow];
                                }
                                else if (iRow >= Rows)
                                {
                                    value = RawDataMatrix[Rows * Columns + (iRow - Rows) * (Rows + Columns) + iCol];
                                }

                                //for (index = 0; index < 7; index ++)
                                //{
                                //    if (value < backColorRule[index])
                                //    {
                                //        break;
                                //    }
                                //}

                                //index = 0;
                                //left = 0;
                                //right = 7;
                                //while (left <= right)
                                //{
                                //    int mid = left + (right - left) / 2;
                                //    if (backColorRule[mid] < value)
                                //    {
                                //        left = mid;
                                //        index = mid + 1;

                                //    }
                                //    else if (backColorRule[mid] >= value)
                                //    {
                                //        right = mid;
                                //    }
                                //    if (value < backColorRule[0])
                                //    {
                                //        index = 0;
                                //        break;
                                //    }
                                //    else if (value > backColorRule[7])
                                //    {
                                //        index = 8;
                                //        break;
                                //    }
                                //    if ((right - left) <=1)
                                //    {
                                //        break;
                                //    }

                                //}

                                if (value >= backColorRule[4])
                                {
                                    if (value >= backColorRule[6])
                                    {
                                        if (value >= backColorRule[7])
                                        {
                                            index = 8;
                                        }
                                        else
                                        {
                                            index = 7;
                                        }
                                    }
                                    else
                                    {

                                        if (value >= backColorRule[5])
                                        {
                                            index = 6;
                                        }
                                        else
                                        {
                                            index = 5;
                                        }

                                    }

                                }
                                else
                                {
                                    if (value >= backColorRule[2])
                                    {
                                        if (value >= backColorRule[3])
                                        {
                                            index = 4;
                                        }
                                        else
                                        {
                                            index = 3;
                                        }

                                    }
                                    else
                                    {
                                        if (value >= backColorRule[1])
                                        {
                                            index = 2;
                                        }
                                        else if (value >= backColorRule[0])
                                        {
                                            index = 1;
                                        }
                                        else
                                        {
                                            index = 0;
                                        }
                                    }

                                }

                                backBufferGraphics.FillRectangle(brushArgb[index], (iCol + 1) * CellWidth + 1, (iRow + 1) * CellHeight + 1, fillWidth, fillHeight);

                                strPixel = string.Format("{0:G5}", value);

                                size = backBufferGraphics.MeasureString(strPixel, ftext);

                                backBufferGraphics.DrawString(strPixel, ftext, Black,
                                    (iCol + 1) * CellWidth + CellWidthC - (size.Width / 2), ((iRow + 1) * CellHeight) + CellHeightC - (size.Height / 2));

                            }
                        }

                        backBufferGraphics.Flush();
                        mos.SetLength(0);
                        backBufferBitmap.Save(mos, System.Drawing.Imaging.ImageFormat.Bmp);
                    }
                }

                this.bitmap.AddDirtyRect(new Int32Rect(0, 0, (int)this.bitmap.Width, (int)this.bitmap.Height));
                this.bitmap.Unlock();

            
            }
            catch
            {
            
            }   
        }

        // 缩放因子，控制每次缩放的幅度
        private const double ZoomFactor = 0.1;
        // 最小缩放比例
        private const double MinScale = 0.1;
        // 最大缩放比例
        private const double MaxScale = 5.0;
        private double zoom = 1;
        ScaleTransform scaleTransform;
        TranslateTransform translateTransform;

        private void Grid_MouseKeyDown(object sender, MouseButtonEventArgs e)
        {
            scaleTransform.ScaleX = 1;
            scaleTransform.ScaleY = 1;
            translateTransform.X = 0;
            translateTransform.Y = 0;
            zoom = 1;
        }

        void WpfDataGrid_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Point mousePosition = e.GetPosition((IInputElement)sender);

            zoom = zoom - ZoomFactor;

            double currentScaleX = scaleTransform.ScaleX;
            double currentScaleY = scaleTransform.ScaleY;

            double newScaleX = currentScaleX * zoom;
            double newScaleY = currentScaleY * zoom;

            newScaleX = Math.Max(MinScale, Math.Min(MaxScale, newScaleX));
            newScaleY = Math.Max(MinScale, Math.Min(MaxScale, newScaleY));

            double scaleRatioX = newScaleX / currentScaleX;
            double scaleRatioY = newScaleY / currentScaleY;

            translateTransform.X = (translateTransform.X - mousePosition.X) * scaleRatioX + mousePosition.X;
            translateTransform.Y = (translateTransform.Y - mousePosition.Y) * scaleRatioY + mousePosition.Y;

            scaleTransform.ScaleX = newScaleX;
            scaleTransform.ScaleY = newScaleY;
        }

    }
}
