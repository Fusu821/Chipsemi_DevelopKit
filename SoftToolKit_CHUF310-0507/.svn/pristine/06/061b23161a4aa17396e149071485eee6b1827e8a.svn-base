using System.Windows;
using System.Windows.Media.Imaging;
using GDI = System.Drawing;
using System.Windows.Media;
public class TemplateView : FrameworkElement
{
    public int ResolutionX
    {
        get { return (int)GetValue(ResolutionXProperty); }
        set { SetValue(ResolutionXProperty, value); }
    }

    // Using a DependencyProperty as the backing store for MyProperty.  This enables animation, styling, binding, etc...
    public static readonly DependencyProperty ResolutionXProperty =
        DependencyProperty.Register("ResolutionX", typeof(int), typeof(TemplateView), new UIPropertyMetadata(1024));

    public static int GetResolutionX(DependencyObject d)
    {
        return (int)d.GetValue(ResolutionXProperty);
    }

    public static void SetResolutionX(DependencyObject d, int value)
    {
        d.SetValue(ResolutionXProperty, value);
    }


    public int ResolutionY
    {
        get { return (int)GetValue(ResolutionYProperty); }
        set { SetValue(ResolutionYProperty, value); }
    }

    // Using a DependencyProperty as the backing store for MyProperty.  This enables animation, styling, binding, etc...
    public static readonly DependencyProperty ResolutionYProperty =
        DependencyProperty.Register("ResolutionY", typeof(int), typeof(TemplateView), new UIPropertyMetadata(768));

    public static int GetResolutionY(DependencyObject d)
    {
        return (int)d.GetValue(ResolutionYProperty);
    }

    public static void SetResolutionY(DependencyObject d, int value)
    {
        d.SetValue(ResolutionYProperty, value);
    }

    public string BackImageName
    {
        get { return (string)GetValue(BackImageNameProperty); }
        set { SetValue(BackImageNameProperty, value); }
    }

    // Using a DependencyProperty as the backing store for MyProperty.  This enables animation, styling, binding, etc...
    public static readonly DependencyProperty BackImageNameProperty =
        DependencyProperty.Register("BackImageName", typeof(string), typeof(TemplateView), new UIPropertyMetadata(""));

    public string ImageDir
    {
        get { return (string)GetValue(ImageDirProperty); }
        set { SetValue(ImageDirProperty, value); }
    }

    // Using a DependencyProperty as the backing store for MyProperty.  This enables animation, styling, binding, etc...
    public static readonly DependencyProperty ImageDirProperty =
        DependencyProperty.Register("ImageDir", typeof(string), typeof(TemplateView), new UIPropertyMetadata(""));

    public static string GetBackImageName(DependencyObject d)
    {
        return (string)d.GetValue(BackImageNameProperty);
    }

    public static void SetBackImageName(DependencyObject d, string value)
    {
        d.SetValue(BackImageNameProperty, value);
    }


    public static readonly DependencyProperty LatestTemplateProperty =
        DependencyProperty.Register("LatestTemplate", typeof(byte[]), typeof(TemplateView),
        new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.None, OnLatestTemplatePropertyChanged));

    public static byte[] GetLatestTemplate(DependencyObject d)
    {
        return (byte[])d.GetValue(LatestTemplateProperty);
    }

    public static void SetLatestTemplate(DependencyObject d, byte[] value)
    {
        d.SetValue(LatestTemplateProperty, value);
    }

    private static void OnLatestTemplatePropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
    {
        TemplateView trendLine = (TemplateView)d;
        byte[] latestTempate = (byte[])e.NewValue;
        if (null != e.NewValue)
        {
            trendLine.OnDataArrived(latestTempate);
        }
    }



    private WriteableBitmap bitmap = null;
    public int width { get; set; }
    public int height { get; set; }

    public TemplateView()
    {
    }

    private void OnDataArrived(byte[] template)
    {
        if (null == this.bitmap) return;

        this.bitmap.Lock();

        using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
            this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
            this.bitmap.BackBuffer))
        {
            using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
            {
                backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;

                backBufferGraphics.Clear(GDI.Color.Black);

                if (!string.IsNullOrEmpty(ImageDir) && !string.IsNullOrEmpty(BackImageName))
                {
                    string filePath = ImageDir + "\\Images\\" + BackImageName;
                    System.Drawing.Image image = System.Drawing.Image.FromFile(filePath);
                    backBufferGraphics.DrawImage(image, new GDI.Rectangle(0, 0, width, height),
                        new GDI.Rectangle(0, 0, image.Width, image.Height), GDI.GraphicsUnit.Pixel);
                }

                int lastX = 0, lastY = 0;
                for (int index = 0; index < template.Length; index += 2)
                {
                    int realX = template[index + 0] * width / ResolutionX;
                    int realY = template[index + 1] * height / ResolutionY;
                    backBufferGraphics.FillEllipse(new GDI.SolidBrush(GDI.Color.Red), realX, realY, 6, 6);
                    if (index > 0) backBufferGraphics.DrawLine(new GDI.Pen(GDI.Color.Red), lastX, lastY, realX, realY);

                    lastX = realX;
                    lastY = realY;
                }

                backBufferGraphics.Flush();
            }
        }
        this.bitmap.AddDirtyRect(new Int32Rect(0, 0, width, height));
        this.bitmap.Unlock();
    }

    protected override void OnRender(DrawingContext dc)
    {
        this.width = (int)RenderSize.Width;
        this.height = (int)RenderSize.Height;
        if (width <= 0 || height <= 0) return;

        if (bitmap == null)
        {
            this.bitmap = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr24, null);

            this.bitmap.Lock();
            using (GDI.Bitmap backBufferBitmap = new GDI.Bitmap(width, height,
             this.bitmap.BackBufferStride, GDI.Imaging.PixelFormat.Format24bppRgb,
             this.bitmap.BackBuffer))
            {
                using (GDI.Graphics backBufferGraphics = GDI.Graphics.FromImage(backBufferBitmap))
                {
                    backBufferGraphics.SmoothingMode = GDI.Drawing2D.SmoothingMode.HighSpeed;
                    backBufferGraphics.CompositingQuality = GDI.Drawing2D.CompositingQuality.HighSpeed;

                    if (!string.IsNullOrEmpty(ImageDir) && !string.IsNullOrEmpty(BackImageName))
                    {
                        string filePath = ImageDir + "\\Images\\" + BackImageName;
                        System.Drawing.Image image = System.Drawing.Image.FromFile(filePath);
                        backBufferGraphics.DrawImage(image, new GDI.Rectangle(0, 0, width, height),
                            new GDI.Rectangle(0, 0, image.Width, image.Height), GDI.GraphicsUnit.Pixel);
                    }
                    else
                    {
                        backBufferGraphics.Clear(GDI.Color.Black);
                    }

                    backBufferGraphics.Flush();
                }
            }
            this.bitmap.AddDirtyRect(new Int32Rect(0, 0, width, height));
            this.bitmap.Unlock();

        }

        dc.DrawImage(bitmap, new Rect(0, 0, RenderSize.Width, RenderSize.Height));
        base.OnRender(dc);
    }
}