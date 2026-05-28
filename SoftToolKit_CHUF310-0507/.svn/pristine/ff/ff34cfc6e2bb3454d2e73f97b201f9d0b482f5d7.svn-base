using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

using System.Web.Script.Serialization;

namespace SEMIEmsSysUpLoad
{
    class CLogin
    {
        public string userNo { get; set; }
        public string password { get; set; }
    }

    class CRetLogin
    {
        public string msgStr { get; set; }
        public int msgId { get; set; }
        public string token { get; set; }
    }

    class CcheckRoute
    {
        public string pcbSeq { get; set; }
        public string prodNo { get; set; }
        public string stationNo { get; set; }
        public string retest { get; set; }
    }

    class CRetRoute
    {
        public int msgId { get; set; }
        public string msgStr { get; set; }
        public string mpcbSeq { get; set; }
        public string[] snList { get; set; }
    }

    class CcreateRoute
    {
        public string pcbSeq    { get; set; }
        public string prodNo    { get; set; }
        public string stationNo { get; set; }
        public string result    { get; set; }

        public string remark { get; set; }
        public string testItem { get; set; }
        public string userNo { get; set; }
        public string weight { get; set; }

        public string packNo { get; set; }
        public string rmk1 { get; set; }
        public string rmk2 { get; set; }
        public string rmk3 { get; set; }
        public string rmk4 { get; set; }
    }

    class EmsMsg
    {
        public string mesUrl { get; set; }
        public string fixtureId { get; set; }
        public string prodNo { get; set; }
        public string stationNo { get; set; }

        public string userNo { get; set; }
        public string password { get; set; }
        public string pcbSeq { get; set; }
        public string result { get; set; }
    }


    class CPbhEmsUpLoad : CUpLoadBase
    {

        /*  infoarray[0] - mesUrl            //上传地址
         *  infoarray[1] - fixtureId         //治具编号
         *  infoarray[2] - testStepId        //工单编号
         *  infoarray[3] - stationId         //站号
         *  infoarray[4] - userId            //工号
         *  infoarray[5] - passWord          //密码
         *  infoarray[6] - serialNumber      //SN码
         *  infoarray[7] - isPass            //结果
         */
        public override int SendEms(String info, ref String errmse)
        {
            int ret = 0;

            var infoarray = Analysis(info);
            if (infoarray.Length != 8)
            {
                ret = 1;
                errmse = "Data transmission error!!!";
            }
            else
            {
                EmsMsg emsMsg = new EmsMsg();
                char[] trimChars = { '/' };
                emsMsg.mesUrl = infoarray[0].Trim().TrimEnd(trimChars); 
                emsMsg.fixtureId = infoarray[1].Trim();
                emsMsg.prodNo = infoarray[2].Trim();
                emsMsg.stationNo = infoarray[3].Trim();
                emsMsg.userNo = infoarray[4].Trim();
                emsMsg.password = infoarray[5].Trim();
                emsMsg.pcbSeq = infoarray[6].Trim();
                emsMsg.result = infoarray[7].Trim();
                String token ="";
                ret =  ClientLogin( emsMsg,  ref errmse, ref  token);
                if (ret != 0) return ret;

                ret = ChecRoute(emsMsg, ref errmse, token);
                if (ret != 0) return ret;

                ret = CreateRoute(emsMsg, ref errmse, token);
                if (ret != 0) return ret;


            }
            
            return ret;
        }

        public int ClientLogin(EmsMsg emsMsg, ref String errmse, ref String token)
        {
            int ret = 0;
            var url = emsMsg.mesUrl;
            url = url + "/clientLogin";
            try
            {
                var req = WebRequest.Create(url);
                req.Timeout = 300000;  //timeout
                req.Method = "POST";
                req.ContentType = "application/json";

                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    JavaScriptSerializer serializer = new JavaScriptSerializer();
                    CLogin msg = new CLogin();
                    msg.userNo = emsMsg.userNo;
                    msg.password = emsMsg.password;
                    string jsonData = serializer.Serialize(msg);
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
                            CRetLogin retLogin = serializer.Deserialize<CRetLogin>(readString);
                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;

                            if ((retLogin.msgId == 0) && (retLogin.token != ""))
                            {
                                token = retLogin.token;
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

        public int ChecRoute(EmsMsg emsMsg, ref String errmse, String token)
        {
            int ret = 0;
            var url = emsMsg.mesUrl;//URL
            url = url + "/checkRoute";

            try
            {
                var req = WebRequest.Create(url);
                req.Timeout = 300000;  //timeout
                req.Method = "POST";
                req.ContentType = "application/json";
                req.Headers["token"] = token;

                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    JavaScriptSerializer serializer = new JavaScriptSerializer();
                    CcheckRoute msg = new CcheckRoute();
                    msg.pcbSeq = emsMsg.pcbSeq;
                    msg.prodNo = emsMsg.prodNo;
                    msg.stationNo = emsMsg.stationNo;
                    msg.retest = "0";
                    string jsonData = serializer.Serialize(msg);
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
                            CRetRoute retRoute = serializer.Deserialize<CRetRoute>(readString);

                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;

                            if ((retRoute.msgId == 0))
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
        public int CreateRoute(EmsMsg emsMsg, ref String errmse, String token)
        {
            int ret = 0;
            var url = emsMsg.mesUrl;//URL
            url = url + "/createRoute";

            try
            {
                var req = WebRequest.Create(url);
                req.Timeout = 300000;  //timeout
                req.Method = "POST";
                req.ContentType = "application/json";
                req.Headers["token"] = token;

                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    JavaScriptSerializer serializer = new JavaScriptSerializer();
                    CcreateRoute msg = new CcreateRoute();

                    msg.pcbSeq = emsMsg.pcbSeq;
                    msg.prodNo = emsMsg.prodNo;
                    msg.stationNo = emsMsg.stationNo;
                    msg.result = emsMsg.result;

                    msg.remark = "";
                    msg.testItem = "";
                    msg.userNo = emsMsg.userNo;
                    msg.weight = "";

                    msg.packNo = "";
                    msg.rmk1 = emsMsg.fixtureId;
                    msg.rmk2 = "";
                    msg.rmk3 = "";
                    msg.rmk4 = "";

                    string jsonData = serializer.Serialize(msg);
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
                            CRetRoute retRoute = serializer.Deserialize<CRetRoute>(readString);

                            var msg = readString;
                            if (msg.Length > 150)
                            {
                                msg = msg.Substring(0, 150);
                            }

                            errmse = msg;

                            if ((retRoute.msgId == 0))
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
