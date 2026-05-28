//#include "Rolling.h"
//
//Rolling::Rolling(unsigned short pDeAARxNum, unsigned short pDeAATxNum)
//{
//	gDeAARxNum = pDeAARxNum > SW_RX_MAX ? SW_RX_MAX : pDeAARxNum;
//	gDeAATxNum = pDeAATxNum > SW_TX_MAX ? SW_TX_MAX : pDeAATxNum;
//
//	gDeAANode = gDeAARxNum * gDeAATxNum;
//
//	initFlag = 0;
//
//	memset(gFrameTemp, 0, sizeof(gFrameTemp));
//
//	memset(g_fit_x, 0, sizeof(g_fit_x));
//
//	memset(g_fit_x_sq, 0, sizeof(g_fit_x_sq));
//
//	memset(g_fit_y_resid, 0, sizeof(g_fit_y_resid));
//
//	g_fit_a = 0;
//	g_fit_b = 0;
//	g_fit_c = 0;
//
//}
//
//Rolling::~Rolling()
//{
//}
//
//void Rolling::RollingNoiseFit1(short* DiffMul)
//{
//	unsigned char i;
//	unsigned short varTh = 10 * 10;                //离群点方差判定阈值
//	signed short* pDiffMulTr = gFrameTemp;       //当前帧互容diff转置
//	signed short* pDiffMulLine;					//互容diff转置后数据行指针
//	pDiffMul = DiffMul;
//	RollingNoiseFitInit();
//
//	/********************** 对各列diff进行二阶拟合减噪处理 ***********************/
//	//先将数据转置，再按行处理（顺序寻址，提升执行效率）
//	tr_vpu(pDiffMulTr, pDiffMul, gDeAATxNum, gDeAARxNum);       //当前帧互容diff转置
//
//	//按行处理（原始数据已转置）
//	pDiffMulLine = pDiffMulTr;      //当前帧互容diff转置数据
//	for (i = 0; i < gDeAATxNum; i++) {
//
//		//对该列diff进行二阶拟合减噪处理
//		RollingNoiseFit1Col(1, varTh, pDiffMulLine, pDiffMulLine);//默认都有触摸
//
//		pDiffMulLine += gDeAARxNum;//指针换行
//	}
//
//	tr_vpu(pDiffMul, pDiffMulTr, gDeAARxNum, gDeAATxNum);   //将处理后的数据转置回去（回填）
//
//	/********************** 对各行diff进行二阶拟合减噪处理 ***********************/
//	//按行处理
//	pDiffMulLine = pDiffMul;      //当前帧互容diff数据
//	for (i = 0; i < gDeAARxNum; i++) {
//
//		//对该行diff进行二阶拟合减噪处理
//		RollingNoiseFit1Row(1, varTh, pDiffMulLine, pDiffMulLine);//默认都有触摸
//
//		pDiffMulLine += gDeAATxNum;//指针换行
//	}
//}
//
//
//void Rolling::RollingNoiseFitInit(void)
//{
//	unsigned char i;
//
//	//初始化拟合自变量及其平方值（自变量从1开始）
//	if (!initFlag) {
//		initFlag = 1;
//
//		for (i = 0; i < gDeAARxNum; i++) {
//			g_fit_x[i] = i + 1;
//			g_fit_x_sq[i] = (i + 1) * (i + 1);
//		}
//	}
//}
//
//void Rolling::memcpy_byte(void* dest, void* src, unsigned int len)
//{
//	unsigned char* s = (unsigned char*)src;
//	unsigned char* d = (unsigned char*)dest;
//
//	while (len--)
//		*d++ = *s++;
//}
//
//void Rolling::memset_byte(void* dest, unsigned char byte, unsigned int len)
//{
//	unsigned char* d = (unsigned char*)dest;
//
//	while (len--)
//		*d++ = byte;
//}
//
//void Rolling::tr_vpu(signed short* dst, signed short* src, unsigned char tx, unsigned char rx)
//{
//	unsigned char i, j;
//	signed short* diff;
//	signed short* diff_dst;
//
//	diff_dst = dst;
//
//	for (i = 0; i < tx; i++) {
//		diff = src + i;
//
//		for (j = 0; j < rx; j++) {
//			*diff_dst = *diff;
//			diff_dst++;
//
//			diff += tx;
//		}
//	}
//}
//
//void Rolling::calMatrixAndCramersSolve(unsigned char x[], signed short y[], unsigned char n, signed long long* a, signed long long* b, signed long long* c)
//{
//	unsigned char i;
//	signed long long sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
//	signed long long sum_y = 0, sum_xy = 0, sum_x2y = 0;
//	signed long long det_A, det_Aa, det_Ab, det_Ac;                  //A矩阵及其构建矩阵行列式值
//	signed long long v;
//
//	// 计算各个求和项
//	for (i = 0; i < n; i++) {
//		v = x[i];
//		sum_x += v;
//		sum_y += y[i];
//		sum_xy += v * y[i];
//
//		v = v * x[i];
//		sum_x2 += v;
//		sum_x2y += v * y[i];
//
//		v = v * x[i];
//		sum_x3 += v;
//
//		v = v * x[i];
//		sum_x4 += v;
//	}
//
//	// 求解A矩阵行列式
//	det_A = sum_x4 * (sum_x2 * n - sum_x * sum_x)
//		- sum_x3 * (sum_x3 * n - sum_x2 * sum_x)
//		+ sum_x2 * (sum_x3 * sum_x - sum_x2 * sum_x2);
//
//	// 求解Aa矩阵行列式（替换第1列）
//	det_Aa = sum_x2y * (sum_x2 * n - sum_x * sum_x)
//		- sum_x3 * (sum_xy * n - sum_y * sum_x)
//		+ sum_x2 * (sum_xy * sum_x - sum_y * sum_x2);
//
//	// 求解Ab矩阵行列式（替换第2列）
//	det_Ab = sum_x4 * (sum_xy * n - sum_y * sum_x)
//		- sum_x2y * (sum_x3 * n - sum_x2 * sum_x)
//		+ sum_x2 * (sum_x3 * sum_y - sum_x2 * sum_xy);
//
//	// 求解Ac矩阵行列式（替换第3列）
//	det_Ac = sum_x4 * (sum_x2 * sum_y - sum_x * sum_xy)
//		- sum_x3 * (sum_x3 * sum_y - sum_x2 * sum_xy)
//		+ sum_x2y * (sum_x3 * sum_x - sum_x2 * sum_x2);
//
//	//求解二阶拟合系数a,b,c
//	if (det_A == 0) {
//		det_A = 1;//防止分母为0
//	}
//	*a = (det_Aa << AMP_NUM_BIT) / det_A;
//	*b = (det_Ab << AMP_NUM_BIT) / det_A;
//	*c = (det_Ac << AMP_NUM_BIT) / det_A;
//
//	//LOG("DebugMatrix0:frame=%d, A=%Id, Aa=%Id, Ab=%Id, Ac=%Id\n", g_frame_cnt, det_A, det_Aa, det_Ab, det_Ac);
//	//LOG("DebugMatrix1:frame=%d, a=%Id, b=%Id, c=%Id\n", g_frame_cnt, *a, *b, *c);
//
//}
//
//unsigned char Rolling::removeOutliers(unsigned char flagCol0Row1, unsigned char* x_src, signed short* y_src, unsigned char* outlierMaskFlag, unsigned char* x_out, signed short* y_out)
//{
//	signed int i;
//	signed int index = 0;
//
//	if (!flagCol0Row1) {
//		//遍历outlierMaskFlag，复制非离群点（x,y）
//		for (i = 0; i < gDeAARxNum; i++) {
//			if (!outlierMaskFlag[i]) {
//				x_out[index] = x_src[i];
//				y_out[index] = y_src[i];
//				index++;
//			}
//		}
//	}
//	else {
//		//遍历outlierMaskFlag，复制非离群点（x,y）
//		for (i = 0; i < gDeAATxNum; i++) {
//			if (!outlierMaskFlag[i]) {
//				x_out[index] = x_src[i];
//				y_out[index] = y_src[i];
//				index++;
//			}
//		}
//	}
//
//	return index;
//}
//
//unsigned int Rolling::calculateVariance(signed short* data, unsigned char size)
//{
//	unsigned char i;
//	signed int aver = 0;
//	signed long long diff = 0;
//	unsigned long long variance = 0;   //方差
//
//#if 1
//	//防止除0，程序崩溃
//	if (size == 0) {
//		return 0;
//	}
//#endif
//
//	//求均值
//	for (i = 0; i < size; i++) {
//		aver += (signed long long)data[i];
//	}
//	aver = (aver << AMP_NUM_BIT) / (signed long long)size;//放大了AMP_NUM
//
//	//求各数据点与它们均值之间的差值平方 的平均值（先累和）
//	for (i = 0; i < size; i++) {
//		diff = ((signed int)data[i] << AMP_NUM_BIT) - aver;    //与均值之间的差值：放大了AMP_NUM
//		variance += (unsigned long long)(diff * diff);                 //与均值之间的差值的平方（先累和）：放大了 AMP_NUM*AMP_NUM
//	}
//
//	//方差
//	variance = (variance / (unsigned long long)size) >> (2 * AMP_NUM_BIT);//与均值之间的差值的平方的平均值
//	return variance;
//}
//
//unsigned char Rolling::isEqualOutliers(unsigned char* data1, unsigned char* data2, unsigned char start, unsigned char end)
//{
//	unsigned char i;
//	unsigned char flag = 1;//默认相同
//
//	for (i = start; i < end; i++) {
//		if (data1[i] != data2[i]) {
//			flag = 0;               //标记data1与data2不完全相同
//			break;                  //存在不同节点，不再比较，认为两组数据不完全相同
//		}
//	}
//	return flag;
//}
////对当前帧某行diff数据进行拟合算法减噪处理，传入是否有触摸标记和方差阈值
//void Rolling::RollingNoiseFit1Row(unsigned char touchFlag, unsigned short varTh, signed short* pDiffNow, signed short* pDiffSub)
//{
//	unsigned char j, k;
//	unsigned char  x[SW_TX_MAX];
//	signed short y[SW_TX_MAX];                       //无需初始化，提升执行效率
//	unsigned char  n = 0;                              //存储去除离群点后的一列数据（自变量和因变量）和数量
//	signed short temp;
//	unsigned char flagFitFinal = 0;                    //是否进行最后一次拟合标志
//	unsigned char outlierMaskFlag[SW_TX_MAX] = { 0 };    //离群点索引标记，1 该索引位置点为离群点；0 该索引位置点为非离群点
//	unsigned char outlierMaskFlagNew[SW_TX_MAX] = { 0 }; //新的标记
//	unsigned int variance = 0;                       //方差
//	signed short diff_new = 0;                       //差值
//	unsigned char cnt = 0;                             //数量临时变量
//	signed short fittedValBuf[SW_TX_MAX];            //拟合值
//
//
//	//有触摸进行：先迭代拟合后判断是否进行最后一次拟合
//	if (touchFlag) {
//		//1、动态自迭代拟合，获取二次项拟合系数abc（最多3次）
//		for (k = 0; k < 5; k++) {
//
//			/********************** 1) 用非outlier点做二次多项式拟合 ********************************/
//			outlierMaskFlag[0] = 1;                                 //首次标记离群点（默认第一个点为离群点）
//			n = removeOutliers(1, g_fit_x, pDiffSub, outlierMaskFlag, x, y);   //前后帧差值 挑出离群点
//			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c
//
//			/********************** 2) 计算残差 *****************************************************/
//			//计算所有节点的残差值（前后帧差值-拟合值）
//			for (j = 0; j < gDeAATxNum; j++) {
//				temp = ((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT;//拟合值
//				g_fit_y_resid[j] = pDiffSub[j] - temp;
//			}
//
//			/********************** 3) 用统计阈值判定哪些点是离群点（强信号） **********************/
//			//先计算非离群点残差的 方差
//			n = removeOutliers(1, g_fit_x, g_fit_y_resid, outlierMaskFlag, x, y);//残差 挑出离群点
//			variance = calculateVariance(y, n);
//
//			//方差较小，整体数据平稳，退出迭代拟合
//			if (variance < varTh) {
//				break;
//			}
//			//基于标准差设定阈值，标记残差中绝对值超过阈值的点为离群点
//			for (j = 0; j < gDeAATxNum; j++) {
//				if ((g_fit_y_resid[j] * g_fit_y_resid[j]) > (variance << 2)) {//使用方差判定进行等价，避免开方操作
//					outlierMaskFlagNew[j] = 1;
//				}
//			}
//			//检查离群点标记是否发生变化（是否出现新的强信号点），若mask未变化表示数据稳定，结束迭代拟合，否则，更新outlierMaskFlag标记
//			if (isEqualOutliers(outlierMaskFlag, outlierMaskFlagNew, 1, gDeAATxNum)) {
//				break;
//			}
//			else {
//				memcpy_byte(outlierMaskFlag, outlierMaskFlagNew, gDeAATxNum);//否则，更新mask标记
//			}
//		}
//
//		//2、再次查找是否存在突出点（原始diff与拟合值差距过大），是否进行拟合（保险起见，从另一个方向进行判断）
//		memset_byte(outlierMaskFlagNew, 0, gDeAATxNum);//清零标记
//		cnt = 0;
//		flagFitFinal = 0;
//		for (j = 0; j < gDeAATxNum; j++) {
//			temp = ((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT;//拟合值
//			diff_new = pDiffNow[j] - temp;  //原始diff-baseline
//			fittedValBuf[j] = temp;     //保存使用迭代得到的拟合系数计算的baseLine（避免重复计算）
//
//			//存在突出点，标记需要最后进行一次拟合
//			if (!flagFitFinal) {
//				if (ABS_DATA(diff_new) > 100) {
//					cnt++;
//				}
//				if (cnt > 2) {
//					flagFitFinal = 1;
//				}
//			}
//
//			//标记差值超过阈值的突出点（标记为离群点Mask）
//			if (ABS_DATA(diff_new) > 200) {
//				outlierMaskFlagNew[j] = 1;
//			}
//		}
//		//3、需要进行最后一次拟合，用非离群点拟合baseLine（只要有手指触摸就会触发？），进行减噪
//		if (flagFitFinal) {
//			n = removeOutliers(1, g_fit_x, pDiffNow, outlierMaskFlagNew, x, y);    //实际diff 挑出离群点
//			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c
//			for (j = 0; j < gDeAATxNum; j++) {
//				temp = ((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT;//拟合值
//				pDiffNow[j] -= temp;    //减噪：原始diff-拟合diff
//			}
//		}
//		else {//无需进行最后一次拟合，使用前面保存的使用迭代得到的拟合系数计算的baseLine进行减噪
//			for (j = 0; j < gDeAATxNum; j++) {
//				pDiffNow[j] -= fittedValBuf[j]; //减噪：原始diff-拟合diff
//			}
//		}
//	}
//}
//
//void Rolling::RollingNoiseFit1Col(unsigned char touchFlag, unsigned short varTh, signed short* pDiffNow, signed short* pDiffSub)
//{
//	unsigned char j, k;
//	unsigned char  x[SW_RX_MAX];
//	signed short y[SW_RX_MAX];                       //无需初始化，提升执行效率
//	unsigned char  n = 0;                              //存储去除离群点后的一列数据（自变量和因变量）和数量
//	signed short temp;
//	unsigned char flagFitFinal = 0;                    //是否进行最后一次拟合标志
//	unsigned char outlierMaskFlag[SW_RX_MAX] = { 0 };    //离群点索引标记，1 该索引位置点为离群点；0 该索引位置点为非离群点
//	unsigned char outlierMaskFlagNew[SW_RX_MAX] = { 0 }; //新的标记
//	unsigned int variance = 0;                       //方差
//	signed short diff_new = 0;                       //差值
//	unsigned char cnt = 0;                             //数量临时变量
//	signed short fittedValBuf[SW_RX_MAX];            //拟合值
//
//
//	//有触摸进行：先迭代拟合后判断是否进行最后一次拟合
//	if (touchFlag) {
//		//1、动态自迭代拟合，获取二次项拟合系数abc（最多3次）
//		for (k = 0; k < 5; k++) {
//
//			/********************** 1) 用非outlier点做二次多项式拟合 ********************************/
//			outlierMaskFlag[0] = 1;                                 //首次标记离群点（默认第一个点为离群点）
//			n = removeOutliers(0, g_fit_x, pDiffSub, outlierMaskFlag, x, y);   //前后帧差值 挑出离群点
//			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c
//
//			/********************** 2) 计算残差 *****************************************************/
//			//计算所有节点的残差值（前后帧差值-拟合值）
//			for (j = 0; j < gDeAARxNum; j++) {
//				temp = ((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT;//拟合值
//				g_fit_y_resid[j] = pDiffSub[j] - temp;
//			}
//
//			/********************** 3) 用统计阈值判定哪些点是离群点（强信号） **********************/
//			//先计算非离群点残差的 方差
//			n = removeOutliers(0, g_fit_x, g_fit_y_resid, outlierMaskFlag, x, y);//残差 挑出离群点
//			variance = calculateVariance(y, n);
//
//			//方差较小，整体数据平稳，退出迭代拟合
//			if (variance < varTh) {
//				break;
//			}
//			//基于标准差设定阈值，标记残差中绝对值超过阈值的点为离群点
//			for (j = 0; j < gDeAARxNum; j++) {
//				if ((g_fit_y_resid[j] * g_fit_y_resid[j]) > (variance << 2)) {//使用方差判定进行等价，避免开方操作
//					outlierMaskFlagNew[j] = 1;
//				}
//			}
//			//检查离群点标记是否发生变化（是否出现新的强信号点），若mask未变化表示数据稳定，结束迭代拟合，否则，更新outlierMaskFlag标记
//			if (isEqualOutliers(outlierMaskFlag, outlierMaskFlagNew, 1, gDeAARxNum)) {
//				break;
//			}
//			else {
//				memcpy_byte(outlierMaskFlag, outlierMaskFlagNew, gDeAARxNum);//否则，更新mask标记
//			}
//		}
//
//		//2、再次查找是否存在突出点（原始diff与拟合值差距过大），是否进行拟合（保险起见，从另一个方向进行判断）
//		memset_byte(outlierMaskFlagNew, 0, gDeAARxNum);//清零标记
//		cnt = 0;
//		flagFitFinal = 0;
//		for (j = 0; j < gDeAARxNum; j++) {
//			temp = ((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT;//拟合值
//			diff_new = pDiffNow[j] - temp;  //原始diff-baseline
//			fittedValBuf[j] = temp;     //保存使用迭代得到的拟合系数计算的baseLine（避免重复计算）
//
//			//存在突出点，标记需要最后进行一次拟合
//			if (!flagFitFinal) {
//				if (ABS_DATA(diff_new) > 100) {
//					cnt++;
//				}
//				if (cnt > 2) {
//					flagFitFinal = 1;
//				}
//			}
//
//			//标记差值超过阈值的突出点（标记为离群点Mask）
//			if (ABS_DATA(diff_new) > 200) {
//				outlierMaskFlagNew[j] = 1;
//			}
//		}
//		//3、需要进行最后一次拟合，用非离群点拟合baseLine（只要有手指触摸就会触发？），进行减噪
//		if (flagFitFinal) {
//			n = removeOutliers(0, g_fit_x, pDiffNow, outlierMaskFlagNew, x, y);    //实际diff 挑出离群点
//			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c
//			for (j = 0; j < gDeAARxNum; j++) {
//				temp = ((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT;//拟合值
//				pDiffNow[j] -= temp;    //减噪：原始diff-拟合diff
//			}
//		}
//		else {//无需进行最后一次拟合，使用前面保存的使用迭代得到的拟合系数计算的baseLine进行减噪
//			for (j = 0; j < gDeAARxNum; j++) {
//				pDiffNow[j] -= fittedValBuf[j]; //减噪：原始diff-拟合diff
//			}
//		}
//	}
//}






