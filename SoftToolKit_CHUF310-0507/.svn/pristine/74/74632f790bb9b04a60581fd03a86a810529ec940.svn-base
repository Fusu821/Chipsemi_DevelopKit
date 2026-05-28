using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

using System.Web.Script.Serialization;

namespace SEMIEmsSysUpLoad
{
public class HesMesProcessRequest
{

    private string key_v = "";
    public string key
    { 
        get{return key_v;} 
        set{ if(value != key_v) {key_v = value;} }
    }

    private string method_v = "sn.auto.process";
    public string method
    { 
        get{return method_v;} 
        set{ if(value != method_v) {method_v = value; } }
    }

    public List<HesMesProcessParameter> parameter { get; set; }
}

public class HesMesProcessParameter
{
    private string machine_no_v = "";
    public string machine_no
    {
        get { return machine_no_v; }
        set { if (value != machine_no_v) { machine_no_v = value; } }
    }
    private string lot_no_v = "";
    public string lot_no
    {
        get { return lot_no_v; }
        set { if (value != lot_no_v) { lot_no_v = value; } }
    }
    private string op_no_v = "";
    public string op_no
    {
        get { return op_no_v; }
        set { if (value != op_no_v) { op_no_v = value; } }
    }
    private string subop_no_v = "";
    public string subop_no
    {
        get { return subop_no_v; }
        set { if (value != subop_no_v) { subop_no_v = value; } }
    }
    private string position_no_v = "";
    public string position_no
    {
        get { return position_no_v; }
        set { if (value != position_no_v) { position_no_v = value; } }
    }
    private string sn_v = "";
    public string sn
    {
        get { return sn_v; }
        set { if (value != sn_v) { sn_v = value; } }
    }
    private string zj_code_v = "";
    public string zj_code
    {
        get { return zj_code_v; }
        set { if (value != zj_code_v) { zj_code_v = value; } }
    }
    private string pt_code_v = "";
    public string pt_code
    {
        get { return pt_code_v; }
        set { if (value != pt_code_v) { pt_code_v = value; } }
    }
    private string qc_result_v = "";
    public string qc_result
    {
        get { return qc_result_v; }
        set { if (value != qc_result_v) { qc_result_v = value; } }
    }
    private string qc_reason_v = "";
    public string qc_reason
    {
        get { return qc_reason_v; }
        set { if (value != qc_reason_v) { qc_reason_v = value; } }
    }
    private string report_datetime_v = "";
    public string report_datetime
    {
        get { return report_datetime_v; }
        set { if (value != report_datetime_v) { report_datetime_v = value; } }
    }
    private string process_person_v = "";
    public string process_person
    {
        get { return process_person_v; }
        set { if (value != process_person_v) { process_person_v = value; } }
    }
    public List<HesMesAttributeItem> attribute_list { get; set; }
    public List<HesMesKeyPartItem> keypart_list { get; set; }
}

public class HesMesAttributeItem
{
    private string attrib_no_v = "";
    public string attrib_no
    {
        get { return attrib_no_v; }
        set { if (value != attrib_no_v) { attrib_no_v = value; } }
    }
    private string attrib_value_v = "";
    public string attrib_value
    {
        get { return attrib_value_v; }
        set { if (value != attrib_value_v) { attrib_value_v = value; } }
    }
}

public class HesMesKeyPartItem
{
    private string keypart_no_v = "";
    public string keypart_no
    {
        get { return keypart_no_v; }
        set { if (value != keypart_no_v) { keypart_no_v = value; } }
    }
}

class HesResult
{
    public string code { get; set; }
    public string msg { get; set; }
    public string msg_code { get; set; }
}

