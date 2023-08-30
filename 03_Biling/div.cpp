#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    char s[500];//定义被除数
    //定义除数b, a用来保存整数化后的被除数
    //ans用来保存最后的结果
    //x用来保存上一次的余数
    long long b, a[500], ans[500], x = 0;
    cin >> s >> b;
    //除法不需要倒置
    int len = strlen(s);
    
    //转换为整数
    for (int i = 0; i < len; i++){
        a[i] = s[i] - '0';
    }

    //计算
    for (int i = 0; i < len; i++) {
        //商
        ans[i] = (x * 10 + a[i]) / b;
        //计算余数并保存
        x = (x * 10 + a[i]) % b;
    }

    //先导0问题
    // int start = 0;
    // while (ans[start] == 0 && start < len) {
    //     start++;
    // }

    // for (int i = start; i<len;i++) {
    //     cout << ans[i];
    // }
    // cout << endl;

    int flag = 0;
    for (int i = 0; i < len; i++) {
        if (flag == 0 && ans[i] != 0) {
            flag = 1;
        }

        if (flag == 1) {
            cout << ans[i];
        }
    }

    cout << endl;
    
    return 0;
}
