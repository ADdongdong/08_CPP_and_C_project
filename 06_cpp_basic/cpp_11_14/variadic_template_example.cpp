#include <iostream>
#include <bitset>

using namespace std;

namespace adong01{

// 定义一个参数为空的printx
void printx() {
}

template <typename T, typename... types>
void printx(const T& first, const types&... args){
    //处理第一个参数
    cout << first <<endl;
    printx(args...);
}

// 再写一个版本，和上一个版本同时调用，实验会调用哪个版本的
template <typename... types>
void printx(const types&... args) {
     cout << "using printx(const types&... args);" << endl;
}

void test() {
    printx(7.5, "hello", bitset<16>(377), 42);
}

};


namespace adong02{
// 这个例子使用varidic template 来模拟c中的printf
void printf(const char* s) {
    while(*s) {
        if (*s == '%' && *(++s)!= '%')
            throw std::runtime_error("invalid format string:missing argument");
        cout << *s++;
    }
}

template <typename T, typename... Args>
void printf(const char* s, T value, Args... args) {
    while(*s) {
        if (*s == '%' && *(++s) != '%') {
            cout << value;
            printf(++s, args...);//
            return;
        }
        cout << *s++;
    }
    throw std::logic_error("extra arguments provided to printf");
}

void test() {
int *pi = new int;
printf("%d %s %p %f\n",
       15,
       "This is Ace.",
       pi,
       3.1415926);
}

};

namespace adong03{
// 重点为：递归继承
template<typename... Values> class tuple;
template<>class tuple<>{};

template<typename Head, typename... Tail>
class tuple<Head, Tail...>:private tuple<Tail...> {
    typedef tuple<Tail...> inherited;
protected:
    Head m_head;
public:
    tuple(){}
    tuple(Head v, Tail... vtail):m_head(v),inherited(vtail...){}

    //typename Head::type head(){return m_head;}
    // 这里用到了decltype()来获取Head这种类型的返回值（head)为一会要传入模板的类型
    //auto head()->decltype(m_head){return m_head;}
    Head head() {return m_head;}

    inherited& tail() {return *this;}

};

void test() {
    tuple<int, float, string> t(41, 6.3, "nico");
    cout << sizeof(t) << endl;
    cout << t.head() << endl;
    cout << t.tail().head() << endl;
    cout << t.tail().tail().head() <<endl;
}

};

namespace adong04{
template<typename... Values> class tup;
template<>class tup<>{};

template<typename Head, typename... Tail>
class tup<Head, Tail...>{
    typedef tup<Tail...> composited;
protected:
    composited m_tail;
    Head m_head;
public:
    tup() {}
    tup(Head v, Tail... vtail):m_tail(vtail...), m_head(v) {}
    Head head() {return m_head;}
    composited& tail() {return m_tail;}
};

void test() {
    tup<int, float, string> it1(41, 6.3, "hello");
    cout << sizeof(it1) << endl;
    cout << it1.head() << endl;
    cout << it1.tail().head() << endl;
    cout << it1.tail().tail().head() << endl;
}
};


int main() {
    adong04::test();
    return 0;
}
