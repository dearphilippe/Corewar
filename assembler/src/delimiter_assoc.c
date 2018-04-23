/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_assoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:14:00 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 14:40:52 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

char	*delimiter_assoc(t_ininit *handler, char **sfile, t_buffers *cor)
{
	char	*delim;

	delim = *sfile;
	while (*delim)
	{
		if (*delim == SEPARATOR_CHAR
			|| *delim == COMMENT_CHAR
			|| (*delim == LABEL_CHAR && delim != *sfile)
			|| *delim == ' '
			|| *delim == '\t')
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
