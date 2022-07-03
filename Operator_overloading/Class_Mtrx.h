#ifndef CLASS_MTRX_H
#define CLASS_MTRX_H
#include <string>
using namespace std;
class MtrxArray;
class Mtrx {
    friend ostream& operator<< (ostream&, Mtrx&); // 행렬을 파일에 출력하는 연산자 
    friend istream& operator>> (istream&, Mtrx&); // 파일에서 데이터를 읽어 행렬에 저장하는 연산자
    friend class MtrxArray;
    // friend형으로 선언하여 데이터멤버에 접근할수있도록 만들어줌
public:
    Mtrx(); // 기본생성자
    Mtrx(string nm, int num_row, int num_col);
    Mtrx(string nm, double* pA, int num_row, int num_col);
    Mtrx(istream& fin); // 인수에 따른 생성자
    ~Mtrx(); // 소멸자
    void init(int num_row, int num_col); // 데이터멤버 초기화
    void set_name(string nm) { name = nm; } // 이름을 설정하는 함수
    string get_name() { return name; } // 이름을 반환하는 함수
    int get_n_row() const { return n_row; } // n_row를 반환하는 함수
    int get_n_col() const { return n_col; } // n_col을 읽어오는 함수
    Mtrx operator+(const Mtrx&); // 행렬의 덧셈연산을하는 연산자
    const Mtrx operator-(const Mtrx&); // 행렬의 뺄셈연산을하는 연산자
    const Mtrx operator*(const Mtrx&); // 행렬의 곱셈연산을하는 연산자
    const Mtrx& operator=(const Mtrx&); // 어떤행렬을 대입하는 연산을 하는 연산자
    bool operator==(const Mtrx&); // 행렬을 비교하는 비교연산자
    bool operator!=(const Mtrx&); // 행렬을 비교하는 비교연산자
private:
    string name;
    int n_row;
    int n_col;
    double** dM; // 데이터멤버
};
#endif
