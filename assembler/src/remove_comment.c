/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:57:01 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 14:20:05 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "op.h"

int		remove_comment(char **strp1, t_buffers *cor)
{
	char	*sub;
	int		ret;

	ret = 0;
	while (IS_WHSPC(**strp1))
	{
		ft_printf("wspc\n");
		(*strp1)++;
	}
	if (**strp1 == COMMENT_CHAR)
	{
		while (**strp1 == COMMENT_CHAR)
		{
			if (!(sub = ft_strchr(*strp1, '\n')))
			{
				*strp1 = NULL;
				return (ret);
			}
			*strp1 = sub;
			(*strp1)++;
			cor->line++;
			ret = 1;
			while (IS_WHSPC(**strp1))
				(*strp1)++;
		}
	}
	return (ret);
}
