#include "HandlingBinaryFile.h"
#define BUFFER_LEN 16
#define MAX_FILE_SIZE 1024

void dumpBinaryFile(FILE* fin, FILE* fout)
{
	int nbytes;
	unsigned char buffer[BUFFER_LEN] = { '\0' }; // 배열 buffer 선언
	for (int addr = 0; addr < MAX_FILE_SIZE; addr += BUFFER_LEN)
	{
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin); // 이진데이터파일 fin으로부터 BUFFER_LEN만큼 읽어 buffer에저장
		if (nbytes <= 0)
			break; 
		fprintf(fout, "%08X: ", addr); // 현재 주소를 16진수로 출력
		for (int i = 0; i < nbytes; i++)
		{
			if (i == (BUFFER_LEN / 2))
				fprintf(fout, " "); // i가 BUFFER_LEN / 2가되면 한칸뛰움
			fprintf(fout, "%02X ", buffer[i]); // buffer[i]값을 16진수로 출력
			
		}
		fprintf(fout, " ");
		for (int i = 0; i < nbytes; i++)
		{
			if (isprint(buffer[i])) // buffer[i]가 출력이 가능하면
				fprintf(fout, "%c", buffer[i]); // buffer[i]를 char형문자로 출력
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	}
}