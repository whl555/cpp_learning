#include <iostream>
#include <optional>

using namespace std;


struct Out
{
    string out1{""};
    string out2{""};
};

pair<bool, Out> func(const string &in)
{
    Out o;
    if (in.size() == 0)
        return make_pair(false, o);
    o.out1 = "hello";
    o.out2 = "world";
    return make_pair(true, o);
}

// std::nullopt 是 C++ 17 中提供的没有值的 optional 的表达形式，等同于 { } 。
optional<Out> func2(const string &in)
{
    Out o;
    if (in.size() == 0)
        return nullopt;
    o.out1 = "hello";
    o.out2 = "world";
    return { o };
}

int main()
{
    auto [status, output] = func("hi");
    if (status)
    {
        cout << output.out1 << ", " << output.out2 << endl;
    }

    auto res = func2("hi");
    if (res.has_value()) {
        cout << res.value().out1 << ", " << res.value().out2 << endl;
    }

    return 0;
}