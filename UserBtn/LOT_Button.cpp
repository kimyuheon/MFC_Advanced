// LOT_Button.cpp: 구현 파일
#include "pch.h"
#include "UserBtn.h"
#include "LOT_Button.h"

// LOT_Button
IMPLEMENT_DYNAMIC(LOT_Button, CButton)

LOT_Button::LOT_Button()
{
}

LOT_Button::~LOT_Button()
{
}

BEGIN_MESSAGE_MAP(LOT_Button, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

// LOT_Button 메시지 처리기
void LOT_Button::PreSubclassWindow()
{
	CButton::PreSubclassWindow();
}

void LOT_Button::DrawItem(LPDRAWITEMSTRUCT ap_dis)
{
	// 버튼 제목이 수정되지 않는다면 PreSubclassWindow() 함수에 아래의 코드를 사용해서
	// 얻은 문자열 계속 사용해도 됩니다.
	int len = ::GetWindowText(m_hWnd, m_temp_str, sizeof(m_temp_str) / sizeof(wchar_t));

	// 색상만 변경해서 사용하는 Pen, Brush 지정
	::SelectObject(ap_dis->hDC, ::GetStockObject(DC_BRUSH));
	::SelectObject(ap_dis->hDC, ::GetStockObject(DC_PEN));

	if ((ap_dis->itemState & ODS_SELECTED) || m_over_flag) { // 선택 상태이거나 롤오버된 상태
		::SetDCBrushColor(ap_dis->hDC, RGB(107, 121, 146));
		::SetDCPenColor(ap_dis->hDC, RGB(127, 141, 166));
	} else { // 선택이 되지 않았거나 롤오버가 해제된 상태
		SetDCBrushColor(ap_dis->hDC, RGB(87, 101, 126));
		::SetDCPenColor(ap_dis->hDC, RGB(107, 121, 146));
	}

	// 버튼이 포커스 상태라면 조금더 테두리를 어둡게 표시
	if (ap_dis->itemState & ODS_FOCUS) ::SetDCPenColor(ap_dis->hDC, RGB(128, 152, 158));

	// 버튼의 배경 그리기.
	::Rectangle(ap_dis->hDC, ap_dis->rcItem.left, ap_dis->rcItem.top,
		ap_dis->rcItem.right, ap_dis->rcItem.bottom);

	// 버튼 텍스트 색상 지정
	::SetTextColor(ap_dis->hDC, RGB(232, 248, 248));
	// 텍스트의 배경은 투명으로 지정
	::SetBkMode(ap_dis->hDC, TRANSPARENT);

	// 버튼이 눌러져있다면 버튼이 좌측과 위쪽에 어두운 선을 한 번 더 그리기
	if (m_over_flag && (ap_dis->itemState & ODS_SELECTED)) {
		::SetDCPenColor(ap_dis->hDC, RGB(188, 202, 208));
		::MoveToEx(ap_dis->hDC, ap_dis->rcItem.left + 1, ap_dis->rcItem.bottom, NULL);
		::LineTo(ap_dis->hDC, ap_dis->rcItem.left + 1, ap_dis->rcItem.top + 1);
		::LineTo(ap_dis->hDC, ap_dis->rcItem.right, ap_dis->rcItem.top + 1);
		// 글씨도 우측과 아래쪽으로 살짝 내려서 출력 - 눌러지는 효과를 위해!
		ap_dis->rcItem.left += 2;
		ap_dis->rcItem.top += 2;
	}

	// 가운데 정렬을 사용해서 버튼 문자 출력
	::DrawText(ap_dis->hDC, m_temp_str, len, &ap_dis->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void LOT_Button::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_over_flag) { // 롤오버 체크를 하지 않는 경우!
		m_over_flag = 1; // 롤오버 체크 상태로 변경
		Invalidate(0); // 화면을 갱신해서 롤오버 상태를 표시

		// 롤오버가 해제될 때 체크
		TRACKMOUSEEVENT data = { sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd };
		TrackMouseEvent(&data);
	}

	CButton::OnMouseMove(nFlags, point);
}

void LOT_Button::OnMouseLeave()
{
	if (m_over_flag) { // 롤 오버가 진행중이라면!
		m_over_flag = 0; // 롤오버 해제 상태로 변경
		Invalidate(0); // 화면을 갱신해서 롤오버 해제 상태를 표시
	}

	CButton::OnMouseLeave();
}
