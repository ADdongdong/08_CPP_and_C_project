#include <iostream>
using namespace std;

struct ele{
	int val;
	int abs;
}a[105];

void swap(ele *a, ele *b){
	ele t = *a;
	*a = *b;
	*b = t;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i<=n; i++){
		cin >> a[i].val;
		a[i].abs = a[i].val;
		if (a[i].val < 0) a[i].abs *= -1;
	}

	//选择排序
	for (int i = 1; i < n; i++){
		for (int j = i + 1; j <= n; j++) {
			if (a[i].abs < a[j].abs)
				swap(&a[i], &a[j]);
		}
	}
	for (int i = 1; i <= n; i++){
		cout << a[i].val << " ";
	}
	cout << endl;
	return 0;
}
