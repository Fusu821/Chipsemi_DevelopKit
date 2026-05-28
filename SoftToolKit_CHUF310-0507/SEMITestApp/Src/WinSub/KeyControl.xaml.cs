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
    /// KeyControl.xaml 的交互逻辑
    /// </summary>
    public partial class KeyControl : UserControl
    {
        public KeyControl()
        {
            InitializeComponent();
        }
        public void SetXCaptionAndValue(string xcaption, int xvalue)
        {
            this.X_Caption.Content = xcaption;
            this.X_Value.Text = Convert.ToString(xvalue);
        }
        public void SetYCaptionAndValue(string ycaption, int yvalue)
        {
            this.Y_Caption.Content = ycaption;
            this.Y_Value.Text = Convert.ToString(yvalue);
        }

        public int GetXValue()
        {
            int ret = 0;
            if (this.X_Value.Text == "")
            {
                ret = 0;
            }
            else
            {
                try
                {
                    ret = Convert.ToInt32(this.X_Value.Text);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                    ret = 0;
                }
            }
            return ret;
        }

        public int GetYValue()
        {
            int ret = 0;
            if (this.Y_Value.Text == "")
            {
                ret = 0;
            }
            else
            {
                try
                {
                    ret = Convert.ToInt32(this.Y_Value.Text);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                    ret = 0;
                }

            }
            return ret;
        }

    }
}
