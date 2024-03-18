cmake_minimum_required(VERSION 3.5)
project(laser_chess_server VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)
endif()

########################## Common Lib #############################
file(GLOB_RECURSE common_src RELATIVE "${CMALE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/common/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/common/src/**/**.cpp")
add_library(common ${common_src})
target_include_directories(common PRIVATE "common/include/")

##########################   Server   #############################
file(GLOB_RECURSE server_src RELATIVE "${CMALE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/server/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/server/src/**/**.cpp")
if (server_src)
  add_executable(server ${server_src})
  target_include_directories(server PRIVATE "server/include" "common/include")
  target_link_libraries(server PRIVATE common)
endif()

##########################     AI     #############################
file(GLOB_RECURSE ai_src RELATIVE "${CMALE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/ai/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/ai/src/**/**.cpp")
# if (ai_src)
#   add_executable(ai_client ${ai_src})
#   target_include_directories(ai_client PRIVATE "ai/include" "common/include")
#   target_link_libraries(ai_client PRIVATE common)
# endif()
