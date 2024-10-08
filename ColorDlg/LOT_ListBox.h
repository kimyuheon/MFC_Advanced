﻿#pragma once


// LOT_ListBox
//#pragma comment (lib, "LOT_ListBox.lib")
/*
void LOT_ListBox::DrawUserItem(CDC *ap_dc, RECT *ap_rect, int a_index, void * ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
{
	if (a_select_flag)
		ap_dc->SetTextColor(RGB(255, 255, 0));
	else
		ap_dc->SetTextColor(RGB(128, 128, 0));

	CString str;
	GetText(a_index, str);
	ap_dc->TextOut(ap_rect->left + 6, ap_rect->top + 5, str);
}
*/

class LOT_ListBox : public CListBox
{
	DECLARE_DYNAMIC(LOT_ListBox)
private:
	CBrush m_list_bk_brush;
	COLORREF m_select_color;
	COLORREF m_focus_color;
	COLORREF m_bk_color;
public:
	LOT_ListBox();
	virtual ~LOT_ListBox();

	void SetItemColor(COLORREF a_select_color, COLORREF a_focus_color, COLORREF a_bk_color);
	virtual void DrawListItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);
	virtual void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


