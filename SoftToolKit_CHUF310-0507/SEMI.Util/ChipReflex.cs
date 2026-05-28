using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SEMI.Util
{
    public class ChipReflex
    {
        //tester
        public const int SEMI_TEST_MAIN_SET = 1;
        public const int SEMI_TEST_COMMON_SET = 2;
        public const int SEMI_TEST_ITEM_SET = 3;
        public const int SEMI_TEST_BASIC_SET = 4;
        public const int SEMI_TEST_DETAIL_SET = 5;
        public const int SEMI_TEST_GRAPH_SET = 6;
        public const int SEMI_TEST_SAVE_SET = 7;

        public const int SEMI_TEST_MAIN_SET_MODE = 11;
        public const int SEMI_TEST_COMMON_SET_MODE = 12;
        public const int SEMI_TEST_ITEM_SET_MODE = 12;
        public const int SEMI_TEST_BASIC_SET_MODE = 14;
        public const int SEMI_TEST_DETAIL_SET_MODE = 15;
        public const int SEMI_TEST_GRAPH_SET_MODE = 16;
        public const int SEMI_TEST_SAVE_SET_MODE = 17;

        //develop
        public const int SEMI_DEVLOP_RAWDATA = 1;
        public const int SEMI_DEVLOP_TOUCH   = 2;
        public const int SEMI_DEVLOP_TOOLS   = 3;
        public const int SEMI_DEVLOP_STATIS  = 4;
        public const int SEMI_DEVLOP_TUNING  = 5;

        private const ushort mask = 0xff00;
        
        private IDictionary<UInt32, string> dcSEMIReflex = new Dictionary<UInt32, string>();
        private IDictionary<string, object> dcSEMICatch = new Dictionary<string, object>();

        public virtual void RegistByTypeAndId(ushort icID, string szReflex, byte type, bool usemask = true)
        {
            if (usemask) icID = (ushort)(icID & mask);
            if (dcSEMIReflex.ContainsKey((UInt32)(type << 16) | icID)) return;

            dcSEMIReflex.Add((UInt32)((type << 16) | icID), szReflex);
        }

        public virtual Type TypeOfReflexObject(string objName)
        {
            return null;
        }

        public object GetSemiModuleByChipAndType(int kindof, ushort icID)
        {
            try
            {
                UInt32 key = (UInt32)((kindof << 16) + icID);
                if (!dcSEMIReflex.ContainsKey(key))
                {
                    icID = (ushort)(icID & mask);
                    key = (UInt32)((kindof << 16) + icID);
                }
                if (!dcSEMIReflex.ContainsKey(key))
                {
                    icID = (ushort)(0xffff & mask);
                    key = (UInt32)((kindof << 16) + icID);
                }

                string className = dcSEMIReflex[key];
                if (!dcSEMICatch.ContainsKey(className))
                {
                    //Type o = Type.GetType(className);
                    dcSEMICatch[className] = Activator.CreateInstance(TypeOfReflexObject(className), true);
                }
                return dcSEMICatch[className];
            }
            catch (Exception ex)
            {
                ex.ToString();

                return null;
                //return new System.Windows.Controls.TextBlock() { Text = "Function Not Support Yet!" };
            }
        }
    }
}
