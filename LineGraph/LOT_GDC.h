#ifndef _LOT_GDC_H_
#define _LOT_GDC_H_


#include <gdiplus.h>
using namespace Gdiplus;

#define RGB24(r, g, b) (0XFF000000 | (r << 16) | (g << 8) | b) // 0xFFRRGGBB
#define RGB32(a, r, g, b) ((a << 24) | (r << 16) | (g << 8) | b) // 0xAARRGGBB

class LOT_GDC
{
protected:
	Brush* mp_brush;
	Brush* mp_font_brush;	// 문자 브러쉬 색상
	Pen* mp_pen;
	Gdiplus::Font* mp_font;
	Bitmap* mp_bitmap;
	Graphics* mp_graphic;

	int m_cx, m_cy;
	int m_last_pos_x, m_last_pos_y;
	Color m_temp_color;

	static ULONG_PTR m_token;
	static int m_object_count;
public:
	LOT_GDC();
	LOT_GDC(int a_cx, int a_cy);
	virtual ~LOT_GDC();

	void Init();
	void CreateGDC(int a_cx, int a_cy);

	// 사각형을 그리는 함수들
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey);  // 채우기와 테두리 같이 그림
	void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // 채우기만 함
	void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey);  // 채우기만 함
	void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // 테두리만 그림
	void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey); // 테두리만 그림

	// 타원을 그리는 함수들
	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey);  // 채우기와 테두리 같이 그림
	void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color); // 채우기만 함
	void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey); // 채우기만 함
	void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color); // 테두리만 그림
	void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey); // 테두리만 그림

	// 선을 그리는 함수들
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // 시작, 끝을 사용해서 선그리기
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey);  // 시작, 끝을 사용해서 선그리기
	void MoveTo(int a_x, int a_y);  // 선의 시작 위치를 지정
	void LineTo(int a_x, int a_y);  // MoveTo 또는 마지막 LineTo를 사용한 지점과 선을 연결

	void SetDCBrushColor(ARGB a_color);  // 채우기 색상을 변경
	void SetDCPenColor(ARGB a_color);  // 선 색상을 변경
	void SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color);  // 선 스타일, 굵기 그리고 선 색상 변경
	void SetTextColor(ARGB a_color);  // 글꼴의 색상을 변경
	Gdiplus::Font* SelectObject(Gdiplus::Font* ap_font);  // 폰트 객체를 다시 설정한다.

	void Draw(Image* ap_image, int a_x, int a_y);  // 전달된 이미지 객체를 출력
	void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);  // 전달된 DC에 현재 이미지를 출력

	// 문자열을 지정한 위치에 출력하는 함수들
	void TextOut(int a_x, int a_y, ARGB a_color, const wchar_t* ap_str, int a_str_len);
	void TextOut(int a_x, int a_y, const wchar_t* ap_str, int a_str_len);

	// 내부 보호 멤버의 값을 외부에서 사용할 수 있게 해주는 함수들
	Image* GetImage() { return mp_bitmap; }
	Graphics* GetGraphics() { return mp_graphic; }

	// GetImage 함수와 GetGraphics 함수를 편하게 사용하도록 연산자 오버로딩 사용
	operator Image* () { return mp_bitmap; }
	operator Graphics* () { return mp_graphic; }
};

#endif
