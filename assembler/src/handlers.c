/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:31:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 12:17:32 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

static void	bytetrans(int *param, t_buffers *cor, int len)
{
	unsigned char	*transfer;

	printf("num to convert %d\n", *param);
	transfer = (unsigned char *)param;
	while (len--)
	{
		printf("byte: %x\n", transfer[len]);
		*(cor->prog_cor)++ = transfer[len];
	}
}

void	handle_ind(t_buffers *cor, t_ininit *handler, int i)
{
	if (!cor->pass)
	{
		if (handler->opbyte)
		{
			if (!i)
				handler->opbyte = handler->opbyte ^ handler->opbyte;
			if (handler->trans[i] & T_DIR)
				handler->opbyte = handler->opbyte |
					(DIR_CODE << (((int)(sizeof(t_arg_type) - 2)) - (i * 2)));
			else
				handler->opbyte = handler->opbyte |
					(IND_CODE << (((int)(sizeof(t_arg_type) - 2)) - (i * 2)));
		}
		cor->prog_len += IND_SIZE;
	}
	if (cor->pass)
		bytetrans(&(handler->param[i]), cor, IND_SIZE);
}

void	handle_dir(t_buffers *cor, t_ininit *handler, int i)
{
	if (!cor->pass)
	{
		if (handler->opbyte)
		{
			if (!i)
				handler->opbyte = handler->opbyte ^ handler->opbyte;
			if (handler->trans[i] & T_REG)
				handler->opbyte = handler->opbyte |
					(REG_CODE << (((int)(sizeof(t_arg_type) - 2)) - (i * 2)));
			else
				handler->opbyte = handler->opbyte |
					(DIR_CODE << (((int)(sizeof(t_arg_type) - 2)) - (i * 2)));
		}
		(handler->trans[i] & T_DIR) ? (cor->prog_len += DIR_SIZE) : 
			(cor->prog_len += 1);
	}
	/* second pass shit */
	if (cor->pass)
		bytetrans(&(handler->param[i]), cor, 
				((handler->param[i] & T_DIR) ? DIR_SIZE : 1));
}
