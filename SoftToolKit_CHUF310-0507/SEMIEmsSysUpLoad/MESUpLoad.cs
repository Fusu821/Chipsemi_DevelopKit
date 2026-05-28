using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using SMInvokeBridge;

namespace SEMIEmsSysUpLoad
{
    //public class SMUpLoadInfo
    //{
    //    public int SelectedFormat;
    //    public string str;
    //}
    public static class MESUpLoad
    {
        private static IDictionary<int, CUpLoadBase> dcEmsMap = new Dictionary<int, CUpLoadBase>() { { 7, new CHesEmsUpLoad() }, { 8, new COfilmEmsUpLoad() }, { 9, new CPbhEmsUpLoad() }, { 13, new CHesNewEmsUpLoad() }, { 14, new CHesNewEmsUpLoad() },
        { 15, new CLsEmsUpLoad() } };

        public static int UpLoadEmsSystem(SMUpLoadInfo info,ref String errcode)
        {
            int ret = 0;

            var param = dcEmsMap[info.codenum];
            if (param != null)
            {
                ret = param.SendEms(info.str, ref errcode); 
            }
            else
            {
                ret = 1;
            }
            if (errcode.Length > 512)
            {
                errcode = errcode.Substring(0, 512);
            }

            return ret;

        }
    }
}
