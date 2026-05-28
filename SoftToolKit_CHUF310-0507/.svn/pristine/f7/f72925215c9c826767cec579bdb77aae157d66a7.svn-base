using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

using System.Web.Script.Serialization;

namespace SEMIEmsSysUpLoad
{

    class ReportProcess
    {
        public string user = "";
        public string processcode = "";
        public string linecode = "";
        public string barcode = "";
        public string result = "";
        public string message = "";
    }

    class CheckProcess
    {
        public string user = "";
        public string processcode = "";
        public string linecode = "";
        public string barcode = "";
    }

    class ReportLog
    {
        public string user = " ";
        public string processcode = " ";
        public string linecode = " ";
        public string barcode = " ";
        public string result = " ";
        public string orderno = " ";

        public string equipname1 = "0";
        public string equipname2 = "0";
        public string equipname3 = "0";
        public string testlog = "0";
        public string taketime = "0";
        public string softwarever = "0";
        public string channel = "0";

        public string ngcode = "0";
        public string pcid = "0";
        public string weightvalue = "0";
        public string message = "0";
        public string bindname = "0";
        public string binddata = "0";
        public bool reportprocflag = false;
    }

    class ChuangWeiResult
    {

        public bool Result { get; set; }
        public string Message { get; set; }

    }


    class CChuangWeiEmsUpLoad : CUpLoadBase
    {

        /*  infoarray[0] - mesUrl           
         *  infoarray[1] - user              
         *  infoarray[2] - processcode      
         *  infoarray[3] - linecode        
         *  infoarray[4] - bar_code        
         *  infoarray[5] - result         
         *  infoarray[6] - message          
         *  infoarray[7] - simulationUp
         *  infoarray[8] - orderno
         *  infoarray[9] - TestAppVersion
         *  infoarray[10] - macAddress

         */
        public override int SendEms(String info, ref String errmse)
        {
            int ret = 0;

            var infoarray = Analysis(info);
            if (infoarray.Length != 12)
            {
                ret = 1;
                errmse = "Data transmission error!!!";
            }
            else
            {
                ReportProcess emsMsg = new ReportProcess();
                char[] trimChars = { '/' };
                String mesUrl = infoarray[0].Trim().TrimEnd(trimChars); 

                emsMsg.user = infoarray[1].Trim();
                emsMsg.processcode = infoarray[2].Trim();
                emsMsg.linecode = infoarray[3].Trim();
                emsMsg.barcode = infoarray[4].Trim();
                emsMsg.result = infoarray[5].Trim();           

                String simulationUp = infoarray[7].Trim();
                String orderno = infoarray[8].Trim();
                String softwarever = infoarray[9].Trim();
                String macAddress = infoarray[10].Trim();
                String failReason = infoarray[11].Trim();

                emsMsg.message = (emsMsg.result == "OK") ? infoarray[6].Trim() : failReason;

                CheckProcess checkMsg = new CheckProcess();
                checkMsg.user = emsMsg.user;
                checkMsg.processcode = emsMsg.processcode;
                checkMsg.linecode = emsMsg.linecode;
                checkMsg.barcode = emsMsg.barcode;
                ret = CheckProcess(mesUrl, checkMsg, ref errmse);
                if (ret != 0) return ret;

                if (simulationUp == "0")
                {
                    ret = ReportProcess(mesUrl, emsMsg, ref errmse);
                    if (ret != 0) return ret;
                }
              
                ReportLog logMsg = new ReportLog();
                logMsg.user = emsMsg.user;
                logMsg.processcode = emsMsg.processcode;
                logMsg.linecode = emsMsg.linecode;
                logMsg.barcode = emsMsg.barcode;
                logMsg.result = emsMsg.result;
                logMsg.orderno = orderno;
                logMsg.softwarever = softwarever;
                logMsg.pcid = macAddress;
                logMsg.ngcode = (logMsg.result!="OK") ? failReason : "";
                logMsg.reportprocflag = false;
                if (ret != 0) logMsg.message = errmse;

                ret = ReportLog(mesUrl, logMsg, ref errmse);
                if (ret != 0) return ret;   

            }
            
            return ret;
        }

        public int CheckProcess(String url, CheckProcess emsMsg, ref String errmse)
        {
            int ret = 0;
            try
            {
                url = url + "/CheckProcess?user=" + emsMsg.user + "&processcode=" + emsMsg.processcode + "&linecode=" + emsMsg.linecode + "&barcode=" + emsMsg.barcode;
                var req = WebRequest.Create(url);
                req.Timeout = 5000;  //timeout
                req.Method = "GET";
                using (var rsp = req.GetResponse())
                {
                    //req.GetRequestStream().Close();
                    if (rsp != null)
                    {
                        using (var answerReader = new StreamReader(rsp.GetResponseStream()))
                        {
                            var readString = answerReader.ReadToEnd();
                            JavaScriptSerializer serializer = new JavaScriptSerializer();
                            ChuangWeiResult pChuangWeiResult = serializer.Deserialize<ChuangWeiResult>(readString);
                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;

                            if (pChuangWeiResult.Result == true)
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

        public int ReportProcess(String url, ReportProcess emsMsg, ref String errmse)
        {
            int ret = 0;
            try
            {
                url = url + "/ReportProcess";
                var req = WebRequest.Create(url);
                req.Timeout = 5000;  //timeout
                req.Method = "POST";
                req.ContentType = "application/json";

                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    JavaScriptSerializer serializer = new JavaScriptSerializer();

                    string jsonData = serializer.Serialize(emsMsg);
                    writer.WriteLine(jsonData);
                    writer.Close();

                }
                using (var rsp = req.GetResponse())
                {
                    req.GetRequestStream().Close();
                    if (rsp != null)
                    {
                        using (var answerReader = new StreamReader(rsp.GetResponseStream()))
                        {
                            var readString = answerReader.ReadToEnd();
                            JavaScriptSerializer serializer = new JavaScriptSerializer();
                            ChuangWeiResult pChuangWeiResult = serializer.Deserialize<ChuangWeiResult>(readString);
                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;

                            if(pChuangWeiResult.Result == true)
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

        public int ReportLog(String url, ReportLog emsMsg, ref String errmse)
        {
            int ret = 0;
            try
            {
                url = url + "/UploadTestLog";
                var req = WebRequest.Create(url);
                req.Timeout = 5000;  //timeout
                req.Method = "POST";
                req.ContentType = "application/json";

                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    JavaScriptSerializer serializer = new JavaScriptSerializer();

                    string jsonData = serializer.Serialize(emsMsg);
                    writer.WriteLine(jsonData);
                    writer.Close();

                }
                using (var rsp = req.GetResponse())
                {
                    req.GetRequestStream().Close();
                    if (rsp != null)
                    {
                        using (var answerReader = new StreamReader(rsp.GetResponseStream()))
                        {
                            var readString = answerReader.ReadToEnd();
                            JavaScriptSerializer serializer = new JavaScriptSerializer();
                            ChuangWeiResult pChuangWeiResult = serializer.Deserialize<ChuangWeiResult>(readString);
                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;

                            if (pChuangWeiResult.Result == true)
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
