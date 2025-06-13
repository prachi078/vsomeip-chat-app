cmake_minimum_required(VERSION 3.13)
project(vsomeip_chat)

find_package(vsomeip3 REQUIRED)

add_executable(chat_user1 user1/chat_user1.cpp)
target_link_libraries(chat_user1 vsomeip3)

add_executable(chat_user2 user2/chat_user2.cpp)
target_link_libraries(chat_user2 vsomeip3)
