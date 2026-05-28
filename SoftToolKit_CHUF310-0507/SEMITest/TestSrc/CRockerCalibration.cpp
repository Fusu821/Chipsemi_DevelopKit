#include "CRockerCalibration.h"


CRockerCalibration::CRockerCalibration()
{
	listsize = 1000;
}

CRockerCalibration::~CRockerCalibration()
{

}

void CRockerCalibration::SetCentreValue(RockerData pcentre)
{
	centerData = pcentre;
}

RockerData CRockerCalibration::GetRockerData(short* data,unsigned short size)
{
	RockerData rockerData;
	if(size < 32)
	{
		return rockerData;
	}
	else
	{
		rockerData.cap_value[0] = data[0];
		rockerData.cap_value[1] = data[1];
		rockerData.cap_value[2] = data[2];
		rockerData.cap_value[3] = data[3];

		rockerData.x_centerValue = data[16];
		rockerData.y_centerValue = data[17];

		return rockerData;

	}
}

void CRockerCalibration::Add_X_MinData(RockerData pcentre)
{
	if(x_minlist.size()<100)
	{
		x_minlist.push_back(pcentre);
	}
}
void CRockerCalibration::Add_X_MaxData(RockerData pcentre)
{
	if(x_maxlist.size()<listsize)
	{
		x_maxlist.push_back(pcentre);
	}
}
void CRockerCalibration::Add_Y_MinData(RockerData pcentre)
{
	if(y_minlist.size()<listsize)
	{
		y_minlist.push_back(pcentre);
	}

}
void CRockerCalibration::Add_Y_MaxData(RockerData pcentre)
{
	if(y_maxlist.size()<listsize)
	{
		y_maxlist.push_back(pcentre);
	}
}

RockerData CRockerCalibration::Get_X_MinData()
{
	RockerData pRockerData;
	if (x_maxlist.size()==0)
	{
		return centerData;
	}
	pRockerData = x_maxlist[0];

	for (unsigned int i=0; i < x_maxlist.size();i++)
	{
		if(pRockerData.x_centerValue>x_maxlist[i].x_centerValue)
		{
			pRockerData.x_centerValue = x_maxlist[i].x_centerValue;
			pRockerData.y_centerValue = x_maxlist[i].y_centerValue;
			pRockerData.cap_value[0] = x_maxlist[i].cap_value[0];
			pRockerData.cap_value[1] = x_maxlist[i].cap_value[1];
			pRockerData.cap_value[2] = x_maxlist[i].cap_value[2];
			pRockerData.cap_value[3] = x_maxlist[i].cap_value[3];
		}
	}
	return pRockerData;
}
RockerData CRockerCalibration::Get_X_MaxData()
{
	RockerData pRockerData;
	if (x_maxlist.size()==0)
	{
		return centerData;
	}
	pRockerData = x_maxlist[0];

	for (unsigned int i=0; i < x_maxlist.size();i++)
	{
		if(pRockerData.x_centerValue<x_maxlist[i].x_centerValue)
		{
			pRockerData.x_centerValue = x_maxlist[i].x_centerValue;
			pRockerData.y_centerValue = x_maxlist[i].y_centerValue;
			pRockerData.cap_value[0] = x_maxlist[i].cap_value[0];
			pRockerData.cap_value[1] = x_maxlist[i].cap_value[1];
			pRockerData.cap_value[2] = x_maxlist[i].cap_value[2];
			pRockerData.cap_value[3] = x_maxlist[i].cap_value[3];
		}
	}
	return pRockerData;

}
RockerData CRockerCalibration::Get_Y_MinData()
{
	RockerData pRockerData;
	if (y_maxlist.size()==0)
	{
		return centerData;
	}
	pRockerData = y_maxlist[0];

	for (unsigned int i=0; i < y_maxlist.size();i++)
	{
		if(pRockerData.y_centerValue>y_maxlist[i].y_centerValue)
		{
			pRockerData.x_centerValue = y_maxlist[i].x_centerValue;
			pRockerData.y_centerValue = y_maxlist[i].y_centerValue;
			pRockerData.cap_value[0] = y_maxlist[i].cap_value[0];
			pRockerData.cap_value[1] = y_maxlist[i].cap_value[1];
			pRockerData.cap_value[2] = y_maxlist[i].cap_value[2];
			pRockerData.cap_value[3] = y_maxlist[i].cap_value[3];
		}
	}
	return pRockerData;

}
RockerData CRockerCalibration::Get_Y_MaxData()
{
	RockerData pRockerData;
	if (y_maxlist.size()==0)
	{
		return centerData;
	}
	pRockerData = y_maxlist[0];

	for (unsigned int i=0; i < y_maxlist.size();i++)
	{
		if(pRockerData.y_centerValue<y_maxlist[i].y_centerValue)
		{
			pRockerData.x_centerValue = y_maxlist[i].x_centerValue;
			pRockerData.y_centerValue = y_maxlist[i].y_centerValue;
			pRockerData.cap_value[0] = y_maxlist[i].cap_value[0];
			pRockerData.cap_value[1] = y_maxlist[i].cap_value[1];
			pRockerData.cap_value[2] = y_maxlist[i].cap_value[2];
			pRockerData.cap_value[3] = y_maxlist[i].cap_value[3];
		}
	}
	return pRockerData;

}

std::vector<RockerData> CRockerCalibration::Get_X_List()
{
	return x_maxlist;
}

std::vector<RockerData> CRockerCalibration::Get_Y_List()
{
	return y_maxlist;
}

int CRockerCalibration::Get_X_Count()
{
	return x_maxlist.size();
}

int CRockerCalibration::Get_Y_Count()
{
	return y_maxlist.size();
}

void CRockerCalibration::SetInit()
{
	x_minlist.clear();
	x_maxlist.clear();
	y_minlist.clear();
	y_maxlist.clear();

	centerData.x_centerValue = -20000;
	centerData.y_centerValue = 20000;
	centerData.cap_value[0] = 0;
	centerData.cap_value[1] = 0;
	centerData.cap_value[2] = 0;
	centerData.cap_value[3] = 0;

}


RockerData CRockerCalibration810::GetRockerData(short* data,unsigned short size)
{
	RockerData rockerData;
	if(size < 32)
	{
		return rockerData;
	}
	else
	{
		rockerData.cap_value[0] = data[0];
		rockerData.cap_value[1] = data[1];
		rockerData.cap_value[2] = data[2];
		rockerData.cap_value[3] = data[3];

		rockerData.x_centerValue = data[8];
		rockerData.y_centerValue = data[9];

		return rockerData;

	}
}

vector<RockerData> CRockerCalibration810::GetRockerDataList(short* data,unsigned short size)
{
 	vector<RockerData> ret;

	for(int i = 0; i < 5; i++)
	{
		RockerData rockerData;
		rockerData.cap_value[0] = data[0 + i * 16];
		rockerData.cap_value[1] = data[1 + i * 16];
		rockerData.cap_value[2] = data[2 + i * 16];
		rockerData.cap_value[3] = data[3 + i * 16];

		rockerData.x_centerValue = data[8 + i * 16];
		rockerData.y_centerValue = data[9 + i * 16];
		ret.push_back(rockerData);
	}

	return ret;

}
