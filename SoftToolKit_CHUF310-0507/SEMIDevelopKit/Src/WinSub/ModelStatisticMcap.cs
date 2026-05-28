using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using System.Windows.Input;
using SEMIDevelopKit.Src.Util;
using SelCoordinate = System.Tuple<int, int>;
using System.Windows;
using SMInvokeBridge;

namespace SEMIDevelopKit.Src.WinSub
{
    public partial class SMDevelopChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexStatisticMcap()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5472, "SEMIDevelopKit.Src.WinSub.ModelStatisticMcap", SEMI.Util.ChipReflex.SEMI_DEVLOP_STATIS);
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_5816, "SEMIDevelopKit.Src.WinSub.ModelStatisticMcap", SEMI.Util.ChipReflex.SEMI_DEVLOP_STATIS);
        }
    }
    public class ModelStatisticMcap : ModelStatistic
    {
        public ModelStatisticMcap()
        {

            XMin = 12;
            XMax = 22;

            YMin = 6000;
            YMax = 15000;
        }

        public override void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;
        }
    }
}
