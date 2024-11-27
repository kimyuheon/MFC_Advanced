
// EX_Draw_RectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "EX_Draw_Rect.h"
#include "EX_Draw_RectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEXDrawRectDlg 대화 상자



CEXDrawRectDlg::CEXDrawRectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EX_DRAW_RECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	mp_select_object = NULL;
	m_is_clicked = NULL;
	m_resize_type = 0;
}

void CEXDrawRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEXDrawRectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADD_RECT, &CEXDrawRectDlg::OnBnClickedAddRect)
	ON_BN_CLICKED(IDC_REMOVE_RECT, &CEXDrawRectDlg::OnBnClickedRemoveRect)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CEXDrawRectDlg 메시지 처리기

BOOL CEXDrawRectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_WORK_RECT)->GetWindowRect(m_work_rect);
	ScreenToClient(m_work_rect);

	m_work_image.Create(m_work_rect.Width(), m_work_rect.Height(), 32);
	// CDC와 연결 및 사용
	m_work_dc.Attach(m_work_image.GetDC());
	DrawWorkImage();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEXDrawRectDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_work_image.Draw(dc, m_work_rect.left, m_work_rect.top);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CEXDrawRectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEXDrawRectDlg::DrawWorkImage()
{
	m_work_dc.SelectStockObject(DC_BRUSH);
	m_work_dc.SelectStockObject(DC_PEN);

	m_work_dc.SetDCBrushColor(RGB(0, 0, 0));
	m_work_dc.SetDCPenColor(RGB(200, 228, 255)); // 테두리 색상

	m_work_dc.Rectangle(0, 0, m_work_rect.Width(), m_work_rect.Height());
	m_work_dc.SelectStockObject(NULL_BRUSH);

	CRect* p;
	POSITION pos = m_object_list.GetHeadPosition();
	m_work_dc.SetDCPenColor(RGB(255, 255, 255));
	while (pos != NULL) {
		p = (CRect*)m_object_list.GetNext(pos);
		m_work_dc.Rectangle(p);
	}

	// 정점 그리기
	if (mp_select_object != NULL) { 
		int hw = mp_select_object->Width() / 2, hh = mp_select_object->Height() / 2;
		m_work_dc.SetDCPenColor(RGB(255, 255, 0));
		m_work_dc.Rectangle(mp_select_object->left - 4, mp_select_object->top - 4, mp_select_object->left + 4, mp_select_object->top + 4);
		m_work_dc.Rectangle(mp_select_object->left - 4 + hw, mp_select_object->top - 4, mp_select_object->left + 4 + hw, mp_select_object->top + 4);
		m_work_dc.Rectangle(mp_select_object->right - 4, mp_select_object->top - 4, mp_select_object->right + 4, mp_select_object->top + 4);
		m_work_dc.Rectangle(mp_select_object->right - 4, mp_select_object->top - 4 + hh, mp_select_object->right + 4, mp_select_object->top + 4 + hh);
		m_work_dc.Rectangle(mp_select_object->right - 4, mp_select_object->bottom - 4, mp_select_object->right + 4, mp_select_object->bottom + 4);
		m_work_dc.Rectangle(mp_select_object->left - 4 + hw, mp_select_object->bottom - 4, mp_select_object->left + 4 + hw, mp_select_object->bottom + 4);
		m_work_dc.Rectangle(mp_select_object->left - 4, mp_select_object->bottom - 4, mp_select_object->left + 4, mp_select_object->bottom + 4);
		m_work_dc.Rectangle(mp_select_object->left - 4, mp_select_object->top - 4 + hh, mp_select_object->left + 4, mp_select_object->top + 4 + hh);
	}
}



void CEXDrawRectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_work_dc.Detach();
	m_work_image.ReleaseDC();
	m_work_image.Destroy();

	POSITION pos = m_object_list.GetHeadPosition();
	while (pos != NULL)
		delete (CRect*)m_object_list.GetNext(pos);
	m_object_list.RemoveAll();
}


void CEXDrawRectDlg::OnBnClickedAddRect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mp_select_object = new CRect(10, 10, 50, 50);
	m_object_list.AddTail(mp_select_object);

	DrawWorkImage();
	InvalidateRect(m_work_rect, 0);
}


