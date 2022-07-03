#include "MtrxArray.h"
#include "Class_Mtrx.h"

MtrxArray::MtrxArray(int arraySize, int n_row, int n_col) // ������
{
	/*cout << "MtrxArray :: constructor (int arraySize: " << arraySize << ", n_row: " << n_row << ",
    n_col: <<" << n_col <<\n";*/
    this->mtrxArrySize = arraySize; // �޾ƿ�  arraySize�� mtrxArrySize�� ����
    pMtrx = new Mtrx[arraySize]; // pMtrx�� arraySize��ŭ �����Ҵ�
    for (int i = 0; i < arraySize; i++)
    {
	    pMtrx[i].init(n_row, n_col); // pMtrx[i]�� �����͸���� �ʱ�ȭ
    }
}
MtrxArray::~MtrxArray()
{
	//cout << "MtrxArray :: destructor" << endl;
	if (pMtrx != NULL) {
		delete[] pMtrx; // �����Ҵ��� pMtrx�� ��������
	}
}
Mtrx& MtrxArray::operator [](int sub)
{
	if (sub < 0 || sub >= mtrxArrySize)
	{
		cout << "ERROR: Subscript out of range.	\n";
			exit(0);
	}// ������ �����ȿ� ��������ʴٸ� �����޼��� ���
	return pMtrx[sub]; // ������ �����ȿ��ִٸ� pMtrx[sub]��ȯ
}