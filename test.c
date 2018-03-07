#include <string.h>
#include <stdio.h>
#include "libstar/libft.h"



size_t     ft_strcspn(char *str, char *delim)
{
    int     x;
    int     y;

    if (str == NULL)
        return (0);
    x = 0;
    while (str[x] != '\0')
    {
        y = 0;
        while (delim[y] != '\0')
        {
            if (str[x] == delim[y])
                return (x);
            y++;
        }
        x++;
    }
    return (x);
}

char    *ft_strtok(char *s, const char *delim)
{
    static char *lasts;
    register int ch;

    if (s == NULL)
	    s = lasts;
    if ((ch = *s++) == '\0')
	    return (NULL);
    while (strchr(delim, ch))
    {
	if ((ch = *s++) == '\0')
	    return (NULL);
    }
    --s;
    lasts = s + strcspn(s, delim);
    if (*lasts != '\0')
        *lasts++ = '\0';
    return (s);
}




int main(int argc, char **argv)
{
    char *s;
    char *token;
    char *test_str;

    s = argv[2];
    test_str = ft_strdup(argv[1]);
    token = argv[1];

    printf("\tthe real thing\n");
    token = strtok(token, s);
    while (token != NULL)
    {
        ft_putendl(token);
        token = strtok(NULL, s);
    }
    printf("\n\tMyturn\n");
    
    test_str = ft_strtok(test_str, s);
    while (test_str != NULL)
    {
        printf(" %s\n", test_str);
        test_str = ft_strtok(NULL, s);
    }
    return (0);
}