/**
 * @file libC.h
 * @brief 静态库 C 的公共接口（Header-only）
 * 
 * 设计原则：
 * - 纯头文件实现，演示 INTERFACE 可见性
 * - 类似 Boost 的设计理念
 * 
 * 这是 INTERFACE 可见性的典型应用场景：
 * - 目标自身构建时不使用
 * - 但会传播给消费者
 */

#ifndef LIBC_H
#define LIBC_H

#include <type_traits>
#include <cmath>

namespace libc {

/**
 * @brief 获取库 C 的版本信息
 * 
 * Header-only 库的内联函数
 */
inline const char* getVersion() {
    return "libC version 1.0.0 (Header-only)";
}

/**
 * @brief 获取库 C 的描述信息
 */
inline const char* getDescription() {
    return "Library C: Header-only library demonstrating INTERFACE usage";
}

/**
 * @brief 泛型处理函数：演示模板的使用
 * 
 * 这是 Header-only 库的典型用法，模板必须在头文件中定义
 * 
 * @tparam T 数值类型
 * @param value 输入值
 * @return 处理后的结果
 */
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
genericProcess(T value) {
    return static_cast<T>(std::sqrt(std::abs(static_cast<double>(value))));
}

/**
 * @brief 编译期计算工具
 * 
 * 演示 C++14 特性，这也是为什么 libC 需要 INTERFACE cxx_std_14
 */
template<typename T>
constexpr T compileTimeCompute(T base, int power) {
    return (power == 0) ? T(1) : base * compileTimeCompute(base, power - 1);
}

} // namespace libc

#endif // LIBC_H
