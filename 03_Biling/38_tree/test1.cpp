#include <iostream>

using namespace std;

struct treenode{
	int val;
	treenode* lchild;//这个指针保存的是这个结点的左孩子的地址
	treenode* rchild;//这个指针保存的是这个结点的右孩子的地址
};

//生成一个新结点
treenode* newNode(int data){
	//newNode(10);
	treenode* Node = new treenode;//创建一个新结点，并且返回这个结点的地址
	Node->val = data;
	Node->lchild = NULL;
	Node->rchild = NULL;
	return Node;
}

//使用先序遍历来创建一个二叉树了
void pre_creat(treenode* &tree){
	//传引用，可以被改变
	cout << "请输入数字:" << endl;
	int data;
	cin >> data;
	if(data == 0){
		tree = NULL;
	}else{
		//遍历根
		treenode* node = newNode(data);
		tree = node;
		//遍历左子树
		pre_creat(tree->lchild);
		//遍历右子树
		pre_creat(tree->rchild);
	}
}

//二叉树的先序遍历
//递归
void pre_travaersal(treenode* tree){
	if (tree == NULL) return;
	/*return 两个作用
	 * 1.返回一个值
	 * 2.结束这个函数，就在return这个位置
	 */
	cout << tree->val << " ";
	pre_travaersal(tree->lchild);
	pre_travaersal(tree->rchild);
}



int main(){
	treenode* T = NULL;
	pre_creat(T);
	cout << "先序遍历的结果：" <<endl;
	pre_travaersal(T);
	return 0;
}
