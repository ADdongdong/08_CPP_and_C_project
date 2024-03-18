#include <iostream>
#include <ctime>
#include <cstring>
#include <typeinfo>
#include <string>

using namespace std;

namespace test1{
    void process(int& i) {
        cout << "process(int&):" << i << endl;
    }

    void process(int&& i) {
        cout << "process(int&&):" << i << endl;
    }

    void forward(int&& i) {
        cout << "forward(int&&):" << i << ",";
        process(i);
    }

    void test(){
        int a = 0;
        process(a); // 传入左值
        process(1); // 传入右值
        process(move(a));// 强制将a使用move转换为右值
                        // 最终传入process的是右值
        forward(2); // 2在forward函数中赋值给变量i,i为左值，所以，给forward中process传入的是左值i
        forward(move(a)); // 和上面一样，

        //forward(a); // a 是左值，forward(int&&i);接受右值，报错
        const int& b = 1;
        //proecss(b); // 报错，没有proecss(const int&);这个函数
        //process(move(b)) // process(std::remove_reference<const int&>::type)
        // int& x(5);
        // process(move(x));// 报错
    }
};

namespace test2{

class Person{
private:
    std::string *name;
public:
    // Constructor
    Person(const std::string& n):name(new std::string(n)) {}

    // move Constructor
    Person(Person&& other) noexcept : name(nullptr) {
        cout << "Move constructor is callled" << std::endl;
        name = other.name;
        other.name = nullptr;  // 这里要确保原来指向这个资源的指针被设置为nullptr, 这样才不会出内存泄漏问题
    }

    // move assignment operator
    Person& operator=(Person&& other)noexcept{
        cout << "move assignment operator is called" << endl;
        if (this != &other) {
            delete name; // 释放当前对象name所指向的内存资源

            name = other.name;
            other.name = nullptr; // 这里要确保原来指向这个资源的指针被设置为nullptr, 这样才不会出内存泄漏问题
        }
        return *this;
    }

    // Destructor
    ~Person() {
        delete name;
    }

    // Display name
    void display() {
        if (name != nullptr) {
            std::cout << "Name: " << *name << endl;
        } else {
            cout << "Name is null" << endl;
        }
    }

};

void test() {
    Person person1("headong");
    person1.display();

    Person person2 = move(person1);// Using move constructor, move的作用将person1（左值）转换为右值
    person1.display();
    person2.display();

    Person person3("Lisa");
    person3.display();

    person3 = move(person2); // using move assignment operator
    person2.display();
    person3.display();

}

};

int main(){
    test2::test();
    return 0;
}
