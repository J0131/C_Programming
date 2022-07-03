#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Rectang : public Shape // Shape클래스로부터 상속받음
{
	//friend ostream& operator<<(ostream &, Rectangle &);
public:
	Rectang();
	Rectang(string name);
	Rectang(int x,int y, int w, int l, double ang, COLORREF ln_clr,COLORREF br_clr, int pen_thick, string name); // 생성자
	//Rectangle(Rectangle &tr);
	~Rectang(); // 소멸자
	double getArea(); // 사각형 넓이 구하는 함수
	virtual void draw(ConsolePixelFrame cp_frame); // 화면에 사각형을 그리는 함수
	//void fprint(ostream &);
	int getWidth() { return width; }
	int getLength() { return length; }
	Rectang& operator=(Rectang& rec);
protected:
	int width; // 밑변 
	int length; // 높이
};
