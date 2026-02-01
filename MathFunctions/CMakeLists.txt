# =============================================================================
# MathFunctions - 数学计算模块的 CMake 配置
# 
# 设计目标：演示变量管理与系统内省 (System Introspection)
# 
# 处理跨平台敏感性是高级程序员的必修课。例如，在某些平台上 log 和 exp
# 函数位于标准库，而在另一些平台上则需要链接 m (Math library)。
# =============================================================================

include(CheckSymbolExists)

# =============================================================================
# 架构师的自动探测逻辑
# 
# 先尝试不链接数学库探测符号，如果失败再尝试链接数学库 m
# =============================================================================

# 检查是否有 log 函数（不链接数学库）
check_symbol_exists(log "math.h" HAVE_LOG)
if(NOT HAVE_LOG)
    # 如果初始探测失败，尝试寻找并链接数学库 m
    set(CMAKE_REQUIRED_LIBRARIES "m")
    check_symbol_exists(log "math.h" HAVE_LOG)
    if(HAVE_LOG)
        # 需要链接数学库 m
        set(NEED_MATH_LIB TRUE)
    endif()
endif()

# 恢复 CMAKE_REQUIRED_LIBRARIES
set(CMAKE_REQUIRED_LIBRARIES "")

# 检查是否有 exp 函数
check_symbol_exists(exp "math.h" HAVE_EXP)

# 检查是否有 sqrt 函数
check_symbol_exists(sqrt "math.h" HAVE_SQRT)

# =============================================================================
# 定义库目标
# =============================================================================
add_library(MathFunctions mysqrt.cxx)

target_compile_features(MathFunctions PUBLIC cxx_std_11)

target_include_directories(MathFunctions
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# =============================================================================
# 条件链接数学库
# 
# 根据系统内省结果决定是否需要链接数学库
# =============================================================================
if(NEED_MATH_LIB)
    target_link_libraries(MathFunctions PRIVATE m)
    message(STATUS "MathFunctions: Linking against math library 'm'")
else()
    message(STATUS "MathFunctions: Math library not needed (built-in)")
endif()

# =============================================================================
# 安装规则
# =============================================================================
include(GNUInstallDirs)

install(TARGETS MathFunctions
    EXPORT TutorialTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES MathFunctions.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
