#include "assembler.h"

#define LABEL 0b00000001
#define PARAM 0b00000010
#define NL_LN 0b00000100
#define COMME 0b00001000

char        *get_instruction(int i, char *str)
{
    while (!ft_isspace(str[i]) && str[i] != '\0' && str[i] != ',')
        i++;
    str[i] = '\0';
    ft_bzero(&str[i], sizeof(&str[i]));
    while (str[i] != '\n' && str[i] != ',' && str[i] != ' ' && str[i] != '\t')
        i--;
    return (&str[++i]);
}

void        syntax_error(int point, char *string)
{
    int	nl;
	int	row; 
    int i;

    i = 0;
	row = 0;
	nl = 1;
	while (i < point)
	{
		if (string[i] == '\n' || string[i] == '\0')
		{	
			nl++;
			row = 0;
		}
		row++;
		i++;
	}
    printf("Syntax error at token [TOKEN][%0.3d][%0.3d] ", nl, row);
    printf("INSTRUCTION %s", get_instruction(point, string));
    exit(0);
    //Syntax error at token [TOKEN][019:022] INSTRUCTION "r3i99"
}

int         label_check(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
        return (0);
    while (ft_strchr(LABEL_CHARS , (int)str[i]))
        i++;
    if (str[i] == ':')
        i++;
    return (i);
}

int         param_check(int i, char *str)
{

    i += blankspace(&str[i]);
    if (str[i] == '\0' || str[i] == '\n' || str[i] == '#')
        return (0);
    while (str[i] != '\0' && str[i] != '\n' && str[i] != '#')
    {
        i += blankspace(&str[i]);
        if (str[i] == '%')
        {
            i++;
            if (ft_isdigit(str[i]))
            {
                if (str[i] == '-')
                    i++;
                while (ft_isdigit((int)str[i]))
                    i++;
            }
            else if (str[i] == ':')
            {
                i++;
                while (ft_strchr(LABEL_CHARS, (int)str[i]))
                    i++;
            }
        }
        else if (str[i] == 'r')
        {
            i++;
            while (ft_isdigit(str[i]))
                i++; 
        }
        else if (str[i] == ',')
        {
            i++;
            if(comment_space(&str[i + blankspace(&str[i])]))
            {
                printf("failing char='%c'", str[i]);
                syntax_error(i, str);
            }
           continue;
        }
        else if (str[i] == '#') 
            i += comment_space(&str[i]);
        else
        {
            printf("failing char='%c'", str[i]);
            syntax_error(i, str);
        }
        if (str[i] == '\n' || str[i] == '\0')
            continue;
        if (str[i] != ',')
            i++;
    }
    return (i);
}

int         name_comment_param_chk(char *str)
{
    int i;

    i = 0;
    while (ft_strchr(NAME_CMD_STRING, str[i]))
        i++;
    i += blankspace(&str[i]);
    if (str[i] == '"')
        i++;
    while (ft_strchr(ERR_THANG, str[i]))
        i++;
    if (str[i] == '"')
        i++;
    while (ft_isspace(str[i]) && str[i] != '\n')
        i++;
    if (str[i] != '\n')
        syntax_error(i, str);
    i += blankspace(&str[i]);
    while (ft_strchr(COMMENT_CMD_STRING, str[i]))
        i++;
    i += blankspace(&str[i]);
    if (str[i] == '"')
        i++;
    while (ft_strchr(ERR_THANG, str[i]))
        i++;
    if (str[i] == '"')
        i++;
    while (ft_isspace(str[i]) && str[i] != '\n')
        i++;
    if (str[i] != '\n')
        syntax_error(i, str);
    return (i);
}

void    	syntcheck(char *content)
{
    int     i;

    i = name_comment_param_chk(content);
    i += blankspace(&content[i]);
    while (content[i] != '\0')
    {
        i += blankspace(&content[i]);
        if (label_check(&content[i]))
            i += label_check(&content[i]);
        i += blankspace(&content[i]);
        while (ft_strchr(LABEL_CHARS, (int)content[i]) && content[i] != '\0')
            i++;
        if (param_check(i, content))        //here need to have a check for #comment, '\0' ? or '\n'?
            i = param_check(i, content);
        else if (comment_space(&content[i]))
            i += comment_space(&content[i]);
        else
            syntax_error(i, content);
    }
}



/* take off here 
while debugging here there is an issue of not identifying 
	and	r1,%0,#r1
as syntax error*/