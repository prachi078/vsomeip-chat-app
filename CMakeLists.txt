# cmake_minimum_required(VERSION 3.13)
# project(vsomeip_chat)

# find_package(vsomeip3 REQUIRED)

# add_executable(chat_user1 user1/chat_user1.cpp)
# target_link_libraries(chat_user1 vsomeip3)

# add_executable(chat_user2 user2/chat_user2.cpp)
# target_link_libraries(chat_user2 vsomeip3)



cmake_minimum_required(VERSION 3.13)
project(chat_app)

#  Set Boost paths for ARM64 build
set(BOOST_ROOT "/home/prachi/vscode/boost/boost-arm64")
set(BOOST_LIBRARYDIR "/home/prachi/vscode/boost/boost-arm64/lib")

#  Find required packages
find_package(vsomeip3 REQUIRED)
find_package(Boost 1.76 REQUIRED COMPONENTS system thread)

#  Include directories
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#  Add executables
add_executable(chat_user1 user1/chat_user1.cpp)
target_link_libraries(chat_user1 vsomeip3 ${Boost_LIBRARIES})

add_executable(chat_user2 user2/chat_user2.cpp)
target_link_libraries(chat_user2 vsomeip3 ${Boost_LIBRARIES})
