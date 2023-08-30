#include <iostream>

using namespace std;

const int V = 100;

int n,m,ans,e[V][V];
bool visited[V];

void dfs(int x, int len) {
	int i;
	visited[x] = true;
	// 如果当前路径比已经记录的最长的路径还要长
	// 那就更新最长的路径
	if (len > ans) ans = len;
	for (i = 1; i <= n; i++) {
		// 如果顶点i尚未被访问，并且，与当前顶点x右边链接
		// 这里定义没有边链接是,边权值为-1
		if ((!visited[i]) && (e[x][i] != -1)) {
			dfs(i, len+e[x][i]);
		}
	}
	//回溯时，将顶点标记为未访问
	visited[x] = false;
}

int main() {
	int i, j, a, b, c;
	cin >> n >> m; //输入n为顶点数，m为边数
	// 初始化邻接矩阵，所有元素为-1,表示都没有连接
	for (i = 1; i <= n; i++) {
		for (j = 1; j<=n;j++){
			e[i][j] = -1;
		}
	}
	// 循环输入边的信息，更新邻接矩阵
	for (i = 1; i <= m; i++) {
		cin >> a >> b >> c; //a起点，b重点，c边权值,如果权值为-1,代表未连接
		// 从a->b和从b->a的权值是一样的，因为这是无向图
		e[a][b] = c;
		e[b][a] = c;
	}
	
	// 初始化顶点访问列表，初始化为false，表示所有顶点都没有访问过
	for (i = 1; i <= n; i++) {
		visited[i] = false;
	}
	
	//初始化最长路径为0
	ans = 0;
	//开始进行深度优先遍历，寻找最长路径
	for (i = 1; i <= n; i++) {
		dfs(i, 0);
	}
	//输出结果
	cout << ans << endl;
	return 0;

}

