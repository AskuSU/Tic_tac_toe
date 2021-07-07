#include "BaseWin.h"

#include"MainWindow.h"
// Explicit template instantiation
template class BaseWindow<MainWindow>;

//Конструктор Базового окна
template<class DERIVED_TYPE>
BaseWindow<DERIVED_TYPE>::BaseWindow(HINSTANCE* hInst) : hWnd(NULL)
{    
    pt_hInst = hInst;
    // Инициализация глобальных строк
    LoadStringW(*pt_hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(*pt_hInst, IDC_HWL8TICTACTOE, szWindowClass, MAX_LOADSTRING);
}

template<class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::SetSizeWindow(size_t width, size_t height)
{
    BaseWindow::width = width;
    BaseWindow::height = height;
    return true;
}

//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
template<class DERIVED_TYPE>
inline ATOM BaseWindow<DERIVED_TYPE>::RegisterWinClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //CS_NOCLOSE - отключить кнопку закрыть
    wcex.lpfnWndProc = MainWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //GetModuleHandle(NULL); //Если явно не передал hInstance
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HWL8TICTACTOE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_HWL8TICTACTOE);
    wcex.lpszClassName = ClassName();// szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
template<class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd = CreateWindowW(ClassName(), TitleName(), WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - width) / 2,  // x центр формы
        (GetSystemMetrics(SM_CYSCREEN) - height) / 2, // y центр формы
        width,                                        // width 
        height,                                       // height
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
template<class DERIVED_TYPE>
LRESULT BaseWindow<DERIVED_TYPE>::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DERIVED_TYPE* pThis = NULL;

    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->hWnd = hwnd;
    }
    else
    {
        pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pThis)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


template<class DERIVED_TYPE>
template<class T>
inline void BaseWindow<DERIVED_TYPE>::SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }    
}

// Обработчик сообщений для окна "О программе".
static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}