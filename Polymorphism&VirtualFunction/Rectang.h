#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Rectang : public Shape // ShapeŬ�����κ��� ��ӹ���
{
	//friend ostream& operator<<(ostream &, Rectangle &);
public:
	Rectang();
	Rectang(string name);
	Rectang(int x,int y, int w, int l, double ang, COLORREF ln_clr,COLORREF br_clr, int pen_thick, string name); // ������
	//Rectangle(Rectangle &tr);
	~Rectang(); // �Ҹ���
	double getArea(); // �簢�� ���� ���ϴ� �Լ�
	virtual void draw(ConsolePixelFrame cp_frame); // ȭ�鿡 �簢���� �׸��� �Լ�
	//void fprint(ostream &);
	int getWidth() { return width; }
	int getLength() { return length; }
	Rectang& operator=(Rectang& rec);
protected:
	int width; // �غ� 
	int length; // ����
};
