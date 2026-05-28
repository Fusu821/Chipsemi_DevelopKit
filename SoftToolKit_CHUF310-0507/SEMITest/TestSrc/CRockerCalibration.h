#pragma once

#include "NativeTestInterface.h"
#include <vector>

typedef struct _rockerData
{
	short cap_value[4];
	short x_centerValue;
	short y_centerValue;
	_rockerData()
	{
		x_centerValue = -20000;
		y_centerValue = 20000;
		cap_value[0] = 0;
		cap_value[1] = 0;
		cap_value[2] = 0;
		cap_value[3] = 0;
	}

}RockerData;

class CRockerCalibration
{
public:
	CRockerCalibration();
	~CRockerCalibration();
public:
	void SetCentreValue(RockerData pcentre);
    virtual	RockerData GetRockerData(short* data,unsigned short size);

	void Add_X_MinData(RockerData pcentre);
	void Add_X_MaxData(RockerData pcentre);

	void Add_Y_MinData(RockerData pcentre);
	void Add_Y_MaxData(RockerData pcentre);

	RockerData Get_X_MinData();
	RockerData Get_X_MaxData();
	RockerData Get_Y_MinData();
	RockerData Get_Y_MaxData();

	int Get_X_Count();
	int Get_Y_Count();

	vector<RockerData> Get_X_List();
	vector<RockerData> Get_Y_List();

	virtual void SetInit();

protected:
	unsigned int listsize;

	RockerData centerData;

	vector<RockerData> x_minlist;
	vector<RockerData> x_maxlist;
	vector<RockerData> y_minlist;
	vector<RockerData> y_maxlist;

};

class CRockerCalibration810 : public CRockerCalibration
{
public:
	CRockerCalibration810(){};
	~CRockerCalibration810(){};
public:
	virtual RockerData GetRockerData(short* data,unsigned short size) override ;
	vector<RockerData> GetRockerDataList(short* data,unsigned short size) ;
	
};