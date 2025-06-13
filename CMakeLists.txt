cmake_minimum_required(VERSION 3.13)
project(chat_app)

find_package(vsomeip3 REQUIRED)
find_package(Boost REQUIRED)

add_executable(chat_server server/chat_server.cpp)
add_executable(chat_client client/chat_client.cpp)

target_link_libraries(chat_server vsomeip3)
target_link_libraries(chat_client vsomeip3)
