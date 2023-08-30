#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main() {
    char s[500];//定义被除数
    //string s; s.size();
    //b是除数
    //a用来保存s转化为整数的结果
    //ans 结果
    //x 每一次计算出来的商
    long long b,a[500], ans[500], x = 0;
    cin >> s >> b;
    
    //转换为整数
    int len = strlen(s);

    //转换为整数，不需要翻转的
    for (int i = 0; i < len; i++) {
        a[i] = s[i] - '0';
    }

    //计算
    for (int i = 0; i < len; i++) {
        //求商
        // （40 * 10 + 8） /64 = 商
        ans[i] = (x * 10 + a[i]) / b;
        // 求余数并保存下来
        x = (x * 10 + a[i]) %b;
    }

    //输出
    int flag = 0;
    for (int i = 0; i < len; i++ ){
        if (flag == 0 && ans[i] != 0) {
            flag  = 1;
        }

        if (flag == 1) {
            cout << ans[i];
        }
    }

    cout << endl;




}