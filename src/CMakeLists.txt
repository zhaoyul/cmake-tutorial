# =============================================================================
# src - 核心应用入口的 CMake 配置
# 
# 设计目标：演示如何组合使用所有模块
# 展示现代 CMake 的依赖传播机制
# =============================================================================

# 定义可执行目标
add_executable(Tutorial main.cpp)

target_compile_features(Tutorial PUBLIC cxx_std_14)

# =============================================================================
# 依赖链接：演示依赖传播
# 
# 链接顺序说明（与 Makefile 的关键区别）：
# 
# 在 Makefile 中，你需要手动且精准地排列 -l 标志，因为链接器是
# 单遍（One-pass）的。错误的顺序会导致未定义符号错误。
# 
# 在现代 CMake 中，你只需要声明直接依赖：
# - Tutorial 直接依赖 libB、libC 和 MathFunctions
# - libB 的 PUBLIC 链接会自动传播 libA
# - CMake 会自动计算正确的链接顺序
# =============================================================================
target_link_libraries(Tutorial
    PRIVATE
        libB        # PUBLIC 依赖 libA，会自动传播
        libC        # INTERFACE 库，仅传播头文件
        MathFunctions  # 数学库，可能需要链接 m
)

# 包含生成的配置头文件目录
target_include_directories(Tutorial
    PRIVATE
        ${CMAKE_BINARY_DIR}
)

# =============================================================================
# 安装规则
# =============================================================================
install(TARGETS Tutorial
    EXPORT TutorialTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
