#pragma once

#include <windows.h>
#include <Windowsx.h>
#include "framework.h"
#include <d2d1.h>

#pragma comment(lib, "d2d1")

#ifndef _BASEWIN_H
#define _BASEWIN_H

#define MAX_LOADSTRING 100

template <class DERIVED_TYPE>
class BaseWindow
{
public:

    BaseWindow();
    HWND Window() const { return m_hwnd; }

    BOOL SetSizeWindow(size_t width, size_t height) : this.width(width), this.height(height) { return true };

    //  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
    //  ����: ������������ ��������� � ������� ����.
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    //  �������: MyRegisterClass()
    //  ����: ������������ ����� ����.
    ATOM MyRegisterClass(HINSTANCE hInstance);
    
    //  �������: InitInstance(HINSTANCE, int)
    //  ����: ��������� ������ ���������� � ������� ������� ����
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );    

protected:
    WCHAR szTitle[MAX_LOADSTRING];        // ����� ������ ���������
    WCHAR szWindowClass[MAX_LOADSTRING];  // ��� ������ �������� ����

    HWND m_hwnd;
    size_t width, height;

    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

#endif