cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_library(native-lib SHARED
            native-lib.cpp)

# add lib dependencies
target_link_libraries(native-lib
                      android
                      log 
                      EGL
                      GLESv2)

