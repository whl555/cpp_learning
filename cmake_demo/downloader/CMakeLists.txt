# CMake最低版本号要求
cmake_minimum_required(VERSION 3.0)

project(downloader)

# 递归遍历获取项目的所有源文件列表
file(GLOB_RECURSE SRC_LIST FOLLOW_SYMLINKS main.cpp src/*.cpp)

# 打印消息：把获取到的源文件列表打印出来
message(DEBUG, ${SRC_LIST})

# 生成可执行文件 main，后面是源码列表
add_executable(main ${SRC_LIST})
