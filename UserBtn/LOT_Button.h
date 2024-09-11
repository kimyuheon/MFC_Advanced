#ifndef _LOT_BUTTON_EX_H_
#define _LOT_BUTTON_EX_H_

// CButton Ŭ�������� ���
// Focus ó���� Mouse Over ó���� ����

// LOT_Button
class LOT_Button : public CButton
{
	DECLARE_DYNAMIC(LOT_Button)

protected:
	UINT8 m_over_flag = 0;  // �ѿ��� ����
	wchar_t m_temp_str[256]; // ��ư�� ������ �̸��� ������ ����

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