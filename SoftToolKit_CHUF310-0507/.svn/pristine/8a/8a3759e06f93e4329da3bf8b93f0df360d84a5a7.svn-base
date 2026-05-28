#ifndef __CHECK_SUM__
#define __CHECK_SUM__
/*************************************************************************************/

static unsigned char caculate_check_sum_u8( unsigned char * buf, unsigned int length )
{
	unsigned int i = 0;
	unsigned char sum = 0;

	for( i=0; i< length; i++ )
		sum += buf[i];

	return sum;
}

static unsigned short caculate_check_sum_u16( unsigned short * buf, unsigned int length )
{
	unsigned short sum = 0, len = 0, i = 0;

	len = length >> 1;  //length is in byte unit;

	for( i=0; i< len; i++ )
		sum += buf[i];

	return sum;
}

static unsigned int caculate_check_sum_u32( unsigned int * buf, unsigned int length )
{
	unsigned int sum = 0, len = 0, i = 0;

	len = length >> 2;  //length is in byte unit;

	for( i=0; i< len; i++ )
		sum += buf[i];

	return sum;
}

static unsigned short caculate_check_sum_u816( unsigned char * buf, unsigned int length )
{
	unsigned int i = 0;
	unsigned short sum = 0;
	for( i = 0; i < length; i++ )
	    sum += buf[i];

	return sum;
}
static unsigned int caculate_check_sum_ex( const unsigned char * buf, unsigned int length )
{
	unsigned int k;
	unsigned int combChk = 0;
	unsigned short check = 0, checkEx = 0;

	for(k = 0; k < length; k++)
	{
		check += buf[k];
		checkEx += (unsigned short)( k * buf[k] );
	}
	combChk = (checkEx<<16)|check;

	return combChk;
}

/*************************************************************************************/
#endif