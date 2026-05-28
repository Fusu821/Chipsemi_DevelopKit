#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
#include <Windows.h>
#include "../Include/SEMITouch.h"
#include "../Include/NativeTestInterface.h"
#include "../Util/Header/checksum.h"

#include "SMComm.h"

namespace SMInvokeBridge {

    public enum class EnIoComplex
	{
		SM_OTP_R = OTP_R,
		SM_CORE_R = CORE_R,
		SM_CORE_W = CORE_W,
		SM_OTP_W_NOCHK = OTP_W_NOCHK,
		SM_OTP_W_CHK = OTP_W_CHK,
		SM_OTP_W_TAIL = OTP_W_TAIL,
		SM_OTP_W_CHKEX = OTP_W_CHKEX,
		SM_TLK_B4WRCHK_EX = TLK_B4WRCHK_EX,
		SM_TLK_DUT_FLASH = TLK_DUT_FLASH,
		SM_TLK_DATACHK_MSK = TLK_DATACHK_MSK,
		SM_TLK_DATACHK_EX1 = TLK_DATACHK_EX1,
		SM_TLK_DATA_ENCRY = TLK_DATA_ENCRY,
	};

    public ref class SMCheckTools
	{
	public:
		static unsigned int CaculateCheckSumEx( array<unsigned char>^ buffer, unsigned int len )
		{
			IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
			return caculate_check_sum_ex( (unsigned char*)buffPtr.ToPointer(), len );
		}

		static unsigned short CaculateCheckSumU816(array<unsigned char>^ buffer, unsigned int len)
		{
			IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
			return caculate_check_sum_u816( (unsigned char*)buffPtr.ToPointer(), len );
		}

		static unsigned short CaculateCheckSumU16(array<unsigned char>^ buffer, unsigned int len)
		{
			IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
			return caculate_check_sum_u16( (unsigned short*)buffPtr.ToPointer(), len );
		}

		static unsigned int CaculateCheckSumU32(array<unsigned char>^ buffer, unsigned int len)
		{
			IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
			return caculate_check_sum_u32( (unsigned int*)buffPtr.ToPointer(), len );
		}

		static unsigned char CaculateCheckSumU8(array<unsigned char>^ buffer, unsigned int len)
		{
			IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
			return caculate_check_sum_u8( (unsigned char*)buffPtr.ToPointer(), len );
		}

		static void StructToBytes(System::Object^ obj, array<unsigned char>^ buffer)
		{
			UINT32 size = Marshal::SizeOf(obj);
			if(buffer->Length >= (int)size)
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				Marshal::StructureToPtr(obj, buffPtr, false);
			}
		}

