#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE* hInst) : BaseWindow(hInst), pFactory(NULL), pRenderTarget(NULL), pBrush(NULL),
ptMouse(D2D1::Point2F()), nextColor(0)//, selection(ellipses.end())
{
    CalculeteObjectOnField();
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        //DPIScale::Initialize(pFactory);
        //SetMode(DrawMode);
        return 0;

    case WM_DESTROY:
        //DiscardGraphicsResources();
        //SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        Resize();
        return 0;

    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    case WM_LBUTTONUP:
        OnLButtonUp();
        return 0;

    case WM_MOUSEMOVE:
        //OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    /*case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(hCursor);
            return TRUE;
        }
        break;*/

    case WM_KEYDOWN:
        //OnKeyDown((UINT)wParam);
        return 0;

    case WM_COMMAND:
        /*switch (LOWORD(wParam))
        {
        case ID_DRAW_MODE:
            SetMode(DrawMode);
            break;

        case ID_SELECT_MODE:
            SetMode(SelectMode);
            break;

        case ID_TOGGLE_MODE:
            if (mode == DrawMode)
            {
                SetMode(SelectMode);
            }
            else
            {
                SetMode(DrawMode);
            }
            break;
        }*/
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

////  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
////
////  WM_COMMAND  - обработать меню приложения
////  WM_PAINT    - Отрисовка главного окна
////  WM_DESTROY  - отправить сообщение о выходе и вернуться
////
//LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // Разобрать выбор в меню:
//        switch (wmId)
//        {
//        case IDM_ABOUT:
//                DialogBox(*pt_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About, 0L);
//            break;
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }    
//    return 0;    
//}

shared_ptr<CellField> MainWindow::Selection()
{
    if (selection == cells.end())
    {
        return nullptr;
    }
    else
    {
        return (*selection);
    }
}

BOOL MainWindow::HitTest(POINT pt)
{
    for (auto i = cells.rbegin(); i != cells.rend(); ++i)
    {
        if ((*i)->HitTest(pt))
        {
            selection = (++i).base();
            return TRUE;
        }
    }
    return FALSE;
}

void MainWindow::clickOnCell(POINT pt)
{
}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 1.0f);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);

        pRenderTarget->BeginDraw();        

        for (auto i = cells.begin(); i != cells.end(); i++)
        {
            (*i)->DrawCell(pRenderTarget, pBrush);
            (*i)->DrawValue(pRenderTarget, pBrush);

        }
        //if (Selection())
        //{
        //    pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
        //   // pRenderTarget->DrawRectangle(Selection()->rect, pBrush, gameF.thicknessBorderpx);
        //}
        /*pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

        rect = D2D1::RectF(
            300 / 2 - 50.0f,
            200 / 2 - 50.0f,
            300 / 2 + 50.0f,
            200 / 2 + 50.0f
        );
        
        pRenderTarget->DrawRectangle(rect, pBrush, 3.0f);*/

        /*for (auto i = ellipses.begin(); i != ellipses.end(); ++i)
        {
            (*i)->Draw(pRenderTarget, pBrush);
        }

        if (Selection())
        {
            pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
            pRenderTarget->DrawEllipse(Selection()->ellipse, pBrush, 2.0f);
        }*/

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(hWnd, &ps);
    }
}

void MainWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);

        InvalidateRect(hWnd, NULL, FALSE);
    }
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
    
    POINT pt = { pixelX, pixelY };

    if (HitTest(pt))
    {
        gameLogic.playerTurn(Selection().get());
    }
            
    InvalidateRect(hWnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp()
{
    //InvalidateRect(hWnd, NULL, FALSE);
    //ReleaseCapture();
}

void MainWindow::CalculeteObjectOnField()
{
    for (size_t i = 0; i < gameField.sizeMatrix; i++)
    {
        for (size_t j = 0; j < gameField.sizeMatrix; j++)
        {
            selection = cells.insert(
                cells.end(),
                shared_ptr<CellField>(new CellField(&gameField)));

            Selection()->rect.top = (float)gameField.spaceBetweenCellpx + (gameField.sizeCellpx + gameField.spaceBetweenCellpx) * i;
            Selection()->rect.left = (float)gameField.spaceBetweenCellpx + (gameField.sizeCellpx + gameField.spaceBetweenCellpx) * j;
            Selection()->rect.bottom = Selection()->rect.top + gameField.sizeCellpx;
            Selection()->rect.right = Selection()->rect.left + gameField.sizeCellpx;
        }        
    }
}
