cmake_minimum_required(VERSION 3.6)

#设置项目名称
project(AsioServer)

set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT "/usr/local/include/boost")

#添加头文件搜索路径
include_directories(/usr/local/include)

#添加库文件搜索路径
link_directories(/usr/local/lib)

#用于将当前目录下的所有源文件的名字保存在变量 DIR_SRCS 中
aux_source_directory(. DIR_SRCS)

add_executable(AsioServer ${DIR_SRCS}
        connection.cpp
        connection.h
        io_service_pool.cpp
        io_service_pool.h
        message.cpp
        message.h
        server.cpp
        server.h
        sync_queue.cpp
        sync_queue.h
        factory.hpp action/login_action.h action/action.h action/register_action.h global_data.h action/before_game_action.h)

#在这里根据名字boost_thread去寻找libboost_thread.a文件
target_link_libraries(AsioServer boost_thread boost_system json)

