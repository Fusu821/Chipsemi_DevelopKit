using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Net.NetworkInformation;
using System.Xml;

namespace SEMIEmsSysUpLoad
{
    #region 
    public static class MesConstant
    {
        // SOAP Action
        public const string SOAP_ACTION_CHECK = "http://tempuri.org/Web_StartCheck_V2";
        public const string SOAP_ACTION_REPORT = "http://tempuri.org/Web_GetTestResult_V2";

        public const int WEB_REQUEST_TIMEOUT = 5000;

        public const string RESULT_PASS = "PASS";

        public const string DEFAULT_MAC = "d06f623d809f";

        public const string TEST_SUCCESS_MSG = "Test OK";

        public const int INFO_ARRAY_REQUIRED_LENGTH = 13;

        public const int INDEX_TESTRESULT = 14;
        public const int INDEX_RETURNMSG = 19;
    }
    #endregion

    #region 
    public class LsMesProcessRequest
    {
        public string resourcename { get; set; }
        public string lotsn { get; set; }
        public string spec_code { get; set; }
        public string testsoft { get; set; }
        public string operator_ls { get; set; }

        public LsMesProcessRequest()
        {
            resourcename = string.Empty;
            lotsn = string.Empty;
            spec_code = string.Empty;
            testsoft = string.Empty;
            operator_ls = string.Empty;
        }
    }

    public class LsMesProcessParameter
    {
        public string lotsn { get; set; }
        public string device_no { get; set; }
        public string mac { get; set; }
        public string testresult { get; set; }
        public string start_time { get; set; }
        public string test_time { get; set; }
        public string testitem { get; set; }
        public string ismatcingfail { get; set; }
        public string isitem { get; set; }

        public LsMesProcessParameter()
        {
            lotsn = string.Empty;
            device_no = string.Empty;
            mac = MesConstant.DEFAULT_MAC;
            testresult = string.Empty;
            start_time = string.Empty;
            test_time = string.Empty;
            testitem = string.Empty;
            ismatcingfail = "0";
            isitem = "0";
        }
    }

    public class LsResult
    {
        public string I_ReturnMessage { get; set; }
        public string TestResult { get; set; }

        public LsResult()
        {
            I_ReturnMessage = string.Empty;
            TestResult = string.Empty;
        }
    }
    #endregion

    class CLsEmsUpLoad : CUpLoadBase
    {
        /*  infoarray
         *  0 - mesUrl        MES接口地址
         *  1 - Resource_no   资源编号
         *  2 - Special_Code  规格编码
         *  3 - Operator_Ls   操作员
         *  4 - Device_num    设备编号
         *  5 - Barcode       条码
         *  6 - Result        测试结果（PASS/FAIL）
         *  7 - FailReason    失败原因
         *  8 - TestAppVersion 测试软件版本
         *  9 - StartTime     开始时间
         *  10 - TestTime     测试耗时
         *  11 - DisplayEN    显示测试
         *  12 - LogolContent 整体日志
         */
        public override int SendEms(String info, ref String errmse)
        {
            int ret = 0;

            var infoarray = Analysis(info);
            if (infoarray.Length != MesConstant.INFO_ARRAY_REQUIRED_LENGTH)
            {
                ret = 1;
                errmse = "Data transmission error!!!";
            }
            else
            {
                LsMesProcessRequest mesRequest = new LsMesProcessRequest();
                char[] trimChars = { '/' };
                String mesUrl = SafeTrim(infoarray[0]).TrimEnd(trimChars);

                mesRequest.resourcename = SafeTrim(infoarray[1]);
                mesRequest.lotsn = SafeTrim(infoarray[5]);
                mesRequest.spec_code = SafeTrim(infoarray[2]);
                mesRequest.testsoft = SafeTrim(infoarray[8]);
                mesRequest.operator_ls = SafeTrim(infoarray[3]);

                LsMesProcessParameter paramModel = new LsMesProcessParameter();
                paramModel.lotsn = mesRequest.lotsn;
                paramModel.device_no = SafeTrim(infoarray[4]);
                paramModel.mac = GetSimple12BitMac();
                paramModel.testresult = SafeTrim(infoarray[6]);
                paramModel.start_time = SafeTrim(infoarray[9]);
                paramModel.test_time = SafeTrim(infoarray[10]);
                string DisplayEn = SafeTrim(infoarray[11]);
                string TestLog = infoarray[12] ?? string.Empty;
                string mesage = MesConstant.TEST_SUCCESS_MSG;
                if (DisplayEn == "0")
                {
                    mesage = TestLog;
                }
                string failReason = SafeTrim(infoarray[7]);
                paramModel.testitem = (paramModel.testresult == MesConstant.RESULT_PASS) ? mesage : failReason;

                var Check_Soap = BuildCheckXml(mesRequest);
                ret = CheckProcess(mesUrl, Check_Soap, ref errmse);
                if (ret != 0) return ret; 

                var Report_Soap = BuildReportXml(paramModel);
                ret = ReportProcess(mesUrl, Report_Soap, ref errmse);
            }

            return ret;
        }