    class CHesNewEmsUpLoad : CUpLoadBase
    {
        /*  infoarray[0] - mesUrl
         *  infoarray[1] - machine_no
         *  infoarray[2] - lot_no
         *  infoarray[3] - subop_no
         *  infoarray[4] - person
         *  infoarray[5] - barcode
         *  infoarray[6] - result
         *  infoarray[7] - failReason
         *  infoarray[8] - ic_type
         */
        public override int SendEms(String info, ref String errmse)
        {
            int ret = 0;

            var infoarray = Analysis(info);
            if (infoarray.Length != 9)
            {
                ret = 1;
                errmse = "Data transmission error!!!";
            }
            else
            {
                HesMesProcessRequest mesRequest = new HesMesProcessRequest();
                mesRequest.parameter = new List<HesMesProcessParameter>();
                HesMesProcessParameter paramModel = new HesMesProcessParameter();
                char[] trimChars = { '/' };
                String mesUrl = infoarray[0].Trim().TrimEnd(trimChars);

                paramModel.machine_no = infoarray[1].Trim();
                paramModel.lot_no = infoarray[2].Trim();
                paramModel.subop_no = infoarray[3].Trim();
                paramModel.process_person = infoarray[4].Trim();
                paramModel.sn = infoarray[5].Trim();
                paramModel.qc_result = infoarray[6].Trim();
                String failReason = infoarray[7].Trim();
                String failReasonrp = "6";
                string ic_type = infoarray[8].Trim();
                Dictionary<string, string> failCodeMap = new Dictionary<string, string>();
                if (ic_type == "1")
                {
                    failCodeMap.Add("10", "1");
                    failCodeMap.Add("11", "1");
                    failCodeMap.Add("12", "1");
                    failCodeMap.Add("16", "2");
                    failCodeMap.Add("13", "3");
                    failCodeMap.Add("7", "4");
                    failCodeMap.Add("5", "5");
                }
                else //3536
                {
                    failCodeMap.Add("11", "1");
                    failCodeMap.Add("12", "1");
                    failCodeMap.Add("13", "1");
                    failCodeMap.Add("10", "2");
                    failCodeMap.Add("14", "3");
                    failCodeMap.Add("7", "4");
                    failCodeMap.Add("5", "5");
                    failCodeMap.Add("6", "5");
                }
                string newFailCode = string.Empty;
                if (failCodeMap.TryGetValue(failReason, out newFailCode))
                {
                    failReasonrp = newFailCode;
                }
                paramModel.qc_reason = (paramModel.qc_result == "1") ? "" : failReasonrp;

                paramModel.attribute_list = new List<HesMesAttributeItem>();
                HesMesAttributeItem attrItem1 = new HesMesAttributeItem();
                //attrItem1.attrib_no = "";
                //attrItem1.attrib_value = "";
                //paramModel.attribute_list.Add(attrItem1);
                //HesMesAttributeItem attrItem2 = new HesMesAttributeItem();
                //attrItem2.attrib_no = "";
                //attrItem2.attrib_value = "";
                //paramModel.attribute_list.Add(attrItem2);
                paramModel.attribute_list.Add(new HesMesAttributeItem());
                paramModel.attribute_list.Add(new HesMesAttributeItem());

                paramModel.keypart_list = new List<HesMesKeyPartItem>();
                //HesMesKeyPartItem keyPartItem = new HesMesKeyPartItem();
                //keyPartItem.keypart_no = "";
                //paramModel.keypart_list.Add(keyPartItem);
                paramModel.keypart_list.Add(new HesMesKeyPartItem());

                mesRequest.parameter.Add(paramModel);

                ret = ReportProcess(mesUrl, mesRequest, ref errmse);
            }

            return ret;
        }

        public int ReportProcess(String url, HesMesProcessRequest mesRequest, ref String errmse)
        {
            int ret = 0;
            WebRequest req = null;
            try
            {
                //url = url + "/ReportProcess";
                req = WebRequest.Create(url);
                req.Timeout = 5000;  //timeout
                req.Method = "POST";
                req.ContentType = "application/json;charset=utf-8";
                ((HttpWebRequest)req).Accept = "application/json";

                JavaScriptSerializer serializer = new JavaScriptSerializer();
                string jsonData = serializer.Serialize(mesRequest);

                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    //JavaScriptSerializer serializer = new JavaScriptSerializer();
                    //string jsonData = serializer.Serialize(mesRequest);
                    //writer.WriteLine(jsonData);
                    writer.Write(jsonData);
                    //writer.Close();
                }
                using (var rsp = req.GetResponse())
                {
                    //req.GetRequestStream().Close();
                    if (rsp != null)
                    {
                        using (var answerReader = new StreamReader(rsp.GetResponseStream()))
                        {
                            var readString = answerReader.ReadToEnd();
                            //JavaScriptSerializer serializer = new JavaScriptSerializer();
                            //HesResult pHesResult = serializer.Deserialize<HesResult>(readString);
                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;
                            HesResult pHesResult = null;
                            try
                            {
                                pHesResult = serializer.Deserialize<HesResult>(readString);
                            }
                            catch
                            {
                                ret = 1;
                                errmse = "MES return data format error: " + msg;
                                return ret;
                            }
                            if (pHesResult != null && pHesResult.code == "0")
                            {
                                ret = 0;
                            }
                            else
                            {
                                ret = 1;
                            }
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                var msg = ex.ToString();
                if (msg.Length > 150)
                {
                    msg = msg.Substring(0, 150);
                }
                errmse = msg;
                ret = 1;
            }

            return ret;
        }

    }
}
