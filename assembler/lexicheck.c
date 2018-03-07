/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 21:36:11 by sbalcort          #+#    #+#             */
/*   Updated: 2018/02/18 21:36:12 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"



int      end_check(char *str, char C)
{
    int i;

    i = 0;
    if (str[i] == C)
        i++;
    while (ft_isspace(str[i]) && str[i] != '\n')
        i++;
    if (str[i] == '\n' || str[i] == '#' || str[i] == '\0')
        return (-1);
    return (i);
}

void        lexi_check(char *str)
{
    size_t  i;
    
    i = name_comment_chk(str);
    //printf("name check success\n");
    while (str[i] != '\0')
    {
        while (ft_isspace(str[i]) && str[i] != '\0')
            i++;
        if (ft_strchr(LABEL_CHARS, (int)str[i]) && str[i] != '\0')
            while (ft_strchr(LABEL_CHARS, (int)str[i]))
                i++;
        if (str[i] == ',')
            i++;
        if (str[i] == ':' && ft_strchr(LABEL_CHARS, str[i - 1]) && str[i] != '\0')
            i++;
        if (str[i] == '%')
        {
            i++;
            if (str[i] == ':')
            {
                i++;
                if (ft_strchr(LABEL_CHARS, (int)str[i]) && str[i] != '\0')
                    while (ft_strchr(LABEL_CHARS, (int)str[i]) && str[i] != '\0')
                        i++;
                else
                    err_lex_error(i, str);
            }
            else if (ft_isdigit(str[i]) || str[i] == '-')
            {
                if (str[i] == '-')
                    i++;
                while (ft_strchr(LABEL_CHARS, (int)str[i]) && str[i] != '\0')
                    i++;
            }
            else
                err_lex_error(i, str);
        }
        if (str[i] == '#')
        {
            while (str[i] != '\n' && str[i] != '\0')
                i++;
        }
        if (str[i] == '\n')
        {
            i++;
            continue;
        }
        if (!ft_strchr("0123456789_abcdefghijklmnopqrstuvwxyz%%:\t#, ", (int)str[i]))
            err_lex_error(i, str);
    }
}