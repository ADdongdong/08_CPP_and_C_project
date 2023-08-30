#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    //声明变量与初始化
    string s1, s2;
    //输入数据
    /*
    1, 2, 3, 6
    0, 1, 2, 3
    */
    cin >> s1 >> s2;
    //定义数组
    int a[100] = {}, b[100] = {}; 

    
    //减法
    /*
    if (si < s2 || s1.size() < s2.size()) {
        cout << "-" ;
        //交换a，b,还是修改为大减小
        string t = s1;
        s1 = s2;
        s2 = t;
    }
    */
    int len = s1.size();
    for (int i = 0, j = s1.size() - 1; j>=0; j--, i++) {
        a[i] = s1[j] - '0';
    }
    /*
    for (int i = 0; i <= len - 1; i++) {
        a[len - 1 - i] = s1[i] - '0';
    }
    */

    len = s2.size();
    for (int i = 0, j = len-1; j >= 0; i++, j--) {
        b[i] = s2[j] - '0';
    }

    //按位暴力相加
    //最终遍历到最大的那一位的末尾
    len = max(s1.size(), s2.size());
    for (int i = 0; i < len; i++) {
        a[i] += b[i];
    }
    for (int i = 0; i < len; i++) {
        a[i+1] ++;
        a[i] %= 10;
    }
        /*
        if(a[i] < 0) {
            //减法不够减，向前一位借位借位
            a[i+1]--;
            a[i] += 10;
        }
        */
    

    //遍历输出，如果最终两位相加结果大于len,最终要多遍历一位
    //如何判断，倒叙遍历，遇到第一个不为0的数就是最高位
    int flag = 0;
    for (int i = 99; i >= 0; i-- ) {
        if (a[i] != 0 && flag == 0) {
            flag = 1;
        }
        //当flags为1开始输出
        if (flag == 1) {
            cout << a[i];
        }
    }

    if (flag == 0) {
        cout << 0 << endl;
    }
    cout << endl;

    return 0;
}
