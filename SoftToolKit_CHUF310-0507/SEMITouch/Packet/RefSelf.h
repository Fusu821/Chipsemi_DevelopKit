#pragma once
#include "SEMITouch.h"

class RefSelf 
{
public:
	virtual void SetWrapperAddr( ISMChipWrapper* addr ){ m_ItemWrapperAddr = addr; }
	inline ISMChipWrapper* GetWrapperAddr(){ return m_ItemWrapperAddr; }
private:
	ISMChipWrapper* m_ItemWrapperAddr;
};

