cmake_minimum_required(VERSION 3.27)
cmake_policy(SET CMP0072 NEW)

# Nome do projeto e definição dos padrões de linguagem
project(LearnOpenGL LANGUAGES C CXX VERSION 0.1.0)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Adicionar o diretório ./include ao caminho de inclusão
include_directories(${CMAKE_SOURCE_DIR}/include)

# Adicionar as fontes do projeto
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c*
    ${CMAKE_SOURCE_DIR}/src/**/*.c*
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

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)


# Cria o executável e inclui as bibliotecas necessárias
add_executable(${PROJECT_NAME} ${SOURCES})

# Adicionar glad
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/gl.c)
add_library(vulkan STATIC ${CMAKE_SOURCE_DIR}/src/vulkan.c)

# Se estiver no windows não exibir o console para o usuario
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _GLFW_WIN32)
endif()

# Linkar o executável com glad, glfw e OpenGL
if (MSVC)
  target_link_libraries(${PROJECT_NAME} glad vulkan glfw glm OpenGL32)
else()
  target_link_libraries(${PROJECT_NAME} glad vulkan glfw GL glm X11 wayland-client pthread Xrandr Xi dl)
endif()
