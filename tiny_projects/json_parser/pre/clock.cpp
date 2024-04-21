#include <iostream>
#include <string>
#include <string_view>
#include <chrono>

using namespace std;

class Timer
{
private:
    string str;
    chrono::high_resolution_clock::time_point start, end;

public:
    Timer(const string &s) : str(s)
    {
        start = chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = chrono::high_resolution_clock::now();
        chrono::milliseconds time = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << str << " time cost: " << (time.count()) * 0.001 << "s" << endl;
    }
};

void functionWithString(const std::string &string)
{
}

void functionWithString(const std::string_view &stringView)
{
}

int main()
{
    {
        Timer timer("string");
        for (int i = 0; i < 10000000; i++)
        {
            string s = "wuhaolei";
            // string a = s.substr(0, 2);
            // string b = s.substr(2, 6);
            functionWithString(s);
            functionWithString(s);
        }
    }

    {
        Timer timer("string_view");
        for (int i = 0; i < 10000000; i++)
        {
            const char *s = "wuhaolei";
            // string_view a = string_view(s, 2);
            // string_view b = string_view(s + 2, 6);
            string_view a = string_view(s);
            functionWithString(a);
            functionWithString(a);
        }
    }
}