#include "Rolling.h"

RollingR::RollingR()
{

	memset(g_fit_x, 0, sizeof(g_fit_x));
	memset(g_fit_x_sq, 0, sizeof(g_fit_x_sq));
	memset(g_fit_y_resid, 0, sizeof(g_fit_y_resid));
	memset(gFrameTemp, 0, sizeof(gFrameTemp));

	g_fit_a = 0;
	g_fit_b = 0;
	g_fit_c = 0;
}

RollingR::~RollingR()
{
}

void RollingR::memcpy_byte(void* dest, void* src, u32 len)
{
	u8* s = (u8*)src;
	u8* d = (u8*)dest;

	while (len--)
		*d++ = *s++;
}

void RollingR::memset_byte(void* dest, u8 byte, u32 len)
{
	vu8* d = (vu8*)dest;

	while (len--)
		*d++ = byte;
}

void RollingR::tr_vpu(s16* dst, s16* src, u8 tx, u8 rx)
{
	u8 i, j;
	s16* diff;
	s16* diff_dst;

	diff_dst = dst;

	for (i = 0; i < tx; i++) {
		diff = src + i;

		for (j = 0; j < rx; j++) {
			*diff_dst = *diff;
			diff_dst++;

			diff += tx;
		}
	}
}

void RollingR::RollingNoiseFitInit(u8 gDeAARxNum)
{
	u8 i;

	//初始化拟合自变量及其平方值（自变量从1开始）
	for (i = 0; i < gDeAARxNum; i++) {
		g_fit_x[i] = i + 1;
		g_fit_x_sq[i] = (i + 1) * (i + 1);
	}
}

