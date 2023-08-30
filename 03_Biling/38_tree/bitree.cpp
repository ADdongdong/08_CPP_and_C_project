#include <iostream>

using namespace std;

struct treenode{
	int data;
	treenode* lchild;//指向当前结点左孩子的结点
	treenode* rchild;//指向当前孩子右孩子的结点
};

//生成一个新结点
treenode* newNode(int val){
	treenode* Node = new treenode;
	Node->data = val;
	Node->lchild = NULL;
	Node->rchild = NULL;
	return Node;
}

//二叉树的先序遍历
void pre_travaersal(treenode* tree){
	if (tree == NULL) return;
	cout << tree->data << " ";
	pre_travaersal(tree->lchild);
	pre_travaersal(tree->rchild);
}

//使用先序遍历的方式创建一个二叉树
void pre_create(treenode* &tree){
	cout << "请输入数字：" << endl;
	int data;
	cin >> data;
	if (data == 0){
		tree = NULL;
	}else {
		treenode* node = newNode(data);
		tree = node;
		pre_create(tree->lchild);
		pre_create(tree->rchild);
	}
}

int main(){
	treenode* T = NULL;
	pre_create(T);
	pre_travaersal(T);

	return 0;
}
