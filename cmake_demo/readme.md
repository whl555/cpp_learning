## CMake学习

### add_subdirectory
添加一个子目录并构建该子目录, project集成module
```cmake
add_subdirectory(lib-utils)
add_subdirectory(src)
```

### add_library
用于使用指定的源文件向项目(project)中添加库, 作为library module
```cmake
aux_source_directory(src UTILS_SRC) // 收集src源码

add_library(utils ${UTILS_SRC}) // 将src源码作为utils库

# 指定库向外部暴露(PUBLIC)的头文件
target_include_directories(utils PUBLIC include)
```

### target_link_libraries
依赖库文件, 作为业务module
```cmake
add_executable(HelloCmake ${EXE_SRC})
target_link_libraries(HelloCmake PRIVATE utils) // 该module依赖utils库, 以private私有形式
```

### set_target_properties
todo 

### 添加第三方库之target_include_directories绝对路径
将指定目录添加为库
![alt text](image.png)
```cmake
# 添加spdlog依赖
target_include_directories(HelloCmake PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty)
```

### 添加第三方库之target_link_libraries + find_packages
通过ld去电脑上查询库文件
```cmake
# 添加curl依赖
find_package(CURL REQUIRED)
target_link_libraries(HelloCmake PRIVATE curl)
```
