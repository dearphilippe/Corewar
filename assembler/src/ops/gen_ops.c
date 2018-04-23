/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:46:30 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 16:54:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asmops.h"

void		genop(char **sfile, t_buffers *cor, t_ininit *handler)
{
	handler->params = op_tab[(handler->op - 1)].num_param;
	cor->prog_len++; /* opcode byte count increase */
	handler->opbyte = op_tab[(handler->op - 1)].coding_byte;
	/* handle some other initialization properties on second pass */
	if (!cor->pass)
	{
		while (IS_ALPHA(**sfile))
			(*sfile)++;
		handler->opbyte = 0;
	}
	/* find, classify the parameters, and then store, pointer moved to end */
	instr_paramsplit(handler, cor, sfile);
	if (!cor->pass)
		ft_lstadd(&cor->instructions, handler, sizeof(*handler));
}
