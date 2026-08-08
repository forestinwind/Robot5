cmake_minimum_required(VERSION 3.16)
project(Robot5)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========== 强制使用 MSVC 2019 版本的 Qt 6.7.3 ==========
set(QT_ROOT "C:/Qt/6.7.3/msvc2019_64")
set(CMAKE_PREFIX_PATH ${QT_ROOT} ${CMAKE_PREFIX_PATH})
set(Qt6_DIR "${QT_ROOT}/lib/cmake/Qt6")

# 添加可执行文件
add_executable(Robot5 src/main.cpp src/Robot.cpp)
set_target_properties(Robot5 PROPERTIES VS_STARTUP_PROJECT TRUE)

# 查找 Qt6 核心组件
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Quick QuickWidgets)

# ---------- Eigen3 查找与集成 ----------
if(Eigen3_FOUND)
    message(STATUS "Eigen3 found: ${Eigen3_VERSION}")
    target_link_libraries(Robot5 PRIVATE Eigen3::Eigen)
else()
    find_path(EIGEN3_INCLUDE_DIR "Eigen/Dense"
        HINTS
            "$ENV{EIGEN3_DIR}"
            "C:/Program Files (x86)/eigen-5.0.0"
            "C:/local/include"
            "/usr/include/eigen3"
    )
    if(EIGEN3_INCLUDE_DIR)
        message(STATUS "Eigen3 include found at: ${EIGEN3_INCLUDE_DIR}")
        target_include_directories(Robot5 PRIVATE ${EIGEN3_INCLUDE_DIR})
    else()
        message(FATAL_ERROR "Eigen3 not found. Install Eigen or set EIGEN3_DIR environment variable.")
    endif()
endif()

# 头文件包含目录（DLL 文件夹）
target_include_directories(Robot5 PRIVATE ${CMAKE_SOURCE_DIR}/DLL)

# 查找静态库/导入库
find_library(MCSLPCI_LIB MCSLPCI_PMC PATHS ${CMAKE_SOURCE_DIR}/DLL REQUIRED)
find_library(PMCPCI_LIB PMCPCIDrv   PATHS ${CMAKE_SOURCE_DIR}/DLL REQUIRED)

# 链接所有库
target_link_libraries(Robot5 PRIVATE
    ${MCSLPCI_LIB}
    ${PMCPCI_LIB}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickWidgets
)

# 预处理器定义
target_compile_definitions(Robot5 PRIVATE _CONSOLE)

# MSVC 特定编译选项（解决中文编码问题）
if(MSVC)
    target_compile_options(Robot5 PRIVATE /UTF-8)
endif()

# ------------------------------
# 复制自定义 DLL（你自己的第三方库）
# ------------------------------
set(DLL_DIR ${CMAKE_SOURCE_DIR}/DLL)
set(DLL_FILES
    ${DLL_DIR}/MCSLPCI_PMC.dll
    ${DLL_DIR}/PMCPCIDrv.dll
)

foreach(DLL_FILE ${DLL_FILES})
    if(EXISTS ${DLL_FILE})
        add_custom_command(TARGET Robot5 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL_FILE}
                $<TARGET_FILE_DIR:Robot5>
            COMMENT "Copying ${DLL_FILE} to output directory"
        )
    else()
        message(WARNING "DLL file ${DLL_FILE} not found, will not be copied.")
    endif()
endforeach()

# ============================================================
# 使用 windeployqt 自动部署 Qt 依赖
# ============================================================
find_program(WINDEPLOYQT windeployqt
    HINTS "${QT_ROOT}/bin"
    REQUIRED  # 如果找不到，会停止配置并报错
)

add_custom_command(TARGET Robot5 POST_BUILD
    COMMAND ${WINDEPLOYQT}
        --no-translations   # 跳过翻译文件，减小体积（如果需要翻译可去掉）
        $<TARGET_FILE:Robot5>
    COMMENT "Deploying Qt libraries via windeployqt"
)