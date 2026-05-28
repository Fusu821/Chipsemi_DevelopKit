// Algorithm.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Algorithm.h"


#include "Algs/dsp.h"

void do_fft(short* input, const int len)
{
	fft<double> clsfft;

	complex<double> cpx[256];
	for(int index = 0; index < len; index++)
		cpx[index].real = input[index];

	const complex<double>* result = clsfft.fft_translate(cpx, len);

	for(int index = 0; index < len; index++)
	{
		cpx[index] = result[index];
		if(index > max(4, (len >> 3)))
			cpx[index] = complex<double>(0, 0);
	}

	const complex<double>* ifft = clsfft.ifft_translate(cpx, len);

	for(int index = 0; index < len; index++)
	{
		input[index] = (short)ifft[index].modulus();
	}
}

void fft_test(float* input, const int len)
{
	static fft<double> clsfft;

	complex<double> cpx[128];
	for(int index = 0; index < len; index++)
		cpx[index].real = input[index];

	const complex<double>* result = clsfft.fft_translate(cpx, len);

	double fReal[128] = {0};
	double fImag[128] = {0};
	double fMode[128] = {0};

	for(int index = 0; index < 128; index++)
	{
		fReal[index] = result[index].real;
		fImag[index] = result[index].imag;
		fMode[index] = result[index].modulus();
	}

	for(int index = 0; index < len; index++)
	{
		cpx[index] = result[index];
	}

	const complex<double>* ifft = clsfft.ifft_translate(cpx, len);
	

	for(int index = 0; index < 128; index++)
	{
		fReal[index] = result[index].real;
		fImag[index] = result[index].imag;
		fMode[index] = result[index].modulus();
	}
}

// 这是导出变量的一个示例
//ALGORITHM_API int nAlgorithm=0;

// 这是导出函数的一个示例。
// ALGORITHM_API int fnAlgorithm(void)
// {
// 	return 42;
// }

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Algorithm.h
// CAlgorithm::CAlgorithm()
// {
// 	return;
// }
