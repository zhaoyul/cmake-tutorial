# =============================================================================
# libC - 静态库 C 的 CMake 配置
# 
# 设计目标：演示 INTERFACE 可见性的使用
# 此库为 Header-only 库，仅包含模板和内联函数
# 
# 技术辨析：
# 使用 INTERFACE 是实现类似 Boost 这种 Header-only 库的核心。
# 通过 target_link_libraries 传播属性，CMake 彻底解决了 Makefile 中
# 常见的"符号污染"与"头文件冲突"问题。
# =============================================================================

# INTERFACE 库：没有源码文件，仅包含头文件
add_library(libC INTERFACE)

# INTERFACE 编译特性：消费者需要 C++14 才能使用此库
target_compile_features(libC INTERFACE cxx_std_14)

# INTERFACE 包含目录：
# - 库自身构建时不需要（因为是 INTERFACE）
# - 但会传播给消费者
target_include_directories(libC
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# INTERFACE 编译定义：向消费者传播宏定义
target_compile_definitions(libC
    INTERFACE
        LIBC_HEADER_ONLY
)

# =============================================================================
# 安装规则
# 
# Header-only 库只需安装头文件
# =============================================================================
include(GNUInstallDirs)

install(TARGETS libC
    EXPORT TutorialTargets
)

install(FILES libC.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
