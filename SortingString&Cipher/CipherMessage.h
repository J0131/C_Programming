#define CIPHER_CODE 0x69 // 암호화 코드
#include <stdio.h>
#include <stdlib.h>

void xtoa(unsigned char uc); // 입력받은수를 상위4비트 하위4비트로 나누어 16진수형식으로 출력하는 함수
void cipherChar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l); //입력받은char형값의 상위4비트를 pCC_u에 저장하고 하위4비트를 pCC_l에저장하는 함수
void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code); // 파일에서 데이터를 읽어 암호화하여 파일에 출력하는 함수
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l); // 상위4비트인 rc_u, 하위4비트인 rc_l 두값을 입력받아 하나의 1바이트값으로 만드는 함수
void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code); // 파일에서 암호화된 데이터를 읽어 복호화하여 파일에 출력하는 함수
