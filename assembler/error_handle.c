#include "assembler.h"

void	err_usage_warning(char *str)
{
	int	errno;

	if (str != NULL)
	{
		errno = EACCES;
		printf("Usage: ./asm [%s]", str);
	}
	else
	{
		printf("Usage: ./asm [file ...]\n");
		errno = EFTYPE;
	}
	exit(errno);
}

void    err_lex_error(int point, char *str)
{
    int	i;
	int	nl;
	int	row;

	row = 0;
	i = 0;
	nl = 1;
	while (i < point)
	{
		if (str[i] == '\n' || str[i] == '\0')
		{	
			nl++;
			row = 0;
		}
		row++;
		i++;
	}
	printf("\n%s\n'%c'\t%d\n", &str[point], str[point], (int)str[point]);
	printf("Lexical error at [%0.3d][%0.3d]", nl, row);
    exit(0);
}