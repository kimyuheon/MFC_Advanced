// UserBtn.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
#include "pch.h"
#include "framework.h"
#include "UserBtn.h"
#include "UserBtnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// UserBtnApp
BEGIN_MESSAGE_MAP(UserBtnApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// UserBtnApp 생성
UserBtnApp::UserBtnApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 UserBtnApp 개체입니다.
UserBtnApp theApp;

// UserBtnApp 초기화
BOOL UserBtnApp::InitInstance()
{
	CWinApp::InitInstance();

	UserBtnDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}