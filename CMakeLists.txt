cmake_minimum_required(VERSION 3.24)
project(Wordlist)

# 设置C++14标准
set(CMAKE_CXX_STANDARD 14)

# 设置可执行文件.exe输出的地址
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 设置动态链接库的编译输出地址
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 生成可执行文件.exe
add_executable(Wordlist src/main.cpp)
add_executable(Test src/Test.cpp)

set(CORE
        src/Core.cpp
        src/Core.h
        src/Node.cpp
        src/Node.h)

set(LIB
        src/FileIO.cpp
        src/FileIO.h)

add_library(core SHARED ${CORE})

# 指定导出符号，使得其他程序可以使用动态链接库中的函数和变量
set_target_properties(core PROPERTIES
        PUBLIC_HEADER core.h
        )

# 指定安装路径
install(TARGETS core
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )


add_library(lib SHARED ${LIB})

# 指定导出符号，使得其他程序可以使用动态链接库中的函数和变量
set_target_properties(lib PROPERTIES
        PUBLIC_HEADER lib.h
        )

# 指定安装路径
install(TARGETS lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )