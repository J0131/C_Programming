#include "CipherMessage.h"

void xtoa(unsigned char uc)
{
	char low, high;
	low = uc & 0x0f; // uc�� 0000 1111�� bit and�ϸ� ���� 4��Ʈ�� �������Ҽ��ִ�
	high = (uc >> 4) & 0x0f; // uc�� ���������� bit shift�ѵڿ� 0000 1111�� bit and�ϸ� ���� 4��Ʈ�̰��� ���Ҽ��ִ�
	printf("%X%X", high, low); // 16�������·� ���
}

void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l)
{
	char low, high;
	low = ch & 0x0f;// ch�� 0000 1111�� bit and�ϸ� ���� 4��Ʈ�� �������Ҽ��ִ�
	high = (ch >> 4) & 0x0f;// ch�� ���������� bit shift�ѵڿ� 0000 1111�� bit and�ϸ� ���� 4��Ʈ�̰��� ���Ҽ��ִ�
	*pCC_u = high; // ����4��Ʈ�ǰ��� *pCC_u�� �����Ѵ�
	*pCC_l = low; // ����4��Ʈ���� *pCC_l�� �����Ѵ�
}

void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code)
{
	char c, res;
	unsigned char a, b;
	char* s;
	s = (char*)calloc(1000, sizeof(char)); // ���ڿ��� ������ 1���� �����迭 ����

	while (!feof(fp_msg)) // ���������Ͱ� fp_msg�� ���Ͽ��� ������ ���� ���ö����� �ݺ�
	{
		fgets(s, 1000, fp_msg); // ���������Ͱ� fp_msg�� ���Ͽ��� 1���� �о� s�迭�� �����Ѵ�
		for (int i = 0; i < 100; i++)
		{
			c = s[i]; // s[i]�� c������
			if (c == NULL)
				break;// c�� ���ڿ��� ���̸� �ݺ����� ����������
			res = c ^ cipher_code; // c�� cipher_code�� bit exclusive or �����Ͽ� res�������Ѵ�. 
			cipherChar(res, &a, &b); // res�� ab�� �ּҰ��� cipherChar�Լ��� �־� a,b�� ���� �����Ѵ�
			fprintf(fp_tx, "%X%X", a, b); // a,b�� 16�������·� ���Ͽ� ����Ѵ� 
		}
		fprintf(fp_tx, "\n");
	}
}

unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l)
{
	unsigned char high, low,sum=0; // ����4��Ʈ, ����4��Ʈ, ��

	if (rc_u >= 48 && rc_u <= 57)  // rc_u�� 0~9�� ���϶�
	{
		high = (rc_u - 48) * 16; // 16���� ���� 4��Ʈ���ش��ϴ� rc_u�� ������ ���̱��Ͽ� high������
	}
	else if (rc_u >= 65 && rc_u <= 70)  // rc_u�� 'A'~'F'�� ���϶�
	{
		high = (rc_u - (65 - 10)) * 16; // 16���� ���� 4��Ʈ���ش��ϴ� rc_u�� ������ ���̱��Ͽ� high������
	}
	else if (rc_u >= 97 && rc_u <= 102)  // rc_u�� 'a'~'f'�� ���϶�
	{
		high = (rc_u - (97 - 10)) * 16; // 16���� ���� 4��Ʈ���ش��ϴ� rc_u�� ������ ���̱��Ͽ� high������
	}
	
	if (rc_l >= 48 && rc_l <= 57) // rc_l�� 0~9�� ���϶�
	{
		low = (rc_l - 48); // 16���� ���� 4��Ʈ���ش��ϴ� rc_l�� ������ ���̱��Ͽ� low������
	}
	else if (rc_l >= 65 && rc_l <= 70) // rc_l�� 'A'~'F'�� ���϶�
	{
		low = (rc_l - (65 - 10)) ; // 16���� ���� 4��Ʈ���ش��ϴ� rc_l�� ������ ���̱��Ͽ� low������
	}
	else if (rc_l >= 97 && rc_l <= 102)  // rc_l�� 'a'~'f'�� ���϶�
	{
		low = (rc_l - (97 - 10)) ; // 16���� ���� 4��Ʈ���ش��ϴ� rc_l�� ������ ���̱��Ͽ� low������
	}
	sum = high + low; // high���� low���� ���Ѱ����� ������ ���ڸ� ���Ҽ��ִ�
	return sum;
}

void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code)
{
	char a, b;
	char ch,res;
	char* s;
	s = (char*)calloc(1000, sizeof(char)); // ���ڿ��� ������ 1���� ���� �迭����

	while (!feof(fp_tx)) // ���������Ͱ� fp_tx�� ���Ͽ��� ������ ���� ���ö����� �ݺ�
	{
		fgets(s, 1000, fp_tx); // ���������Ͱ� fp_tx�� ���Ͽ��� ������ �о� �迭 s�� ����
		if (feof(fp_tx))
			break; // ���������Ͱ� fp_tx�� ���Ͽ��� ������ ���� ������ �ݺ����� ������
		for (int i = 0; i < 1000; i+=2) // 2���� �б����� i�ǰ��� 2������
		{
			a = s[i]; // ���ڸ����� ���ǰ��� a������
			b = s[i + 1]; // ���ڸ����� ���ǰ��� b������
			if (a == NULL)
				break;
			if (b == NULL)
				break; // a�� b�� ���ڿ��� ���� ��Ÿ���� �ݺ��� ������
			ch = deCipherChar(a, b); // 16���� ����4��Ʈ a�� ����4��Ʈ b�� ������ ���� ��ȣȭ������ ���� ch�� ���Ҽ��ִ�
			res = ch ^ cipher_code; // ch�� cipher_code�� bit exclusive or ������ �ϰԵǸ� ��ȣȭ�Ǳ��� ���� res�� ���Ҽ��ִ�
			fprintf(fp_out, "%c", res); // ��ȣȭ�� ���ڸ� ���
		}
	}	
}
