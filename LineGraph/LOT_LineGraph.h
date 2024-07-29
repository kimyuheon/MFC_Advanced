#pragma once
#include "LOT_GDC.h"

#define SCALE_STEP_COUNT	20

// LOT_LineGraph

typedef struct BlogInquiryData
{
	wchar_t date[12];
	wchar_t day_of_week[3];
	int total;
	int neighter;
	int adjoin;
	int etc;
} BID;

class LOT_LineGraph : public CWnd
{
	DECLARE_DYNAMIC(LOT_LineGraph)
private:
	/*ULONG_PTR m_token;
	SolidBrush* mp_brush;
	Pen* mp_pen;
	Bitmap* mp_mem_image;
	Graphics* mp_mem_graphics;

	CImage m_draw_image;
	CDC m_draw_dc;*/

	LOT_GDC m_frame_gdc;
	LOT_GDC m_graph_gdc;

	int m_max_value = 1;
	CRect m_rect, m_graph_rect;
	CPtrList m_data_list;
public:
	LOT_LineGraph();
	virtual ~LOT_LineGraph();

	void CreateGraph(int a_rect_id, CWnd* ap_parent, int a_ctrl_id);
	void LoadData(const wchar_t* ap_data_path);
	void DrawGraph();
	void DrawFrame(); // 그래프의 프레임을 그리는 함수

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};


