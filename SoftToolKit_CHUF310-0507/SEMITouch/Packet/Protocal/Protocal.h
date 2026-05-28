#pragma once

//typedef struct __test_cmd_wr
//{
//	//offset 0;
//	unsigned char id; //cmd_id;
//	unsigned char idv; //inverse of cmd_id
//	unsigned short d0; //data 0
//	unsigned short d1; //data 1
//	unsigned short d2; //data 2
//	//offset 8;
//	unsigned char resv;  //offset 8
//	unsigned char tag;   //offset 9
//	unsigned short chk;  // 16 bit checksum
//
//	// section 2
//	unsigned short s2Pad0;  //
//	unsigned short s2Pad1;  //
//}ctp_cmd_std_t;
//
//typedef struct __test_cmd_rd
//{
//	//offset 0;
//	unsigned char id; //cmd_id;
//	unsigned char cc; //complete code
//	unsigned short d0; //data 0
//	unsigned short sn; //session number
//	unsigned short chk;  // 16 bit checksum
//}ctp_rsp_std_t;

typedef struct _s_ctp_cmd_std_t
{
	//offset 0;
	unsigned char  id; //cmd_id;
	unsigned char  idv; //inverse of cmd_id
	unsigned short d0; //data 0
	unsigned short d1; //data 1
	unsigned short d2; //data 2
	//offset 8;
	unsigned char  resv;  //offset 8
	unsigned char  tag;   //offset 9
	unsigned short chk;  // 16 bit checksum
	unsigned short s2Pad0;  //
	unsigned short s2Pad1;  //
}s_ctp_cmd_std_t;

//cammand struct for mcap
typedef struct _m_ctp_cmd_std_t
{
	unsigned short chk; // 16 bit checksum
	unsigned short d0;  //data 0
	unsigned short d1;  //data 1
	unsigned short d2;  //data 2
	unsigned short d3;  //data 3
	unsigned short d4;  //data 4
	unsigned short d5;  //data 5

	unsigned char  id;   //offset 15
	unsigned char  tag;  //offset 16 
}m_ctp_cmd_std_t;

typedef struct _ctp_cmd_cross_t
{
	unsigned short res1;   
	unsigned short d0;     //data 0
	unsigned short d1;     //data 1
	unsigned short d2;     //data 2
	unsigned short res2; 
	unsigned short res3; 
	unsigned short res4; 
	unsigned short res5; 
}ctp_cmd_cross_t;

typedef union _ctp_cmd_std_t
{
	ctp_cmd_cross_t cross;
	s_ctp_cmd_std_t scap;
	m_ctp_cmd_std_t mcap;
}ctp_cmd_std_t;

//response struct for scap
typedef struct _s_ctp_rsp_std_t
{
	//offset 0;
	unsigned char id; //cmd_id;
	unsigned char cc; //complete code
	unsigned short d0; //data 0
	unsigned short sn; //session number
	unsigned short chk;  // 16 bit checksum
}s_ctp_rsp_std_t;

//response struct for mcap
typedef struct _m_ctp_rsp_std_t{
	unsigned short chk; // 16 bit checksum
	unsigned short d0;  //data 0
	unsigned short d1;  //data 1
	unsigned short d2;  //data 2
	unsigned short d3;  //data 3
	unsigned short d4;  //data 4
	unsigned short d5;  //data 5

	unsigned char  cc;  //offset 15
	unsigned char  id;  //offset 16 
}m_ctp_rsp_std_t;

typedef union _ctp_rsp_std_t
{
	s_ctp_rsp_std_t scap;
	m_ctp_rsp_std_t mcap;
}ctp_rsp_std_t;


class ProtocalApi
{
public:
    ProtocalApi(){}
    virtual ~ProtocalApi(){}

public:
	virtual unsigned short KindOfProcal() = 0;
    virtual unsigned short ResponseLength() = 0;
	virtual bool CheckResponseOk( unsigned int& iReCode, unsigned short delay, unsigned char* pWrite, unsigned char* pRead ) = 0;
    virtual bool CheckCoreDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen ) = 0;
	virtual bool CheckOtpDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen ) = 0;
    virtual void PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned int d0 = 0, unsigned short d1 = 0, unsigned short d2 = 0, unsigned short ext1 = 0, unsigned short ext2 = 0, unsigned short ext3 = 0 ) = 0;
    //static void PrepareIoDataToSendEx( ctp_cmd_std_t& wr, unsigned char cmd, unsigned short d0 = 0, unsigned short d1 = 0, unsigned short d2 = 0 );
};

class ProtocalScapApi : public ProtocalApi
{
public:
    ProtocalScapApi(){}
    virtual ~ProtocalScapApi(){}

public:
	virtual unsigned short KindOfProcal();
    virtual unsigned short ResponseLength();
	virtual bool CheckResponseOk( unsigned int& iReCode, unsigned short delay, unsigned char* pWrite, unsigned char* pRead );
    virtual bool CheckCoreDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen );
	virtual bool CheckOtpDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen );
    virtual void PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned int d0 = 0, unsigned short d1 = 0, unsigned short d2 = 0, unsigned short ext1 = 0, unsigned short ext2 = 0, unsigned short ext3 = 0 );
};

class ProtocalMcapApi : public ProtocalApi
{
public:
    ProtocalMcapApi(){}
    virtual ~ProtocalMcapApi(){}

public:
	virtual unsigned short KindOfProcal();
    virtual unsigned short ResponseLength();
	virtual bool CheckResponseOk( unsigned int& iReCode, unsigned short delay, unsigned char* pWrite, unsigned char* pRead );
    virtual bool CheckCoreDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen );
	virtual bool CheckOtpDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen );
    virtual void PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned int d0 = 0, unsigned short d1 = 0, unsigned short d2 = 0, unsigned short ext1 = 0, unsigned short ext2 = 0, unsigned short ext3 = 0 );
};

typedef ProtocalScapApi ProtocalMTKApi;

// void PrepareIoDataToSendScap( ctp_cmd_std_t& wr, unsigned char cmd, unsigned short d0  = 0, unsigned short d1  = 0, unsigned short d2  = 0, unsigned char reserved = 0, unsigned short pad0 = 0, unsigned short pad1 = 0 );
// 
// void PrepareIoDataToSendMcap( ctp_cmd_std_t& wr, unsigned char cmd, unsigned short d0  = 0, unsigned short d1  = 0, unsigned short d2  = 0, unsigned short d3 = 0, unsigned short d4 = 0, unsigned short d5 = 0 );
// 
// #define PrepareIoDataToSendMtk   PrepareIoDataToSendScap

