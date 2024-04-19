#include <iostream>
using namespace std;

/**
 * explicit禁止隐式类型转换
 */
class Book
{
public:
    Book(const string name, const int price = 100) : name_(name)
    {
        cout << "constructor invoke" << endl;
    }
    /*
    explicit Book(const string name, const int price = 100): name_(name) {
        cout << "constructor invoke" << endl;
    }*/

    ~Book()
    {
    }

    // 隐式转换创造了临时变量
    void isSame(const Book &book)
    {
        if (name_ == book.name_)
            cout << "the tow books are the same!" << endl;
        else
            cout << "the tow books are different!" << endl;
    }

private:
    string name_;
    int price_;
};

int main()
{
    Book a("a");
    a.isSame(string("b"));

    return 0;
}