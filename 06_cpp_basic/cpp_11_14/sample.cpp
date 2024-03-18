#include <iostream>
#include <bitset>

using namespace std;

// 01 sample: Variadic Templates
namespace adong01{
void print() {
}

// 定义递归函数模板
template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    cout << firstArg << endl;
    print(args...);
}

/*
template <typename... Types>
void print(const Types&... args) {
    cout << firstArg << endl;
    print(args...);
}
*/
void test() {
    // 直接传入参数，不用声明参数的类型，模板会根据传入的参数自动生成
    print(7.5, "hello", bitset<16>(377), 42);
}
};

namespace adong02{
void print(std::initializer_list<int> vals) {
    for (auto p = vals.begin(); p != vals.end(); ++p) {
        std::cout << *p << "\n";
    }
}

void test() {
    print({1,2,3,4,5,6,7});
}
};

namespace adong03{
class Foo {
public:
    Foo(int i):_i(i){}
    Foo()=default; // 和上一个构造函数并存
    Foo(const Foo& x):_i(x._i){} // copy cotr 拷贝构造函数
    // ! Foo(const Foo&)=default; // 上面已经定义了一个copy cotr了，这里就不能让编译器再生成默认的了
    // ! Foo(const Foo&)=delete;// 报错

    Foo& operator=(const Foo& x) {_i= x._i; return *this;}
    // !Foo& operator=(const Foo& x) = default; // Error
    // !Foo& operator=(const Foo& x) = delete; // Error
    // !void func1() = default;// 普通函数是没有default版本的
    void func2() = delete; // 语法通过,表示我不用这个函数，但是一般不会这么用
    // ! ~Foo() = delete;
    ~Foo() = default;
private:
    int _i;
};
}

namespace adong04{
    void testfunc1() {
        int id = 0;
        auto f = [id]() mutable {
            cout << "id:" << id << endl;
            ++id;// OK
        };

        id = 42;
        f();
        f();
        f();
        cout << id << endl;
    }

    void testfunc2() {
        int id = 0;
        auto f =[&id](int param) {
            cout << "id:" << id << "param:" << param<< endl;
            ++id; ++param;
        };
        id = 42;
        f(7);
        f(7);
        f(7);
        cout << id << endl;
    }
};

namespace adong05{

};


int main() {
    adong04::testfunc2();
    return 0;
}
