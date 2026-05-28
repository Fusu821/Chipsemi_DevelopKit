using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SMInvokeBridge;
using SEMI.Util;

namespace LibraryTools
{
    public enum DrawModes
    {
        SingleLineMode,
        MultiLineMode 
    }

    public class TPoint
    {
        public byte ID;
        public ushort X;
        public ushort Y;
        public ushort Z;
        public ushort xcode;
        public ushort ycode;
    }

    public class TouchReportData
    {
        public byte[] report = null;

        protected TPoint[] points = new TPoint[ExportDeclares.SM_MAX_NUM_POINT];

        protected List<TPoint> sLPoints = new List<TPoint>();

        public TouchReportData(byte[] report)
        {
            this.report = new byte[report.Length];
            Array.Copy(report, this.report, report.Length);
        }

        public virtual byte TCnt { get; set; }

        public virtual TouchReportData Colne()
        {
            return null;
        }

        public virtual TPoint Points(int id)
        {
            return points[id];
        }

        public virtual DrawModes DrawMode { get; set; }

        public virtual String GetPointString()
        {
            String srt = "";

            for (int i = 0; i < ExportDeclares.SM_MAX_NUM_POINT; i++ )
            {
                if (points[i] != null)
                {
                    var msg = String.Format("({0},{1},{2},{3});",points[i].ID,points[i].X,points[i].Y,points[i].Z);
                    srt += msg;
                }
            }

            return srt;
        }

        public virtual TPoint FirstPoint()
        {
            return sLPoints.FirstOrDefault();
        }
        public virtual TPoint LastPoint()
        {
            return sLPoints.LastOrDefault();
        }

        public virtual List<TPoint> GetSLPoints()
        {
            return sLPoints;
        }

    }

    public class MCap8006ReportData : TouchReportData
    {
        public MCap8006ReportData(byte[] report)
            : base(report)
        {
            for (int i = 0; i < 10; i++)
            {
                if (report[6 + i * 6] < 10)
                {
                    TPoint pt = new TPoint();
                    pt.X = (ushort)(((report[2 + i * 6] & 0xff) << 8) + report[3 + i * 6]);
                    pt.Y = (ushort)(((report[4 + i * 6] & 0xff) << 8) + report[5 + i * 6]);
                    pt.Z = 10;
                    pt.ID = report[6 + i * 6];
                    sLPoints.Add(pt);
                }
                else
                {
                    break;
                }
            }
            //TPoint pt = new TPoint();

            //pt.X = (ushort)(((report[0] & 0xff) << 8) + report[1]);
            //pt.Y = (ushort)(((report[2] & 0xff) << 8) + report[3]);
            //pt.Z = 10;
            //pt.ID = 0;
            //points[pt.ID] = pt;
        }

        public override DrawModes DrawMode { get { return DrawModes.SingleLineMode; } }
        public override byte TCnt { get { return (byte)(report[0] & 0xff); } }

        public override TPoint Points(int id)
        {
            return points[id];
        }
        public override String GetPointString()
        {
            String srt = "";

            foreach (var point in sLPoints)
            {
                var msg = String.Format("({0},{1},{2},{3});", point.ID, point.X, point.Y, point.Z);
                srt += msg;
            }
            return srt;
        }
        public override TouchReportData Colne()
        {
            return new MCap8006ReportData(report);
        }
    }

    public class MCap810ReportData : TouchReportData
    {
        public MCap810ReportData(byte[] report)
            : base(report)
        {
            for (int i = 0; i < 10; i++)
            {
                if (report[6 + i * 6] < 10)
                {
                    TPoint pt = new TPoint();
                    pt.X = (ushort)(((report[3 + i * 6] & 0xff) << 8) + report[2 + i * 6]);
                    pt.Y = (ushort)(((report[5 + i * 6] & 0xff) << 8) + report[4 + i * 6]);
                    pt.Z = 10;
                    pt.ID = report[6 + i * 6];
                    sLPoints.Add(pt);
                }
                else
                {
                    break;
                }
            }
            //TPoint pt = new TPoint();

            //pt.X = (ushort)(((report[0] & 0xff) << 8) + report[1]);
            //pt.Y = (ushort)(((report[2] & 0xff) << 8) + report[3]);
            //pt.Z = 10;
            //pt.ID = 0;
            //points[pt.ID] = pt;
        }

        public override DrawModes DrawMode { get { return DrawModes.SingleLineMode; } }
        public override byte TCnt { get { return (byte)(report[0] & 0xff); } }

        public override TPoint Points(int id)
        {
            return points[id];
        }
        public override String GetPointString()
        {
            String srt = "";

            foreach (var point in sLPoints)
            {
                var msg = String.Format("({0},{1},{2},{3});", point.ID, point.X, point.Y, point.Z);
                srt += msg;
            }
            return srt;
        }
        public override TouchReportData Colne()
        {
            return new MCap810ReportData(report);
        }
    }

    class ICDisplayBase
    {
        public Byte[] cfgContent = new Byte[2048];
        public Byte[] touchBuff = new Byte[100];

        public ushort XPixel = 500;
        public ushort YPixel = 500;

        public virtual bool ReadCfg()
        {
            return true;
        }

        public virtual bool SwitchTouchMode(ushort PackagesNum)
        {
            byte[] buf = new byte[16];
            var ret = SMChipBase.IncokeCommand((Byte)0x29, 1, PackagesNum, 0, buf);
            //var ret = SMChipBase.SwitchMode(2, 0);
            if (0 != ret) return false;

            return true;
        }

        public virtual bool GetTouchData()
        {
            ushort len = 0;

            var ret = SMChipBase.GetTouchPoint(touchBuff, ref len);

            if (0 != ret) return false;

            return true;
        } 

        public virtual TouchReportData GetTouchReportData()
        {
            return null;
        }
    }

    class IC8006DisplayBase : ICDisplayBase
    {
        public override bool ReadCfg()
        {
            System.Threading.Thread.Sleep(100);
            var ret = SMChipBase.IncokeCommand(cmdTypeID.CMD_SWITCH_IIC);
            System.Threading.Thread.Sleep(60);
            if (0 != ret) return false;

            ret = SMChipBase.ReadCoreSpace(0x20000000 + 0x1c, cfgContent, 204);
            if (0 != ret) return false;

            BitValue lcdx = new BitValue((cfgContent[38 * 2 + 1] << 8) + cfgContent[38 * 2 + 0]);
            BitValue lcdy = new BitValue((cfgContent[39 * 2 + 1] << 8) + cfgContent[39 * 2 + 0]);

            XPixel = lcdx.UShortValue;
            YPixel = XPixel;

            return true;
        }

        public override TouchReportData GetTouchReportData()
        {
            return new MCap8006ReportData(touchBuff);
        }
    }

    class IC810DisplayBase : ICDisplayBase
    {
        public override bool ReadCfg()
        {
            System.Threading.Thread.Sleep(100);
            var ret = SMChipBase.IncokeCommand(cmdTypeID.CMD_CTP_RST);
            System.Threading.Thread.Sleep(60);

            XPixel = 8192;
            YPixel = XPixel;

            return true;
        }
        public override TouchReportData GetTouchReportData()
        {
            return new MCap810ReportData(touchBuff);
        }
    }
}
