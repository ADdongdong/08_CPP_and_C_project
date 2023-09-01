#include <iostream>

using namespace std;

//定义函数判断是不是素数
bool is_prime(int num) {
	// 如果这个数小于1，则必然不是素数
	if (num <= 1) {
		return false;
	}

	// 从最小素数遍历到num, 如果，num,不能被2-num之间的数字分解，那就说明是素数
	// 反之，只要有一个数能分解num,说明num不是素数
	for (int i = 2; i * i <= num; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}


void goldbach_conjecture(int n) {
	if (n <= 2 || n % 2 != 0) {
		cout << "请输入一个大于2的偶数" << endl;
		return;
	}

	int smaller_prime = 2; //最小的素数是2，从2开始找起
	int larger_prime = n - smaller_prime; // 最大数肯定要从n-smaller_prime开始，
										  // 因为要保证这两个数的和是num

	//只要小数字小于大数字就继续循环
	while (smaller_prime <= larger_prime) {
		// 如果两个数都是素数，那么就证明了哥德巴赫猜想
		if (is_prime(smaller_prime) && is_prime(larger_prime)) {
			cout << n << "=" << smaller_prime << "+" << larger_prime << endl;
			return;
		}
		++smaller_prime;
		--larger_prime;
	}
	cout << "哥德巴赫猜想不满足：" << n<< endl;

}

int main(){
	int num;
	cout << "请输入一个大于2的数字：" << endl;
	cin >> num;

	// 哥德巴赫猜想，任何一个大于2的偶数都可以表示为两个素数之和
	goldbach_conjecture(num);

	return 0;
}
