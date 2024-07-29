
// ColorDlg.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ColorDlg.h"
#include "ColorDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorDlgApp

BEGIN_MESSAGE_MAP(CColorDlgApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CColorDlgApp 생성

CColorDlgApp::CColorDlgApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CColorDlgApp 개체입니다.

CColorDlgApp theApp;


// CColorDlgApp 초기화

BOOL CColorDlgApp::InitInstance()
{
	CWinApp::InitInstance();

	CColorDlgDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

