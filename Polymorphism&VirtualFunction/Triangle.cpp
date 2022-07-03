#include "Triangle.h"

Triangle::Triangle()
{

}
Triangle::Triangle(string name)
{

}
Triangle::Triangle(int px, int py, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	base = b;
	tri_height = h; // 데이터멤버 초기화
} // 생성자
Triangle::~Triangle()
{

}
double Triangle::getArea()
{
	double a;
	a = base * tri_height / 2.0;
	return a;
} // 삼각형 넓이 구하는 함수
void Triangle::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x(); // x좌표 설정
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y(); // y좌표 설정
	POINT p[3];
	p[0].x = pos_center_x - base / 2;
	p[0].y = pos_center_y + tri_height * 1.0 / 2.0;
	p[1].x = pos_center_x + base / 2;
	p[1].y = pos_center_y + tri_height * 1.0 / 2.0;
	p[2].x = pos_center_x;
	p[2].y = pos_center_y - tri_height * 1.0 / 2.0;
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Polygon(hdc, p, 3);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
} // 화면에 삼각형을 그리는 함수