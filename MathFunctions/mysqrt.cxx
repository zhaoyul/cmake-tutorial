/**
 * @file mysqrt.cxx
 * @brief 数学计算模块的实现
 *
 * 演示跨平台代码和条件编译
 */

#include "MathFunctions.h"
#include <cmath>
#include <sstream>

// 根据系统内省结果包含头文件
#ifdef HAVE_LOG
#include <cmath>
#endif

#ifdef HAVE_EXP
#include <cmath>
#endif

namespace mathfunctions {

const char* getVersion() {
    return "MathFunctions version 1.0.0";
}

const char* getFeatures() {
    std::ostringstream oss;
    oss << "Features: ";

#ifdef HAVE_LOG
    oss << "LOG ";
#endif

#ifdef HAVE_EXP
    oss << "EXP ";
#endif

#ifdef HAVE_SQRT
    oss << "SQRT ";
#endif

    static std::string features = oss.str();
    return features.c_str();
}

/**
 * @brief 牛顿迭代法计算平方根
 *
 * 当系统 sqrt 不可用时，使用此备选实现
 */
double newtonSqrt(double x) {
    if (x <= 0) {
        return 0;
    }

    double result = x;
    // 迭代10次达到足够精度
    for (int i = 0; i < 10; ++i) {
        if (result <= 0) {
            result = 0.1;
        }
        double delta = x - (result * result);
        result = result + 0.5 * delta / result;
    }
    return result;
}

double mysqrt(double x) {
#ifdef HAVE_SQRT
    // 使用系统提供的 sqrt
    return std::sqrt(x);
#else
    // 使用自定义实现
    return newtonSqrt(x);
#endif
}

double mylog(double x) {
#ifdef HAVE_LOG
    return std::log(x);
#else
    // 简单的近似实现
    if (x <= 0) return 0;
    if (x == 1) return 0;

    // 使用泰勒展开近似
    double y = (x - 1) / (x + 1);
    double result = 0;
    double term = y;
    for (int i = 0; i < 20; ++i) {
        result += term / (2 * i + 1);
        term *= y * y;
    }
    return 2 * result;
#endif
}

double myexp(double x) {
#ifdef HAVE_EXP
    return std::exp(x);
#else
    // 使用泰勒展开近似
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i < 20; ++i) {
        term *= x / i;
        result += term;
    }
    return result;
#endif
}

} // namespace mathfunctions
