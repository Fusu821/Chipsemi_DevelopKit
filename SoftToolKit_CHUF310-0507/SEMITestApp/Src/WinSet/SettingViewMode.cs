using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SEMITestApp.Src.Util;
using System.Windows.Input;
using System.Windows.Media;
using System.Collections.ObjectModel;
using SEMI.Util;

namespace SEMITestApp.Src.WinSet
{
    public partial class SMTestChipReflex : SEMI.Util.ChipReflex
    {
        protected static ChipReflex single = new SMTestChipReflex();

        public static ChipReflex Instance
        {
            get { return single; }
        }

        static SMTestChipReflex()
        {
            RegisterReflexModule();
        }

        public override Type TypeOfReflexObject(string objName)
        {
            return Type.GetType(objName);
        }

        private static void RegisterReflexModule()
        {
            Type type = typeof(SMTestChipReflex);
            var methods = type.GetMethods();

            var reflexMethods = methods.Where(t => { return t.Name.Contains("RegistReflex") ? true : false; });

            reflexMethods.All((t) => { t.Invoke(SMTestChipReflex.Instance, null); return true; });
        }
    }
    public class SetNode : NotifyBase
    {
        private Boolean selected = false;
        public Boolean Selected
        {
            get { return selected; }
            set { if (value != selected) selected = value; OnPropertyChanged("Selected"); }
        }
        public string ItemName { get; set; }

        public string LinkUri { get; set; }

        public int NodeType { get; set; }

        public IList<SetNode> ItemNodes { get; set; }
    }

    public class SettingViewMode : NotifyBase
    {
        SettingMode mode = new SettingMode();

        private static SettingViewMode instance = null;
        private SettingViewMode()
        {
            ctrlClickCommand = new DelegateCommand(OnCtrlClickCommand, CanCtrlClick);
        }

        public static SettingViewMode Instance()
        {
            if(instance == null)
            {
                instance = new SettingViewMode();
            }
            return instance;
        }

        public IList<SetNode> setLists = new List<SetNode>()
        {
            new SetNode(){ ItemName="Main Set", LinkUri="MainSet.xaml", NodeType=ChipReflex.SEMI_TEST_MAIN_SET, Selected = true, ItemNodes = null },
            new SetNode(){ ItemName="Common Set", ItemNodes = null, NodeType=ChipReflex.SEMI_TEST_COMMON_SET, LinkUri="CommonSet.xaml" },
            new SetNode(){ ItemName="Data Test Items", LinkUri="TestItemSet.xaml", NodeType=ChipReflex.SEMI_TEST_ITEM_SET, ItemNodes = new List<SetNode>()
            {
                new SetNode(){ ItemName="Basic Set", LinkUri="BasicSet.xaml", NodeType=ChipReflex.SEMI_TEST_BASIC_SET, ItemNodes = null },
                new SetNode(){ ItemName="Datail Set", LinkUri="DetailSet.xaml", NodeType=ChipReflex.SEMI_TEST_DETAIL_SET, ItemNodes = null },
            }},
            new SetNode(){ ItemName="Graph Test Items", LinkUri="GraphItemSet.xaml", NodeType=ChipReflex.SEMI_TEST_GRAPH_SET, ItemNodes = null },
            //new SetNode(){ ItemName="Other Set", ItemNodes = null },
            new SetNode(){ ItemName="Save", ItemNodes = null, NodeType=ChipReflex.SEMI_TEST_SAVE_SET, LinkUri="SaveSet.xaml" },
        };

        public IList<SetNode> SetLists
        {
            get { return setLists; }
            private set { setLists = null; }
        }

//         private string curSettingFrame = "MainSet.xaml";
//         public string CurSettingFrame
//         {
//             get { return curSettingFrame; }
//             set { if (value != curSettingFrame) { curSettingFrame = value; OnPropertyChanged("CurSettingFrame"); } }
//         }


        //private Boolean bChecked = true;
        //public Boolean Checked
        //{
        //    get { return bChecked; }
        //    set { if (value != bChecked) { bChecked = value; OnPropertyChanged("Checked"); } }
        //}

        private bool CanCtrlClick(object param)
        {
            return true;
        }
        public ICommand ctrlClickCommand { get; private set; }

        public void OnCtrlClickCommand(object param)
        {
            string strParam = param as string;
            if (null == strParam) return;

            if("setting-next" == strParam)
            {
                List<SetNode> setListsTemp = new List<SetNode>();
                foreach(var item in SetLists)
                {
                    setListsTemp.Add(item);
                    if (null != item.ItemNodes)
                        setListsTemp.AddRange(item.ItemNodes);
                }
                int itemIndex = setListsTemp.FindIndex(t => { return t.Selected == true ? true : false; });
                if(itemIndex == setListsTemp.Count - 1)
                {
                    //finish
                }
                else if(itemIndex >= 0)
                {
                    setListsTemp[itemIndex].Selected = false;
                    setListsTemp[itemIndex + 1].Selected = true;
                }
                
            }
            else if("setting-prev" == strParam)
            {
                List<SetNode> setListsTemp = new List<SetNode>();
                foreach (var item in SetLists)
                {
                    setListsTemp.Add(item);
                    if (null != item.ItemNodes)
                        setListsTemp.AddRange(item.ItemNodes);
                }
                int itemIndex = setListsTemp.FindIndex(t => { return t.Selected == true ? true : false; });
                if (0 == itemIndex)
                {
                    //first
                }
                else
                {
                    setListsTemp[itemIndex].Selected = false;
                    setListsTemp[itemIndex - 1].Selected = true;
                }
            }
        }
    }
}
