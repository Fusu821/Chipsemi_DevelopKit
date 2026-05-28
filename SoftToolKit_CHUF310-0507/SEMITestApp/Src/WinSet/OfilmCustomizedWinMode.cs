using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace SEMITestApp.Src.WinSet
{
    public class OfilmCustomizedWinMode : SettingMode
    {
        private string fixtureId = "";
        public string FixtureId
        {
            get { return fixtureId; }
            set { if (value != fixtureId) { fixtureId = value; OnPropertyChanged("FixtureId"); } }
        }

        private string userId = "";
        public string UserId
        {
            get { return userId; }
            set { if (value != userId) { userId = value; OnPropertyChanged("UserId"); } }
        }

        private string eqpId = "";
        public string EqpId
        {
            get { return eqpId; }
            set { if (value != eqpId) { eqpId = value; OnPropertyChanged("EqpId"); } }
        }
        public OfilmCustomizedWinMode()
        {
            bool bOK = LoadXml(GetWorkPath() + "config\\semichip_ctp_config.xml");

            if (bOK)
            {
                ResolveXmlSetting();
            }
            else
            {
                CreateNewXmlDoc();
            }
        }

        public override void XMLDataToView()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            if (null == smTesterNode) return;
            var WorkStation = GetXmlAttrbuteString(smTesterNode, "common", "work_station");
            XmlNode stNode = smTesterNode.SelectSingleNode(WorkStation);
            if (null == stNode) return;


            FixtureId = GetXmlAttrbuteString(stNode, "custom_ofilm", "fixtureId", "");
            UserId = GetXmlAttrbuteString(stNode, "custom_ofilm", "userId", "");
            EqpId = GetXmlAttrbuteString(stNode, "custom_ofilm", "eqpId", "");

        
        }

        public override void ViewToXMLData()
        {
            XmlNode smTesterNode = xml.SelectSingleNode("semitester");
            if (null == smTesterNode) return;
            var WorkStation = GetXmlAttrbuteString(smTesterNode, "common", "work_station");
            XmlNode stNode = smTesterNode.SelectSingleNode(WorkStation);
            if (null == stNode) return;


            SaveXmlAttrbuteString(stNode, "custom_ofilm", "fixtureId", FixtureId);
            SaveXmlAttrbuteString(stNode, "custom_ofilm", "userId", UserId);
            SaveXmlAttrbuteString(stNode, "custom_ofilm", "eqpId", EqpId);


            SaveXml(GetWorkPath() + "config\\semichip_ctp_config.xml");
        }

    }
}
