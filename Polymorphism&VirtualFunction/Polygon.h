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
	PolyGon(int x, int y, int radius_, int num_poly_, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // ������
	~PolyGon(); // �Ҹ���
	//double getArea();
	virtual void draw(ConsolePixelFrame cp_frame); // ȭ�鿡 �ٰ����� �׸��� �����Լ�
	int getRadius() { return radius; }
	int getNumPoly() { return num_poly; }
	PolyGon& operator=(PolyGon& pg);
protected:
	int radius; // ������
	int num_poly; // ���� ����
};
