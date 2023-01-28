#设置默认静态库保存的位置

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

#设置默认动态库保存的位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)

#将头文件路径包含
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(xml_static STATIC tinyxml2.cpp)
set_target_properties(xml_static PROPERTIES OUTPUT_NAME "tinyxml2")
set_target_properties(xml_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_library(tcp_static STATIC MY_TCP.cpp)
set_target_properties(tcp_static PROPERTIES OUTPUT_NAME "tcp")
set_target_properties(tcp_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)


#add_library(xml_shared SHARED client.cpp)
#set_target_properties(xml_shared PROPERTIES OUTPUT_NAME "tinyxml2")
#set_target_properties(xml_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

#version
#set_target_properties(xml_shared PROPERTIES VERSION 1.0 SOVERSION 1.0)

add_executable(server server.cpp)
add_executable(client client.cpp)
#target_link_libraries(client ${CMAKE_SOURCE_DIR}/lib/libtinyxml2.so.1.0)

#链接静态库
target_link_libraries(client ${CMAKE_SOURCE_DIR}/lib/libtcp.a ${CMAKE_SOURCE_DIR}/lib/libtinyxml2.a)
target_link_libraries(server ${CMAKE_SOURCE_DIR}/lib/libtcp.a ${CMAKE_SOURCE_DIR}/lib/libtinyxml2.a)

