/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machinestart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 13:59:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 18:03:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

#define DATA ((t_ininit *)(instr->data))

void	build_prog(t_buffers *cor)
{
	t_list	*instr;
	int		i;

	instr = cor->instructions;
	cor->pass++;
	i = 0;
	while (instr)
	{
		*cor->prog_cor++ = DATA->op;
		if (DATA->opbyte)
			*cor->prog_cor++ = DATA->opbyte;
		instr_assoc(cor, DATA);
		instr = instr->next;
	}
}
