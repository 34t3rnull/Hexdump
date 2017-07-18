#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void hexdump(FILE *fp, int size)
{
	char buffer[16];
	int buffer_len, offset, i;
	for (offset = 0; offset < size; offset += 16)
	{
		buffer_len = fread(buffer, sizeof(char), sizeof(buffer), fp);
		printf("%08x : ", offset);
		if (offset + 16 > size)
			buffer_len = size - offset;
		for (i = 0; i < buffer_len; i++)
			printf(" %02x", (unsigned char)buffer[i]);
		for (i = 0; i <= 16 - buffer_len; i++)
			printf("   ");
		for (i = 0; i < buffer_len; i++)
		{
			if (isprint(buffer[i]))
				printf("%c", buffer[i]);
			else
				printf(".");
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char *file_name;
	int file_len, i, command, size;

	if (argc == 1)
	{
		printf("[*] Please input a relative path to the file\n");
		printf("[*] How to use : ./hexdump file_name\n");
		exit(1);
	}

	file_name = argv[1];

	if (!(fp = fopen(file_name, "rb")))
	{
		printf("[*] Can't open this file\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	file_len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	printf("[*] File Open Success\n");
	printf("    -> File Name : %s\n", file_name);
	printf("    -> File Length : %d (%x)\n", file_len, file_len);
	printf("[*] How much do you want to see?\n");
	printf("    -> 1. All of size\n");
	printf("    -> 2. Some of size\n");
	printf("> Input : ");
	scanf("%d", &command);
	switch (command)
	{
	case 1:
		hexdump(fp, file_len);
		break;
	case 2:
		printf("> Put the desired size : ");
		scanf("%d", &size);
		hexdump(fp, size);
		break;
	default:
		printf("[*] Unexpected Input\n");
		break;
	}
	fclose(fp);
	return 0;
}