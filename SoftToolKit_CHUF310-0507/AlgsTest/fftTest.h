#pragma once
#include <math.h>

#define N           128 
#define POWER       0//该值代表了输入数据首先被放大的倍数，放大倍数为2^POWER 
#define P_COEF      8//该值代表了旋转因子被放大的倍数，放大倍数为2^POWER #if (N == 4) 
//#define L           2//L的定义满足L = log2(N) 

typedef short s16;
typedef char  s8;
typedef unsigned char u8;

#if (N == 4)
#define L           2  //L的定义满足L = log2(N)  
#elif (N == 8) 
#define L           3//L的定义满足L = log2(N) 
#elif (N == 16) 
#define L           4//L的定义满足L = log2(N) 
#elif (N == 32) 
#define L           5//L的定义满足L = log2(N) 
#elif (N == 64) 
#define L           6//L的定义满足L = log2(N) 
#elif (N == 128) 
#define L           7//L的定义满足L = log2(N) 
#endif   //AD采样位数为12位，本可以采用s16 x[N]定义数据空间，但是为了节省存储空间，fft结果也将存储在该变量空间。由于受 
//fft影响变量需要重新定义，定义的方式及具体原因如下： 
//fft过程会乘以较大旋转因子，因此需要32位定义 
//fft过程会产生负数，因此需要有符号定义 
//fft过程会出现复数，因此需要定义二维数组，[][0]存放实部，[][1]存放虚部 s32 x[N][2] = {};  
//定义*p[N]是为了在第一次指针初始化以后，该数组指针按照位倒序指向数据变量x 
//p[i][0]代表了指向数据的实部，p[i][1]代表了指向数据的虚部 s32 *p[N];  
//定义旋转因子矩阵 
//旋转因子矩阵存储了wn^0,wn^1,wn^2...wn^(N/2-1)这N/2个复数旋转因子  
s16 w[128>>1][2] = {256,0,256,-13,255,-25,253,-38,251,-50,248,-62,245,-74,241,-86,237,-98,231,-109,226,
	-121,220,-132,213,-142,206,-152,198,-162,190,-172,181,-181,172,-190,162,-198,152,
	-206,142,-213,132,-220,121,-226,109,-231,98,-237,86,-241,74,-245,62,-248,50,-251,38,
	-253,25,-255,13,-256,0,-256,-13,-256,-25,-255,-38,-253,-50,-251,-62,-248,-74,-245,-86,
	-241,-98,-237,-109,-231,-121,-226,-132,-220,-142,-213,-152,-206,-162,-198,-172,-190,-181,
	-181,-190,-172,-198,-162,-206,-152,-213,-142,-220,-132,-226,-121,-231,-109,-237,-98,-241,
	-86,-245,-74,-248,-62,-251,-50,-253,-38,-255,-25,-256,-13};  

int x[256][2] = {0};
int* p[256] = {0};

