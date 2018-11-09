#include<iostream>
#include<stack>
#include<queue>
using namespace std;

// 设置二叉树结构
struct BiNode
{
        char data;
        BiNode* left;
        BiNode* right;
};

/**i
 * @brief	Create a binary tree in a pre-ordered manner
 * 
 * @return	Pointer to the binary tree node
 */
BiNode* CreateBiTree()
{
	BiNode* root;
	char data;
	cin >> data;

	if(data == '!')  // 输入！时表明该节点为空
		return NULL;

	root = new BiNode;
	root->data = data;
	
	root->left = CreateBiTree();
	root->right = CreateBiTree();

	return root;
}


/**
 * @brief	Get the hight of the binary tree
 *
 * @param	Pointer to the binary tree node
 * @return	The hight of the binary tree
 */
int getHight(BiNode* root)
{
	if(root == NULL)
		return 0;

	int leftHight = getHight(root->left);
	int rightHight = getHight(root->right);

	return leftHight > rightHight ? leftHight+1 : rightHight+1 ;
}


/**
 * @brief	Print the binary tree in a pre-ordered manner
 *
 * @param	Pointer to the binary tree
 * 
 */
void PreOrder(BiNode* root)
{
	if(root == NULL)
		return ;

	stack<BiNode*> NodeStack;
	NodeStack.push(root);

	while(!NodeStack.empty())
	{
		BiNode* node = NodeStack.top();
		NodeStack.pop();

		cout << node->data << " ";

		if(node->right)
			NodeStack.push(node->right);
		if(node->left)
			NodeStack.push(node->left);

	}
	
}


/**
 * @brief       Print the binary tree in a in-ordered manner
 *
 * @param       Pointer to the binary tree
 * 
 */

void InOrder(BiNode* root)
{
	if(root == NULL)
		return;

	stack<BiNode*> NodeStack;
	BiNode* node = root;

	while(node != NULL || !NodeStack.empty())
	{
		if(node != NULL)
		{
			NodeStack.push(node);
			node = node->left;
		}
		else
		{
			node = NodeStack.top();
			NodeStack.pop();

			cout << node->data << " " ;

			node = node->right;
		}
	}

}

/**
 *
 * @brief       用层次遍历的方式打印二叉树
 *
 * @param       Pointer to the binary tree
 * 
 */

void LevelOrder(BiNode* root)
{
	if(root == NULL)
		return;

	queue<BiNode*> nodeQueue;
	nodeQueue.push(root);

	while(!nodeQueue.empty())
	{
		BiNode* node = nodeQueue.front();
		nodeQueue.pop();

		cout << node->data << " ";

		if(node->left)
			nodeQueue.push(node->left);
		if(node->right)
			nodeQueue.push(node->right);
	}

}


