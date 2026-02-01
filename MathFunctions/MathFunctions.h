/**
 * @file MathFunctions.h
 * @brief 数学计算模块的公共接口
 * 
 * 此模块演示了系统内省和跨平台处理的最佳实践
 */

#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "TutorialConfig.h"

namespace mathfunctions {

/**
 * @brief 计算平方根
 * 
 * 使用系统内省探测到的数学库函数实现
 * 
 * @param x 输入值
 * @return x 的平方根
 */
double mysqrt(double x);

/**
 * @brief 计算自然对数（如果可用）
 * 
 * 根据 HAVE_LOG 宏决定是否可用
 * 
 * @param x 输入值
 * @return x 的自然对数
 */
double mylog(double x);

/**
 * @brief 计算指数函数（如果可用）
 * 
 * 根据 HAVE_EXP 宏决定是否可用
 * 
 * @param x 输入值
 * @return e 的 x 次方
 */
double myexp(double x);

/**
 * @brief 获取数学函数库的版本信息
 */
const char* getVersion();

/**
 * @brief 获取支持的数学功能描述
 */
const char* getFeatures();

} // namespace mathfunctions

#endif // MATHFUNCTIONS_H
