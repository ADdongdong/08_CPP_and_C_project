#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main() {
    string s1, s2;
    int a[400] = {}, b[400] = {}, c[400] = {};
    cin >> s1 >> s2;

    //顺序颠倒
    int len = s1.size();
    for (int i = 0; i < len-1; i++) {
        a[len - i -1] = s1[i] - '0';
    }

    len = s2.size();
    for (int i = 0; i < len-1; i++) {
        b[len - i - 1] = s2[i] - '0';
    }

    //1.直接暴力计算
    /*
    i    0 1 2
         1 2 3
         1 1 1
        --------
         1 2 3
       1 2 3
     1 2 3
     -----------
    */
    for (int i = 0; i < s2.size(); i++) {
        for (int j = 0; j < s1.size(); j++) {
            c[i + j] += a[j] * b[i];
        }
    }
    //2.处理特殊情况
    len = s1.size() + s2.size();
    for (int i = 0; i< len; i++){
        if (c[i] > 10) {
            c[i+1] += c[i]/10;
            c[i] %= 10;
        }
    }

    //输出
    while(c[len-1] == 0 && len > 0){
        len--;
    }

    for (int i = len -1; i >= 0; i--){
        cout << c[i];
    }
    cout << endl;
    return 0;


}