/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:03:20 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 14:03:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asmops.h"

void	ft_add(char **sfile, t_buffers *cor)
{
	struct s_ininit		*handler;

	if (!(handler = (t_ininit *)ft_memalloc(sizeof(t_ininit))))
		exit (1);
	handler->op = ADD;
	genop(sfile, cor, handler);
}
