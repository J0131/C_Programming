#ifndef MTRX_ARRAY_H
#define MTRX_ARRAY_H
#include <iostream>
#include "Class_Mtrx.h"
using namespace std;
class Mtrx;
class MtrxArray
{
public:
    MtrxArray(int arraySize, int n_row, int n_col); // ������
    ~MtrxArray(); // �Ҹ���
    Mtrx& operator[](int sub);// ��Ĺ迭�� �ε����� ���޹޾� ��Ĺ迭�� ��ȯ�ϴ��Լ�
    int getSize() { return mtrxArrySize; } // ��Ĺ迭�� ũ�⸦ ��ȯ�ϴ��Լ�
private:
    Mtrx* pMtrx;
    int mtrxArrySize; // �����͸��
};
#endif

