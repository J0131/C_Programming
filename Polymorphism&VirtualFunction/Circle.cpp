#include "Circle.h"

Circle::Circle()
{

}
Circle::Circle(string name)
{

}
Circle::Circle(int px, int py, int r, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
} // 생성자

Circle::~Circle()
{

}
double Circle::getArea()
{
	double a = radius * radius * 3.14;
	return a;
} // 원 면적 구하는 함수
void Circle::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x(); // x좌표 설정
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y(); // y좌표 설정 
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Ellipse(hdc, pos_center_x - radius, pos_center_y - radius, pos_center_x + radius,
		pos_center_y + radius);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
} // 화면에 도형을 그리는 함수