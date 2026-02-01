/**
 * @file libB.h
 * @brief 静态库 B 的公共接口
 * 
 * 设计原则：
 * - 作为中间层，组合 libA 的功能
 * - 通过 PUBLIC 链接，消费者自动获得 libA 的依赖
 */

#ifndef LIBB_H
#define LIBB_H

namespace libb {

/**
 * @brief 获取库 B 的版本信息
 */
const char* getVersion();

/**
 * @brief 组合处理：使用 libA 的功能进行二次加工
 * @param value 输入值
 * @return 处理后的结果
 */
double compositeProcess(double value);

/**
 * @brief 获取库 B 的描述信息
 */
const char* getDescription();

} // namespace libb

#endif // LIBB_H
