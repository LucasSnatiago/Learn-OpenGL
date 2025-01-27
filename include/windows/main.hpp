#include <GLFW/glfw3.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h> // Para CommandLineToArgvW
#endif

#ifdef _WIN32
int main(int argc, char **argv, char **env);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

#endif
