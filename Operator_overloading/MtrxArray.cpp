#include "MtrxArray.h"
#include "Class_Mtrx.h"

MtrxArray::MtrxArray(int arraySize, int n_row, int n_col) // 생성자
{
	/*cout << "MtrxArray :: constructor (int arraySize: " << arraySize << ", n_row: " << n_row << ",
    n_col: <<" << n_col <<\n";*/
    this->mtrxArrySize = arraySize; // 받아온  arraySize를 mtrxArrySize로 저장
    pMtrx = new Mtrx[arraySize]; // pMtrx를 arraySize만큼 동적할당
    for (int i = 0; i < arraySize; i++)
    {
	    pMtrx[i].init(n_row, n_col); // pMtrx[i]의 데이터멤버를 초기화
    }
}
MtrxArray::~MtrxArray()
{
	//cout << "MtrxArray :: destructor" << endl;
	if (pMtrx != NULL) {
		delete[] pMtrx; // 동적할당한 pMtrx를 동적해제
	}
}
Mtrx& MtrxArray::operator [](int sub)
{
	if (sub < 0 || sub >= mtrxArrySize)
	{
		cout << "ERROR: Subscript out of range.	\n";
			exit(0);
	}// 지정된 범위안에 들어있지않다면 오류메세지 출력
	return pMtrx[sub]; // 지정된 범위안에있다면 pMtrx[sub]반환
}