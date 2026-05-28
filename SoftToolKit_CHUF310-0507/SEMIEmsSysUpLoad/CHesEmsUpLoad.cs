using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

namespace SEMIEmsSysUpLoad
{
    public class CHesEmsUpLoad : CUpLoadBase
    {

        public override int SendEms(String info, ref String errmse)
        {
            int ret = 0;

            var infoarray = Analysis(info);

            if (infoarray.Length != 4)
            {
                ret = 1;
            }
            else
            {
                var soap = StringToXml(infoarray[0], infoarray[1], infoarray[2], infoarray[3]);
                ret = SendInfoXml(soap, ref errmse);
            }

            return ret;
        }

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
        public int SendInfoXml(string soap, ref String errmse)
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

                            //var readString = "<soap:Envelope xmlns:soap=" +
                            //        "<return><interfaceid>INT_MT01</interfaceid><messageid>0000000001</messageid><resultmessage>成功</resultmessage><resultstring>&lt;?xml version=?&gt;&#13;" +
                            //        "&lt;Message&gt;&#13;&lt;Header&gt;&#13;&lt;MESSAGENAME&gt;INT_MT01&lt;/MESSAGENAME&gt;&#13;&lt;EVENTCOMMENT&gt;INT_MT01&lt;/EVENTCOMMENT&gt;&#1&lt;ORIGINALSOURCESUBJECTNAME&gt;amq.rabbitmq.reply-to.g1h2AA9yZXBseUAxMjE4OTkyMDEAAAliAAAQxGUp3Wg=.V/BE0fSg1i3Cp0bpYeJqWw==, AMQPCorrelationID[1474060]&lt;/ORIGINALSOURCESUBJECTNAME&gt;&#13; &lt;listener&gt;QueueListener&lt;/listener&gt;&#13;&lt;/Header&gt;&#13;&lt;Body&gt;&#13;" +
                            //        "&lt;PANELNAME&gt;A1D76000114A23060504093&lt;/PANELNAME&gt;&#13;&lt;MACHINENAME&gt;TFT5-OTP-01&lt;/MACHINENAME&gt;&#13;&lt;PANELJUDGE&gt;G&lt;/PANELJUDGE&gt;&#13;&lt;/Body&gt;&#13;" +
                            //        "&lt;Return&gt;&#13;&lt;RETURNCODE&gt;0&lt;/RETURNCODE&gt;&#13;&lt;RETURNMESSAGE /&gt;&#13;&lt;/Return&gt;&#13;&lt;/Message&gt;&#13;</resultstring> <resulttype>S</resulttype></return> </ns2:TEST_REQUESTResponse></soap:Body></soap:Envelope>";

                            //var readString ="<soap:Envelope><soap:Body><return><interfaceid>INT_MT01</interfaceid><messageid>0000000001</messageid><resultmessage>LOT-9000|LOT-9000</resultmessage><resultstring>&lt;?xml version=?&gt;&#13;&lt;Message&gt;&#13;&lt;Header&gt;&#13;&lt;MESSAGENAME&gt;INT_MT01&lt;/MESSAGENAME&gt;&#13;&lt;EVENTCOMMENT&gt;INT_MT01&lt;/EVENTCOMMENT&gt;&#13;&lt;ORIGINALSOURCESUBJECTNAME&gt;amq.rabbitmq.reply-to.g1h2AA9yZXBseUAxMjE4OTkyMDEAAFjbAAARO2Up3Wg=.HNr3PsmqVCDfHKOEezLa6g==, AMQPCorrelationID[1473944]&lt;/ORIGINALSOURCESUBJECTNAME&gt;&#13;&lt;listener&gt;QueueListener&lt;/listener&gt;&#13;&lt;/Header&gt;&#13;&lt;Body&gt;&#13;"+
                            //"&lt;PANELNAME&gt;B1D76000114A23060504093&lt;/PANELNAME&gt;&#13;&lt;MACHINENAME&gt;TFT5-OTP-01&lt;/MACHINENAME&gt;&#13;&lt;PANELJUDGE&gt;G&lt;/PANELJUDGE&gt;&#13;&lt;/Body&gt;&#13;"+
                            //"&lt;Return&gt;&#13;&lt;RETURNCODE&gt;LOT-9000&lt;/RETURNCODE&gt;&#13;&lt;RETURNMESSAGE&gt;LOT-9000&lt;/RETURNMESSAGE&gt;&#13;&lt;/Return&gt;&#13;"+
                            //"&lt;/Message&gt;&#13;</resultstring><resulttype>F</resulttype></return></ns2:TEST_REQUESTResponse></soap:Body></soap:Envelope>";


                            var posi_one = readString.IndexOf("RETURNCODE&gt;");
                            var posi_two = readString.LastIndexOf("&lt;/RETURNCODE");
                            if ((posi_one != -1) && (posi_two != -1) && (posi_one + 14 < posi_two))
                            {
                                var str1 = readString.Substring(posi_one+14, posi_two - (posi_one + 14));
                                if (str1 == "0")
                                {
                                    ret = 0;
                                }
                                else
                                {

                                    ret = 1;
                                    var posi1 = readString.IndexOf("RETURNMESSAGE&gt;");
                                    var posi2 = readString.LastIndexOf("&lt;/RETURNMESSAGE");
                                    if ((posi1 != -1) && (posi2 != -1) && (posi1 + 17 < posi2))
                                    {
                                        var str2 = readString.Substring(posi1+17, posi2 - (posi1 + 17));
                                        errmse = str2;
                                    }
                                    else
                                    {
                                        errmse = "Not Found ReturnMessage";
                                    }



                                }
                            }
                            else
                            {
                                errmse = "Not Found ReturnCode";
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
