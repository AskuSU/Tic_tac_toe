#pragma once

#include <windows.h>
#include <Windowsx.h>
#include "framework.h"
#include "resource.h"
#include <d2d1.h>

#pragma comment(lib, "d2d1")

#ifndef _BASEWIN_H
#define _BASEWIN_H

#define MAX_LOADSTRING 100

template <class DERIVED_TYPE>
class BaseWindow
{
private:

    WCHAR szTitle[MAX_LOADSTRING];        // “екст строки заголовка
    WCHAR szWindowClass[MAX_LOADSTRING];  // им€ класса главного окна

public:

    static HINSTANCE* pt_hInst;  // текущий экземпл€р
    BaseWindow(HINSTANCE* hInst);
    HWND Window() const { return hWnd; }

    BOOL SetSizeWindow(size_t width, size_t height);
    
    /*
    //  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
    //  ÷≈Ћ№: ќбрабатывает сообщени€ в главном окне.
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    */
    //  ‘”Ќ ÷»я: MyRegisterClass()
    //  ÷≈Ћ№: –егистрирует класс окна.
    ATOM RegisterWinClass(HINSTANCE hInstance);
    
    //  ‘”Ќ ÷»я: InitInstance(HINSTANCE, int)
    //  ÷≈Ћ№: —охран€ет маркер экземпл€ра и создает главное окно
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

    //  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
    //  ÷≈Ћ№: ќбрабатывает сообщени€ в главном окне.
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    // ќбработчик сообщений дл€ окна "ќ программе".    
    static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

    template <class T> void SafeRelease(T** ppT);


protected:

    HWND hWnd;
    size_t width, height;

    PCWSTR  ClassName() const { return szWindowClass; };
    PCWSTR  TitleName() const { return szTitle; };
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};



#endif