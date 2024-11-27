
// EX_Draw_RectDlg.h: 헤더 파일
//

#pragma once


// CEXDrawRectDlg 대화 상자
class CEXDrawRectDlg : public CDialogEx
{
// 생성입니다.
private:
	CRect m_work_rect;
	CImage m_work_image;
	CDC m_work_dc;

	CPtrList m_object_list;
	CRect* mp_select_object;
	CPoint m_prev_pos;
	char m_is_clicked;
	int m_resize_type; // 사각형 8개의 점
public:
	CEXDrawRectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void DrawWorkImage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EX_DRAW_RECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedAddRect();
	afx_msg void OnBnClickedRemoveRect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
