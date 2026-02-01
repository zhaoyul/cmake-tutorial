# =============================================================================
# CMake 深度进阶：现代工程架构示例
# =============================================================================
# 作为版本锚定，cmake_minimum_required 会自动锁定该版本及之前的所有策略行为
cmake_minimum_required(VERSION 3.15)

# 定义项目，声明工程契约
project(CMakeTutorial
    VERSION 1.0.0
    DESCRIPTION "CMake 深度进阶：从 Makefile 逻辑转向现代工程架构"
    LANGUAGES CXX C
)

# =============================================================================
# C++ 标准设置：现代做法
# =============================================================================
# 不推荐全局设置 CMAKE_CXX_STANDARD，而是使用 target_compile_features
# 这确保了标准要求像属性一样在目标间安全传播

# =============================================================================
# 变量管理与系统内省 (System Introspection)
# =============================================================================
# 处理跨平台敏感性是高级程序员的必修课。例如，在某些平台上 log 和 exp
# 函数位于标准库，而在另一些平台上则需要链接 m (Math library)。

include(CheckSymbolExists)

# 检查数学函数是否存在
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
check_symbol_exists(sqrt "math.h" HAVE_SQRT)

# =============================================================================
# 配置头文件生成
# =============================================================================
# 将版本信息和系统内省结果传递给源码
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/TutorialConfig.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/TutorialConfig.h
)

# =============================================================================
# 包含目录管理
# =============================================================================
# 使生成的配置头文件对所有模块可见
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# =============================================================================
# 模块化构建：通过 add_subdirectory 启动作用域管理
# =============================================================================
# 每个模块定义自己的目标，由顶级 CMakeLists.txt 统一编排
# 这种模式实现了物理结构与逻辑依赖的统一

add_subdirectory(libA)
add_subdirectory(libB)
add_subdirectory(libC)
add_subdirectory(MathFunctions)
add_subdirectory(src)

# =============================================================================
# 测试支持
# =============================================================================
include(CTest)
enable_testing()

# 添加简单测试
if(BUILD_TESTING)
    add_test(NAME TutorialRuns COMMAND Tutorial 25)
    set_tests_properties(TutorialRuns PROPERTIES PASS_REGULAR_EXPRESSION "Input:  25")
endif()

# =============================================================================
# 安装规则
# =============================================================================
# 构建产物与开发环境的剥离，这是创建 Docker 镜像或分发二进制包的标准前置步骤
include(GNUInstallDirs)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/TutorialConfig.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# =============================================================================
# CPack 打包配置
# =============================================================================
include(CPack)
