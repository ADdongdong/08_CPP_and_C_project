#include <iostream>

using namespace std;

struct BinTree{
	int data;
	BinTree* left;
	BinTree* right;
};

//递归法找最小值点
BinTree* FindMin(BinTree* BST){
	BinTree* Node = BST;
	if (Node->left != NULL) return FindMin(Node->left);
	return Node;
}

//定义中序遍历二叉搜索树
void mid_travaersal(BinTree* tree){
	if (tree == NULL) return;
	mid_travaersal(tree->left);
	cout << tree->data << endl;
	mid_travaersal(tree->right);
}

//递归法找最大值结点
BinTree* FindMax(BinTree* BST){
	BinTree* Node = BST;
	//如果这个结点有有子树，就往右边寻找，直到找到最右边的节点
	if (Node->right != NULL) return FindMax(Node->right);
	//返回最大的节点
	return Node;
}

//二叉搜索树找到值为val的结点，并返回这个结点的地址
BinTree* Find(BinTree* BST, int key){
	BinTree* Node = BST;
	if (Node == NULL){
		return NULL; 
	}
	//如果找到了这个结点的值
	if (Node->data == key){
		return Node;
	} else if(Node->data > key){
	//如果当前结点的值大于key,那就要往当前结点的左边找
		return Find(Node->left, key);
	} else {
	//否则，当前结点的值就是小于key值，就要往当前结点的右子树找
		return Find(Node->right, key);
	}
}

//创建二叉树/搜索二叉树插入结点
void Insert(int val, BinTree* &BST){
	if(BST == NULL){
		BinTree* node = new BinTree;	
		node->data = val;
		node->left = NULL;
		node->right = NULL;

		BST = node;
	} else {
		if (val > BST->data){
			//如果，要插入的这个数字大于当前结点，那就要插入到
			//当前结点的右子树上
			Insert(val ,BST->right);
		} else if(val < BST->data){
			//如果，当前节点小于要插入的key
			//那就要插入到当前结点的左子树
			Insert(val, BST->left);
		}
	}
}

//二叉搜索树的删除
BinTree* Delete(int key, BinTree* BST){
	BinTree* Node = NULL;
	if (BST == NULL){
		return BST;//如果未找到为key的节点，则返回NULL,没有执行任何操作
	} else if(key < BST->data){
		//如果要删除的结点小于当前结点的data
		//那么就要往当前结点的左边去找
		BST->left = Delete(key, BST->left);
	} else if(key > BST->data){
		BST->right = Delete(key, BST->right);
	} else if(key == BST->data){
		//找到要删除的结点了
		if(BST->left && BST->right){
			//待删除的结点有两个子节点
			//取待删除节点的右子树找一个最小的结点，
			//用来代替这个结点的位置
			Node = FindMin(BST->right);
			BST->data = Node->data;
			//删掉那个代替被删除节点的结点
			BST->right = Delete(BST->data, BST->right);
		}else{
			//待删除结点只有一个活着没有子节点（子树）
			if (BST->left == NULL){
				//只有右子树，或者没有孩子
				//也就是说，只要左子树为NULL，无论右边有没有子树
				BST = BST->right;
			} else if( BST->right == NULL){
				//只有左子树的情况
				//那就让右子树最上面的结点来代替这个结点
				BST = BST->left;
			}
		}
	}
	return BST;
}

int main(){
	
	//创建一个搜索二叉树
	BinTree* T = NULL;

	//插入数据
	int val;

	for(int i = 1; i < 10; i++)	{
		cout << "请输入数据：";
		cin >> val;
		Insert(val, T);
	}

	cout << endl;
	//中序遍历数据
	mid_travaersal(T);

	return 0;
}
