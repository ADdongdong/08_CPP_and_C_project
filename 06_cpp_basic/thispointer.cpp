#include <iostream>

using namespace std;

//定义一个clase
class User{
	public:
		//定义构造函数，参数为name和age
		User(const string& name, int age):m_age(age), m_name(name){
			cout << "this:" << this << endl;
		}
		void print() {
			//this指针是隐式传入的
			cout << this->m_name << "," << this->m_age << endl;
		}
		/*
		 * 编译后
		 * void pointer(User* this) {
		 *		cout << this->m_name << "," << this->m_age << endl;
		 * }
		 */
	private:
		string m_name;
		int m_age;
};

void this_test() {
	User u1("张三", 9);
	cout << "&u1:" << &u1 << endl;
	User u2("李四", 10);
	cout << "&u2:" << &u2 << endl;
	u1.print();
	u2.print();
}

int main() {
	this_test();
}
