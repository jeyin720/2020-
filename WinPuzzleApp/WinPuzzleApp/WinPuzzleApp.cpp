// WinPuzzleApp.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WinPuzzleApp.h"
#include <time.h>
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool MoveBlock(int key, int* pnCursorX, int* pnCursorY, HWND(*pHwnds)[5], int(*pXPos)[5], int(*pYPos)[5]);
bool TestBlocks(HWND(*pHwnds)[5], HWND(*pHwnds2nd)[5]);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINPUZZLEAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINPUZZLEAPP));

    MSG msg;

    // 기본 메시지 루프입니다.
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



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINPUZZLEAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINPUZZLEAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, TEXT("퍼즐게임"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND s_hwnd[5][5];
	static HWND s_hwnd2nd[5][5];

	static int s_nXPos[5][5];
	static int s_nYPos[5][5];
	static int s_nCursorX;
	static int s_nCursorY;

    switch (message)
    {
	case WM_CREATE: 
	{
		s_nCursorX = 4;
		s_nCursorY = 4;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				s_nXPos[i][j] = 10 + j * 60;
				s_nYPos[i][j] = 10 + i * 60;
				if (i == 4 && j == 4)
				{
					s_hwnd[i][j] = NULL;
					break;
				}
					s_hwnd[i][j] = CreateWindow(TEXT("STATIC"), NULL
						, WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE
						, s_nXPos[i][j], s_nYPos[i][j], 50, 50, hWnd, (HMENU)-1
						, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
					TCHAR IpszNumber[10];
					wsprintf(IpszNumber, _T("%d"), (i * 5) + j + 1);
					SetWindowText(s_hwnd[i][j], IpszNumber);

					s_hwnd2nd[i][j] = s_hwnd[i][j];
			}
		}
		srand((unsigned int)time(NULL));
		int key = 0;

		for (int i = 0; i < 3; ++i) {
			key = VK_LEFT+ (rand()%4);
			MoveBlock(key, &s_nCursorX, &s_nCursorY, s_hwnd, s_nXPos, s_nYPos);
		}
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
					if (s_hwnd[i][j] != NULL)
						DestroyWindow(s_hwnd[i][j]);
					PostQuitMessage(0);
			}
		}
        break;
	case WM_KEYUP:
	{
		
		if (MoveBlock(wParam, &s_nCursorX, &s_nCursorY, s_hwnd, s_nXPos, s_nYPos)) {
			if (TestBlocks(s_hwnd, s_hwnd2nd) == true) {
				MessageBox(hWnd, TEXT("게임 종료"), TEXT("정보"), MB_OK);
			}
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);//X
		int y = HIWORD(lParam);//Y
		int key;
		int tileX = (x - 10) / 60;
		int tileY = (y - 10) / 60;
		if (tileX >= 0 && tileX < 5 && tileY >= 0 && tileY < 5) {
			int XOffset = s_nCursorX - tileX;
			int YOffset = s_nCursorY - tileY;

			if (abs(XOffset) <= 1 && abs(YOffset) <= 1 &&(abs( XOffset)+abs(YOffset))==1){
				key = (XOffset == -1) ? VK_LEFT : (XOffset == 1) ? VK_RIGHT : (YOffset == -1) ? VK_UP : (YOffset == 1) ? VK_DOWN : 0;
				if (MoveBlock(key, &s_nCursorX, &s_nCursorY, s_hwnd, s_nXPos, s_nYPos)) {
					if (TestBlocks(s_hwnd, s_hwnd2nd) == true) {
						MessageBox(hWnd, TEXT("게임 종료"), TEXT("정보"), MB_OK);
					}
				}
			}
		}
	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}
bool TestBlocks(HWND(*pHwnds)[5], HWND(*pHwnds2nd)[5]) {
	if (pHwnds[4][4] == NULL) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (pHwnds2nd[i][j] != pHwnds[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}
bool MoveBlock(int key, int* pnCursorX, int* pnCursorY, HWND(*pHwnds)[5],int(*pXPos)[5], int(*pYPos)[5]) {
	bool bResult = false;

	int XOffset = 0, YOffset = 0;
	XOffset = (key == VK_RIGHT) ? -1 : (key == VK_LEFT) ? 1 : 0;
	YOffset = (key == VK_UP) ? 1 : (key == VK_DOWN) ? -1 : 0;

	if (*pnCursorY + YOffset >= 0 && *pnCursorY + YOffset<5 && *pnCursorX + XOffset >= 0 && *pnCursorX + XOffset<5)
	{
		HWND hwnd = pHwnds[*pnCursorY + YOffset][*pnCursorX + XOffset];
		MoveWindow(hwnd, pXPos[*pnCursorY][*pnCursorX], pYPos[*pnCursorY][*pnCursorX], 50, 50, TRUE);
		pHwnds[*pnCursorY][*pnCursorX] = hwnd; //핸들 이동
		pHwnds[*pnCursorY + YOffset][*pnCursorX + XOffset] = NULL;
		*pnCursorX += XOffset;
		*pnCursorY += YOffset;
		bResult = true;
	}
	return bResult;
}
// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