void RollingR::calMatrixAndCramersSolve(u8 x[], s16 y[], u8 n, s64* a, s64* b, s64* c)
{
	u8 i;
	s64 sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
	s64 sum_y = 0, sum_xy = 0, sum_x2y = 0;
	s64 det_A, det_Aa, det_Ab, det_Ac;                  //A矩阵及其构建矩阵行列式值
	s64 v;

	// 计算各个求和项
	for (i = 0; i < n; i++) {
		v = x[i];
		sum_x += v;
		sum_y += y[i];
		sum_xy += v * y[i];

		v = v * x[i];
		sum_x2 += v;
		sum_x2y += v * y[i];

		v = v * x[i];
		sum_x3 += v;

		v = v * x[i];
		sum_x4 += v;
	}

	// 求解A矩阵行列式
	det_A = sum_x4 * (sum_x2 * n - sum_x * sum_x)
		- sum_x3 * (sum_x3 * n - sum_x2 * sum_x)
		+ sum_x2 * (sum_x3 * sum_x - sum_x2 * sum_x2);

	// 求解Aa矩阵行列式（替换第1列）
	det_Aa = sum_x2y * (sum_x2 * n - sum_x * sum_x)
		- sum_x3 * (sum_xy * n - sum_y * sum_x)
		+ sum_x2 * (sum_xy * sum_x - sum_y * sum_x2);

	// 求解Ab矩阵行列式（替换第2列）
	det_Ab = sum_x4 * (sum_xy * n - sum_y * sum_x)
		- sum_x2y * (sum_x3 * n - sum_x2 * sum_x)
		+ sum_x2 * (sum_x3 * sum_y - sum_x2 * sum_xy);

	// 求解Ac矩阵行列式（替换第3列）
	det_Ac = sum_x4 * (sum_x2 * sum_y - sum_x * sum_xy)
		- sum_x3 * (sum_x3 * sum_y - sum_x2 * sum_xy)
		+ sum_x2y * (sum_x3 * sum_x - sum_x2 * sum_x2);

	//求解二阶拟合系数a,b,c
	if (det_A == 0) {
		det_A = 1;//防止分母为0
	}
	*a = (det_Aa << AMP_NUM_BIT) / det_A;
	*b = (det_Ab << AMP_NUM_BIT) / det_A;
	*c = (det_Ac << AMP_NUM_BIT) / det_A;

}

