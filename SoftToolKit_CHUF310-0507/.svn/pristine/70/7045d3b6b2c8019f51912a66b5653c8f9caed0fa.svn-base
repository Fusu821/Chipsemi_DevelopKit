//#pragma once
//
//#include <iostream>
//
//#define SW_TX_MAX       20  //
//#define SW_RX_MAX       42  //
//#define SW_NODE_MAX     (SW_TX_MAX*SW_RX_MAX)
//#define ABS_DATA(x)    ((x)>0?(x):(0-(x)))
//
//#define AMP_NUM_BIT 10              //移位数2^10==1024
//
//class Rolling
//{
//public:
//	Rolling(unsigned short pDeAARxNum, unsigned short pDeAATxNum);
//	~Rolling();
//
//public:
//	void RollingNoiseFit1(short* DiffMul);
//
//private:
//	void RollingNoiseFitInit(void);
//
//	void memcpy_byte(void* dest, void* src, unsigned int len);
//
//	void memset_byte(void* dest, unsigned char byte, unsigned int len);
//
//	void tr_vpu(signed short* dst, signed short* src, unsigned char tx, unsigned char rx);
//
//	void calMatrixAndCramersSolve(unsigned char x[], signed short y[], unsigned char n, signed long long* a, signed long long* b, signed long long* c);
//
//	unsigned char removeOutliers(unsigned char flagCol0Row1, unsigned char* x_src, signed short* y_src, unsigned char* outlierMaskFlag, unsigned char* x_out, signed short* y_out);
//
//	unsigned int calculateVariance(signed short* data, unsigned char size);
//
//	unsigned char isEqualOutliers(unsigned char* data1, unsigned char* data2, unsigned char start, unsigned char end);
//
//	void RollingNoiseFit1Col(unsigned char touchFlag, unsigned short varTh, signed short* pDiffNow, signed short* pDiffSub);
//
//	void RollingNoiseFit1Row(unsigned char touchFlag, unsigned short varTh, signed short* pDiffNow, signed short* pDiffSub);
//
//
//private:
//
//	unsigned short gDeAARxNum;
//	unsigned short gDeAATxNum;
//	unsigned short gDeAANode;
//
//	signed short* pDiffMul;
//	signed short gFrameTemp[SW_NODE_MAX];
//
//	unsigned char g_fit_x[SW_RX_MAX];              //拟合自变量（从1开始）
//	unsigned short g_fit_x_sq[SW_RX_MAX];          //拟合自变量平方值（预计算，加速执行效率）
//	signed short g_fit_y_resid[SW_RX_MAX]; //保存一列diff残差值（前后帧差值-根据差值求解的系数拟合值）
//	signed long long g_fit_a, g_fit_b, g_fit_c;      //二阶拟合系数（y = a*x^2 + b*x + c)
//
//	unsigned char initFlag;
//};
//





#pragma once

#include <iostream>

#define AMP_NUM_BIT 10              //移位数2^10==1024

typedef unsigned char       u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;
typedef  u8        vu8;

#define SW_TX_MAX       20 
#define SW_RX_MAX       42 
#define SW_NODE_MAX     (SW_TX_MAX*SW_RX_MAX)
#define ABS_DATA(x)    ((x)>0?(x):(0-(x)))

class RollingR
{
public:
	RollingR();
	~RollingR();
public:

	//互容：二阶拟合减噪主函数
	void RollingNoiseFit1(s16* pDiffMul, u8 gDeAARxNum, u8 gDeAATxNum);

private:

	void memcpy_byte(void* dest, void* src, u32 len);
	void memset_byte(void* dest, u8 byte, u32 len);
	void tr_vpu(s16* dst, s16* src, u8 tx, u8 rx);
	void RollingNoiseFitInit(u8 gDeAARxNum);

	//构建AB矩阵，并根据克莱姆法则求解二阶拟合系数a,b,c
	void calMatrixAndCramersSolve(u8 x[], s16 y[], u8 n, s64* a, s64* b, s64* c);

	//从输入数据中去除离群点，输出非离群点数据x,y，返回数据点数量
	u8 removeOutliers(u8 n, u8* x_src, s16* y_src, u8* outlierMaskFlag, u8* x_out, s16* y_out);

	//计算方差（方差是各个数据点与它们的平均值之间差值的平方 的平均值）
	u64 calculateVariance(s16* data, u8 size);

	//比较指定范围内数据是否完全相同，相同返回1；否则复制data2数据到data1，返回0
	u8 isEqualOutliers(u8* data1, u8* data2, u8 start, u8 end);

	//对当前帧某列diff数据进行拟合算法减噪处理，传入是否有触摸标记和方差阈值
	void RollingNoiseFit1Col(u8 touchFlag, u16 varTh, s16* pDiffNow, s16* pDiffSub, u8 gDeAARxNum);

	//对当前帧某行diff数据进行拟合算法减噪处理，传入是否有触摸标记和方差阈值
	void RollingNoiseFit1Row(u8 touchFlag, u16 varTh, s16* pDiffNow, s16* pDiffSub, u8 gDeAATxNum);


private:

	u8 g_fit_x[SW_RX_MAX];              //拟合自变量（从1开始）
	u16 g_fit_x_sq[SW_RX_MAX];          //拟合自变量平方值（预计算，加速执行效率）
	s16 g_fit_y_resid[SW_RX_MAX]; //保存一列diff残差值（前后帧差值-根据差值求解的系数拟合值）
	s64 g_fit_a, g_fit_b, g_fit_c;      //二阶拟合系数（y = a*x^2 + b*x + c)

	s16 gFrameTemp[SW_NODE_MAX];

};


