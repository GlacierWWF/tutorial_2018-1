#include<map>
#include<string>
#include<iostream>
using namespace std;


ostream& operator<<(ostream& out, const pair<string, int>& p)
{
  return out << p.first << "\t" << p.second;
}

int main() 
{
	  map<string, int> name_score_map;
	  name_score_map["ZhanSan"] = 90;
	  name_score_map["LiSi"] = 78;
	  name_score_map["WangWu"] = 91;
	  name_score_map["XiaoMin"] = 100;
	  map<string, int>::iterator iter = name_score_map.begin();
	  for (; iter != name_score_map.end(); iter++)
     	  {
	  	 cout << *iter << endl;
          }

  return 0;

}