u8 RollingR::removeOutliers(u8 n, u8* x_src, s16* y_src, u8* outlierMaskFlag, u8* x_out, s16* y_out)
{
	s32 i;
	s32 index = 0;

	//遍历outlierMaskFlag，复制非离群点（x,y）
	for (i = 0; i < n; i++) {
		if (!outlierMaskFlag[i]) {
			x_out[index] = x_src[i];
			y_out[index] = y_src[i];
			index++;
		}
	}

	return index;
}

u64 RollingR::calculateVariance(s16* data, u8 size)
{
	u8 i;
	s32 aver = 0;
	s64 diff = 0;
	u64 variance = 0;   //方差

	//防止除0，程序崩溃
	if (size == 0) {
		return 0;
	}

	//求均值
	for (i = 0; i < size; i++) {
		aver += (s64)data[i];
	}
	aver = (aver << AMP_NUM_BIT) / (s64)size;//放大了AMP_NUM

	//求各数据点与它们均值之间的差值平方 的平均值（先累和）
	for (i = 0; i < size; i++) {
		diff = ((s32)data[i] << AMP_NUM_BIT) - aver;    //与均值之间的差值：放大了AMP_NUM
		variance += (u64)(diff * diff);                 //与均值之间的差值的平方（先累和）：放大了 AMP_NUM*AMP_NUM
	}

	//方差
	variance = (variance / (u64)size) >> (2 * AMP_NUM_BIT);//与均值之间的差值的平方的平均值
	return variance;
}

