---
title: "c++ std::function"
date: 2024-10-11
categories: [c_c++]
tags: [c_c++]
excerpt: "function"
---

## 定义

在 `c++` 中, 可调用对象(`callable objects`)包括普通函数、函数指针、`lambda` 表达式、仿函数(重载 `operator()` 的类)以及类成员函数指针

`std::function` 是 `c++11` 引入的一个通用多态函数包装器(定义在 `<functional>` 头文件中), 它通过类型擦除 (type erasure) 技术, 能够将任何符合特定签名(返回类型和参数类型)的可调用对象统一包装起来, 实现类似"泛型函数指针"的功能

```c++
#include <functional>

// 语法: std::function<返回类型(参数类型列表)>
std::function<int(double, double)> func;
```

### 特性

#### 空函数对象

当 `std::function` 不指向任何可调用对象时, 它的值为 `nullptr`

因此使用 `std::function` 时应该检查其是否有效:

```c++
std::function<void()> func;
if (func) {
    func();  // 调用
} else {
    std::cout << "No function assigned!" << std::endl;
}
```

#### 性能

`std::function`的灵活性和通用性也带来一定的性能开销, 特别是在运行时类型擦除(type erasure)和动态分配内存时

因此如果性能要求较高, 且函数类型已知, 使用普通函数指针或其他低开销的方式可能更合适

## 操作

`std::function` 的最大优势在于其"包容性", 它可以无缝接管以下几种可调用对象

### 普通函数与函数指针

将普通函数绑定到 `std::function` 对象中, 并通过该对象调用函数

```c++
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::function<int(int, int)> func = add;
    // add(2, 3) = 5
    std::cout << "add(2, 3) = " << func(2, 3) << std::endl;
    // add(4, 5) = 9
    std::cout << "add(4, 5) = " << func(4, 5) << std::endl;

    return 0;
}
```

### lambda 表达式

`std::function` 还可以绑定到 `lambda` 表达式, 表达式可以直接在定义时提供功能而无需额外命名

```c++
#include <iostream>
#include <functional>

int main() {
    std::function<int(int, int)> multiply = [](int a, int b) { return a * b; };
    std::cout << "multiply(2, 3) = " << multiply(2, 3) << std::endl;

    return 0;
}
```

### 类成员函数(现代 c++ 实践对比)

当需要绑定类成员函数时, 可结合使用 `std::bind` `std::function`, 同时需传递类对象实例

`std::bind` 用于将类成员函数与特定实例绑定, `std::placeholders::_1` 和 `std::placeholders::_2` 表示函数参数占位符

```c++
#include <iostream>
#include <functional>

class Calculator {
public:
    int subtract(int a, int b) const {
        return a - b;
    }
};

int main() {
    Calculator calc;
    std::function<int(int, int)> func = std::bind(&Calculator::subtract, calc, std::placeholders::_1, std::placeholders::_2);

    // subtract(5, 2) = 3
    std::cout << "subtract(5, 2) = " << func(5, 2) << std::endl;

    return 0;
}
```

### 仿函数(functor / 函数对象)

重载`operator()`的类或结构体对象, 可以像普通函数一样被调用

```c++
#include <iostream>
#include <functional>

struct Divide {
    int operator()(int a, int b) const {
        return a / b;
    }
};

int main() {
    Divide divide;

    std::function<int(int, int)> func = divide;
    std::cout << "divide(6, 2) = " << func(6, 2) << std::endl;

    return 0;
}
```

### 作为回调函数

`std::function` 还常用于回调函数的实现

回调函数允许动态地改变行为, 可以用于事件驱动编程、异步编程等场景

```c++
#include <iostream>
#include <functional>

void process(const std::function<void(int)>& call_back) {
    for (int i = 0; i < 5; ++i) {
        call_back(i);
    }
}

int main() {
    process([](int value) {
        std::cout << "processing value: " << value << std::endl;
    });

    return 0;
}
```

```sh
processing value: 0
processing value: 1
processing value: 2
processing value: 3
processing value: 4
```

`std::function` 可存储所有符合指定函数签名的可调用对象, 但存储对象类型必须与 `std::function` 签名相同

当 `std::function` 不指向任何可调用对象时, 其值为 nullptr, 可以使用 if 判断其有效性

## 高级应用

### 回调函数与依赖注入

`std::function` 是实现回调机制、事件驱动和依赖注入的利器

> 作为参数传递时, 应使用 `const std::function&` 以避免不必要的拷贝开销

```c
#include <iostream>
#include <functional>
#include <vector>

// 事件分发器
void process_events(
    const std::vector<int>& data,
    const std::function<void(int)>& callback
) {
    for (int val : data) {
        callback(val);
    }
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    
    // 动态注入处理逻辑
    process_events(nums, [](int v) {
        std::cout << "Processing: " << v << "\n";
    });
    return 0;
}
```