        public string BuildCheckXml(LsMesProcessRequest mesModel)
        {
            if (mesModel == null)
            {
                throw new ArgumentNullException("mesModel", "The MES entity object cannot be empty.");
            }
            // 用StringBuilder拼接，提升性能；所有属性均XML转义
            StringBuilder soapBuilder = new StringBuilder();
            soapBuilder.Append(@"<?xml version=""1.0"" encoding=""utf-8""?>");
            soapBuilder.Append(@"<soap:Envelope xmlns:xsi=""http://www.w3.org/2001/XMLSchema-instance"" xmlns:xsd=""http://www.w3.org/2001/XMLSchema"" xmlns:soap=""http://schemas.xmlsoap.org/soap/envelope/"">");
            soapBuilder.Append(@"  <soap:Body>");
            soapBuilder.Append(@"    <Web_StartCheck_V2 xmlns=""http://tempuri.org/"">");
            soapBuilder.AppendFormat(@"      <ResourceName>{0}</ResourceName>", XmlEncode(mesModel.resourcename));
            soapBuilder.AppendFormat(@"      <LotSN>{0}</LotSN>", XmlEncode(mesModel.lotsn));
            soapBuilder.AppendFormat(@"      <SpecialCode>{0}</SpecialCode>", XmlEncode(mesModel.spec_code));
            soapBuilder.AppendFormat(@"      <TestSoft>{0}</TestSoft>", XmlEncode(mesModel.testsoft));
            soapBuilder.AppendFormat(@"      <Operator>{0}</Operator>", XmlEncode(mesModel.operator_ls));
            soapBuilder.Append(@"    </Web_StartCheck_V2>");
            soapBuilder.Append(@"  </soap:Body>");
            soapBuilder.Append(@"</soap:Envelope>");
            return soapBuilder.ToString();
        }

        public string BuildReportXml(LsMesProcessParameter mesModel)
        {
            if (mesModel == null)
            {
                throw new ArgumentNullException("mesModel", "The MES entity object cannot be empty.");
            }
            StringBuilder soapBuilder = new StringBuilder();
            soapBuilder.Append(@"<?xml version=""1.0"" encoding=""utf-8""?>");
            soapBuilder.Append(@"<soap:Envelope xmlns:xsi=""http://www.w3.org/2001/XMLSchema-instance"" xmlns:xsd=""http://www.w3.org/2001/XMLSchema"" xmlns:soap=""http://schemas.xmlsoap.org/soap/envelope/"">");
            soapBuilder.Append(@"  <soap:Body>");
            soapBuilder.Append(@"    <Web_GetTestResult_V2 xmlns=""http://tempuri.org/"">");
            soapBuilder.AppendFormat(@"      <LotSN>{0}</LotSN>", XmlEncode(mesModel.lotsn));
            soapBuilder.AppendFormat(@"      <DeviceNumber>{0}</DeviceNumber>", XmlEncode(mesModel.device_no));
            soapBuilder.AppendFormat(@"      <Mac>{0}</Mac>", XmlEncode(mesModel.mac));
            soapBuilder.AppendFormat(@"      <LotTestResult>{0}</LotTestResult>", XmlEncode(mesModel.testresult));
            soapBuilder.AppendFormat(@"      <StartTime>{0}</StartTime>", XmlEncode(mesModel.start_time));
            soapBuilder.AppendFormat(@"      <TestTime>{0}</TestTime>", XmlEncode(mesModel.test_time));
            soapBuilder.AppendFormat(@"      <TestItemXml>{0}</TestItemXml>", XmlEncode(mesModel.testitem));
            soapBuilder.AppendFormat(@"      <IsmatchingFail>{0}</IsmatchingFail>", XmlEncode(mesModel.ismatcingfail));
            soapBuilder.AppendFormat(@"      <IsItem>{0}</IsItem>", XmlEncode(mesModel.isitem));
            soapBuilder.Append(@"    </Web_GetTestResult_V2>");
            soapBuilder.Append(@"  </soap:Body>");
            soapBuilder.Append(@"</soap:Envelope>");
            return soapBuilder.ToString();
        }


