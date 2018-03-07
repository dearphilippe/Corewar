/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 21:59:30 by sbalcort          #+#    #+#             */
/*   Updated: 2018/02/18 21:59:31 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# include "../libstar/libft.h"
# include <stdio.h>
# include "op.h"
# include <stdbool.h>
# include <errno.h>

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define ERR_THANG			"abcdefghijklmnopqrstuvwxyz_0123456\t78 9"
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

void    lexi_check(char *str);
void    	syntcheck(char *content);
void        paramcheck(char *content);



char    *ft_read_alloc(int fd);
char    *ft_strtok(char *s, const char *delim);


void	err_usage_warning(char *str);
void    err_lex_error(int i, char *str);
int		blankspace(char *str);
int     comment_space(char *str);
size_t  name_comment_chk(char *str);
char	*ft_strcdup(char *str, char *delin);
size_t  name_check(char *str, char *command);
size_t  comment_skip(char *str);
int         name_comment_param_chk(char *str);


#endif