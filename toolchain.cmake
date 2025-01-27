# Nome do sistema operacional
set(CMAKE_SYSTEM_NAME Windows)

# Compilador para C
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

# Compilador para C++
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Localização das bibliotecas do MinGW
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Modo de busca para bibliotecas e cabeçalhos
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
