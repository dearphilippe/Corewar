/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_assoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:08:43 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 16:29:13 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

void	instr_assoc(t_buffers *cor, t_ininit *handler)
{
	int		i;

	i = 0;
	while (i < handler->params)
	{
		if ((handler->trans[i] & T_DIR) && !(op_tab[(handler->op - 1)]).tr)
			handle_dir(cor, handler, i);
		else if ((handler->trans[i] & T_DIR) && (op_tab[(handler->op - 1)]).tr)
			handle_ind(cor, handler, i);
		if (handler->trans[i] & T_REG)
		{
			if (handler->param[i] > REG_NUMBER || !handler->param[i])
			{
				printf("too high a register!\n");
				exit (1);
			}
			handle_dir(cor, handler, i);
		}
		if ((handler->trans[i] & T_IND) || (handler->trans[i] & T_LAB))
			handle_ind(cor, handler, i);
		i++;
	}
}
