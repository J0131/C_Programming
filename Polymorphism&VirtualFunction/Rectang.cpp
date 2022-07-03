#include "Rectang.h"

Rectang::Rectang()
{

}
Rectang::Rectang(string name)
{

}
Rectang::Rectang(int px, int py, int w, int l, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	width = w;
	length = l;
} // 생성자

Rectang::~Rectang()
{

}
double Rectang::getArea()
{
	double a;
	a = width * length;
	return a;
} // 사각형 면적구하는 함수
void Rectang::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x(); // x좌표 설정
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y(); // y좌표 설정
	POINT p[4]; // POINT배열 생성
	p[0].x = pos_center_x - width / 2;
	p[0].y = pos_center_y - length / 2;
	p[1].x = pos_center_x + width / 2;
	p[1].y = pos_center_y - length / 2.0;
	p[2].x = pos_center_x + width / 2;
	p[2].y = pos_center_y + length / 2.0;
	p[3].x = pos_center_x - width / 2;
	p[3].y = pos_center_y + length / 2.0;
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(cp_frame.getConsole_DC(), new_brush);
	Polygon(hdc, p, 4);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
} // 화면에 사각형을 그리는 함수