void CEXDrawRectDlg::OnBnClickedRemoveRect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mp_select_object != NULL) {
		POSITION pos = m_object_list.Find(mp_select_object, 0);
		if (pos != NULL) {
			m_object_list.RemoveAt(pos);
			delete mp_select_object;
			mp_select_object = NULL;

			DrawWorkImage();
			InvalidateRect(m_work_rect, 0);
		}
	}
}


void CEXDrawRectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 좌표 재조정 (윈도우/클라이언트 좌표)
	point.x -= m_work_rect.left;
	point.y -= m_work_rect.top;

	CRect* p_old_object = mp_select_object;
	if (mp_select_object != NULL) {
		int hw = mp_select_object->Width() / 2, hh = mp_select_object->Height() / 2;
		if (CRect(mp_select_object->left - 4, mp_select_object->top - 4, mp_select_object->left + 4, mp_select_object->top + 4).PtInRect(point))
			m_resize_type = 1;
		else if (CRect(mp_select_object->left - 4 + hw, mp_select_object->top - 4, mp_select_object->left + 4 + hw, mp_select_object->top + 4).PtInRect(point))
			m_resize_type = 2;
		else if (CRect(mp_select_object->right - 4, mp_select_object->top - 4, mp_select_object->right + 4, mp_select_object->top + 4).PtInRect(point))
			m_resize_type = 3;
		else if (CRect(mp_select_object->right - 4, mp_select_object->top - 4 + hh, mp_select_object->right + 4, mp_select_object->top + 4 + hh).PtInRect(point))
			m_resize_type = 4;
		else if (CRect(mp_select_object->right - 4, mp_select_object->bottom - 4, mp_select_object->right + 4, mp_select_object->bottom + 4).PtInRect(point))
			m_resize_type = 5;
		else if (CRect(mp_select_object->left - 4 + hw, mp_select_object->bottom - 4, mp_select_object->left + 4 + hw, mp_select_object->bottom + 4).PtInRect(point))
			m_resize_type = 6;
		else if (CRect(mp_select_object->left - 4, mp_select_object->bottom - 4, mp_select_object->left + 4, mp_select_object->bottom + 4).PtInRect(point))
			m_resize_type = 7;
		else if (CRect(mp_select_object->left - 4, mp_select_object->top - 4 + hh, mp_select_object->left + 4, mp_select_object->top + 4 + hh).PtInRect(point))
			m_resize_type = 8;;

		if (m_resize_type == 0) {
			if (!mp_select_object->PtInRect(point))
				mp_select_object = NULL;
		}
	}

	if (mp_select_object == NULL) {
		CRect* p;
		POSITION pos = m_object_list.GetHeadPosition();
		while (pos != NULL) {
			p = (CRect*)m_object_list.GetNext(pos);
			if (p->PtInRect(point)) {
				mp_select_object = p;
				break;
			}
		}
	}

	if (mp_select_object != NULL) {
		m_is_clicked = 1;
		SetCapture();
		m_prev_pos = point;
	}

	if (mp_select_object != p_old_object) {
		DrawWorkImage();
		InvalidateRect(m_work_rect, 0);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CEXDrawRectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_is_clicked) {
		m_is_clicked = 0;
		m_resize_type = 0;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CEXDrawRectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_is_clicked) {
		point.x -= m_work_rect.left;
		point.y -= m_work_rect.top;

		CPoint move_pos = point - m_prev_pos;
		switch (m_resize_type)
		{
		case 1:
			mp_select_object->left += move_pos.x;
			mp_select_object->top += move_pos.y;
			break;
		case 2:
			mp_select_object->top += move_pos.y;
			break;
		case 3:
			mp_select_object->right += move_pos.x;
			mp_select_object->top += move_pos.y;
			break;
		case 4:
			mp_select_object->right += move_pos.x;
			break;
		case 5:
			mp_select_object->right += move_pos.x;
			mp_select_object->bottom += move_pos.y;
			break;
		case 6:
			mp_select_object->bottom += move_pos.y;
			break;
		case 7:
			mp_select_object->left += move_pos.x;
			mp_select_object->bottom += move_pos.y;
			break;
		case 8:
			mp_select_object->left += move_pos.x;
			break;
		default:
			*mp_select_object += move_pos;
			break;
		}

		DrawWorkImage();
		InvalidateRect(m_work_rect, 0);
		m_prev_pos = point;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
