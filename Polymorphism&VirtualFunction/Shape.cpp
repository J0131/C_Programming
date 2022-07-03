#include <iostream>
#include "Shape.h"
#include <iomanip>
using namespace std;
Shape::Shape() // �⺻ ������
{
	pos_x = pos_y = 0;
	angle = 0;
	line_color = brush_color = RGB_BLACK;
	name = "no_name";
	//cout << "Shape::Default constructor (" << name << ").\n";
}
Shape::Shape(string n)
	:name(n)
{
	pos_x = pos_y = 0;
	angle = 0;
	line_color = brush_color = RGB_BLACK;
	//cout << "Shape::Constructor (" << name << ").\n";
}
Shape::~Shape()
{
	//cout << "Shape::Destructor (" << name << ").\n";
}
Shape::Shape(int px, int py, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string n)
{
	pos_x = px;
	pos_y = py;
	angle = ang;
	line_color = ln_clr;
	brush_color = br_clr;
	pen_thickness = pen_thick;
	name = n;
	//cout << "Shape::Constructor (" << name << ").\n";
} // �μ� ���޵Ǿ������� ������

void Shape::draw(ConsolePixelFrame cp_frame)
{
	// �����Լ�
}
Shape& Shape::operator=(const Shape& s)
{
	pos_x = s.pos_x;
	pos_y = s.pos_y;
	angle = s.angle;
	name = s.name;
	line_color = s.line_color;
	brush_color = s.brush_color;
	return *this;
} // ���Կ����� �����ε��Լ�
ostream& operator<<(ostream& ostr, Shape& shp)
{
	ostr << shp.name << ": pos(" << shp.get_pos_x() << ", " << shp.get_pos_y() << ")";
	ostr << ", line_color(";
	printRGB(ostr, shp.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, shp.brush_color);
	ostr << ")";
	return ostr;
} // ����ϴ� ������ �����ε��Լ