void init_pointer(void) 
{      
	unsigned char i = 0;    
	unsigned char j = 0;    
	unsigned char k = 0;       
	for(i = 0; i < N; i++)    
	{  
		j = 0;       
		for(k = 0; k < L; k++)       
		{  
			j |= (((i >> k)&0x01)<<(L-k-1));       
		}       
		p[i] = &x[j][0];    
	} 
}    
/* *description:基2fft主函数,该函数将借助指针数组p对全局变量数组x进行fft计算 *            
并将结果存储在数组x中 *global var:rw->x; r->p,w。(r表示读，w表示写，rw表示读写) */ 
void fft2(void) 
{   
	u8 i;//i用于表示蝶形图级联的阶数   
	u8 j;//表示蝶形分组起始点序列，蝶形分组跨度为2^i   
	u8 k;//k表示蝶形组内偶数分支序列点号   
	u8 gp_distance = 1;//蝶形分组跨度   
	u8 temp;//temp用于记录当前组间距离的一半,同时也表示了同一碟形两分支间的距离   
	u8 gp_hf = 0;//记录当前组的中间点序号   
	u8 delta = N;//旋转因子下标增量，本来下标初始值应该为N/2，但是。。    
	s16 *pw = &(w[0][0]);    
	int tp_result[2];       //用于临时存放旋转因子和奇数分组的乘积 

	double module[N] = {0};
	int real[N] = {0};
	int imag[N] = {0};

	for(int index = 0; index < N; index++)
	{
		w[index][0] = (short)(cos(2 * 3.1415 * index / N) * 2048);
		w[index][1] = (short)(-sin(2 * 3.1415 * index / N) * 2048);
	}

	init_pointer();

	//输入信号序列放大   
	for(i = 0; i < N; i++)   
	{  
		x[i][0] <<= POWER;     
		x[i][1] <<= POWER;   
	}     
	for(i = 0; i < L; i++)   
	{  
		temp = gp_distance;      
		gp_distance <<= 1;      
		for(j = 0; j < N; j+=gp_distance)      
		{  
			gp_hf = temp + j;         
			pw = &(w[0][0]);         
			for(k = j; k < gp_hf; k++)//完成一组内的所有蝶形运算         
			{  
				//蝶形运算中的一组复数乘法过程            
				tp_result[0] = pw[0] * (p[k+temp][0]) - pw[1] * (p[k+temp][1]);            
				tp_result[1] = pw[0] * (p[k+temp][1]) + pw[1] * (p[k+temp][0]);            
				tp_result[0] >>= 11;            
				tp_result[1] >>= 11;            //蝶形运算中的2组复数加法过程            
				p[k+temp][0] = p[k][0] - tp_result[0];            
				p[k+temp][1] = p[k][1] - tp_result[1];            
				p[k][0] += tp_result[0];            
				p[k][1] += tp_result[1];     

				real[k] = p[k][0];
				imag[k] = p[k][1];

				real[k+temp] = p[k+temp][0];
				imag[k+temp] = p[k+temp][1];

				pw += delta;         
			}          
		}      
		delta >>= 1;   
	} 

	for(int index = 0; index < N; index++)
	{
		real[index] = p[index][0];
		imag[index] = p[index][1];
		LONGLONG sum = ((LONGLONG)real[index] * real[index] + (LONGLONG)imag[index] * imag[index]);
		module[index] = (double)sqrt((double)sum);
	}
}


// #define DOUBLE_PI 6.283185307179586476925286766559
// // 快速傅里叶变换
// // data 长度为 (2 * 2^n), data 的偶位为实数部分, data 的奇位为虚数部分
// // isInverse表示是否为逆变换
// void FFT(double * data, int n, bool isInverse = false)
// {
// 	int mmax, m, j, step, i;
// 	double temp;
// 	double theta, sin_htheta, sin_theta, pwr, wr, wi, tempr, tempi;
// 	n = 2 * (1 << n);
// 	int nn = n >> 1;
// 	// 长度为1的傅里叶变换, 位置交换过程
// 	j = 1;
// 	for(i = 1; i < n; i += 2)
// 	{
// 		if(j > i)
// 		{
// 			temp = data[j - 1];
// 			data[j - 1] = data[i - 1];
// 			data[i - 1] = temp;
// 			data[j] = temp;
// 			data[j] = data[i];
// 			data[i] = temp;
// 		}
// 		// 相反的二进制加法
// 		m = nn;
// 		while(m >= 2 && j > m)
// 		{
// 			j -= m;
// 			m >>= 1;
// 		}
// 		j += m;
// 	}
// 	// Danielson - Lanczos 引理应用
// 	mmax = 2;
// 	while(n > mmax)
// 	{
// 		step = mmax << 1;
// 		theta = DOUBLE_PI / mmax;
// 		if(isInverse)
// 		{
// 			theta = -theta;
// 		}
// 		sin_htheta = sin(0.5 * theta);
// 		sin_theta = sin(theta);
// 		pwr = -2.0 * sin_htheta * sin_htheta;
// 		wr = 1.0;
// 		wi = 0.0;
// 		for(m = 1; m < mmax; m += 2)
// 		{
// 			for(i = m; i <= n; i += step)
// 			{
// 				j = i + mmax;
// 				tempr = wr * data[j - 1] - wi * data[j];
// 				tempi = wr * data[j] + wi * data[j - 1];
// 				data[j - 1] = data[i - 1] - tempr;
// 				data[j] = data[i] - tempi;
// 				data[i - 1] += tempr;
// 				data[i] += tempi;
// 			}
// 			sin_htheta = wr;
// 			wr = sin_htheta * pwr - wi * sin_theta + wr;
// 			wi = wi * pwr + sin_htheta * sin_theta + wi;
// 		}
// 		mmax = step;
// 	}
// }