u8 RollingR::isEqualOutliers(u8* data1, u8* data2, u8 start, u8 end)
{
	u8 i;
	u8 flag = 1;//默认相同

	for (i = start; i < end; i++) {
		if (data1[i] != data2[i]) {
			flag = 0;               //标记data1与data2不完全相同
			break;                  //存在不同节点，不再比较，认为两组数据不完全相同
		}
	}
	return flag;
}

void RollingR::RollingNoiseFit1Col(u8 touchFlag, u16 varTh, s16* pDiffNow, s16* pDiffSub, u8 gDeAARxNum)
{
	u8 j, k;
	u8  x[SW_RX_MAX];
	s16 y[SW_RX_MAX];                       //无需初始化，提升执行效率
	u8  n = 0;                              //存储去除离群点后的一列数据（自变量和因变量）和数量
	s16 temp;
	u8 flagFitFinal = 0;                    //是否进行最后一次拟合标志
	u8 outlierMaskFlag[SW_RX_MAX] = { 0 };    //离群点索引标记，1 该索引位置点为离群点；0 该索引位置点为非离群点
	u8 outlierMaskFlagNew[SW_RX_MAX] = { 0 }; //新的标记
	u64 variance = 0;                       //方差
	s16 diff_new = 0;                       //差值
	u8 cnt = 0;                             //数量临时变量
	s16 fittedValBuf[SW_RX_MAX];            //拟合值


	//有触摸进行：先迭代拟合后判断是否进行最后一次拟合
	if (touchFlag) {
		//1、动态自迭代拟合，获取二次项拟合系数abc（最多3次）
		for (k = 0; k < 5; k++) {

			/********************** 1) 用非outlier点做二次多项式拟合 ********************************/
			outlierMaskFlag[0] = 1;                                 //首次标记离群点（默认第一个点为离群点）
			n = removeOutliers(gDeAARxNum, g_fit_x, pDiffSub, outlierMaskFlag, x, y);   //前后帧差值 挑出离群点
			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c

			/********************** 2) 计算残差 *****************************************************/
			//计算所有节点的残差值（前后帧差值-拟合值）
			for (j = 0; j < gDeAARxNum; j++) {
				temp = (s16)(((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT);//拟合值
				g_fit_y_resid[j] = pDiffSub[j] - temp;
			}

			/********************** 3) 用统计阈值判定哪些点是离群点（强信号） **********************/
			//先计算非离群点残差的 方差
			n = removeOutliers(gDeAARxNum, g_fit_x, g_fit_y_resid, outlierMaskFlag, x, y);//残差 挑出离群点
			variance = calculateVariance(y, n);

			//方差较小，整体数据平稳，退出迭代拟合
			if (variance < varTh) {
				break;
			}
			//基于标准差设定阈值，标记残差中绝对值超过阈值的点为离群点
			for (j = 0; j < gDeAARxNum; j++) {
				if ((g_fit_y_resid[j] * g_fit_y_resid[j]) > (variance << 2)) {//使用方差判定进行等价，避免开方操作
					outlierMaskFlagNew[j] = 1;
				}
			}
			//检查离群点标记是否发生变化（是否出现新的强信号点），若mask未变化表示数据稳定，结束迭代拟合，否则，更新outlierMaskFlag标记
			if (isEqualOutliers(outlierMaskFlag, outlierMaskFlagNew, 1, gDeAARxNum)) {
				break;
			}
			else {
				memcpy_byte(outlierMaskFlag, outlierMaskFlagNew, gDeAARxNum);//否则，更新mask标记
			}
		}

		//2、再次查找是否存在突出点（原始diff与拟合值差距过大），是否进行拟合（保险起见，从另一个方向进行判断）
		memset_byte(outlierMaskFlagNew, 0, gDeAARxNum);//清零标记
		cnt = 0;
		flagFitFinal = 0;
		for (j = 0; j < gDeAARxNum; j++) {
			temp = (s16)(((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT);//拟合值
			diff_new = pDiffNow[j] - temp;  //原始diff-baseline
			fittedValBuf[j] = temp;     //保存使用迭代得到的拟合系数计算的baseLine（避免重复计算）

			//存在突出点，标记需要最后进行一次拟合
			if (!flagFitFinal) {
				if (ABS_DATA(diff_new) > 100) {
					cnt++;
				}
				if (cnt > 2) {
					flagFitFinal = 1;
				}
			}

			//标记差值超过阈值的突出点（标记为离群点Mask）
			if (ABS_DATA(diff_new) > 200) {
				outlierMaskFlagNew[j] = 1;
			}
		}
		//3、需要进行最后一次拟合，用非离群点拟合baseLine（只要有手指触摸就会触发？），进行减噪
		if (flagFitFinal) {
			n = removeOutliers(gDeAARxNum, g_fit_x, pDiffNow, outlierMaskFlagNew, x, y);    //实际diff 挑出离群点
			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c
			for (j = 0; j < gDeAARxNum; j++) {
				temp = (s16)(((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT);//拟合值
				pDiffNow[j] -= temp;    //减噪：原始diff-拟合diff
			}
		}
		else {//无需进行最后一次拟合，使用前面保存的使用迭代得到的拟合系数计算的baseLine进行减噪
			for (j = 0; j < gDeAARxNum; j++) {
				pDiffNow[j] -= fittedValBuf[j]; //减噪：原始diff-拟合diff
			}
		}
	}
}

void RollingR::RollingNoiseFit1Row(u8 touchFlag, u16 varTh, s16* pDiffNow, s16* pDiffSub, u8 gDeAATxNum)
{
	u8 j, k;
	u8  x[SW_TX_MAX];
	s16 y[SW_TX_MAX];                       //无需初始化，提升执行效率
	u8  n = 0;                              //存储去除离群点后的一列数据（自变量和因变量）和数量
	s16 temp;
	u8 flagFitFinal = 0;                    //是否进行最后一次拟合标志
	u8 outlierMaskFlag[SW_TX_MAX] = { 0 };    //离群点索引标记，1 该索引位置点为离群点；0 该索引位置点为非离群点
	u8 outlierMaskFlagNew[SW_TX_MAX] = { 0 }; //新的标记
	u64 variance = 0;                       //方差
	s16 diff_new = 0;                       //差值
	u8 cnt = 0;                             //数量临时变量
	s16 fittedValBuf[SW_TX_MAX];            //拟合值


	//有触摸进行：先迭代拟合后判断是否进行最后一次拟合
	if (touchFlag) {
		//1、动态自迭代拟合，获取二次项拟合系数abc（最多3次）
		for (k = 0; k < 5; k++) {

			/********************** 1) 用非outlier点做二次多项式拟合 ********************************/
			outlierMaskFlag[0] = 1;                                 //首次标记离群点（默认第一个点为离群点）
			n = removeOutliers(gDeAATxNum, g_fit_x, pDiffSub, outlierMaskFlag, x, y);   //前后帧差值 挑出离群点
			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c

			/********************** 2) 计算残差 *****************************************************/
			//计算所有节点的残差值（前后帧差值-拟合值）
			for (j = 0; j < gDeAATxNum; j++) {
				temp = (s16)(((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT);//拟合值
				g_fit_y_resid[j] = pDiffSub[j] - temp;
			}

			/********************** 3) 用统计阈值判定哪些点是离群点（强信号） **********************/
			//先计算非离群点残差的 方差
			n = removeOutliers(gDeAATxNum, g_fit_x, g_fit_y_resid, outlierMaskFlag, x, y);//残差 挑出离群点
			variance = calculateVariance(y, n);

			//方差较小，整体数据平稳，退出迭代拟合
			if (variance < varTh) {
				break;
			}
			//基于标准差设定阈值，标记残差中绝对值超过阈值的点为离群点
			for (j = 0; j < gDeAATxNum; j++) {
				if ((u64)(g_fit_y_resid[j] * g_fit_y_resid[j]) > (variance << 2)) {//使用方差判定进行等价，避免开方操作
					outlierMaskFlagNew[j] = 1;
				}
			}
			//检查离群点标记是否发生变化（是否出现新的强信号点），若mask未变化表示数据稳定，结束迭代拟合，否则，更新outlierMaskFlag标记
			if (isEqualOutliers(outlierMaskFlag, outlierMaskFlagNew, 1, gDeAATxNum)) {
				break;
			}
			else {
				memcpy_byte(outlierMaskFlag, outlierMaskFlagNew, gDeAATxNum);//否则，更新mask标记
			}
		}

		//2、再次查找是否存在突出点（原始diff与拟合值差距过大），是否进行拟合（保险起见，从另一个方向进行判断）
		memset_byte(outlierMaskFlagNew, 0, gDeAATxNum);//清零标记
		cnt = 0;
		flagFitFinal = 0;
		for (j = 0; j < gDeAATxNum; j++) {
			temp = (s16)(((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT);//拟合值
			diff_new = pDiffNow[j] - temp;  //原始diff-baseline
			fittedValBuf[j] = temp;     //保存使用迭代得到的拟合系数计算的baseLine（避免重复计算）

			//存在突出点，标记需要最后进行一次拟合
			if (!flagFitFinal) {
				if (ABS_DATA(diff_new) > 100) {
					cnt++;
				}
				if (cnt > 2) {
					flagFitFinal = 1;
				}
			}

			//标记差值超过阈值的突出点（标记为离群点Mask）
			if (ABS_DATA(diff_new) > 200) {
				outlierMaskFlagNew[j] = 1;
			}
		}
		//3、需要进行最后一次拟合，用非离群点拟合baseLine（只要有手指触摸就会触发？），进行减噪
		if (flagFitFinal) {
			n = removeOutliers(gDeAATxNum, g_fit_x, pDiffNow, outlierMaskFlagNew, x, y);    //实际diff 挑出离群点
			calMatrixAndCramersSolve(x, y, n, &g_fit_a, &g_fit_b, &g_fit_c);    //初始化AB矩阵并求解拟合系数a、b、c
			for (j = 0; j < gDeAATxNum; j++) {
				temp = (s16)(((g_fit_a * g_fit_x_sq[j]) + (g_fit_b * g_fit_x[j]) + g_fit_c) >> AMP_NUM_BIT);//拟合值
				pDiffNow[j] -= temp;    //减噪：原始diff-拟合diff
			}
		}
		else {//无需进行最后一次拟合，使用前面保存的使用迭代得到的拟合系数计算的baseLine进行减噪
			for (j = 0; j < gDeAATxNum; j++) {
				pDiffNow[j] -= fittedValBuf[j]; //减噪：原始diff-拟合diff
			}
		}
	}
}

void RollingR::RollingNoiseFit1(s16* pDiffMul, u8 gDeAARxNum, u8 gDeAATxNum)
{
	if (pDiffMul == nullptr || gDeAARxNum > SW_RX_MAX || gDeAATxNum > SW_TX_MAX)
	{
		return;
	}
	u8 i;
	u16 varTh = 10 * 10;                //离群点方差判定阈值
	s16* pDiffMulTr = gFrameTemp;       //当前帧互容diff转置
	s16* pDiffMulLine;					//互容diff转置后数据行指针

	RollingNoiseFitInit(gDeAARxNum);

	/********************** 对各列diff进行二阶拟合减噪处理 ***********************/
	//先将数据转置，再按行处理（顺序寻址，提升执行效率）
	tr_vpu(pDiffMulTr, pDiffMul, gDeAATxNum, gDeAARxNum);       //当前帧互容diff转置

	//按行处理（原始数据已转置）
	pDiffMulLine = pDiffMulTr;      //当前帧互容diff转置数据
	for (i = 0; i < gDeAATxNum; i++) {

		//对该列diff进行二阶拟合减噪处理
		RollingNoiseFit1Col(1, varTh, pDiffMulLine, pDiffMulLine, gDeAARxNum);//默认都有触摸

		pDiffMulLine += gDeAARxNum;//指针换行
	}

	tr_vpu(pDiffMul, pDiffMulTr, gDeAARxNum, gDeAATxNum);   //将处理后的数据转置回去（回填）

	/********************** 对各行diff进行二阶拟合减噪处理 ***********************/
	//按行处理
	pDiffMulLine = pDiffMul;      //当前帧互容diff数据
	for (i = 0; i < gDeAARxNum; i++) {

		//对该行diff进行二阶拟合减噪处理
		RollingNoiseFit1Row(1, varTh, pDiffMulLine, pDiffMulLine, gDeAATxNum);//默认都有触摸

		pDiffMulLine += gDeAATxNum;//指针换行
	}
}





