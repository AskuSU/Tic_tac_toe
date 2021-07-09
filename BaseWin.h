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

    WCHAR szTitle[MAX_LOADSTRING];        // ����� ������ ���������
    WCHAR szWindowClass[MAX_LOADSTRING];  // ��� ������ �������� ����

public:

    static HINSTANCE* pt_hInst;  // ������� ���������
    BaseWindow(HINSTANCE* hInst);
    HWND Window() const { return hWnd; }

    BOOL SetSizeWindow(size_t width, size_t height);
    
    /*
    //  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
    //  ����: ������������ ��������� � ������� ����.
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    */
    //  �������: MyRegisterClass()
    //  ����: ������������ ����� ����.
    ATOM RegisterWinClass(HINSTANCE hInstance);
    
    //  �������: InitInstance(HINSTANCE, int)
    //  ����: ��������� ������ ���������� � ������� ������� ����
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

    //  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
    //  ����: ������������ ��������� � ������� ����.
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    // ���������� ��������� ��� ���� "� ���������".    
    static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

    template <class T>
    void SafeRelease(T** ppT);


protected:

    HWND hWnd;
    size_t width, height;

    PCWSTR  ClassName() const { return szWindowClass; };
    PCWSTR  TitleName() const { return szTitle; };
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

template<class DERIVED_TYPE>
template<class T>
void BaseWindow<DERIVED_TYPE>::SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

#endif