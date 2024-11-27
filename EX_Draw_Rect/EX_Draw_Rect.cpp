
// EX_Draw_Rect.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "EX_Draw_Rect.h"
#include "EX_Draw_RectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEXDrawRectApp

BEGIN_MESSAGE_MAP(CEXDrawRectApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEXDrawRectApp 생성

CEXDrawRectApp::CEXDrawRectApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CEXDrawRectApp 개체입니다.

CEXDrawRectApp theApp;


// CEXDrawRectApp 초기화

BOOL CEXDrawRectApp::InitInstance()
{
	CWinApp::InitInstance();

	CEXDrawRectDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

