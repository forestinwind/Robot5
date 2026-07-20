cmake_minimum_required(VERSION 3.10)
project(Robot5)

# 设置 C++ 标准为 C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加可执行文件
add_executable(Robot5 main.cpp Robot.cpp)

# 头文件包含目录（DLL 文件夹）
target_include_directories(Robot5 PRIVATE ${CMAKE_SOURCE_DIR}/DLL)

# 使用 find_library 查找静态库/导入库（如果找不到会在配置时报错）
find_library(MCSLPCI_LIB MCSLPCI_PMC PATHS ${CMAKE_SOURCE_DIR}/DLL REQUIRED)
find_library(PMCPCI_LIB PMCPCIDrv   PATHS ${CMAKE_SOURCE_DIR}/DLL REQUIRED)

# 链接库
target_link_libraries(Robot5 ${MCSLPCI_LIB} ${PMCPCI_LIB})

# 预处理器定义
target_compile_definitions(Robot5 PRIVATE _CONSOLE)

# MSVC 特定编译选项
if(MSVC)
    target_compile_options(Robot5 PRIVATE /UTF-8)
endif()

# ------------------------------
# 在构建后自动复制 DLL 到输出目录
# ------------------------------
set(DLL_DIR ${CMAKE_SOURCE_DIR}/DLL)

# 假设 DLL 文件名与库名一致，但后缀为 .dll
# 如果你需要区分 Debug/Release 版本，可以使用生成器表达式或分别指定
set(DLL_FILES
    ${DLL_DIR}/MCSLPCI_PMC.dll
    ${DLL_DIR}/PMCPCIDrv.dll
)

# 添加 post-build 命令，在每个 dll 文件存在时才复制（避免报错）
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