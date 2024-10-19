cmake_minimum_required(VERSION 3.0)
project(main)

#设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#设置头文件搜索路径
include_directories()
#设置库文件搜索路径
link_directories()

#设置需要编译的源文件列表
set(SRC_LIST ./server.cpp)
#设置可执行文件的存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#把.指定路径下的所有源文件名称放入SRC_LIST里
#aux_source_directory(. SRC_LIST)

#表示生成的可执行文件server，由SRC_LIST变量所定义的源文件编译而来
add_executable(server ${SRC_LIST})

#表示server这个目标程序，需要连接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)