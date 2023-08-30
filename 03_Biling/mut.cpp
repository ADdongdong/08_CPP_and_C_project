#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    string s1, s2;
    int a[405] = {}, b[405] = {}, c[100] = {};
    cin >> s1 >> s2;
    int len = s1.size();
    for (int i = 0; i <=  len -1; i++) {
        a[len - i - 1] = s1[i] - '0';
    }

    len = s2.size();
    for (int i = 0; i <= len -1; i++) {
        b[len - i -1] = s2[i] - '0';
    }

    //进行乘法运算
    for (int i = 0; i < s2.size(); i++) {
        for (int j = 0; j < s1.size(); j++) { 
            //这里的c[i + j]就包含了每次相加往前错一位
            c[i + j] += a[j] * b[i];
        }
    }

    len = s1.size() + s2.size();
    for (int i = 0; i < len; i++) {
        if (c[i] >= 10) {
            //只要大于10就进位，如果是120，那就往上一位进位12位
            c[i+1] += c[i] / 10;
            c[i] %= 10;
        }
    }

    //输出
    while (c[len-1] ==0 && len >0){
        len--;
    }

    for(int i = len-1; i>=0; i--) {
        cout << c[i];
    }
    cout << endl;
    
    return 0;
}
