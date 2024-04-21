## Json 解析器

1. 使用 variant 容纳 parse_value 返回值类型
   官方文档说法
   > 类模板 std::variant 表示一个类型安全的联合体。std::variant 的一个实例在任意时刻要么保有其一个可选类型之一的值，要么在错误情况下无值
   > 如下代码中, Value 在运行时任意时刻只能为 Null、Bool 这些类型中的其中一种

```c++
using Value = std::variant<Null, Bool, Int, Float, String, Array, Object>;
```

2. 使用 optional 包装 parse_value 返回值
   官方文档说法
   > 类模板 std::optional 管理一个可选的容纳值，即可以存在也可以不存在的值。
   > 一种常见的 optional 使用情况是一个可能失败的函数的返回值。与其他手段，如 std::pair<T,bool> 相比， optional 良好地处理构造开销高昂的对象，并更加可读，因为它显式表达意图

- optional 包裹下的返回值, 如果发生异常, 返回值是空

参考: https://zhuanlan.zhihu.com/p/64985296

```c++
 auto parse_value() -> std::optional<Value>
```

3. 使用 string_view 展示 json 字符串
   string_view 只读, 效率要比 string 高, 原因是每个 string 都对应一份单独内存, 操作 string 会涉及频繁的内存变化

```c++
    struct JsonParser
    {
        std::string_view json_str;
    }
```

3. parse_value
   '{}'视为 json_object 处理;
   '[]'视为 json_array 处理;
   '"'视为 string 处理;
   't', "true"开头文字, 视为 true 处理;
   'f', 同理视为 false;
   'n', 视为 null;
   默认剩余情况为数字

```c++
switch (json_str[pos])
{
    case 'n':
        return parse_null();
    case 't':
        return parse_true();
    case 'f':
        return parse_false();
    case '"':
        return parse_string();
    case '[':
        return parse_array();
    case '{':
        return parse_object();
    default:
        return parse_number();
}
```

4. parse_object
   从'{' 到 '}'循环, 每次 pos++, 循环内容是 解析 key -- 解析 value 前置 -- 解析 value -- 填充 kv -- 解析到下个 key

```c++
while (pos < json_str.size() && json_str[pos] != '}')
{
    // 1. 解析出key
    auto key = parse_value();
    // 2. 解析value前置
    parse_whitespace();
    if (!std::holds_alternative<String>(key.value()))
    {
        return {};
    }
    if (pos < json_str.size() && json_str[pos] == ':')
    {
        pos++; // ,
    }
    parse_whitespace();
    // 3. 解析value
    auto val = parse_value();
    // 4. 填充kv
    obj[std::get<String>(key.value())] = val.value();
    // 5. 准备解析到下个key
    parse_whitespace();
    if (pos < json_str.size() && json_str[pos] == ',')
    {
        pos++; // ,
    }
    parse_whitespace();
}
```

5. parse_array
   类比 parse_object, 从'[' 到 ']'循环

有什么高质量的 C++ 单头文件库? - 芒果浩明的回答 - 知乎
https://www.zhihu.com/question/496257115/answer/2255551935
