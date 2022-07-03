/************************************************
* 파일목적 : 상속클래스기반의 도형객체를 생성하여 가상함수를통한 화면출력
* 작성자 : 최범준
* final update : 2020.10.11
**************************************************/

#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectang.h"
#include "Polygon.h"
#include "Star.h"
using namespace std;
int main()
{
	system("color 70");
	Circle cir(100, 100, 80, 0.0, RGB_BLACK, RGB_RED, 3, "Circle"); // Circle 객체생성
	Triangle tri(300, 100, 150, 130, 0.0, RGB_BLACK, RGB_YELLOW, 3, "Triangle"); // Triangle 객체생성
	Rectang rec(500, 100, 150, 150, 0.0, RGB_BLACK, RGB_BLUE, 4, "Rectangle"); // Rectang 객체생성
	PolyGon poly_5(100, 300, 80, 5, 0.0, RGB_BLACK, RGB_GREEN, 4, "Polygon_5"); // PolyGon 객체생성
	PolyGon poly_6(300, 300, 80, 6, 0.0, RGB_BLACK, RGB_BLUE, 4, "Polygon_6"); // PolyGon 객체생성
	PolyGon poly_7(500, 300, 80, 7, 0.0, RGB_BLACK, RGB_MAGENTA, 4, "Polygon_7"); // PolyGon 객체생성
	Star star_5(100, 500, 80, 5, 0.0, RGB_BLACK, RGB_GREEN, 4, "Star_5"); // Star 객체 생성
	ConsolePixelFrame frame(50, 50); // 콘솔화면 좌표설정
	frame.addShape(&cir); 
	frame.addShape(&tri);
	frame.addShape(&rec);
	frame.addShape(&poly_5);
	frame.addShape(&poly_6);
	frame.addShape(&poly_7);
	frame.addShape(&star_5); // frame에 각 객체들의 주소를 저장
	frame.drawShapes(); // frame의 객체들을 화면에 draw
	printf("hit any key to continue ....");
	_getch();
	system("pause");
	return 0;
}