/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_instr1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:09:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 14:06:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asmops.h"

void	ft_aff(char **sfile, t_buffers *cor)
{
	struct s_ininit		*handler;

	if (!(handler = (t_ininit *)ft_memalloc(sizeof(t_ininit))))
		exit (1);
	handler->op = AFF;
	genop(sfile, cor, handler);
}
