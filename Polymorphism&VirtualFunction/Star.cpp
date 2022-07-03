#include "Star.h"

Star::Star()
{

}
Star::Star(string name)
{

}
Star::Star(int px, int py, int radius_, int num_vertices_, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px,py,ang,ln_clr,br_clr,pen_thick,name)
{
	radius = radius_;
	num_vertices = num_vertices_; // �����͸�� �ʱ�ȭ
} // ������
Star::~Star()
{

}
void Star::draw(ConsolePixelFrame cp_frame)
{
	POINT* points = (POINT*)malloc(5.0 * sizeof(POINT));
	double rad_angle, delta_angle;
	// angle in radian
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x(); // x��ǥ ����
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y(); // y��ǥ ����
	int x, y;
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	hdc = cp_frame.getConsole_DC();
	delta_angle = 2.0 * PI / 5.0;
	rad_angle = PI / 2.0;
	for (int i = 0; i < 5.0; i++, rad_angle +=
		delta_angle)
	{
		x = pos_center_x + radius * cos(rad_angle);
		y = pos_center_y - radius * sin(rad_angle);
		points[i].x = x;
		points[i].y = y;
	}
	new_pen = CreatePen(PS_SOLID,pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc,new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc,new_brush);
	//instead of Polygon(hdc, points, num_poly);
	MoveToEx(hdc, points[0].x, points[0].y,NULL);
	LineTo(hdc, points[2].x, points[2].y);
	LineTo(hdc, points[4].x, points[4].y);
	LineTo(hdc, points[1].x, points[1].y);
	LineTo(hdc, points[3].x, points[3].y);
	LineTo(hdc, points[0].x, points[0].y);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
} // ȭ�鿡 ���� �׸��� �Լ