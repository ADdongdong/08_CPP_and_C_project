cmake_minimum_required(VERSION 3.10)

project(webserver)

# 使得Makefile更加详细，当运行make命令时，会显示更多构建信息
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV(CXXFLAGS) -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

# 在Linux/Unix环境下，.cc文件是C++源文件的默认扩展名
# 与windows下的.cpp文件意思相同
set(LIB_SRC
    adong/log.cc
    )

add_library(adong SHARED ${LIB_SRC}) # 创建一个名为adong的共享库

add_executable(test tests/test.cc)  # 定义一个可执行目标test,由tests/test.c构建
add_dependencies(test adong)  # 指定test可执行文件依赖于adong库，意味着，在构建test之前，必须先构建adong库
target_link_libraries(test adong) # 指定test可执行文件要连接到adong库

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) # 设置可执行文件的输出路径为bin/
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #设置库的输出路径为bin/

