/**************************************************************************** 
 * @file    Project1.1 ����������.											*
 * @brief   This file will show how to realize binary_tree manipulate.		*
 * @author	��ӱ�� fengyw8 													*
 * @version	1.0.0															*
 * @date	2018/11/10 														*
 ****************************************************************************/

/// System Headers
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

//---------------------------------------------------------------------------
// Definition of the struct Node
//---------------------------------------------------------------------------
/**
 * @brief	struct Node of binary tree
 */
struct Node
{
	int element;
	Node* left;
	Node* right;
	
	Node(int e=0);
	void push(int e);
	void preorder();
	void inorder();
	void postorder();
};
//----------------------------- 
/**
 * @brief	constructor of Node
 */
Node::Node(int e)
{
	element=e;
	left=NULL;
	right=NULL;
}


//---------------------------------------------------------------------------- 
// User-defined functions
//---------------------------------------------------------------------------- 
/**
 * @brief	function used to push a node into the binary search tree
 */
void Node::push(int e)
{
	if(e<element)
		if(left==NULL)
			left=new Node(e);
		else
			left->push(e);
	if(e>element)
		if(right==NULL)
			right=new Node(e);
		else
			right->push(e);
	return;
}
//--------------------------------------------------------------------------------------
/**
 * @brief	function used to traverse the binary tree in preorder and print the elements
 */
void Node::preorder()
{
	cout<<element<<" ";
	if(left!=NULL)
		left->preorder();
	if(right!=NULL)
		right->preorder();
}
//------------------------------------------------------------------------------------- 
/**
 * @brief	function used to traverse the binary tree in inorder and print the elements
 */
void Node::inorder()
{
	if(left!=NULL)
		left->inorder();
	cout<<element<<" ";
	if(right!=NULL)
		right->inorder();
}
//--------------------------------------------------------------------------------------- 
/**
 * @brief	function used to traverse the binary tree in postorder and print the elements
 */
void Node::postorder()
{
	if(left!=NULL)
		left->postorder();
	if(right!=NULL)
		right->postorder();
	cout<<element<<" ";
}


//---------------------------------------------------
//--------------------------------------------------- 
/**
 * @brief Queue_Manipulate Main Function
 *------------------------------------------------ 
 * @parameter			void
 *
 * @variable temp		temporary variable
 * @variable a		    queue used to store value 
 *
 * @return 				integer
 */
int main()
{
	//����һ������� 
	srand(time(NULL));
	int temp;
	cout<<"generate random number:"<<endl;
	temp=rand()%1000;
	cout<<temp<<" ";
	Node root(temp);
	for(int i=1;i<=9;i++)
	{
		temp=rand()%1000;
		cout<<temp<<" ";
		root.push(temp);
	}
	cout<<endl<<endl;
	//ǰ����� 
	cout<<"preorder:"<<endl;
	root.preorder();
	cout<<endl<<endl;
	//������� 
	cout<<"inorder:"<<endl;
	root.inorder();
	cout<<endl<<endl;
	//������� 
	cout<<"postorder:"<<endl;
	root.postorder();
	cout<<endl<<endl;
	return 0;
}
