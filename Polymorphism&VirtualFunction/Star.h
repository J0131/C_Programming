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
	Star(int px, int py, int radius_, int num_vertices_, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name); // ������
	~Star(); // �Ҹ���
	virtual void draw(ConsolePixelFrame cp_frame); // ȭ�鿡 ���� �׸��� �Լ�
	void fprint(ostream&);
	int getRadius() { return radius; }
	int getNumPoly() { return num_vertices; }
	Star& operator=(Star& pg);
protected:
	int radius; // ������
	int num_vertices; // ������ ����
};
#endif
