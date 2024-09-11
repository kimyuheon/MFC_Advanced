#ifndef _LOT_BUTTON_EX_H_
#define _LOT_BUTTON_EX_H_

// CButton 클래스에서 상속
// Focus 처리와 Mouse Over 처리된 상태

// LOT_Button
class LOT_Button : public CButton
{
	DECLARE_DYNAMIC(LOT_Button)

protected:
	UINT8 m_over_flag = 0;  // 롤오버 상태
	wchar_t m_temp_str[256]; // 버튼이 지정된 이름을 저장할 변수

public:
	LOT_Button();
	virtual ~LOT_Button();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT ap_dis);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};

#endif