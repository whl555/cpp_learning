## 手写shared_ptr

### explicit
explicit的作用就是防止其他类型对该类类型的隐式转换

### 拷贝构造函数
```c++
SharedPtr<MyClass> ptr2(ptr1);
SharedPtr<MyClass> ptr2 = ptr1;
```
https://blog.csdn.net/qq_43519886/article/details/105170209


### =运算符重载
```c++
SharedPtr<MyClass> ptr2(nullptr);
ptr2 = ptr1;
```