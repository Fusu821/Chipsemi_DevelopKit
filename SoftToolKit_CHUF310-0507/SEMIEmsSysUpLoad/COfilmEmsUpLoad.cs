using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MesOnlineNetDll;

namespace SEMIEmsSysUpLoad
{
    public class COfilmEmsUpLoad : CUpLoadBase
    {

        /*  infoarray[0]-url
         *  infoarray[1]-UserId
         *  infoarray[2]-EqpId
         *  infoarray[3]-StepId
         *  infoarray[4]-SerialNumber
         *  infoarray[5]-ChipId
         *  infoarray[6]-TestStepId
         *  infoarray[7]-IsPass
         *  infoarray[8]-MacAddress
         *  infoarray[9]-FixtureId
         */
        public override int SendEms(String info, ref String errmse)
        {
            int ret = 0;

            var infoarray = Analysis(info);
            if (infoarray.Length != 10)
            {
                ret = 1;
            }
            else
            {
                if (CheckSerialNumber(infoarray, ref errmse) == MesRespType.OK)
                {
                    if (UploadToMes(infoarray, ref errmse) != MesRespType.OK) ret = 1;
                
                }
                else
                {
                    ret = 1;
                }

            }
            return ret;
        }

        public MesRespType CheckSerialNumber(String[] infoarray, ref String errmse)
        {
            MesRespType ret = MesRespType.OK;
            string url = infoarray[0];
            var param = new CheckSnParam
            {
                UserId = infoarray[1],
                EqpId =  infoarray[2],
                StepId = infoarray[3],
                SerialNumber = infoarray[4],
            };

            var errorMessage = string.Empty;
            var mes = new MesHelper(url);
            ret = mes.CheckSerialNum(param, ref errorMessage);
            errmse = errorMessage;
            return ret;
        }

        /*  infoarray[0]-url
         *  infoarray[1]-UserId
         *  infoarray[2]-EqpId
         *  infoarray[3]-StepId
         *  infoarray[4]-SerialNumber
         *  infoarray[5]-ChipId
         *  infoarray[6]-TestStepId
         *  infoarray[7]-IsPass
         *  infoarray[8]-MacAddress
         *  infoarray[9]-FixtureId
         */
        public MesRespType UploadToMes(String[] infoarray, ref String errmse)
        {
            MesRespType ret = MesRespType.OK;

            string url = infoarray[0];

            var param = new UploadMesParam
            {
                UserId = infoarray[1],
                EqpId =  infoarray[2],
                StepId = infoarray[3],
                SerialNumber = infoarray[4],
                ChipId = infoarray[5],
                TestStepId = infoarray[6],
                IsPass = infoarray[7] == "G" ? true: false,
                MacAddress = infoarray[8],

                FailBin = "00",
                FixtureId = infoarray[9]
            };


            //添加数据回传项
            //param.AddCallbackItem("name","value");

            string errorMessage = string.Empty;
            var mes = new MesHelper(url);
            ret = mes.UploadToMes(param, ref errorMessage);
            errmse = errorMessage;
            return ret;
        }



    }
}
