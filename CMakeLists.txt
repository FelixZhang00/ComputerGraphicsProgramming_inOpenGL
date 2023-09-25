cmake_minimum_required(VERSION 3.24)
project(opengl_demo)

set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE INTERNAL "" FORCE)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLEW_H /opt/homebrew/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /opt/homebrew/Cellar/glfw/3.3.8/include/GLFW)
set(GLM_H /opt/homebrew/Cellar/glm/0.9.9.8/include)
include_directories(${GLEW_H} ${GLFW_H} ${GLM_H})

# Add target link
set(GLEW_LINK /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# Execute compilation command
set(SOURCE_FILES main.cpp)
add_executable(opengl_demo main.cpp Utils.cpp Utils.h Transform.cpp Transform.h)

if (APPLE)
    target_link_libraries(opengl_demo "-framework OpenGL")
    target_link_libraries(opengl_demo "-framework GLUT")
endif()