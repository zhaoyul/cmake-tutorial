/**
 * @file libA.h
 * @brief 静态库 A 的公共接口
 * 
 * 设计原则：
 * - 暴露最小化的公共接口
 * - 内部实现细节完全隐藏在源文件中
 */

#ifndef LIBA_H
#define LIBA_H

namespace liba {

/**
 * @brief 获取库 A 的版本信息
 * @return 版本号字符串
 */
const char* getVersion();

/**
 * @brief 执行库 A 的核心功能
 * @param value 输入值
 * @return 处理后的结果
 * 
 * 此函数演示了 PRIVATE 可见性的使用：
 * - 实现中可能使用内部辅助函数，这些不会暴露给消费者
 */
double processValue(double value);

/**
 * @brief 获取库 A 的描述信息
 * @return 描述字符串
 */
const char* getDescription();

} // namespace liba

#endif // LIBA_H
