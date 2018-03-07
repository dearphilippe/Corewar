#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int i;
	int fd;
	int count;
	char buffer[2510];
	
	printf("sizeof(magic_number)=%lu\n",sizeof(0xea83f3));
	count = 0;
	bzero(buffer, 2510);
	fd = open(argv[1], O_RDONLY);
	i = read(fd, buffer, 2510);
	while(count < i)
	{	
		printf("%d:%d\t%c\t\t",count, (int)buffer[count], buffer[count]);
		count++;
	}
	return (0);
}
