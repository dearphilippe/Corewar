/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:09:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 14:10:05 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asmops.h"

void	ft_lfork(char **sfile, t_buffers *cor)
{
	struct s_ininit		*handler;

	if (!(handler = (t_ininit *)ft_memalloc(sizeof(t_ininit))))
		exit (1);
	handler->op = LFORK;
	genop(sfile, cor, handler);
}
