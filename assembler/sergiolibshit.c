#include "assembler.h"

size_t          comment_skip(char *str)
{
    size_t index;

    index = 0;
    if (str[index] == '#' && str[index] != '\0')
    {
        while (str[index] != '\n' && str[index] != '\0')
            index++;
        while (str[index] == '\n' && str[index] != '\0')
            index++;
    }
    return (index);
}

size_t         name_check(char *str, char *command)
{
    size_t i;

    i = 0;
    while (ft_strchr(command, str[i]) && str[i] != '\n' && str[i] != '\0')
        i++;
    while (ft_isspace(str[i]))
        i++;
    if (str[i++] != '\"')
       err_lex_error(i, str);
    while (str[i] != '\"' && str[i] != '\0')
        i++;
    if (str[i++] != '\"')
        err_lex_error(i, str);
    while (ft_isspace(str[i]) && str[i] != '\0')
        i++;
    i += comment_skip(&str[i]);
    return (i);
}


size_t         name_comment_chk(char *str)
{
    size_t     i;
    bool    name;
    bool    comment;

    i = 0;
    name = false;
    comment = false;
    while (str[i] != '\0' && (name == false || comment == false))
    {
        i += comment_skip(&str[i]);
        while(ft_isspace(str[i]) && str[i] != '\0' && (name == false || comment == false))
            i++;
        if (ft_strcmp(NAME_CMD_STRING, &str[i]) && name == false)
        {
            i += name_check(&str[i], NAME_CMD_STRING);
            name = true;
        }
        if (ft_strcmp(COMMENT_CMD_STRING, &str[i]) && comment == false)
        {
            i += name_check(&str[i], COMMENT_CMD_STRING);
            comment = true;
        }
        i++;
    }
    return (i);
}


int			blankspace(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int			comment_space(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '#')
	{
		i++;
		while (str[i] != '\n' && str[i] != '\0')
			i++;
	}
	return(i);
}

/*
**Makes a copy of a string up to deliniating chars
*/

char			*ft_strcdup(char *str, char *delin)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (!ft_strchr(delin, str[i]))
		i++;
	tmp = ft_strnew(i + 1);
	ft_bzero(tmp, i + 1);
	ft_memcpy(tmp, str, i);
	return (tmp);
}

/*
**ft_strtok and ft_strcspn
**required for tokenizing char strings
*/

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



/*
**dependancy for the ft_read_alloc func
*/

char		*ft_strnjoin(char const *s1, char const *s2, int i)
{
	char *string;

	string = ft_strjoin(s1, s2);
	if (i == 1 || i == 3)
	{
		free((void*)s1);
		s1 = NULL;
	}
	else if (i == 2 || i == 3)
	{
		free((void*)s2);
		s2 = NULL;
	}
	return ((char*)string);
}

/*
**Below is needed to read from an FD and return a char *
**without parsing data
*/


void		bigger_buffer(char *chr_buffer, int buffer_cnt)
{
	buffer_cnt *= 2;
	free(chr_buffer);
}

char		*ft_read_alloc(int fd)
{
	char	*content;
	char	*chr_buffer;
	int		buffer_cnt;
	int		read_count;

	buffer_cnt = 64;
	chr_buffer = ft_strnew(buffer_cnt);
	if (fd < 0 || (read(fd, &chr_buffer, 0) < 0))
		return (NULL);
	content = ft_strnew(1);
	while ((read_count = read(fd, chr_buffer, buffer_cnt)))
	{
		if (!(content = ft_strnjoin(content, chr_buffer, 1)))
		{
			free(&content);
			return (NULL);
		}
		if (read_count == buffer_cnt)
		{
			bigger_buffer(chr_buffer, buffer_cnt);
			chr_buffer = ft_strnew(buffer_cnt);
		}
	}
	free(chr_buffer);
	return (content);
}