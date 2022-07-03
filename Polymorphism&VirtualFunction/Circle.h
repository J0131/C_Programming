#include <string>
#include "Shape.h"
using namespace std;
#define PI 3.14159
class Circle : public Shape // ShapeŬ�����κ��� ��ӹ���
{
	friend ostream& operator<<(ostream&, Circle&); 
public:
	Circle();
	Circle(string name);
	Circle(int x, int y, int r, double ang, COLORREF ln_clr, COLORREF br_clr,int pen_thick, string name); // ������
	~Circle(); // �Ҹ���
	double getArea();
	void draw(ConsolePixelFrame cp_frame); // ȭ�鿡 ���� �׸��� �����Լ�
	void fprint(ostream&);
	int getradius() { return radius; }
	Circle& operator=(const Circle& cir);
protected:
	int radius; // ������ 
};
