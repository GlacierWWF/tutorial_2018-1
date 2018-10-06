#include <iostream>
#include <cstdio>
#include <cstdlib> 
using namespace std;

int main ()
{    
	unsigned short a=0,b=0,c=0,d=0; 
        int n;    
	cin>>n;   
	unsigned int *ip=new unsigned int[n];     
	for (int i = 0; i < n; i++)   
	{         
		cin>>a;
		cin.get();
		cin>>b;
		cin.get();
		cin>>c;
		cin.get();
		cin>>d;
		ip[i]=(a<<24)+(b<<16)+(c<<8)+d; 
	}        
	unsigned int ziw=~0;  
	unsigned int max=ip[0];     
	for(int i=0;i<n;i++)    
	{           
		unsigned int k=ip[i]^max;       
		while (k)          
		{           
			ziw&=~(k|(k-1));     
			k=k&(k-1);            
		}       
	}   
	;
	unsigned int a2,b2,c2,d2,a3,b3,c3,d3; 
	unsigned int min=max&ziw;
	d2=min%(1<<8);
	min>>= 8;    
	c2=min%(1<<8);  
	min>>= 8;   
	b2=min%(1<<8);  
	min>>= 8;   
	a2=min;    
	cout<<a2<<'.'<<b2<<'.'<<c2<<'.'<<d2<<endl;
	d3=ziw%(1<<8);
	ziw>>= 8;    
	c3=ziw%(1<<8);  
	ziw>>= 8;   
	b3=ziw%(1<<8);  
	ziw>>= 8;   
	a3=ziw;    
	cout<<a3<<'.'<<b3<<'.'<<c3<<'.'<<d3<<endl;
	return 0;
} 

