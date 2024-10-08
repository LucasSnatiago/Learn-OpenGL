cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0072 NEW)

# Nome do projeto e definição dos padrões de linguagem
project(LearnOpenGL LANGUAGES C CXX VERSION 0.1.0)

# Adicionar o diretório ./include ao caminho de inclusão
include_directories(${CMAKE_SOURCE_DIR}/include)

# Adicionar as fontes do projeto
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/window/*.c
    ${CMAKE_SOURCE_DIR}/src/input/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

find_package(OpenGL REQUIRED)

# Cria o executável e inclui as bibliotecas necessárias
add_executable(${PROJECT_NAME} ${SOURCES})

# Adicionar glad
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/glad.c)

# Linkar o executável com glad, glfw e OpenGL
target_link_libraries(${PROJECT_NAME} glad glfw GL X11 wayland-client pthread Xrandr Xi dl)
