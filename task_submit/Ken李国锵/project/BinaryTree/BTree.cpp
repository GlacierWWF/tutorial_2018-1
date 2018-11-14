#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

typedef struct Btree
{
		int value;
		struct Btree *lchild;
		struct Btree *rchild;
}Btree;

//前序递归建立二叉树
//num -- 前序序列
//index -- 下标
Btree *CreateBtree(Btree *node,int *num, int& index)
{
		if(num[index] == 0)
				return NULL;
		else
		{
				node = new Btree;
				node -> value = num[index];
				node -> lchild = CreateBtree(node->lchild, num, ++index);
				node -> rchild = CreateBtree(node->rchild, num, ++index);
		}
		return node;
}

void preOrder(BTree * root)
{
		if(root == NULL)
				return;
		cout << root -> value << " ";
		preOrder(root -> lchild);
		preOrder(root -> rchild);
}

void inOrder(BTree * root)
{
		if(root == NULL)
				return;
		inOrder(root -> lchild);
		cout << root -> value << " ";
		inOrder(root -> rchild);
}

void postOrder(BTree * root)
{
		if(root == NULL)
				return;
		postOrder(root -> lchild);
		postOrder(root -> rchild);
		cout << root -> value << " ";
}

int getdepth(BTree *root)
{
		if(root == NULL)
				return 0;
		int lchild_depth = getdepth(root -> lchild);
		int rchild_depth = getdepth(root -> rchild);
		return max(lchild_depth, rchild_depth) + 1;
}

int getleaves(BTree *root)
{
		if(root == NULL)
				return 0;
		if(root -> lchild == NULL && root -> rchild == NULL)
				return 1;
		return 1 + getleaves(root -> lchild) + getleaves(root -> rchild);
}

void print(BTree *root, int h)
{
		if(root != NULL)
		{
				print(root -> rchild, h+1);
				for (int i = 0; i<h; i++)
						cout << " ";
				cout << root -> value;
				print(root -> lchild, h+1);
		}
		cout << endl;
}

int main()
{
		int num[] = {1,2,4,8,0,0,9,0,0,5,10,0,0,11,0,0,3,6,12,0,0,13,0,0,7,14,0,0,15,0,0};
		BTree *root = NULL;
		int index = 0;
		root = CreateBTree(root, num, index);

		cout << "preorder" << endl;
		preOrder(root);
		cout << endl;

		cout << "inOrder" << endl;
		inOrder(root);
		cout << endl;

		cout << "postOrder" << endl;
		postOrder(root);
		cout << endl << endl;

		cout << "shape of BTREE" << endl;
		print(root,1);

		return 0;
}
