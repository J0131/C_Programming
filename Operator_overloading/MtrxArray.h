#ifndef MTRX_ARRAY_H
#define MTRX_ARRAY_H
#include <iostream>
#include "Class_Mtrx.h"
using namespace std;
class Mtrx;
class MtrxArray
{
public:
    MtrxArray(int arraySize, int n_row, int n_col); // 생성자
    ~MtrxArray(); // 소멸자
    Mtrx& operator[](int sub);// 행렬배열의 인덱스를 전달받아 행렬배열을 반환하는함수
    int getSize() { return mtrxArrySize; } // 행렬배열의 크기를 반환하는함수
private:
    Mtrx* pMtrx;
    int mtrxArrySize; // 데이터멤버
};
#endif

