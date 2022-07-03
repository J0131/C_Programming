#ifndef Star_H
#define Star_H
#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Star : public Shape
{
public:
	Star();
	Star(string name);
	Star(int px, int py, int radius_, int num_vertices_, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // 생성자
	~Star(); // 소멸자
	virtual void draw(ConsolePixelFrame cp_frame); // 화면에 별을 그리는 함수
	void fprint(ostream&);
	int getRadius() { return radius; }
	int getNumPoly() { return num_vertices; }
	Star& operator=(Star& pg);
protected:
	int radius; // 반지름
	int num_vertices; // 꼭짓점 갯수
};
#endif
