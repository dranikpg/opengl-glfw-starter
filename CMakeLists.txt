cmake_minimum_required(VERSION 3.10)

project(OGL_APP)

include_directories("include")

file(GLOB SRC
    "include/*.hpp"
    "source/*.cpp"
)
add_executable(main ${SRC})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 3 REQUIRED)
target_link_libraries(main glfw)

cmake_policy (SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)
