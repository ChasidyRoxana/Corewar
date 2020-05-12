#include "./includes/asm.h"

int main(int argc, char **argv)
{
	int buf_size = 50;
	int fd1, fd2;
	char buf1[buf_size + 1], buf2[buf_size + 1];
	int k1, k2;

	if (argc < 3)
	{
		printf("need -cor [file.cor] || two files for comparison\n");
		return 1;
	}
	if (!ft_strcmp(argv[1], "-cor"))
	{
		if ((fd2 = open(argv[2], O_RDONLY)) < 0)
		{
			printf("open error\n");
			return 1;
		}
		while (1)
		{
			k2 = read(fd2, buf2, buf_size);
			if (k2 <= 0)
				break;
			buf2[k2] = '\0';
			for (int i = 0; i < buf_size; i++)
				printf("%d ", buf2[i]);
			printf("\n");
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
			if (ft_strcmp(buf1, buf2) != 0)
			{
				int j = 0;
				while (buf1[j])
					printf("%d ", buf1[j++]);
				printf("\n");
				j = 0;
				while (buf2[j])
					printf("%d ", buf2[j++]);
				break;
			}
		}
		if (k1 == 0 && k1 == k2)
			printf("all good\n");
		else if (k1 < k2)
			printf("1 file is over\n");
		else if (k2 < k1)
			printf("2 file is over\n");
	}
	return 0;
}