        public int CheckProcess(String url, string soap, ref String errmse)
        {
            return CallSoapService(url, soap, MesConstant.SOAP_ACTION_CHECK, ref errmse);
        }

        public int ReportProcess(String url, string soap, ref String errmse)
        {
            return CallSoapService(url, soap, MesConstant.SOAP_ACTION_REPORT, ref errmse);
        }


 /// <summary>
    /// 调用SOAP服务
    /// </summary>
    /// <param name="url">接口地址</param>
    /// <param name="soapXml">SOAP请求报文</param>
    /// <param name="soapAction">SOAPAction头</param>
    /// <param name="errmse">输出错误信息</param>
    /// <returns>0=成功，1=失败</returns>
    private int CallSoapService(string url, string soapXml, string soapAction, ref string errmse)
    {
        int ret = 1;
        WebRequest req = null;
        WebResponse rsp = null;
        Stream requestStream = null;
        StreamReader responseReader = null;
        errmse = string.Empty;

        try
        {
            if (string.IsNullOrEmpty(url))
            {
                errmse = "MES interface URL is empty.";
                return ret;
            }

            req = WebRequest.Create(url);
            req.Timeout = MesConstant.WEB_REQUEST_TIMEOUT;
            req.Method = "POST";
            req.ContentType = "text/xml;charset=utf-8";
            req.Headers.Add("SOAPAction", soapAction);

            byte[] soapBytes = Encoding.UTF8.GetBytes(soapXml);
            req.ContentLength = soapBytes.Length;
            requestStream = req.GetRequestStream();
            requestStream.Write(soapBytes, 0, soapBytes.Length);

            rsp = req.GetResponse();
            responseReader = new StreamReader(rsp.GetResponseStream(), Encoding.UTF8);
            string responseXml = responseReader.ReadToEnd();
            LsResult mesResult = ParseMesResponse(responseXml);

            if (mesResult == null)
            {
                errmse = "Failed to parse MES response XML.";
                return ret;
            }

            if (mesResult.TestResult == MesConstant.RESULT_PASS)
            {
                ret = 0;
                errmse = string.IsNullOrEmpty(mesResult.I_ReturnMessage) ? "Success" : mesResult.I_ReturnMessage;
            }
            else
            {
                errmse = string.IsNullOrEmpty(mesResult.I_ReturnMessage)
                    ? "MES service returned failure without message."
                    : mesResult.I_ReturnMessage;
            }
        }
        catch (WebException ex)
        {
            errmse = string.Format("Web Request Error: {0}", ex.Message);
            // 若服务端返回错误响应，拼接响应内容
            if (ex.Response != null)
            {
                using (var exReader = new StreamReader(ex.Response.GetResponseStream(), Encoding.UTF8))
                {
                    errmse += string.Format(", Server Response: {0}", exReader.ReadToEnd());
                }
            }
        }
        catch (Exception ex)
        {
            errmse = string.Format("Service Call Error: {0}", ex.Message);
        }
        finally
        {
            //responseReader?.Close();
            if (responseReader != null) responseReader.Close();
            //requestStream?.Close();
            if (requestStream != null) requestStream.Close();
            //rsp?.Close();
            if (rsp != null) rsp.Close();
            //req?.Abort();
            if (req != null) req.Abort();
        }

        return ret;
    }

