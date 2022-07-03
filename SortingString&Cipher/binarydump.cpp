#include "HandlingBinaryFile.h"
#define BUFFER_LEN 16
#define MAX_FILE_SIZE 1024

void dumpBinaryFile(FILE* fin, FILE* fout)
{
	int nbytes;
	unsigned char buffer[BUFFER_LEN] = { '\0' }; // �迭 buffer ����
	for (int addr = 0; addr < MAX_FILE_SIZE; addr += BUFFER_LEN)
	{
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin); // �������������� fin���κ��� BUFFER_LEN��ŭ �о� buffer������
		if (nbytes <= 0)
			break; 
		fprintf(fout, "%08X: ", addr); // ���� �ּҸ� 16������ ���
		for (int i = 0; i < nbytes; i++)
		{
			if (i == (BUFFER_LEN / 2))
				fprintf(fout, " "); // i�� BUFFER_LEN / 2���Ǹ� ��ĭ�ٿ�
			fprintf(fout, "%02X ", buffer[i]); // buffer[i]���� 16������ ���
			
		}
		fprintf(fout, " ");
		for (int i = 0; i < nbytes; i++)
		{
			if (isprint(buffer[i])) // buffer[i]�� ����� �����ϸ�
				fprintf(fout, "%c", buffer[i]); // buffer[i]�� char�����ڷ� ���
			else
				fprintf(fout, ".");
		}
		fprintf(fout, "\n");
	}
}