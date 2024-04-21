#include <iostream>
#include <string>
#include <string_view>

using namespace std;

string_view getString()
{
    string s = "whl哈哈哈哈";
    return string_view(s);
}

int main()
{
    string_view res = getString();
    cout << res << endl;
}