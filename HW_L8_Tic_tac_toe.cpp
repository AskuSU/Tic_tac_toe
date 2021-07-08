#include "HW_L8_Tic_tac_toe.h"


#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    MainWindow MainWin(&hInst); //Главное окно

    

    MainWin.SetSizeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    MainWin.RegisterWinClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!MainWin.InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HWL8TICTACTOE));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



