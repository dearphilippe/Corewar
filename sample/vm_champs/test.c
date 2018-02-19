#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int 	fd = open("champs/ex.cor", O_RDONLY);
    char    buff[4];
    int 	result;
    int 	*value;

    read(fd, buff, 4);
    result = 0;
	printf("leftmost: %#x\nbyte: %#x\nbyte: %#x\nrightmost: %#x\n", buff[0], buff[1], buff[2], buff[3]);
	value = (int *)buff;
	printf("cast: %#x\n", *value);
    result |= (*value & 0x000000FF) << 24;
    result |= (*value & 0x0000FF00) << 8;
    result |= (*value & 0x00FF0000) >> 8;
    result |= (*value & 0xFF000000) >> 24;
    printf("read : %d\n", *value == 0xea8373);
    printf("result : %d\n", *value == 0xea8373);
    printf("read: %#x\nresult: %#x\nmagic: %#x\n", *value, result, 15369075); 
	return (0);
}
