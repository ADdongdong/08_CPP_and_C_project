#include <iostream>
using namespace std;


//定义小方块结构体
struct wd{
	int l, r, t, b;
};

int main(){
	wd a, b, t;
	cin >> a.l >> a.r >> a.t>> a.b;
	cin >> b.l >> b.r >> b.t>> b.b;
	//计算阴影部分的数据，我先假装有阴影部分
	t.l = max(a.l, b.l);
	t.r = min(a.r, b.r);
	t.t = max(a.t, b.t);
	t.b = min(a.b, b.b);
	//定义阴影部分的面积
	int s = 0;
	if (t.l >= t.r || t.t >= t.b){
		//确实a和b没有相交，没有阴影部分
		s = 0;
	}else{
		//计算阴影部分的面积
		s = ((t.r - t.l) * (t.b - t.t));
	}
	cout << s << endl;
	return 0;
}
