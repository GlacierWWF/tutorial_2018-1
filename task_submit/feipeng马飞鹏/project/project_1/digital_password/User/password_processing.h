/******************************************************************************
*                                                                             *
*  @file    password_processing.h                                             *
*  @brief   This header file contains some definition to process the password *
*                                                                             *
*  @author   Feipeng Ma                                                       *
*  @email    767102280@qq.com                                                 *
*  @version  1.0.1                                                            *
*  @date     2018/10/19                                                       *                     
*                                                                             *
*---------------------------------------------------------------------------- *
*  Remark         : Description                                               *
*---------------------------------------------------------------------------- *
*  Change History :                                                           *
*  <Date>     | <Version> | <Author>       | <Description>                    *
*---------------------------------------------------------------------------- *
*  2018/10/19 | 1.0.0   | Feipeng Ma      | Create file                       *
*---------------------------------------------------------------------------- *
*  2018/10/19 | 1.0.1   | Feipeng Ma      | add the function                  *
*---------------------------------------------------------------------------- *   
******************************************************************************/

#ifndef __PASSWORD_H
#define __PASSWORD_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "stm32f10x.h"
#include "display_num.h"

int rand_num(void);
void break_password(int *digital,int *digital_1,int *digital_2);




#endif

