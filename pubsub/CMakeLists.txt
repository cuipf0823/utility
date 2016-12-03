PROJECT(pubsub)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_INSTALL_PREFIX  ${CMAKE_SOURCE_DIR})
SET(src_path ${CMAKE_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${src_path}/proto)
message(STATUS ${src_path})
SET(src_list
${src_path}codec/codec.h
${src_path}codec/codec.cc
${src_path}dispatcher.h
${src_path}subclient.h
${src_path}subclient.cc
${src_path}proto/pubsub.pb.h
${src_path}proto/pubsub.pb.cc
${src_path}pubsub_client.cc
)

SET(src_list_s
${src_path}codec/codec.h
${src_path}codec/codec.cc
${src_path}dispatcher.h
${src_path}pubserver.h
${src_path}pubserver.cc
${src_path}proto/pubsub.pb.h
${src_path}proto/pubsub.pb.cc
${src_path}pubsub_server.cc
${src_path}topic.h
${src_path}topic.cc
)

add_executable(pubsub_server ${src_list_s})
add_executable(pubsub_client ${src_list})
target_link_libraries(pubsub_client "muduo_net" "muduo_base" "pthread" "protobuf" "z")
target_link_libraries(pubsub_server "muduo_net" "muduo_base" "pthread" "protobuf" "z")
add_definitions("-ggdb -ffunction-sections -O0 -std=c++11")
#install(targets pubsub_client destination bin)
install (TARGETS pubsub_client pubsub_server DESTINATION bin)
