#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Triangle : public Shape // ShapeŬ�����κ��� ��ӹ���
{
	//friend ostream& operator<<(ostream &, Triangle &);
public:
	Triangle();
	Triangle(string name);
	Triangle(int x, int y, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // ������
	~Triangle(); // �Ҹ���
	double getArea(); // �ﰢ���� ������ ���ϴ� �Լ�
	virtual void draw(ConsolePixelFrame cp_frame); // ȭ�鿡 �ﰢ���� �׸��� �Լ�
	void fprint(ostream&);
	int getBase() { return base; }
	int getHeight() { return tri_height; }
	Triangle& operator=(const Triangle& tri);
protected:
	int base; // �غ�
	int tri_height; // ����
};
