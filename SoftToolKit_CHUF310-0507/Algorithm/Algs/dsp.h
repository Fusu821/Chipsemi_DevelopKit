#pragma once
#include "Algorithm.h"

#define SHIFT_BITS            8
#define SHIFT_VALS            256
#define PI                    3.14159

template<class T>
class fft
{
public:
	fft()
		:N(0)
	{
		
	}
	virtual ~fft()
	{
		delete[] w;
		delete[] fft_tranformed;
	}

public:
// 	complex<T>* fft_translate(T* data, int len)
// 	{
// 		if(N != len) return NULL;
// 
// 		for(int index = 0; index < len; index++)
// 		{
// 
// 		}
// 	}

	const complex<T>* fft_translate(complex<T>* data, int len)
	{
		N = len;

		w = new complex<T>[N];
		fft_tranformed = new complex<T>[N];
		for(int index = 0; index < (N >> 1); index++)
		{
			w[index].real = (T)(+cos(PI * 2 * index / N));
			w[index].imag = (T)(-sin(PI * 2 * index / N));
		}

		double dw = 2;
		unsigned char L = (unsigned char)(log((double)N)/log((double)dw));
		fft_sort(L, data);

		int cross_distance = 1;
		for(int istep = 0; istep < L; istep++)
		{
			int groups = N/(cross_distance << 1);
			for(int group = 0; group < groups; group++)
			{
				complex<T>* weight = w;
				complex<T>* ppt = &fft_tranformed[group * cross_distance << 1];
				for(int index = 0; index < cross_distance; index++)
				{
					complex<T> cross = complex<T>::dot(*weight, ppt[cross_distance]);
					ppt[cross_distance] = ppt[0] - cross;
					ppt[0] = ppt[0] + cross;
					weight += groups;
					ppt++;
				}
				
			}
			cross_distance <<= 1;
		}

		return fft_tranformed;
	}

	const complex<T>* ifft_translate(complex<T>* data, int len)
	{
		if(N != len) return NULL;

		for(int index = 0; index < len; index++)
			data[index].conjugate();

		fft_translate(data, len);

		for(int index = 0; index < len; index++)
		{
			fft_tranformed[index] = fft_tranformed[index].conjugate() / (T)(N);
		}

		return fft_tranformed;
	}

private:
	void fft_sort(char L, complex<T>* data)
	{
		for(int index = 0; index < N; index++)
		{
			int ptx = 0;
			for(int k = 0; k < L; k++)
			{
				ptx |= ((index >> k) & 0x01) << (L - k - 1);
			}
			fft_tranformed[index] = data[ptx];
		}
	}

private:
	complex<T>* w;
	complex<T>* fft_tranformed;
	int N;
};

