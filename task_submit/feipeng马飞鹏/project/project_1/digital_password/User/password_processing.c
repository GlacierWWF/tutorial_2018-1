/*****************************************************************************
*                                                                            *
*  @file     password_processing.c                                           *
*  @brief    This file contains the funtion to process the password      		 *
*                                                                            *
*  @author   Feipeng Ma                                                      *
*  @email    767102280@qq.com                                                *
*  @version  1.0.0                                                           *
*  @date     2018/10/26                                                      *                     
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/10/19 | 1.0.0   | Feipeng Ma      | Create file                      *
*----------------------------------------------------------------------------*
*  2018/10/19 | 1.0.1   | Feipeng Ma      | add the function                 *
*----------------------------------------------------------------------------*
*  2018/10/26 | 1.0.2   | Feipeng Ma      | add the function          			 *
*****************************************************************************/

#include "password_processing.h"
extern volatile uint32_t rtime;

int rand_num(void)
{
	
	int out1,out2,out;
	srand(rtime);
	out1 = rand()%10;
	delay_ms(2);
	srand(rtime+100);
	out2 = rand()%10;
	out = (out1+out2)/2;
	return out;
}
void break_password(int *digital,int *digital_1,int *digital_2)
{
	int i;
	int k=2;
	for(i=0;i<7;i++)
	{
		if(digital[i]==1)
		{
			k=rand_num();
//		printf("%d\n",k);
			delay_ms(1);
			if(k<=4)
			{
				digital_1[i]=1;
				digital_2[i]=0;
			}
			else
			{
				digital_1[i]=0;
				digital_2[i]=1;
			}
		
		}
		else
		{
			digital_1[i]=0;
			digital_2[i]=0;
		}

	}
	
}

