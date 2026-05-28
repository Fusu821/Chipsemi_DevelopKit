#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
#include <Windows.h>
#include "../Include/SEMITouch.h"
#include "../Include/NativeTestInterface.h"

namespace SMInvokeBridge {

	public delegate void ProcessDelegate(unsigned char devNo, int iPos, int maxPos);

    #define DevNo (SMCommBase::GetDevice())
	public ref class SMCommBase
	{
	private:
		static unsigned int m_DeviceID = 0;
	public:
		static void UpdateDevice(unsigned int device)
		{
			m_DeviceID = device;	
		}
		inline static unsigned int GetDevice()
		{
             return m_DeviceID;
		}

		static BOOL Connected() 
		{
			return SM_CommBase(m_DeviceID)->Connected();
		}
		static unsigned int GetCommType() 
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;
			return SM_CommBase(m_DeviceID)->GetCommType();
		}
		static unsigned int SyncWorkcInit() 
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;
			return SM_CommBase(m_DeviceID)->SyncWorkcInit();
		}
		static unsigned int ReadFromUsbMemory( unsigned short addr, array<unsigned char>^ pRead, unsigned short len ) 
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;

			unsigned short tempVal = 0;

			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pRead, 0 );
				unsigned int iRet = SM_CommBase(m_DeviceID)->ReadFromUsbMemory( addr, (unsigned char*)buffPtr.ToPointer(), len );
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
		static unsigned int WriteToUsbMemory( unsigned short addr, array<unsigned char>^ pWrite, unsigned short len ) 
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;

			unsigned short tempVal = 0;

			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pWrite, 0 );
				unsigned int iRet = SM_CommBase(m_DeviceID)->WriteToUsbMemory( addr, (unsigned char*)buffPtr.ToPointer(), len );
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
		static unsigned int MtkBoardReBoot(unsigned int wantGo)
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;

			return SM_CommBase(m_DeviceID)->MtkBoardReBoot(wantGo);
		}
		static unsigned int PrepareMtkBoardUpgrade(  )
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;

			return SM_CommBase(m_DeviceID)->PrepareMtkBoardUpgrade();
		}
		static unsigned int UpgradeMtkBoard( array<unsigned char>^ pMtkBin, unsigned int len, ProcessDelegate^ delProcess )
		{
			if(NULL == SM_CommBase(m_DeviceID)) return ERROR_CODE_DEVICE_CLOSED;

			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pMtkBin, 0 );
				IntPtr pvFun = Marshal::GetFunctionPointerForDelegate(delProcess);
				return SM_CommBase(m_DeviceID)->UpgradeMtkBoard( m_DeviceID, (unsigned char*)buffPtr.ToPointer(), len, (LPUpdateProcessPosCallBack)pvFun.ToInt32() );
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int ReadMtkBoard( array<unsigned char>^ pMtkBin, unsigned int len, ProcessDelegate^ delProcess )
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pMtkBin, 0 );
				IntPtr pvFun = Marshal::GetFunctionPointerForDelegate(delProcess);
				return SM_CommBase(m_DeviceID)->ReadMtkBoard( m_DeviceID, (unsigned char*)buffPtr.ToPointer(), len, (LPUpdateProcessPosCallBack)pvFun.ToInt32() );
			}
			catch(...)
			{
			}
			finally
			{
			}

			return ERROR_CODE_OK;
		}
		static unsigned int SetIoVoltage( unsigned short vdd, unsigned short iovdd,unsigned short vih )
		{
			if(NULL == SM_CommBase(m_DeviceID)) return 0;
			return SM_CommBase(m_DeviceID)->SetIoVoltage(vdd, iovdd, vih);
		}
	};

}