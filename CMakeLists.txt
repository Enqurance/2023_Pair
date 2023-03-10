cmake_minimum_required(VERSION 3.24)
project(Wordlist)

# 设置C++14标准
set(CMAKE_CXX_STANDARD 14)

# 设置.exe文件输出的地址
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 设置动态链接库的编译输出地址
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 将main.cpp生成可执行文件
add_executable(Wordlist src/main.cpp)
add_executable(Test src/Test.cpp)

# 生成共享库
#add_library(common SHARED src/Core.h src/Core.cpp src/FileReader.cpp src/FileReader.h src/Node.cpp src/Node.h)