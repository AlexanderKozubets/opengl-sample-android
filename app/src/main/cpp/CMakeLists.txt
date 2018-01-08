cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Sources
set(SOURCES
  "native-lib.cpp"
  "Shader.cpp"
  "gl_wrapper/GL2.cpp"
  "repository/ShaderRepository.cpp"
  "scenes/Scene.cpp"
  "scenes/triangle/TriangleScene.cpp"
  "scenes/texture/TextureScene.cpp"
  "scenes/transformation/TransformationScene.cpp"
  )

add_library(native-lib SHARED ${SOURCES} )

target_include_directories(native-lib PRIVATE
     ${CMAKE_CURRENT_SOURCE_DIR}
     ${CMAKE_CURRENT_SOURCE_DIR}/math
     ${CMAKE_CURRENT_SOURCE_DIR}/scenes/triangle
     ${CMAKE_CURRENT_SOURCE_DIR}/scenes/texture
     ${CMAKE_CURRENT_SOURCE_DIR}/scenes/transformation
     ${CMAKE_CURRENT_SOURCE_DIR}/utils
     ${CMAKE_CURRENT_SOURCE_DIR}/gl_wrapper)

# add lib dependencies
target_link_libraries(native-lib
                      android
                      log 
                      EGL
                      GLESv2)

