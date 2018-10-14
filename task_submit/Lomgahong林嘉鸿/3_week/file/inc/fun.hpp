/*****************************************************************
 * @file	fun.hpp
 * @brief	This file void some functions used in this project
 * Details.
 *
 * @version	1.0.1
 * @author	Lomgahong
 * @email	1073097404@qq.com
 *
 * ----------------------------------------------------------------
 *  Change History:
 *  <Date>	|<Version>	|<Author>	|<Description>
 *  ---------------------------------------------------------------
 *  2018/10/14	|1.0.1		|Lomgahong	|Create file
 *
 *  ***************************************************************/

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


bool cmp(const Rect&,const Rect&);
int getnumber(Rect,Mat);
void transform(int*);

