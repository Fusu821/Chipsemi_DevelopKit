using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMI.Util;
using System.Windows.Input;
using SEMIDevelopKit.Src.Util;
//using sz_value_pair = System.Collections.Generic.KeyValuePair<int, int>;
using SelCoordinate = System.Tuple<int, int>;
using System.Windows;
using SMInvokeBridge;

namespace SEMIDevelopKit.Src.WinSub
{
    public partial class SMDevelopChipReflex : SEMI.Util.ChipReflex
    {
        public void RegistReflexStatisticScap()
        {
            RegistByTypeAndId(SMInvokeBridge.eChipTypeList.SM_IC_3536, "SEMIDevelopKit.Src.WinSub.ModelStatisticScap", SEMI.Util.ChipReflex.SEMI_DEVLOP_STATIS);
        }
    }
    public class ModelStatisticScap : ModelStatistic
    {
        public ModelStatisticScap()
        {
            listKeys = new List<SMDefinition>()
            {
                new SMDefinition(0x00, "None"),
                new SMDefinition(0x01, "ScapData:"),
                new SMDefinition(0x02, "OS - M1:"),
                new SMDefinition(0x02, "Slow CLK RawData:"),
                new SMDefinition(0x03, "Fast CLK RawData:"),
            };
        }


    }
}
