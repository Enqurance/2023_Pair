cmake_minimum_required(VERSION 3.24)
project(Wordlist)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# 设置C++14标准
set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# 关闭编译器优化
#set(CMAKE_CXX_FLAGS "-O0")

# 连接jni库
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
link_libraries(${JNI_LIBRARIES})

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

#set(COTESTCORE
#        src/Node.cpp
#        src/api_cpy.cpp)
#add_library(coTestCore SHARED ${COTESTCORE})
#set_target_properties(coTestCore PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
#        OUTPUT_NAME "coTestCore")

# 生成动态链接库lib.dll
set(LIB
        src/FileIO.cpp
        src/Error.h)
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

add_executable(PerfTest test/PerfTest/PerfTest.cpp)
set_target_properties(PerfTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test_bin)


# 添加测试单元库
add_subdirectory(lib)
include_directories(lib/googletest/include googletest)

# 添加测试文件
# core测试
add_executable(coretest test/coretest/coretest.cpp)
set_target_properties(coretest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test_bin)
target_link_libraries(coretest gtest gtest_main)

# error测试
add_executable(errorTest test/coretest/errorTest.cpp)
set_target_properties(errorTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test_bin)
target_link_libraries(errorTest gtest gtest_main)

# 单元测试代码覆盖率
add_compile_options(-fprofile-arcs -ftest-coverage)

# gcov设置
add_custom_command(TARGET coretest
        POST_BUILD
        COMMAND gcov -k test/coretest/coretest.cpp)
