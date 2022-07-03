#include <string>
#include "Shape.h"
using namespace std;
#define PI 3.14159
class Circle : public Shape // Shape클래스로부터 상속받음
{
	friend ostream& operator<<(ostream&, Circle&); 
public:
	Circle();
	Circle(string name);
	Circle(int x, int y, int r, double ang, COLORREF ln_clr, COLORREF br_clr,int pen_thick, string name); // 생성자
	~Circle(); // 소멸자
	double getArea();
	void draw(ConsolePixelFrame cp_frame); // 화면에 원을 그리는 가상함수
	void fprint(ostream&);
	int getradius() { return radius; }
	Circle& operator=(const Circle& cir);
protected:
	int radius; // 반지름 
};