		static void BytesToStruct(System::Object^ obj, array<unsigned char>^ buffer)
		{
			UINT32 size = Marshal::SizeOf(obj);
			if(buffer->Length >= (int)size)
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				Marshal::PtrToStructure(buffPtr, obj);
			}
		}

		static void ShortArrayToByteArray(array<short>^ source, unsigned short slen, array<unsigned char>^ target, unsigned short tlen)
		{
			IntPtr sbuff = Marshal::UnsafeAddrOfPinnedArrayElement( source, 0 );
			IntPtr tbuff = Marshal::UnsafeAddrOfPinnedArrayElement( target, 0 );

			memcpy_s( (unsigned char*)tbuff.ToPointer(), tlen, (unsigned char*)sbuff.ToPointer(), slen << 1 );
		}
	};

	public ref class CommContext
	{
	public:
		unsigned short icType;
		unsigned char protocalType;
		unsigned char slaveAddr;
		unsigned short i2cSpeed;
		unsigned char spiMode;
		unsigned short spiSpeed;
		unsigned short vdd;
		unsigned short iovdd;
		unsigned short vih;
	};

    public ref class FirmwareSimulate
	{
	public: 
		typedef void (*simulate_function_point)( int simulationIndex, unsigned char txNum, unsigned char rxNum, unsigned char* rawDataBuffer, unsigned char* differBuffer, unsigned char* touchBuffer );
		static void FirmwareSimulation( int simulationIndex, int tx, int rx, array<short>^ raw, array<short>^ differ, array<unsigned char>^ touch )
		{
			static HMODULE module = ::LoadLibrary("ChipSimulation.dll");
			if( NULL != module )
			{
				simulate_function_point fp = (simulate_function_point)::GetProcAddress( module, "FirmwareSimulation" );
				if( fp ) 
				{
					IntPtr rawPtr = Marshal::UnsafeAddrOfPinnedArrayElement( raw, 0 );
					IntPtr diffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( differ, 0 );
					IntPtr touchPtr = Marshal::UnsafeAddrOfPinnedArrayElement( touch, 0 );
					(*fp)( simulationIndex, tx, rx, (unsigned char*)rawPtr.ToPointer(), (unsigned char*)diffPtr.ToPointer(), (unsigned char*)touchPtr.ToPointer() );
				}
			}
		}
	};

    public ref class SMChipBase
	{
	public:
		static void SMScreenXYChange( USHORT InX, USHORT InY, System::Drawing::Point %Out, System::Drawing::Rectangle^ tp, System::Drawing::Rectangle^ pc )
		{
			long out_x = 0, out_y = 0;
			RECT rcTp, rcPc;
			rcTp.left = tp->Left;
			rcTp.top = tp->Top;
			rcTp.right = tp->Right;
			rcTp.bottom = tp->Bottom;

			rcPc.left = pc->Left;
			rcPc.top = pc->Top;
			rcPc.right = pc->Right;
			rcPc.bottom = pc->Bottom;
			ScreenXYChange( InX, InY, out_x, out_y, rcTp, rcPc );
			Out.X = out_x;
			Out.Y = out_y;
		}
		static unsigned int SetICTypeAndCreateComponent( unsigned short icType )
		{
			return GetChipWrapperAddr(DevNo)->SetICTypeAndCreateComponent( icType );
		}
		static bool HaveTpLinked(  )
		{
			return SM_ChipBase(DevNo)->HaveTpLinked( 1 ) == TRUE;
		}
		static unsigned int SwitchMode( unsigned short modeType, unsigned short len )
		{
			return SM_ChipBase(DevNo)->SwitchMode( (unsigned char)modeType, len );
		}
		static unsigned int SetCommContext( CommContext^ ctx )
		{
			CtpHalCfg halCfg;
			halCfg.protocalType = ctx->protocalType;
			halCfg.IIC.slaveAddr = ctx->slaveAddr;
			halCfg.SPI.mode = ctx->spiMode;
			halCfg.vddVoltage = (unsigned char)ctx->vdd;
			halCfg.iovddVotage = (unsigned char)ctx->iovdd;
			halCfg.icType = ctx->icType;
			halCfg.vihVotage = ctx->vih;

			if(PROTOCAL_IIC == halCfg.protocalType)
				halCfg.speed = ctx->i2cSpeed;
			else if(PROTOCAL_SPI == halCfg.protocalType)
				halCfg.speed = ctx->spiSpeed;

			return SM_ChipBase(DevNo)->SetCommContext( halCfg );
		}
		static unsigned int IncokeCommand( cmdTypeID command )
		{
			return SM_ChipBase(DevNo)->IncokeCommand( (unsigned char)command );
		}
		static unsigned int IncokeCommand( byte command, unsigned int d0, unsigned short d1, unsigned short d2, array<unsigned char>^ readedBytes )
		{
			unsigned char tempByte[16] = {0};
			unsigned int ret = SM_ChipBase(DevNo)->IncokeCommand( (unsigned char)command, d0, d1, d2, tempByte );
 			for(int index = 0; index < readedBytes->Length, index < 16; index++ )
 			{
				readedBytes[index] = tempByte[index];
 			}
			
			return ret;
		}
		static unsigned int HalAccessMode( unsigned char accType )
		{
			return SM_ChipBase(DevNo)->HalAccessMode( accType );
		}
		static unsigned int WriteRegister( unsigned int address, unsigned int ucData )
		{
			return SM_ChipBase(DevNo)->WriteRegister( address, ucData );
		}
		static unsigned int ReadRegister( unsigned int address, unsigned int% pUcData )
		{
			unsigned int regData = 0;
			unsigned int iRet = SM_ChipBase(DevNo)->ReadRegister( address, &regData );
			pUcData = regData;

			return iRet;
		}
		static unsigned int GetTouchPoint( array<unsigned char>^ pointBuffer, unsigned short %len )
		{
			unsigned short tempVal = 0;

			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pointBuffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->GetTouchPoint( (unsigned char*)buffPtr.ToPointer(), &tempVal );
				len = tempVal;
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}

		

		static unsigned int GetRawDataPoint( array<short>^ pointBuffer, unsigned short len )
		{
			try
			{
				
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pointBuffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->GetRawData( (short*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int ReadCoreSpace( unsigned int addr, array<unsigned char>^ buffer, unsigned int len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->ReadCoreSpace( addr, (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int WriteCoreSpace( unsigned int addr, array<unsigned char>^ buffer, unsigned int len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->WriteCoreSpace( addr, (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int ReadBurnSpace( unsigned int addr, array<unsigned char>^ buffer, unsigned int len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->ReadBurnSpace( addr, (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int WriteBurnSpace( unsigned int addr, array<unsigned char>^ buffer, unsigned int len, EnIoComplex type )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->WriteBurnSpace( addr, (unsigned char*)buffPtr.ToPointer(), len, (byte)type );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int ReadMtkFlash( unsigned int addr, array<unsigned char>^ buffer, unsigned int len)
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( buffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->ReadMtkFlash( addr, (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
// 		static unsigned int CheckCatchBootToMtk( unsigned int addr, array<unsigned char>^ bootBuffer, unsigned int bootLen)
// 		{
// 			try
// 			{
// 				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( bootBuffer, 0 );
// 				unsigned int iRet = SM_ChipBase(DevNo)->CheckCatchBootToMtk( addr, (unsigned char*)buffPtr.ToPointer(), bootLen );
// 				return iRet;
// 			}
// 			catch(...)
// 			{
// 			}
// 			finally
// 			{
// 			}
// 
// 			return ERROR_CODE_OK;
// 		}
		static unsigned int EraseBurnSpace( unsigned int addr, unsigned int len )
		{
			return SM_ChipBase(DevNo)->EraseBurnSpace( addr, len );
		}

		static unsigned int SetClkInFctMode( unsigned short clkDiv, bool filterOff )
		{
			return SM_ChipBase(DevNo)->SetClkInFctMode( clkDiv, filterOff ? 1 : 0 );
		}

// 		static unsigned int BSPRWrite( array<unsigned char>^ writeBuffer, unsigned int iWrite )
// 		{
// 			try
// 			{
// 				IntPtr writePtr = Marshal::UnsafeAddrOfPinnedArrayElement( writeBuffer, 0 );
// 				unsigned int iRet = SM_ChipBase(DevNo)->BSPRWrite( (unsigned char*)writePtr.ToPointer(), iWrite );
// 
// 				return iRet;
// 			}
// 			catch (...)
// 			{
// 
// 			}
// 
// 			return ERROR_CODE_OK;
// 		}
// 
// 		static unsigned int BSPRRead( array<unsigned char>^ readBuffer, unsigned int iRead )
// 		{
// 			try
// 			{
// 				IntPtr readPtr = Marshal::UnsafeAddrOfPinnedArrayElement( readBuffer, 0 );
// 				unsigned int iRet = SM_ChipBase(DevNo)->BSPRRead( (unsigned char*)readPtr.ToPointer(), iRead );
// 
// 				return iRet;
// 			}
// 			catch (...)
// 			{
// 
// 			}
// 
// 			return ERROR_CODE_OK;
// 		}

		static unsigned int BSPRWriteAndRead( array<unsigned char>^ writeBuffer, unsigned int iWrite, array<unsigned char>^ readBuffer, unsigned int iRead )
		{
			try
			{
				IntPtr writePtr = Marshal::UnsafeAddrOfPinnedArrayElement( writeBuffer, 0 );
				IntPtr readPtr = Marshal::UnsafeAddrOfPinnedArrayElement( readBuffer, 0 );
				unsigned int iRet = SM_ChipBase(DevNo)->BSPRWriteAndRead( (unsigned char*)writePtr.ToPointer(), iWrite, (unsigned char*)readPtr.ToPointer(), iRead );

				return iRet;
			}
			catch (...)
			{

			}

			return ERROR_CODE_OK;
		}
	};

	public ref class SMChip3535 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned short %trim, unsigned int osStd )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->GetOSCTrim( &tempVal, osStd );
			trim = tempVal;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime, unsigned int %marginCheck, unsigned int %normalCheck )
		{
			unsigned int tempVal1 = 0, tempVal2 = 0, margin = 0, normal = 0;
			unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2, &margin, &normal );
			checkSum = tempVal1;
			omTime = tempVal2;
			marginCheck = margin;
			normalCheck = normal;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( unsigned int addr, array<unsigned char>^ configBuffer, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->GetFirmWareConfig( addr, (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		//static unsigned int GetOSData( unsigned char integral, unsigned char scale_a, unsigned char scale_b, unsigned short* osData, unsigned short len )
		static unsigned int GetFSDFastData( unsigned short fclkDiv, unsigned short integral, array<short>^ clkData, unsigned short buffersize, unsigned char fclkCnt )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( clkData, 0 );
				unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->GetFSDFastData( fclkDiv, integral, (unsigned short*)buffPtr.ToPointer(), buffersize, fclkCnt );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		//static unsigned int GetFSDSlowData( unsigned short fclkDiv, unsigned short* clkData, unsigned short buffersize, unsigned char fclkCnt = 4 )
		//static unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0 )
		static unsigned int BurnConfigBin( unsigned int addr, array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->BurnConfigBin( addr, (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int FindLastCfgAddress()
		{
			return ((ISMChip3535*)SM_ChipBase(DevNo))->FindLastCfgAddress();
		}
	};

	public ref class SMChip3536 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned short %trim, unsigned int osStd )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip3536*)SM_ChipBase(DevNo))->GetOSCTrim( &tempVal, osStd );
			trim = tempVal;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip3536*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip3536*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip3536*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
// 		static unsigned int GetOSData( unsigned char integral, unsigned char scale_a, unsigned char scale_b, unsigned short* osData, unsigned short len ) 
// 		static unsigned int GetFSDFastData( unsigned short fclkDiv, unsigned short* clkData, unsigned short buffersize, unsigned char fclkCnt ) 
		static unsigned int GetFSDFastData( unsigned short fclkDiv, unsigned short integral, array<short>^ clkData, unsigned short buffersize, unsigned char fclkCnt )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( clkData, 0 );
				unsigned int iRet = ((ISMChip3535*)SM_ChipBase(DevNo))->GetFSDFastData( fclkDiv, integral, (unsigned short*)buffPtr.ToPointer(), buffersize, fclkCnt );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
// 		static unsigned int GetFSDSlowData( unsigned short fclkDiv, unsigned short* clkData, unsigned short buffersize, unsigned char fclkCnt ) 
		//unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0 ) 
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip3536*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};


	public ref class SMChip5472 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim48m, unsigned char %trim150m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd150m )
		{
			unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
			unsigned int iRet = ((ISMChip5472*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &temp48m, &temp150m, trim_mode, osStd32k, osStd48m, osStd150m );
			trim32k = temp32k;
			trim48m = temp48m;
			trim150m = temp150m;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip5472*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip5472*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip5472*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip5472*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip5472*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};
	public ref class SMChip5562 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim48m, unsigned char %trim150m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd150m )
		{
			unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
			unsigned int iRet = ((ISMChip5562*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &temp48m, &temp150m, trim_mode, osStd32k, osStd48m, osStd150m );
			trim32k = temp32k;
			trim48m = temp48m;
			trim150m = temp150m;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip5562*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip5562*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip5562*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip5562*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip5562*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};

	public ref class SMChip570 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim48m, unsigned char %trim150m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd150m )
		{
			unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
			unsigned int oscTrimArray[8];

			unsigned int iRet = ((ISMChip570*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &temp48m, &temp150m, trim_mode, osStd32k, osStd48m, osStd150m, oscTrimArray );
			trim32k = temp32k;
			trim48m = temp48m;
			trim150m = temp150m;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip570*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip570*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip570*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip570*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip570*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};


	public ref class SMChip7126 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim48m, unsigned char %trim150m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd150m )
		{
			unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
			unsigned int iRet = ((ISMChip7126*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &temp48m, &temp150m, trim_mode, osStd32k, osStd48m, osStd150m );
			trim32k = temp32k;
			trim48m = temp48m;
			trim150m = temp150m;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip7126*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip7126*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip7126*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip7126*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip7126*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};

	public ref class SMChip8006 : public SMChipBase
	{
	public:
		//static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim64m, unsigned int osStd32k, unsigned int osStd64m)
		//{
		//	unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
		//	unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &trim64m, osStd32k, osStd64m);
		//	trim32k = temp32k;
		//	trim48m = temp48m;
		//	return iRet;
		//}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};
	public ref class SMChip810 : public SMChipBase
	{
	public:
		//static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim64m, unsigned int osStd32k, unsigned int osStd64m)
		//{
		//	unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
		//	unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &trim64m, osStd32k, osStd64m);
		//	trim32k = temp32k;
		//	trim48m = temp48m;
		//	return iRet;
		//}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip8006*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};

	public ref class SMChip7449 : public SMChipBase
	{
	public:
		static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim48m, unsigned char %trim150m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd150m )
		{
			unsigned char temp32k = 0, temp48m = 0, temp150m = 0;
			unsigned int iRet = ((ISMChip7449*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &temp48m, &temp150m, trim_mode, osStd32k, osStd48m, osStd150m );
			trim32k = temp32k;
			trim48m = temp48m;
			trim150m = temp150m;
			return iRet;
		}
		static unsigned int GetBootVersion( unsigned short %bootVer )
		{
			unsigned short tempVal = 0;
			unsigned int iRet = ((ISMChip7449*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
			bootVer = tempVal;
			return iRet;
		}
		static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
		{
			unsigned int tempVal1 = 0, tempVal2 = 0;
			unsigned int iRet = ((ISMChip7449*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
			checkSum = tempVal1;
			omTime = tempVal2;
			return iRet;
		}
		static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
				unsigned int iRet = ((ISMChip7449*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip7449*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
				unsigned int iRet = ((ISMChip7449*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
				return iRet;
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
	};

	public ref class SMChip5816 : public SMChip5472
	{

	};

    public ref class SMChip310 : public SMChipBase
    {
    public:
        //static unsigned int GetOSCTrim( unsigned char %trim32k, unsigned char %trim52m, unsigned char %trim250m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd250m )
        //{
        //    unsigned char temp32k = 0, temp52m = 0, temp250m = 0;
        //    unsigned int iRet = ((ISMChip310*)SM_ChipBase(DevNo))->GetOSCTrim( &temp32k, &temp52m, &temp250m, trim_mode, osStd32k, osStd48m, osStd250m );
        //    trim32k = temp32k;
        //    trim52m = temp52m;
        //    trim250m = temp250m;
        //    return iRet;
        //}
        static unsigned int GetBootVersion( unsigned short %bootVer )
        {
            unsigned short tempVal = 0;
            unsigned int iRet = ((ISMChip310*)SM_ChipBase(DevNo))->GetBootVersion( &tempVal );
            bootVer = tempVal;
            return iRet;
        }
        static unsigned int GetBootCheckSum( unsigned int %checkSum, unsigned int %omTime ) 
        {
            unsigned int tempVal1 = 0, tempVal2 = 0;
            unsigned int iRet = ((ISMChip310*)SM_ChipBase(DevNo))->GetBootCheckSum( &tempVal1, &tempVal2 );
            checkSum = tempVal1;
            omTime = tempVal2;
            return iRet;
        }
        static unsigned int GetFirmWareConfig( array<unsigned char>^ configBuffer, unsigned short len ) 
        {
            try
            {
                IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( configBuffer, 0 );
                unsigned int iRet = ((ISMChip310*)SM_ChipBase(DevNo))->GetFirmWareConfig( (unsigned char*)buffPtr.ToPointer(), len );
                return iRet;
            }
            catch(...)
            {
            }
            finally
            {
            }

            return ERROR_CODE_OK;
        }
        static unsigned int BurnConfigBin( array<unsigned char>^ config, unsigned short len )
        {
            try
            {
                IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
                unsigned int iRet = ((ISMChip310*)SM_ChipBase(DevNo))->BurnConfigBin( (unsigned char*)buffPtr.ToPointer(), len );
                return iRet;
            }
            catch(...)
            {
            }
            finally
            {
            }

            return ERROR_CODE_OK;
        }
        static unsigned int SetConfigInFctMode( array<unsigned char>^ config, unsigned short len )
        {
            try
            {
                IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( config, 0 );
                unsigned int iRet = ((ISMChip310*)SM_ChipBase(DevNo))->SetConfigInFctMode( (unsigned char*)buffPtr.ToPointer(), len );
                return iRet;
            }
            catch(...)
            {
            }
            finally
            {
            }

            return ERROR_CODE_OK;
        }
    };


}	