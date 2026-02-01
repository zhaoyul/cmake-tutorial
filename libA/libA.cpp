/**
 * @file libA.cpp
 * @brief 静态库 A 的实现
 */

#include "libA.h"
#include <cmath>
#include <sstream>

namespace liba {

// 内部命名空间：完全隐藏实现细节
namespace internal {
    
    /**
     * @brief 内部辅助函数：对输入值进行预处理
     * 
     * 这是一个 PRIVATE 实现细节，消费者无法访问
     */
    double preprocess(double value) {
        // 确保值为正数
        return std::abs(value);
    }
    
    /**
     * @brief 内部辅助函数：计算调整因子
     */
    double getAdjustmentFactor() {
        return 1.5;
    }
    
} // namespace internal

const char* getVersion() {
    return "libA version 1.0.0";
}

const char* getDescription() {
    return "Library A: Core processing module with PRIVATE dependencies";
}

double processValue(double value) {
    // 使用内部辅助函数
    double preprocessed = internal::preprocess(value);
    double factor = internal::getAdjustmentFactor();
    
    return preprocessed * factor;
}

} // namespace liba
