#define CIPHER_CODE 0x69 // ��ȣȭ �ڵ�
#include <stdio.h>
#include <stdlib.h>

void xtoa(unsigned char uc); // �Է¹������� ����4��Ʈ ����4��Ʈ�� ������ 16������������ ����ϴ� �Լ�
void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l); //�Է¹���char������ ����4��Ʈ�� pCC_u�� �����ϰ� ����4��Ʈ�� pCC_l�������ϴ� �Լ�
void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code); // ���Ͽ��� �����͸� �о� ��ȣȭ�Ͽ� ���Ͽ� ����ϴ� �Լ�
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l); // ����4��Ʈ�� rc_u, ����4��Ʈ�� rc_l �ΰ��� �Է¹޾� �ϳ��� 1����Ʈ������ ����� �Լ�
void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code); // ���Ͽ��� ��ȣȭ�� �����͸� �о� ��ȣȭ�Ͽ� ���Ͽ� ����ϴ� �Լ�
