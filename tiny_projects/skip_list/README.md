## 基于跳表的kv数据库

### 1. 仿函数
Less仿函数
```c++
template <typename T>
struct Less
{
    bool operator()(const T &a, const T &b) const
    {
        return a < b;
    }
};
```

### 2. 跳表
多层链表


### 3. 支持自定义类型与自定义比较函数

### 4. 迭代器遍历