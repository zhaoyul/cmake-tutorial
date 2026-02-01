/**
 * @file libB.cpp
 * @brief 静态库 B 的实现
 */

#include "libB.h"
#include "libA.h"
#include <cmath>

namespace libb {

const char* getVersion() {
    return "libB version 1.0.0";
}

const char* getDescription() {
    return "Library B: Intermediate layer demonstrating PUBLIC linking";
}

double compositeProcess(double value) {
    // 使用 libA 的功能
    double result = liba::processValue(value);
    
    // 添加 libB 的额外处理
    return std::pow(result, 0.5) + 1.0;
}

} // namespace libb
