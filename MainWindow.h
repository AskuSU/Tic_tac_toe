#pragma once
#include"BaseWin.h"
#include"Resource.h"
#include "GameField.h"
#include "GameLogic.h"

#include<list>
#include <memory>
using namespace std;

class MainWindow : public BaseWindow<MainWindow>
{
    /*enum Mode
    {
        DrawMode,
        SelectMode,
        DragMode
    };*/

    GameField gameField;
    GameLogic gameLogic;

    //HCURSOR                 hCursor;

    ID2D1Factory*           pFactory;
    ID2D1HwndRenderTarget*  pRenderTarget;
    ID2D1SolidColorBrush*   pBrush;
    D2D1_POINT_2F           ptMouse;

    //Mode                    mode;
    size_t                  nextColor;
    
    list<shared_ptr<CellField>>             cells;
    list<shared_ptr<CellField>>::iterator   selection;
        
    shared_ptr<CellField> Selection();
    

    void    ClearSelection() { selection = cells.end(); }
    //HRESULT InsertEllipse(float x, float y);

    BOOL    HitTest(POINT pt);
    void    clickOnCell(POINT pt);
    //void    SetMode(Mode m);
    //void    MoveSelection(float x, float y);
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void    OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void    OnLButtonUp();
    //void    OnMouseMove(int pixelX, int pixelY, DWORD flags);
    //void    OnKeyDown(UINT vkey);
    void    CalculeteObjectOnField();

public:

    MainWindow(HINSTANCE* hInst);    
    
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    //  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
    //  ÷≈Ћ№: ќбрабатывает сообщени€ в главном окне.
    //static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

HINSTANCE* BaseWindow<MainWindow>::pt_hInst = nullptr;