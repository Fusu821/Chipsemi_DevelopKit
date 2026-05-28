#pragma once

#include <tchar.h>
#include <windows.h>
#include "../Include/Algorithm.h"
using namespace System;
using namespace System::Runtime::InteropServices;

namespace SMInvokeBridge{
	public ref class SMAlgorithm{
	public:
		static void SingalFilter(array<short>^ pSingnal, int len)
		{
			try
			{
				IntPtr buffPtr = Marshal::UnsafeAddrOfPinnedArrayElement( pSingnal, 0 );
				do_fft( (short*)buffPtr.ToPointer(), len );
			}
			catch(...)
			{
			}
			finally
			{
			}
		}
	};
};