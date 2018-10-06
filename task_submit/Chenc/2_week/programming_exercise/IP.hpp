/*Title:IP.hpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-10-04
*Version:1.0.0
*Abstract: A head file to describe IP class
*/
#pragma once
//#pragma comment( lib, "opencv_highgui343d.lib")
#define IP_HPP
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
class IP
{
public:
	int Bin[4][8];
	int Dec[4];

	IP();
	bool morethan(IP, IP);
	bool lessthan(IP, IP);
	void dec2bin(IP &);
	void bin2dec(IP &);
	void check(IP &, IP &);
};
