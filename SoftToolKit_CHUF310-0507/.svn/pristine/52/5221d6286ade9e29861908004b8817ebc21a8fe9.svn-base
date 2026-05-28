#pragma once
#include <math.h>
#include "Macro.h"
/*******************************************************************************
***complex data definition
********************************************************************************/
template<class T>
class SM_ALGORITHM_API complex
{
public:
	T real;
	T imag;
	complex(T r_part, T i_part)
		:real(r_part)
		,imag(i_part)
	{

	}
	complex()
		:real(0)
		,imag(0)
	{

	}
	bool operator == (complex& rts)
	{
		return (this->real == rts.real) && (this->imag == rts.imag);
	}

	complex operator + (complex& rst)
	{
		return complex(this->real + rst.real, this->imag + rst.imag);
	}

	complex operator - (complex& rst)
	{
		return complex(this->real - rst.real, this->imag - rst.imag);
	}

	complex operator / (T div)
	{
		return complex(this->real/div, this->imag/div);
	}

	complex& conjugate()
	{
		this->imag = -this->imag;
		return *this;
	}

	T modulus() const
	{
		return sqrt(real * real + imag * imag);
	}

	static complex dot(complex& lft, complex& rst)
	{
		return complex(lft.real * rst.real - lft.imag * rst.imag, lft.real * rst.imag + lft.imag * rst.real);
	}
};

SM_ALGORITHM_CSTYLE_API void fft_test(float* input, int len);

SM_ALGORITHM_CSTYLE_API void do_fft(short* input, const int len);

