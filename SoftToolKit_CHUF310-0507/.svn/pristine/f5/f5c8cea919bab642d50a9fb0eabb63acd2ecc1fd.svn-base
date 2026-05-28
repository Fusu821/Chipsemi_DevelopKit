#pragma once
#include "SEMITouch.h"
class CChipWrapper : public ISMChipWrapper
{
public:
	CChipWrapper(  );
	CChipWrapper( unsigned char id );
	virtual ~CChipWrapper();
	inline ISMChipBase*& GetChipBaseInterface()   { return m_pChipIntr; }
	inline ICommBase*& GetCommBaseInterface()   { return m_pCommIntr; }
	inline unsigned char GetIDMark() { return m_ucIDMark; }
	//inline IICProgram*& GetProgramInterface() { return m_pProgramIntr; }

	//virtual unsigned char HalLinkAndDoInit( int commType, Device hDevice );
	virtual unsigned int HalLinkAndDoInit( LinkParam& param, Device hDevice );
	virtual unsigned int SetICTypeAndCreateComponent( USHORT uIcType );

	void MakeClean();
private:
	CChipWrapper(const CChipWrapper&);
    ISMChipBase*    m_pChipIntr;
	//ISMProgram*  m_pProgramIntr;
	ICommBase*      m_pCommIntr;
	unsigned char   m_ucIDMark;
public:
#ifdef _1_MULTIPLE_N_
	static CChipWrapper* m_SeltContainer[MAX_DEVICE_NUM];
#else
	static CChipWrapper* m_SeltContainer;
#endif
};