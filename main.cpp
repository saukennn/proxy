#define _WIN32_WINNT 0x0601 //

#include <Windows.h>
#include <iostream>

bool IniciaCnf(char* retIP, char* retPorta, char* entIP, char* entPorta) {
    HKEY hKey;
    DWORD dwValue = 1;
    DWORD dwType = REG_DWORD;
    DWORD dwSize = sizeof(DWORD);

    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao abrir a chave do registro.", "Erro", MB_ICONERROR);
        return false;
    }

    if (RegSetValueEx(hKey, "ProxyServer", 0, REG_SZ, (const BYTE*)entIP, strlen(entIP) + 1) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao configurar o endereço IP de entrada.", "Erro", MB_ICONERROR);
        RegCloseKey(hKey);
        return false;
    }

    if (RegSetValueEx(hKey, "ProxyPort", 0, REG_SZ, (const BYTE*)entPorta, strlen(entPorta) + 1) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao configurar a porta de entrada.", "Erro", MB_ICONERROR);
        RegCloseKey(hKey);
        return false;
    }

    if (RegSetValueEx(hKey, "ProxyEnable", 0, dwType, (const BYTE*)&dwValue, dwSize) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao configurar a opção de habilitar o proxy.", "Erro", MB_ICONERROR);
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);

    strncpy(retIP, entIP, strlen(entIP) + 1);
    strncpy(retPorta, entPorta, strlen(entPorta) + 1);

    return true;
}

bool RetornaCnf(char* entIP, char* entPorta) {
    HKEY hKey;
    char proxyServer[256];
    char proxyPort[256];
    DWORD bufferSize = sizeof(proxyServer);

    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao abrir a chave do registro.", "Erro", MB_ICONERROR);
        return false;
    }

    if (RegGetValue(hKey, NULL, "ProxyServer", RRF_RT_REG_SZ, NULL, proxyServer, &bufferSize) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao obter o endereço IP de retorno.", "Erro", MB_ICONERROR);
        RegCloseKey(hKey);
        return false;
    }

    bufferSize = sizeof(proxyPort);
    if (RegGetValue(hKey, NULL, "ProxyPort", RRF_RT_REG_SZ, NULL, proxyPort, &bufferSize) != ERROR_SUCCESS) {
        MessageBox(NULL, "Erro ao obter a porta de retorno.", "Erro", MB_ICONERROR);
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);

    strncpy(entIP, proxyServer, strlen(proxyServer) + 1);
    strncpy(entPorta, proxyPort, strlen(proxyPort) + 1);

    return true;
}

// Função de tratamento de mensagens da janela
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            char retIP[256];
            char retPorta[256];
            char entIP[] = "192.158.9.100";
            char entPorta[] = "3333";

            if (IniciaCnf(retIP, retPorta, entIP, entPorta)) {
                // Operação de proxy bem-sucedida
            } else {
                // Erro ao alterar as configurações de proxy
            }

            // Feche a janela após o processamento
            PostQuitMessage(0);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Registre a classe da janela
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ProxyWindow";
    RegisterClass(&wc);

    // Crie a janela
    HWND hwnd = CreateWindowEx(0, "ProxyWindow", "Alteração de Proxy", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, hInstance, NULL);

    // Exiba a janela
    ShowWindow(hwnd, nCmdShow);

    // Loop de mensagens
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
