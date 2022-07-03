#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <Windows.h>
#include <conio.h>
#include "ConsolePixelDrawing.h"
#include "Color.h"
using namespace std;
#define PI 3.14159
class ConsolePixelFrame;
class Shape
{
	friend ostream& operator<<(ostream&, Shape&);
public:
	Shape(); // 기본생성자
	Shape(string name);
	Shape(int px, int py, double angle, COLORREF ln_clr, COLORREF br_clr,int pen_thick, string name); // 생성자
	virtual ~Shape();
	virtual void draw(ConsolePixelFrame cp_frame); // 화면에 도형을 그리는 함수 가상함수로 선언
	void fprint(ostream&);
	int get_pos_x() const { return pos_x; }
	int get_pos_y() const { return pos_y; }
	void set_pos_x(int x) { pos_x = x; }
	void set_pos_y(int y) { pos_y = y; }
	string getName() { return name; }
	void setName(string n) { name = n; }
	Shape& operator=(const Shape& s);
protected:
	int pos_x; // x좌표
	int pos_y; // y좌표
	double angle; // 각도
	string name; // 이름
	int pen_thickness; // 펜굵기
	COLORREF line_color; // 선색상
	COLORREF brush_color; // 브러쉬색상
};
#endif
