#pragma once

#ifndef YSXWIN_H
#define YSXWIN_H

//#include "framework.h"
#include "windows.h"
#include "Wingdi.h" // https://docs.microsoft.com/en-us/windows/desktop/api/wingdi

#define MAX_LOADSTRING 100

// #####################
// ####### By Sophia Cristina
// #######
// #####################

// #################################################
// REFERENCES:
// [1] https://docs.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
// [2] https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
// [3] https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowW
// [4] https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633573(v=vs.85) // Window Proc
// [5] https://github.com/MicrosoftDocs/cpp-docs
// [6] http://www.winprog.org/tutorial/
// - PAINT:
// [p1] https://docs.microsoft.com/en-us/windows/win32/gdi/colorref // COLORREF RGB COLOR: '0x00ffffff = white' | typedef DWORD COLORREF; typedef DWORD* LPCOLORREF;
// [p2] https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createsolidbrush // I used to paint the background, it is a HBRUSH function
// [p3] https://docs.microsoft.com/en-us/windows/win32/gdi/about-painting-and-drawing // Topics about it
//     [1] https://docs.microsoft.com/en-us/windows/win32/gdi/when-to-draw-in-a-window
//     [2] https://docs.microsoft.com/en-us/windows/win32/gdi/using-the-wm-paint-message
//        [1] https://docs.microsoft.com/en-us/windows/win32/gdi/the-wm-paint-message
//     [3] https://docs.microsoft.com/en-us/windows/win32/gdi/drawing-in-the-client-area
// [p4] https://docs.microsoft.com/en-us/windows/win32/gdi/painting-and-drawing
// [p5] https://docs.microsoft.com/en-us/windows/win32/api/gdipluspen/nl-gdipluspen-pen // Pen class (gdipluspen.h) | Windows GDI + object used to draw lines and curves.
// [p6] https://docs.microsoft.com/en-us/windows/win32/gdi/filled-shapes // Filled shapes are geometric forms that are outlined by using the current pen and filled by using the current brush.
                                                                         // There are five filled shapes: Ellipse; Chord; Pie; Polygon; Rectangle;
// [p7] https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-paintstruct // PAINTSTRUCT structure contains information for an application. This information can be used to
                                                                                          // paint the client area of a window owned by that application.
                                                                                          // { HDC  hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32]; }
// [p8] https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-redrawwindow // BOOL RedrawWindow(HWND hWnd, const RECT* lprcUpdate, HRGN hrgnUpdate, UINT flags);
                                                                                           // hWnd: A handle to the window to be redrawn.If this parameter is NULL, the desktop window is updated.
                                                                                           // lprcUpdate: A pointer to a RECT structure containing the coordinates, in device units, of the update
                                                                                           //             rectangle.This parameter is ignored if the hrgnUpdate parameter identifies a region.
                                                                                           // hrgnUpdate: A handle to the update region.If both the hrgnUpdateand lprcUpdate parameters are NULL,
                                                                                           //             the entire client area is added to the update region.
                                                                                           // flags: One or more redraw flags.This parameter can be used to invalidate or validate a window,
                                                                                           //        control repainting, and control which windows are affected by RedrawWindow.

// [p9] https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-beginpaint
// [p10] https://docs.microsoft.com/en-us/windows/win32/gdi/painting-and-drawing-functions
// #################################################

// ###############################################################################################################################################################################
// FROM VISUAL STUDIO:
#define MAX_LOADSTRING 100

//HBRUSH MainBrush = CreateSolidBrush(RGB(0, 0, 0));
// ###############################################################################################################################################################################

// ###############################################################################################################################################################################

// STRING TO WCHAR:
// Use the same size of the string OR LESS!
WCHAR* Str2WCHAR(std::string s, const int Size)
{
    WCHAR* c = new WCHAR[Size];
    for (int n = 0; n < s.size(); ++n) { c[0] = s[n]; }
    return (c);
}

// #################################################
// DIALOG BOX:
INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################



// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_