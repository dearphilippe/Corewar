#include "assembler.h"

void            instruction_error(int point, char *string)
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
    printf("Instruction_error\t[INDEX] [%0.3d][%0.3d]\n", nl, row);
    printf("|%s|\n",&string[point]);
    exit(0);
}

/*
**finds op name in the t_op struct
**upon success, sets param in index 16 of t_op
*/
int         op_check(int i, char *str)
{
    int     code;
    char    *op;
    
    code = 0;
    op = ft_strcdup(&str[i], " \t\n\0");
    while (code < 17)
    {
        if (!ft_strcmp(op_tab[code].op, op))        //checking the struct for opcode
            break;    
        code++;
    }
    ft_bzero(op, sizeof(op));
    free(op);
    if (code == 17)
        instruction_error(i, str);
    return (code);
}


/*
**This get the param from funcyion get_code (T_REG, T_DIR, T_IND) 
**and makes a comparison with 
*/

int         each_param(int i, char *str, int count,int op_code)
{
    int code;
    int possible;

    code = 0;
    if (str[i] == 'r')                              //sets the opcode based on 'r' '%' or '%:'
        code = T_REG;
    else if (str[i] == '%')
    {
        code = T_IND | T_DIR;
        //if (str[i + 1] == ':')
        //    code = T_IND;
        //else if (ft_isdigit(str[i + 1]))
        //    code = T_DIR;
    }
    if (code != 0 && op_tab[op_code].param_type[count] & code)
    {
        while (str[i] != ',' && str[i] != '\n' && str[i] != '\0')
            i++;
        return (i);
    }
    else if (str[i] == '\n')
        return (i);
    else                                             //this should be the error code 
        instruction_error(i, str);                   //for too many parameters 
    return (i);
}

//param check:
//find first opp code in t_op op_tab[17]
//from there count param as they come, back check
//  assess param for define code 'T_REG. T_DIR, T_IND, T_LAB
int        param_chk(int i, char *str)
{
    int param_count;
    int op_code;

    param_count = 0;
    op_code = op_check(i, str);      //if invalid op code, goes to syntax error
    i += ft_strlen(op_tab[op_code].op);
    i += blankspace(&str[i]);
    while (str[i] != '\n' && str[i] != '#' && str[i] != '\0') //&& param_count < op_tab[op_code].num_param 
    {
        if (param_count > op_tab[op_code].num_param)
            instruction_error(i, str);
        i = each_param(i, str, param_count, op_code);
        param_count++;
        if (str[i] == ',')
            i++;
        if (str[i] == '\n')
            break;
        if (blankspace(&str[i]))
            i += blankspace(&str[i]);      //bring me up to the next param
    }
    if (param_count > op_tab[op_code].num_param)
        instruction_error(i, str);
    return (i);
}

//label check: if label, confirms there is a ':' after and returns count up to param
int         label_chk(int i, char *str)
{
    int offset;

    offset = 0;
    while (str[i + offset] != ':' && str[i + offset] != '\n' && str[i + offset] != '\0')
    {    
        offset++;
        if ((str[i + offset - 1] == '%' && str[i + offset] == ':') || str[i + offset] == '\n')
            return (0);
    }
    if (str[i + offset] == ':')
        offset++;
    offset += blankspace(&str[i + offset]);
    return (offset);
}

void        paramcheck(char *content)
{
    int i;

    i = name_comment_param_chk(content);
    i += blankspace(&content[i]);
    while (content[i] != '\0')
    {
        i += label_chk(i, content);      //**skips past the lable up to the parameters
        i = param_chk(i, content);       //this is where the checks are done,
        i += blankspace(&content[i]);      //skips past all blank space up to nl or the comment char
        i += comment_space(&content[i]);    //if comment char is present, skips up to the nl char
    }
}

/*
    last left off at a segfault while debugging 
    and reading ex.s file.
    
*/