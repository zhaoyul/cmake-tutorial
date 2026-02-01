# =============================================================================
# libB - 静态库 B 的 CMake 配置
# 
# 设计目标：演示 PUBLIC 可见性的使用
# 此库作为中间层，依赖 libA 并传播给消费者
# =============================================================================

add_library(libB STATIC libB.cpp)

target_compile_features(libB PUBLIC cxx_std_11)

target_include_directories(libB
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(libB PRIVATE -Wall -Wextra)

# =============================================================================
# 依赖关系：PUBLIC 链接 libA
# 
# 使用 PUBLIC 意味着：
# - libB 自身构建时需要 libA
# - 链接 libB 的消费者也会自动链接 libA
# - 这解决了 Makefile 中臭名昭著的"链接顺序问题"
# =============================================================================
target_link_libraries(libB PUBLIC libA)

# =============================================================================
# 安装规则
# =============================================================================
include(GNUInstallDirs)

install(TARGETS libB
    EXPORT TutorialTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES libB.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
