cmake_minimum_required(VERSION 3.24)
project(Wordlist)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# 设置C++14标准
set(CMAKE_CXX_STANDARD 14)

# 设置可执行文件.exe输出的地址
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 生成可执行文件.exe
add_executable(Wordlist src/main.cpp)
set_target_properties(Wordlist PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(Test test/Test.cpp)
set_target_properties(Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test_bin)

# 设置动态链接库的编译输出地址
set(CMAKE_LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 生成动态链接库core.dll
set(CORE src/Core.cpp src/Core.h src/Node.cpp src/Node.h)
add_library(CORE SHARED ${CORE})
set_target_properties(CORE PROPERTIES OUTPUT_NAME "core")

# 生成动态链接库lib.dll
set(LIB src/FileIO.cpp src/FileIO.h)
add_library(LIB SHARED ${LIB})
set_target_properties(LIB PROPERTIES OUTPUT_NAME "lib")

# 添加测试单元库
add_subdirectory(lib)
include_directories(lib/googletest/include googletest)

# 添加测试文件
# io测试
add_executable(iotest test/iotest/iotest.cpp)
target_link_libraries(iotest gtest gtest_main)

# core测试
add_executable(coretest test/coretest/coretest.cpp)
target_link_libraries(coretest gtest gtest_main)

# 单元测试代码覆盖率
add_compile_options(-fprofile-arcs -ftest-coverage)

# GUI的main文件
add_executable(GUIMain GUI/main.cpp)