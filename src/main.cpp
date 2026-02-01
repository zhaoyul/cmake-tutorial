/**
 * @file main.cpp
 * @brief CMake 深度进阶教程的主程序
 * 
 * 此程序演示了现代 CMake 的各种特性：
 * - 模块化的库结构
 * - PRIVATE/PUBLIC/INTERFACE 可见性
 * - 依赖传播机制
 * - 系统内省
 */

#include <iostream>
#include <cstdlib>
#include "TutorialConfig.h"
#include "libA.h"
#include "libB.h"
#include "libC.h"
#include "MathFunctions.h"

/**
 * @brief 打印分隔线
 */
void printSeparator(const char* title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

/**
 * @brief 显示项目信息
 */
void showProjectInfo() {
    printSeparator("Project Information");
    std::cout << "Project: CMakeTutorial" << std::endl;
    std::cout << "Version: " << Tutorial_VERSION << std::endl;
    std::cout << "C++ Standard: 14 (enforced via target_compile_features)" << std::endl;
}

/**
 * @brief 演示 libA (PRIVATE 依赖)
 */
void demoLibA(double input) {
    printSeparator("Library A - PRIVATE Usage");
    std::cout << liba::getVersion() << std::endl;
    std::cout << liba::getDescription() << std::endl;
    std::cout << "Input:  " << input << std::endl;
    std::cout << "Output: " << liba::processValue(input) << std::endl;
}

/**
 * @brief 演示 libB (PUBLIC 依赖)
 */
void demoLibB(double input) {
    printSeparator("Library B - PUBLIC Linking");
    std::cout << libb::getVersion() << std::endl;
    std::cout << libb::getDescription() << std::endl;
    std::cout << "Note: libB PUBLIC links libA, so libA is automatically available" << std::endl;
    std::cout << "Input:  " << input << std::endl;
    std::cout << "Output: " << libb::compositeProcess(input) << std::endl;
}

/**
 * @brief 演示 libC (INTERFACE 头文件库)
 */
void demoLibC(double input) {
    printSeparator("Library C - INTERFACE Header-only");
    std::cout << libc::getVersion() << std::endl;
    std::cout << libc::getDescription() << std::endl;
    std::cout << "Input:  " << input << std::endl;
    std::cout << "Output: " << libc::genericProcess(input) << std::endl;
    std::cout << "Compile-time compute 2^10: " << libc::compileTimeCompute(2, 10) << std::endl;
}

/**
 * @brief 演示 MathFunctions (系统内省)
 */
void demoMathFunctions(double input) {
    printSeparator("MathFunctions - System Introspection");
    std::cout << mathfunctions::getVersion() << std::endl;
    std::cout << mathfunctions::getFeatures() << std::endl;
    
    std::cout << "\nResults for input = " << input << ":" << std::endl;
    
    if (input >= 0) {
        std::cout << "  sqrt(" << input << ") = " << mathfunctions::mysqrt(input) << std::endl;
    }
    
    if (input > 0) {
#ifdef HAVE_LOG
        std::cout << "  log(" << input << ")  = " << mathfunctions::mylog(input) << std::endl;
#else
        std::cout << "  log() not available on this platform" << std::endl;
#endif
    }
    
#ifdef HAVE_EXP
    std::cout << "  exp(" << input << ")  = " << mathfunctions::myexp(input) << std::endl;
#else
    std::cout << "  exp() not available on this platform" << std::endl;
#endif
}

int main(int argc, char* argv[]) {
    // 解析命令行参数
    double inputValue = 25.0;
    if (argc > 1) {
        inputValue = std::atof(argv[1]);
    }
    
    // 显示项目信息
    showProjectInfo();
    
    // 演示各个库的功能
    demoLibA(inputValue);
    demoLibB(inputValue);
    demoLibC(inputValue);
    demoMathFunctions(inputValue);
    
    // 总结
    printSeparator("Summary");
    std::cout << "This project demonstrates:" << std::endl;
    std::cout << "  1. PRIVATE visibility (libA): Hidden implementation details" << std::endl;
    std::cout << "  2. PUBLIC visibility (libB): Dependency propagation to consumers" << std::endl;
    std::cout << "  3. INTERFACE visibility (libC): Header-only library" << std::endl;
    std::cout << "  4. System introspection (MathFunctions): Cross-platform detection" << std::endl;
    std::cout << "\nModern CMake builds a DAG of targets with Usage Requirements," << std::endl;
    std::cout << "automatically propagating include paths, link flags, and definitions." << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return 0;
}
