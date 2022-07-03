#include "CipherMessage.h"

void xtoa(unsigned char uc)
{
	char low, high;
	low = uc & 0x0f; // uc를 0000 1111과 bit and하면 하위 4비트의 값을구할수있다
	high = (uc >> 4) & 0x0f; // uc를 오른쪽으로 bit shift한뒤에 0000 1111과 bit and하면 상위 4비트이값을 구할수있다
	printf("%X%X", high, low); // 16진수형태로 출력
}

void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l)
{
	char low, high;
	low = ch & 0x0f;// ch를 0000 1111과 bit and하면 하위 4비트의 값을구할수있다
	high = (ch >> 4) & 0x0f;// ch를 오른쪽으로 bit shift한뒤에 0000 1111과 bit and하면 상위 4비트이값을 구할수있다
	*pCC_u = high; // 상위4비트의값을 *pCC_u에 저장한다
	*pCC_l = low; // 하위4비트값을 *pCC_l에 저장한다
}

void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code)
{
	char c, res;
	unsigned char a, b;
	char* s;
	s = (char*)calloc(1000, sizeof(char)); // 문자열을 저장할 1차원 동적배열 생성

	while (!feof(fp_msg)) // 파일포인터가 fp_msg인 파일에서 파일의 끝이 나올때까지 반복
	{
		fgets(s, 1000, fp_msg); // 파일포인터가 fp_msg인 파일에서 1줄을 읽어 s배열에 저장한다
		for (int i = 0; i < 100; i++)
		{
			c = s[i]; // s[i]를 c에저장
			if (c == NULL)
				break;// c가 문자열의 끝이면 반복문을 빠져나간다
			res = c ^ cipher_code; // c를 cipher_code와 bit exclusive or 연산하여 res에저장한다. 
			cipherChar(res, &a, &b); // res와 ab의 주소값을 cipherChar함수에 넣어 a,b의 값을 저장한다
			fprintf(fp_tx, "%X%X", a, b); // a,b를 16진수형태로 파일에 출력한다 
		}
		fprintf(fp_tx, "\n");
	}
}

unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l)
{
	unsigned char high, low,sum=0; // 상위4비트, 하위4비트, 합

	if (rc_u >= 48 && rc_u <= 57)  // rc_u가 0~9의 값일때
	{
		high = (rc_u - 48) * 16; // 16진수 상위 4비트에해당하는 rc_u를 다음과 같이구하여 high에저장
	}
	else if (rc_u >= 65 && rc_u <= 70)  // rc_u가 'A'~'F'의 값일때
	{
		high = (rc_u - (65 - 10)) * 16; // 16진수 상위 4비트에해당하는 rc_u를 다음과 같이구하여 high에저장
	}
	else if (rc_u >= 97 && rc_u <= 102)  // rc_u가 'a'~'f'의 값일때
	{
		high = (rc_u - (97 - 10)) * 16; // 16진수 상위 4비트에해당하는 rc_u를 다음과 같이구하여 high에저장
	}
	
	if (rc_l >= 48 && rc_l <= 57) // rc_l가 0~9의 값일때
	{
		low = (rc_l - 48); // 16진수 하위 4비트에해당하는 rc_l을 다음과 같이구하여 low에저장
	}
	else if (rc_l >= 65 && rc_l <= 70) // rc_l가 'A'~'F'의 값일때
	{
		low = (rc_l - (65 - 10)) ; // 16진수 하위 4비트에해당하는 rc_l을 다음과 같이구하여 low에저장
	}
	else if (rc_l >= 97 && rc_l <= 102)  // rc_l가 'a'~'f'의 값일때
	{
		low = (rc_l - (97 - 10)) ; // 16진수 하위 4비트에해당하는 rc_l을 다음과 같이구하여 low에저장
	}
	sum = high + low; // high값과 low값을 더한값으로 원래의 문자를 구할수있다
	return sum;
}

void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code)
{
	char a, b;
	char ch,res;
	char* s;
	s = (char*)calloc(1000, sizeof(char)); // 문자열을 저장할 1차원 동적 배열생성

	while (!feof(fp_tx)) // 파일포인터가 fp_tx인 파일에서 파일의 끝이 나올때까지 반복
	{
		fgets(s, 1000, fp_tx); // 파일포인터가 fp_tx인 파일에서 한줄을 읽어 배열 s에 저장
		if (feof(fp_tx))
			break; // 파일포인터가 fp_tx인 파일에서 파일의 끝이 나오면 반복문을 나간다
		for (int i = 0; i < 1000; i+=2) // 2개씩 읽기위해 i의값을 2씩증가
		{
			a = s[i]; // 두자리수의 앞의값을 a에저장
			b = s[i + 1]; // 두자리수의 뒤의값을 b에저장
			if (a == NULL)
				break;
			if (b == NULL)
				break; // a나 b가 문자열의 끝을 나타내면 반복문 나가기
			ch = deCipherChar(a, b); // 16진수 상위4비트 a와 하위4비트 b를 넣으면 문자 암호화된후의 문자 ch를 구할수있다
			res = ch ^ cipher_code; // ch와 cipher_code를 bit exclusive or 연산을 하게되면 암호화되기전 문자 res를 구할수있다
			fprintf(fp_out, "%c", res); // 복호화한 문자를 출력
		}
	}	
}
