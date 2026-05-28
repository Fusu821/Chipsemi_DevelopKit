using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Text.RegularExpressions;

namespace LibraryTools
{
   public class ToolCheckSumViewModel
    {
       ModelToolCheckSum m_ModelToolCheckSum = new ModelToolCheckSum();
       public ModelToolCheckSum ModelToolCheckSum
       { 
           get
           {
               return m_ModelToolCheckSum;
           }
       }
       public ToolCheckSumViewModel()
       {
           m_ModelToolCheckSum.BtnCommand = new Command()
           {
               DoExecute = obj =>
                   {
                       CheckSumCalc_Click();
                   }
           };
       }
    public void CheckSumCalc_Click()
    {
        try
        {
            string input = m_ModelToolCheckSum.CheckSumDataInput.Trim(' ');
            input = input.TrimStart(' ');
            input = new Regex("[\\s]+").Replace(input, " ");
            input = input.Replace(',', ' ');         
            string[] inputArray = input.Split(' ');
            var ls = inputArray.Select((t) =>
            {
                t = t.Replace("0x", "").Trim();
                return byte.Parse(t, System.Globalization.NumberStyles.HexNumber);
            });
            var inputData = ls.ToArray();
            if (m_ModelToolCheckSum.CurSelCheckSum == CheckSumType.CheckSumU816)
            {
                m_ModelToolCheckSum.CalcCheckSum = CaculateCheckSumU816(inputData, (uint)inputData.Length);
            }
            else if (m_ModelToolCheckSum.CurSelCheckSum == CheckSumType.CheckSumU16)
            {
                m_ModelToolCheckSum.CalcCheckSum = CaculateCheckSumU16(inputData, (uint)inputData.Length);
            }
            else if (m_ModelToolCheckSum.CurSelCheckSum == CheckSumType.CheckSumEx)
            {
                m_ModelToolCheckSum.CalcCheckSum = CaculateCheckSumEx(inputData, (uint)inputData.Length);
            }
            else if (m_ModelToolCheckSum.CurSelCheckSum == CheckSumType.CheckSumU8)
            {
                m_ModelToolCheckSum.CalcCheckSum = CaculateCheckSumU8(inputData, (uint)inputData.Length);
            }
            else if (m_ModelToolCheckSum.CurSelCheckSum == CheckSumType.CheckSum32)
            {
                m_ModelToolCheckSum.CalcCheckSum = CaculateCheckSum32(inputData, (uint)inputData.Length);
            }
        }
        catch (Exception ex)
        {
            ex.ToString();
        }

    }

        protected  ushort CaculateCheckSumU816(byte[] buf, uint length)
       {          
           ushort sum = 0;
           uint i = 0;
           for (i = 0; i < length; i++)
           {
               sum += buf[i];
           }
           //foreach (var i in buf)
           //{
           //    sum += (ushort)i;
           //}
           return sum;
       }
        protected  byte CaculateCheckSumU8(byte[] buf, uint length)
       {          
 
           byte sum = 0;
           uint i = 0;
           for (i = 0; i < length; i++)
           {
               sum += buf[i];
           }
           //foreach (var i in buf)
           //{
           //    sum += i;
           //}
           return sum;
       }

        protected  ushort CaculateCheckSumU16(byte[] buf, uint length)
       {
           //var shorts = buf.Select(b => (short)b).ToArray();
           ushort sum = 0;
           List<ushort> ushorts=new List<ushort>();           
           for (ushort i = 0; i < length; i+=2) 
           {
               ushort num = 0;
               num = (ushort)((buf[i + 1]<<8)|buf[i]);
               ushorts.Add(num);
           }
            foreach(var i in ushorts)
            {
                sum += i;
            }
            ushorts.Clear();
           //ushort sum = 0,i=0;
           //for (i = 0; i < length / 2;i++ )
           //{
           //    sum += (ushort)shorts[i];
           //}
           //foreach(var i in shorts)
           //{
           //    sum += (ushort)i;
           //}
           return sum;
       }

        protected  uint CaculateCheckSumEx(byte[] buf, uint length)
       {
           uint k;
	       uint combChk = 0;
	       ushort check = 0, checkEx = 0;
           for(k = 0; k < length; k++)
	       {
		    check += buf[k];
		    checkEx += (ushort)( k * buf[k] );
	       }
           combChk = (uint)(checkEx * 65536 + check);
           return combChk;
       }

        protected uint CaculateCheckSum32(byte[] buf, uint length)
        {
            uint k;
            uint combChk = 0;
            for (k = 0; k < length; k=k+4)
            {
                uint chk = (uint)(buf[k+3] << 24 | buf[k+2] << 16 | buf[k+1] << 8 | buf[k]);
                combChk += chk;
          
            }
            return combChk;
        }

    }
}
