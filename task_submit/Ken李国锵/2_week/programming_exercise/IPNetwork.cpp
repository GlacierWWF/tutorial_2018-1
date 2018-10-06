/***************************************
 * IPnetwork Programme
 * Author: Ken, Li Kwok Cheong         *
 * Version:1.0.0                       *
 * Date:2018.10.5                      *
 ***************************************/

#include<iostream>
#include<cstring>
#include<sstream>

using namespace std;

const int MAXN = 1005, INF = 0x3f3f3f3f;
const int NUM[9] = {255, 254, 252, 248, 240, 224, 192, 128, 0};

struct ip
{
		int n1, n2, n3, n4;

		bool operator<(const ip &another) const
		{
				if (n1 == another.n1)
						if (n2 == another.n2)
								if (n3 == another.n3)
										return n4 < another.n4;
								else
										return n3 < another.n3;
						else
								return n2 < another.n2;
				else
						return n1 < another.n1;
		}

		ip operator&(const ip &another) const
		{
				ip ans;
				ans.n1 = n1 & another.n1;
				ans.n2 = n2 & another.n2;
				ans.n3 = n3 & another.n3;
				ans.n4 = n4 & another.n4;
				return ans;
		}

		bool operator==(const ip &another) const
		{
				return (n1 == another.n1 && n2 == another.n2 && n3 == another.n3 && n4 == another.n4);
		}

		const ip &operator=(const ip &another)
		{
				n1 = another.n1;
				n2 = another.n2;
				n3 = another.n3;
				n4 = another.n4;
				return *this;
		}
};

int b;
ip n[MAXN];

int main()
{
		while (cin >> b)
		{
				cin.get();
				string buff;
				stringstream stream;
				ip minone, maxone;
				minone.n1 = minone.n2 = minone.n3 = minone.n4 = INF;
				maxone.n1 = maxone.n2 = maxone.n3 = maxone.n4 = 0;
				for (int i = 1; i <= b; i++)
				{
						getline(cin, buff);
						int len = buff.length();
						for (int j = 0; j < len; j++)
								if (buff[j] == '.') buff[j] = ' ';
						stream.str("");
						stream.clear();
						stream << buff;
						stream >> n[i].n1 >> n[i].n2 >> n[i].n3 >> n[i].n4;
						if (n[i] < minone) minone = n[i];
						if (maxone < n[i]) maxone = n[i];
				}

				ip mask;
				mask.n1 = mask.n2 = mask.n3 = mask.n4 = NUM[0];
				bool flag = false;
				for (int i = 0; i <= 8 && !flag; i++)
				{
						mask.n4 = NUM[i];
						if ((maxone & mask) == (minone & mask)) flag = true;
				}

				for (int i = 0; i <= 8 && !flag; i++)
				{
						mask.n3 = NUM[i];
						if ((maxone & mask) == (minone & mask)) flag = true;
				}
				for (int i = 0; i <= 8 && !flag; i++)
				{
						mask.n2 = NUM[i];
						if ((maxone & mask) == (minone & mask)) flag = true;
				}
				for (int i = 0; i <= 8 && !flag; i++)
				{
						mask.n1 = NUM[i];
						if ((maxone & mask) == (minone & mask)) flag = true;
				}
				ip ans = (minone & mask);
				cout << ans.n1 << "." << ans.n2 << "." << ans.n3 << "." << ans.n4 << endl;
				cout << mask.n1 << "." << mask.n2 << "." << mask.n3 << "." << mask.n4 << endl;
		}
		return 0;
}
