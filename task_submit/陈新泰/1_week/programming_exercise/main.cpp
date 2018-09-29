
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class mirpal
{
    public:
        mirpal(const string& ifn="test.txt",const string& ofn="of.txt");//初始化文件指针
		~mirpal();
        void output();  //将结果打印到文件和屏幕
    private:
        ifstream inf;//输入文件
        ofstream outf;//输出文件
		
        bool decimir(const string& str);//判断是否是mirrored string
        bool decipal(const string& str);//判断是否是palindrome
};


int main()
{
    //输入；
    string ifn,ofn;
    cout<<"请输入所要读取的文件名：";
    cin>>ifn;
	cout<<"请输入所要输出的文件名（如：\"outputfile.txt\"):";
    cin>>ofn;
    //处理；
    mirpal dec1(ifn,ofn);
	//mirpal dec1;
    //输出；
    dec1.output();
	return 0;
}

mirpal::mirpal(const string& ifn,const string& ofn):inf(ifn),outf(ofn)//只能使用初始化列表
{
    //cout<<inf.is_open()<<outf.is_open()<<endl;
}

mirpal::~mirpal()
{
	if(inf.is_open())
	inf.close();
	if(outf.is_open())
	outf.close();
}

void mirpal::output()
{
    //逐行判断
	string s;
    while(getline(inf,s))
    {
        bool d1=decimir(s);
		bool d2=decipal(s);//判断	

        if(d1&&d2)
        {
            outf<<s<<" -- is a mirrored palindrome.\n";
			cout<<s<<" -- is a mirrored palindrome.\n";
        }
        else if(d1)
        {
            outf<<s<<" -- is a mirrored string.\n";
			cout<<s<<" -- is a mirrored string.\n";
        }
        else if(d2)
        {
            outf<<s<<" -- is a regular palindrome.\n";
			cout<<s<<" -- is a regular palindrome.\n";
        }
        else
        {
            outf<<s<<" -- is not a palindrome.\n";
			cout<<s<<" -- is not a palindrome.\n";
        }
    }
}

bool mirpal::decimir(const string& str)
{
    string flag1="EJLSZ235AHIMOTUVWXY8";
	string flag2="3LJ25SEZAHIMOTUVWXY8";
    int len=str.length();
    bool f1=true; //是否为mirrored string的标志；

	for(int i=0;i<len/2;i++)
    {
	    int j;
	    bool f2=false;  //判断是否符合flag；
	    for(j=0;j<20;j++)
	    {
			if(str[i]==flag1[j]&&str[len-i-1]==flag2[j])
			{   
				f2=true;
				break;
			}
	    }
	    if(f2==true)
		continue;
        
        f1=false;//当不符合上面的条件时退出；
        break;
    }
    return f1;
}

bool mirpal::decipal(const string& str)
{
    bool f=true;
	int len=str.length();
    for(int i=0;i<len/2;i++)
    {
        if(str[i]!=str[len-1-i])
        {
            f=false;
            break;
        }
    }
    return f;
}



