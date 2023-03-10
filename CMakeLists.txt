cmake_minimum_required(VERSION 3.24)
project(Wordlist)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# 设置C++14标准
set(CMAKE_CXX_STANDARD 14)

# 设置可执行文件.exe输出的地址
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 设置动态链接库的编译输出地址
set(CMAKE_LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 生成动态链接库core.dll
set(CORE
        src/Core.cpp
        src/Node.cpp)
add_library(core SHARED ${CORE})
set_target_properties(core PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        OUTPUT_NAME "core")

# 生成动态链接库lib.dll
set(LIB
        src/FileIO.cpp)
add_library(lib SHARED ${LIB})
set_target_properties(lib PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        OUTPUT_NAME "lib")

# 为dll文件设置include的文件夹
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(lib PUBLIC ${CMAKE_SOURCE_DIR}/src)

# 生成可执行文件.exe
add_executable(Wordlist src/main.cpp)
target_link_libraries(Wordlist core)
target_link_libraries(Wordlist lib)
set_target_properties(Wordlist PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(Test test/Test.cpp)
set_target_properties(Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test_bin)


# 添加测试单元库
add_subdirectory(lib)
include_directories(lib/googletest/include googletest)

# 添加测试文件
# core测试
add_executable(coretest test/coretest/coretest.cpp)
set_target_properties(coretest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test_bin)
target_link_libraries(coretest gtest gtest_main)

# 单元测试代码覆盖率
add_compile_options(-fprofile-arcs -ftest-coverage)

# GUI的main文件
#add_executable(GUIMain GUI/main.cpp)