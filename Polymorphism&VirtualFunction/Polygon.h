#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class PolyGon : public Shape
{
	//friend ostream& operator<<(ostream &, PolyGonle &);
public:
	PolyGon();
	PolyGon(string name);
	PolyGon(int x, int y, int radius_, int num_poly_, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // 생성자
	~PolyGon(); // 소멸자
	//double getArea();
	virtual void draw(ConsolePixelFrame cp_frame); // 화면에 다각형을 그리는 가상함수
	int getRadius() { return radius; }
	int getNumPoly() { return num_poly; }
	PolyGon& operator=(PolyGon& pg);
protected:
	int radius; // 반지름
	int num_poly; // 각의 갯수
};
