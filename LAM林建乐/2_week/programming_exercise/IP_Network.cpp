#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int trans(string con)
{
	int i=0, point=0, n=0, iIP;
	//string con = "192.168.0.2";
	while(i<3)
	{
		point = con.find(".",point+1);
      		if(point==3)
		{n=4;}
		if(point==7)
		{n=8;}
		if(point==11)
		{n=12;}
		while(point != 3 ||point != 7 ||point != 11)
		{
			con.insert(n, "0");
			n++;
		}
		con.erase(".");
		i++;
	}
	stringstream ss;
	ss << con;
	ss >> iIP;
	int IPs[4];
	IPs[0]=iIP/1000000000;
	IPs[1]=iIP/1000000-iIP0*1000;
	IPs[2]=iIP/1000-iIP0*1000000-iIP1*1000;
	IPs[3]=iIP-iIP0-iIP1-iIP2;
	return IPs;
}

