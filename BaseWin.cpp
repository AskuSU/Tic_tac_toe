#include "BaseWin.h"

// онструктор Ѕазового окна
template<class DERIVED_TYPE>
BaseWindow<DERIVED_TYPE>::BaseWindow() : m_hwnd(NULL)
{
    // »нициализаци€ глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HWL8TICTACTOE, szWindowClass, MAX_LOADSTRING);
}

//  ‘”Ќ ÷»я: MyRegisterClass()
//
//  ÷≈Ћ№: –егистрирует класс окна.
//
template<class DERIVED_TYPE>
inline ATOM BaseWindow<DERIVED_TYPE>::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //CS_NOCLOSE - отключить кнопку закрыть
    wcex.lpfnWndProc = DERIVED_TYPE::WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //GetModuleHandle(NULL); //≈сли €вно не передал hInstance
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HWL8TICTACTOE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_HWL8TICTACTOE);
    wcex.lpszClassName = ClassName();// szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
template<class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = ClassName();

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
        dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
        nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
    );

    return (m_hwnd ? TRUE : FALSE);
}
//   ‘”Ќ ÷»я: InitInstance(HINSTANCE, int)
//
//   ÷≈Ћ№: —охран€ет маркер экземпл€ра и создает главное окно
//
//    ќћћ≈Ќ“ј–»»:
//
//        ¬ этой функции маркер экземпл€ра сохран€етс€ в глобальной переменной, а также
//        создаетс€ и выводитс€ главное окно программы.
//
template<class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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

//  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ÷≈Ћ№: ќбрабатывает сообщени€ в главном окне.
//
//  WM_COMMAND  - обработать меню приложени€
//  WM_PAINT    - ќтрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернутьс€
//
template<class DERIVED_TYPE>
LRESULT BaseWindow<DERIVED_TYPE>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DERIVED_TYPE* pThis = NULL;

    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hwnd = hwnd;
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