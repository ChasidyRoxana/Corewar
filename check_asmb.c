#include "./includes/asm.h"

int main(int argc, char **argv)
{
	int buf_size = 16;
	int fd1, fd2;
	unsigned char buf1[buf_size + 1], buf2[buf_size + 1];
	int k1, k2;
	int num_line = 0;

	if (argc < 2)
	{
		printf("need [file.cor] for hex || two files for comparison\n");
		return 1;
	}
	if (argc == 2)
	{
		if ((fd2 = open(argv[1], O_RDONLY)) < 0)
		{
			printf("open error\n");
			return 1;
		}
		int tmp_line;
		while (1)
		{
			k2 = read(fd2, buf2, buf_size);
			if (k2 <= 0)
				break;
			buf2[k2] = '\0';
			if (num_line > 0 &&buf2[0]==0&&buf2[1]==0&&buf2[2]==0&&
				buf2[3]==0&&buf2[4]==0&&buf2[5]==0&&buf2[6]==0&&
				buf2[7]==0&&buf2[8]==0&&buf2[9]==0&&buf2[10]==0&&
				buf2[11]==0&&buf2[12]==0&&buf2[13]==0&&
				buf2[14]==0&&buf2[15]==0)
				;
			else
			{
				if (num_line > 0 && tmp_line != num_line - 1)
					printf("\n...");
				printf("\n%08d: ", num_line);
				for (int i = 0; i < k2; i++)
				{
					unsigned int one = buf2[i]/16;
					unsigned int two = buf2[i]%16;
					printf("%c",(one > 9 ? one+'W':one+'0'));
					printf("%c ", (two > 9 ? two+'W':two+'0'));
				}
				tmp_line = num_line;
			}
			num_line++;
		}
	}
	else
	{
		if ((fd1 = open(argv[1], O_RDONLY)) < 0 || (fd2 = open(argv[2], O_RDONLY)) < 0)
		{
			printf("open error\n");
			return 1;
		}
		while (1)
		{
			k1 = read(fd1, buf1, buf_size);
			k2 = read(fd2, buf2, buf_size);
			if (k1 <= 0 || k2 <= 0)
				break;
			buf1[k1] = '\0';
			buf2[k2] = '\0';
			if (buf1[0]==buf2[0]&&buf1[1]==buf2[1]&&
				buf1[2]==buf2[2]&&buf1[3]==buf2[3]&&buf1[4]==buf2[4]&&
				buf1[5]==buf2[5]&&buf1[6]==buf2[6]&&buf1[7]==buf2[7]&&
				buf1[8]==buf2[8]&&buf1[9]==buf2[9]&&buf1[10]==buf2[10]&&
				buf1[11]==buf2[11]&&buf1[12]==buf2[12]&&buf1[13]==buf2[13]&&
				buf1[14]==buf2[14]&&buf1[15]==buf2[15])
				;
			else
			{
				printf("\n%08d: ", num_line);
				for (int i = 0; i < k1; i++)
				{
					unsigned int one = buf1[i]/16;
					unsigned int two = buf1[i]%16;
					printf("%c",(one > 9 ? one+'W':one+'0'));
					printf("%c ", (two > 9 ? two+'W':two+'0'));
				}
				printf("\n%08d: ", num_line);
				for (int i = 0; i < k2; i++)
				{
					unsigned int one = buf2[i]/16;
					unsigned int two = buf2[i]%16;
					printf("%c",(one > 9 ? one+'W':one+'0'));
					printf("%c ", (two > 9 ? two+'W':two+'0'));
				}
				printf("\nERROR!!!");
				break;
			}
			num_line++;
		}
		if (k1 == 0 && k2 == 0)
			printf("ALL GOOD C:\n");
	}
	return 0;
}