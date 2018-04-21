/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_assoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:14:00 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 16:16:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

char	*delimiter_assoc(t_ininit *handler, char **sfile, t_buffers *cor)
{
	char	*delim;
	int		params;

	handler ? (params = handler->params) : (params = 0);
	delim = *sfile;
	while (*delim)
	{
		if (*delim == SEPARATOR_CHAR
			|| *delim == COMMENT_CHAR
			|| *delim == LABEL_CHAR
			|| *delim == SEPARATOR_CHAR
			|| ft_isspace(*delim))
			return (delim);
		else if (*delim == '\n')
		{
			cor->line++;
			return (delim);
		}
		else
			delim++;
	}
	handler ? handler->eof = 1 : 0;
	return (delim);
}
