cmake_minimum_required(VERSION 3.27)
cmake_policy(SET CMP0072 NEW)

# Nome do projeto e definição dos padrões de linguagem
project(LearnOpenGL LANGUAGES C CXX VERSION 0.1.0)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Adicionar o diretório ./include ao caminho de inclusão
include_directories(${CMAKE_SOURCE_DIR}/include)

# Adicionar as fontes do projeto
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/shaders/*.cpp
    ${CMAKE_SOURCE_DIR}/src/texture/*.cpp
    ${CMAKE_SOURCE_DIR}/src/window/*.c
    ${CMAKE_SOURCE_DIR}/src/input/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

find_package(OpenGL REQUIRED)

# Faz o download e inclui o GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw)


# Cria o executável e inclui as bibliotecas necessárias
add_executable(${PROJECT_NAME} ${SOURCES})

# Adicionar glad
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/gl.c)
add_library(vulkan STATIC ${CMAKE_SOURCE_DIR}/src/vulkan.c)

# Linkar o executável com glad, glfw e OpenGL
target_link_libraries(${PROJECT_NAME} glad vulkan glfw GL X11 wayland-client pthread Xrandr Xi dl)
