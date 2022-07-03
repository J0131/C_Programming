/***************************************************************
* 파일목적 : 연산자오버로딩을 사용하여 배열연산을 하는 프로그램
* 작성자 : 최범준
* FINAL UPDATE : 2020.09.24
****************************************************************/
#include <iostream>
#include <fstream>
#include "Class_Mtrx.h"
#include "MtrxArray.h"
#define NUM_ROW 7
#define NUM_COL 7
#define NUM_MTRX 6
using namespace std;
int main()
{
    ifstream fin; // 파일입력객체 선언
    ofstream fout; // 파일출력객체 선언
    fin.open("Matrix_7x7.txt"); // 파일을 읽을때 open 파일 설정
    if (fin.fail())
    {
        cout << "Error in opening input data file !!" << endl;
        exit;
    }
    fout.open("Result.txt"); // 파일에 쓸 때 open할 파일 설정
    if (fout.fail())
    {
        cout << "Error in opening output data file !!" << endl;
        exit;
    }
    MtrxArray mtrx(NUM_MTRX, NUM_ROW, NUM_COL); // 다음과 같은 인수를 전달하여 MtrxArray형의 mtrx생성
    fin >> mtrx[0]; // 파일데이터를 읽어 mtrx[0]에 저장
    fin >> mtrx[1]; // 파일데이터를 읽어 mtrx[1]에 저장
    mtrx[0].set_name("mtrx[0] ="); // mtrx[0] 이름을 지정
    mtrx[1].set_name("mtrx[1] ="); // mtrx[1] 이름을 지정
    fout << mtrx[0] << endl; // 
    fout << mtrx[1] << endl; // mtrx[0], mtrx[1]를 파일에 출력
    mtrx[2] = mtrx[0] + mtrx[1]; // mtrx[0] + mtrx[1]를 연산하여 mtrx[2]에 저장
    mtrx[2].set_name("mtrx[2] = mtrx[0] + mtrx[1] ="); // mtrx[2] 의 이름을 지정
    fout << mtrx[2] << endl; 
    mtrx[3] = mtrx[0] - mtrx[1]; // mtrx[0] - mtrx[1]를 연산하여 mtrx[3]에 저장
    mtrx[3].set_name("mtrx[3] = mtrx[0] - mtrx[1] =");
    fout << mtrx[3] << endl;
    mtrx[4] = mtrx[0] * mtrx[1]; // mtrx[0] * mtrx[1]를 연산하여 mtrx[4]에 저장
    mtrx[4].set_name("mtrx[4] = mtrx[0] * mtrx[1] =");
    fout << mtrx[4] << endl;
    mtrx[5] = mtrx[0]; // mtrx[5] 에 mtrx[0]의 정보를 대입
    mtrx[5].set_name("mtrx[5] = mtrx[0] =");
    fout << mtrx[5] << endl;
    if (mtrx[0] == mtrx[1])
        fout << "mtrx[0] and mtrx[1] are equal.\n";
    if (mtrx[0] != mtrx[1])
        fout << "mtrx[0] and mtrx[1] are not equal.\n";
    fin.close();
    fout.close();
    return 0;
}