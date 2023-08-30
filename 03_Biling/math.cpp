#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    char s1[505];
    long long b, ans[505], x = 0, a[505], a_length;
    
    cin >> s1 >> b;//读入被除数， 除数

    a_length = strlen(s1); //最后运算的结果的位数不可能超过被除数
    for (int i = 0; i < a_length; i++) {
        //去0，出发不用倒装
        a[i] = s1[i] - '0'; //转换为整数
    }

    for (int i = 0; i < a_length; i++) {
        ans[i] = ((x * 10 + a[i])/b);
        x = ((x * 10 + a[i]) % b);
    }

    int start = 0;
    while (ans[start] == 0 && start < a_length) start++;//输出

    for (int i = start; i < a_length; i++) cout << ans[i];

    cout << endl;

    return 0;
}
