/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:57:01 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 18:00:07 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "op.h"

int		remove_comment(char **strp1, t_buffers *cor)
{
	char	*sub;
	int		ret;

	ret = 0;
	*strp1 += ft_skip_spaces(*strp1);
	if (**strp1 == COMMENT_CHAR)
	{
		while (**strp1 == COMMENT_CHAR)
		{
			if (!(sub = ft_strchr(*strp1, '\n')))
			{
				*strp1 = ft_strchr(*strp1, '\0');
				return (ret);
			}
			else
				*strp1 = sub;
			if (*strp1)
			{
				(*strp1)++;
				cor->line++;
				ret = 1;
			}
			*strp1 += ft_skip_spaces(*strp1);
		}
	}
	return (ret);
}
