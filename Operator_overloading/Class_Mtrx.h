#ifndef CLASS_MTRX_H
#define CLASS_MTRX_H
#include <string>
using namespace std;
class MtrxArray;
class Mtrx {
    friend ostream& operator<< (ostream&, Mtrx&); // ����� ���Ͽ� ����ϴ� ������ 
    friend istream& operator>> (istream&, Mtrx&); // ���Ͽ��� �����͸� �о� ��Ŀ� �����ϴ� ������
    friend class MtrxArray;
    // friend������ �����Ͽ� �����͸���� �����Ҽ��ֵ��� �������
public:
    Mtrx(); // �⺻������
    Mtrx(string nm, int num_row, int num_col);
    Mtrx(string nm, double* pA, int num_row, int num_col);
    Mtrx(istream& fin); // �μ��� ���� ������
    ~Mtrx(); // �Ҹ���
    void init(int num_row, int num_col); // �����͸�� �ʱ�ȭ
    void set_name(string nm) { name = nm; } // �̸��� �����ϴ� �Լ�
    string get_name() { return name; } // �̸��� ��ȯ�ϴ� �Լ�
    int get_n_row() const { return n_row; } // n_row�� ��ȯ�ϴ� �Լ�
    int get_n_col() const { return n_col; } // n_col�� �о���� �Լ�
    Mtrx operator+(const Mtrx&); // ����� �����������ϴ� ������
    const Mtrx operator-(const Mtrx&); // ����� �����������ϴ� ������
    const Mtrx operator*(const Mtrx&); // ����� �����������ϴ� ������
    const Mtrx& operator=(const Mtrx&); // ������ �����ϴ� ������ �ϴ� ������
    bool operator==(const Mtrx&); // ����� ���ϴ� �񱳿�����
    bool operator!=(const Mtrx&); // ����� ���ϴ� �񱳿�����
private:
    string name;
    int n_row;
    int n_col;
    double** dM; // �����͸��
};
#endif
