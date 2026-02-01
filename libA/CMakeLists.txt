# =============================================================================
# libA - 静态库 A 的 CMake 配置
# 
# 设计目标：演示 PRIVATE 可见性的使用
# 此库封装内部实现细节，不对外暴露依赖
# =============================================================================

# 定义库目标
add_library(libA STATIC libA.cpp)

# 设置 C++ 标准：现代做法
# 使用 target_compile_features 而非全局 CMAKE_CXX_STANDARD
target_compile_features(libA PUBLIC cxx_std_11)

# 包含目录管理：使用生成表达式区分构建接口与安装接口
# 这避免了在安装后的库中残留开发路径
target_include_directories(libA
    PUBLIC
        # 构建时使用源码目录
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        # 安装后使用系统 include 目录
        $<INSTALL_INTERFACE:include>
)

# 编译器选项：PRIVATE 表示仅用于当前目标，不传播给消费者
target_compile_options(libA PRIVATE -Wall -Wextra)

# =============================================================================
# 安装规则
# =============================================================================
include(GNUInstallDirs)

install(TARGETS libA
    EXPORT TutorialTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES libA.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
