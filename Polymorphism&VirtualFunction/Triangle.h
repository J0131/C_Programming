#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Triangle : public Shape // Shape클래스로부터 상속받음
{
	//friend ostream& operator<<(ostream &, Triangle &);
public:
	Triangle();
	Triangle(string name);
	Triangle(int x, int y, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // 생성자
	~Triangle(); // 소멸자
	double getArea(); // 삼각형의 면적을 구하는 함수
	virtual void draw(ConsolePixelFrame cp_frame); // 화면에 삼각형을 그리는 함수
	void fprint(ostream&);
	int getBase() { return base; }
	int getHeight() { return tri_height; }
	Triangle& operator=(const Triangle& tri);
protected:
	int base; // 밑변
	int tri_height; // 높이
};
