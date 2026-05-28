using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

namespace SEMITestApp.Src.FileUpload
{
    public class Upload
    {
        public int UploadCallBack(int SelectedFormat, string info)
        {
            int ret = 0;

            if (SelectedFormat == 7 )
            {
                var ems = new EMSUpload();
                ret = ems.Save(info);
            }
            return ret;

        }
    }


    public class EMSUpload
    {
        public string StringToXml(string num, string id, string name, string result)
        {

            string soap = @"<soapenv:Envelope xmlns:soapenv=""http://schemas.xmlsoap.org/soap/envelope/""  xmlns:ser=""http://service.webservice.solution.zero.ricardo.com/"">" +
                            "<soapenv:Header/>" +
                               "<soapenv:Body>" +
                                    "<ser:TEST_REQUEST>" +
                                        "<INTERFACEID>INT_MT01</INTERFACEID>" +
                                        "<MESSAGEID>0000000001</MESSAGEID>" +
                                        "<TRANSID>202305140000001</TRANSID>" +
                                        "<SENDER>" + name + "</SENDER>" +
                                        "<RECEIVER>MES</RECEIVER>" +
                                        @"<REQUESTSTRING><![CDATA[<?xml version=""1.0"" encoding=""utf - 8"" standalone=""yes""?><Message><Header><MESSAGENAME>INT_MT01</MESSAGENAME><EVENTCOMMENT></EVENTCOMMENT></Header><Body><PANELNAME>" + num + "</PANELNAME><MACHINENAME>" + id + "</MACHINENAME><PANELJUDGE>" + result + "</PANELJUDGE></Body></Message>]]></REQUESTSTRING>" +
                                    "</ser:TEST_REQUEST>" +
                                "</soapenv:Body>" +
                            "</soapenv:Envelope>";

            return soap;
        }

        public int Save(string info)
        {
            int ret = 0;

            var infoarray = info.Split('^');
            if (infoarray.Length != 4)
            {
                ret = 1;
            }
            else
            {
                var soap = StringToXml(infoarray[0], infoarray[1], infoarray[2], infoarray[3]);
                ret = Send_Info(soap);
            }

            return ret;
            
        }

        public int Send_Info(string soap)
        {

            int ret = 1;
            string srt = @"http://192.168.1.231:8988/service/api?wsdl";
            var req = WebRequest.Create(srt);
            req.Timeout = 300000;  //timeout
            req.Method = "POST";
            req.ContentType = "text/xml;charset=UTF-8";
            try
            {
                using (var writer = new StreamWriter(req.GetRequestStream()))
                {
                    writer.WriteLine(soap);
                    writer.Close();
                    //ret = 0;

                }
                using (var rsp = req.GetResponse())
                {
                    req.GetRequestStream().Close();
                    if (rsp != null)
                    {
                        using (var answerReader = new StreamReader(rsp.GetResponseStream()))
                        {
                            var readString = answerReader.ReadToEnd();
                            var posi_one = readString.IndexOf("RETURNCODE");
                            var posi_two = readString.LastIndexOf("RETURNCODE");
                            if ((posi_one != -1) && (posi_two != -1) && (posi_one < posi_two))
                            {
                                var str1 = readString.Substring(posi_one, posi_two - posi_one);
                                var posi = str1.IndexOf("gt;0&lt");
                                if (posi != -1)
                                {
                                    ret = 0;
                                }
                            }


                        }
                    }
                    else
                    {
                        ret = 1;
                    }
                }
            }
            catch (System.Exception ex)
            {
                ex.ToString();
            }
            
            return ret;    
        }

    }
}