    private LsResult ParseMesResponse(string responseXml)
    {
        if (string.IsNullOrEmpty(responseXml)) return null;

        LsResult result = new LsResult();
        try
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.LoadXml(responseXml);
            XmlNamespaceManager nsMgr = new XmlNamespaceManager(xmlDoc.NameTable);
            nsMgr.AddNamespace("temp", "http://tempuri.org/");

            // 查找节点：兼容命名空间+无命名空间+本地名称，最大限度避免找不到
            XmlNode trNode = xmlDoc.SelectSingleNode("//temp:TestResult", nsMgr) 
                ?? xmlDoc.SelectSingleNode("//TestResult")
                ?? xmlDoc.SelectSingleNode("//*[local-name()='TestResult']");
            XmlNode msgNode = xmlDoc.SelectSingleNode("//temp:I_ReturnMessage", nsMgr)
                ?? xmlDoc.SelectSingleNode("//I_ReturnMessage")
                ?? xmlDoc.SelectSingleNode("//*[local-name()='I_ReturnMessage']");

            result.TestResult = trNode != null ? SafeTrim(trNode.InnerText) : SafeTrim(null);
            result.I_ReturnMessage = msgNode != null ? SafeTrim(msgNode.InnerText) : SafeTrim(null);
        }
        catch
        {
            result = ParseMesResponseByIndex(responseXml);
        }

        if (string.IsNullOrEmpty(result.TestResult))
        {
            result = ParseMesResponseByIndex(responseXml);
        }

        return result;
    }

        private LsResult ParseMesResponseByIndex(string responseXml)
        {
            LsResult result = new LsResult();
            // 查找TestResult（转义后）
            int trStart = responseXml.IndexOf("TestResult&gt;");
            int trEnd = responseXml.LastIndexOf("&lt;/TestResult");
            if (trStart > -1 && trEnd > trStart + MesConstant.INDEX_TESTRESULT)
            {
                result.TestResult = SafeTrim(responseXml.Substring(trStart + MesConstant.INDEX_TESTRESULT, trEnd - (trStart + MesConstant.INDEX_TESTRESULT)));
            }
            // 查找I_ReturnMessage（转义后）
            int msgStart = responseXml.IndexOf("I_ReturnMessage&gt;");
            int msgEnd = responseXml.LastIndexOf("&lt;/I_ReturnMessage");
            if (msgStart > -1 && msgEnd > msgStart + MesConstant.INDEX_RETURNMSG)
            {
                result.I_ReturnMessage = SafeTrim(responseXml.Substring(msgStart + MesConstant.INDEX_RETURNMSG, msgEnd - (msgStart + MesConstant.INDEX_RETURNMSG)));
            }
            return result;
        }


        public static string GetSimple12BitMac()
        {
            try
            {
                // 过滤：启用的、非环回、非虚拟、非蓝牙的物理网卡（优先以太网，标准6字节MAC）
                var physicalNic = NetworkInterface.GetAllNetworkInterfaces()
                    .FirstOrDefault(n => n.OperationalStatus == OperationalStatus.Up
                                        && n.NetworkInterfaceType != NetworkInterfaceType.Loopback
                                        && !n.Description.Contains("VMware")
                                        && !n.Description.Contains("Virtual")
                                        && !n.Description.Contains("蓝牙")
                                        && n.GetPhysicalAddress().GetAddressBytes().Length == 6);

                // 无有效网卡返回默认MAC
                if (physicalNic == null) return MesConstant.DEFAULT_MAC;

                // 6字节MAC转换后刚好12位，无需Substring，避免索引越界
                byte[] bytes = physicalNic.GetPhysicalAddress().GetAddressBytes();
                StringBuilder sb = new StringBuilder();
                foreach (byte b in bytes) sb.AppendFormat("{0:X2}", b);
                return sb.ToString();
            }
            catch
            {
                // 任何异常都返回默认MAC，不中断上报流程
                return MesConstant.DEFAULT_MAC;
            }
        }

        private string SafeTrim(string str)
        {
            return str == null ? string.Empty : str.Trim();
        }

        private string XmlEncode(string str)
        {
            if (string.IsNullOrEmpty(str)) return string.Empty;
            return str.Replace("&", "&amp;")
                      .Replace("<", "&lt;")
                      .Replace(">", "&gt;")
                      .Replace("\"", "&quot;")
                      .Replace("'", "&apos;");
        }
    }

}