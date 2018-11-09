#include"BiTree.cpp"
#include<iostream>

using namespace std;


int main()
{
	BiNode* tree = CreateBiTree();

	cout << "hight: " << getHight(tree) << endl;

	cout << "PreOrder: " << endl;
	PreOrder(tree);
	cout << endl;

	cout << "InOrder: " << endl;
	InOrder(tree);
	cout << endl;

	cout << "LevelOrder: " << endl ;
	LevelOrder(tree);
	cout << endl;

	return 0;
}



