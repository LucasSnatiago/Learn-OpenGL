#include <GLFW/glfw3.h>
#include <iostream>

#ifdef _WIN32
#include <windows/main.hpp>
#include <windows.h>
#include <shellapi.h> // Para CommandLineToArgvW
#endif

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Converte a linha de comando para argc e argv
    int argc;
    char** argv;

    // Usando CommandLineToArgvW para converter a linha de comando
    LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argvW) {
        return -1;
    }

    // Converte argvW (wide char) para argv (multibyte)
    argv = (char**)malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; i++) {
        int size = WideCharToMultiByte(CP_UTF8, 0, argvW[i], -1, NULL, 0, NULL, NULL);
        argv[i] = (char*)malloc(size);
        WideCharToMultiByte(CP_UTF8, 0, argvW[i], -1, argv[i], size, NULL, NULL);
    }
    LocalFree(argvW);

    // Chama a função main com os argumentos
    int result = main(argc, argv, nullptr);

    // Libera a memória alocada para argv
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);

    return result;
}
#endif
