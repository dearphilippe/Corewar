/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 19:26:00 by satkins           #+#    #+#             */
/*   Updated: 2018/02/28 09:29:09 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		param_size(char coding_byte, int truncate)
{
	int			len;

	len = 0;
	if ((coding_byte) & 0xFF == REG_CODE)
		len += 1;
	else if ((coding_byte) & 0xFF == IND_CODE)
		len += IND_SIZE;
	else if ((coding_byte) & 0xFF == DIR_CODE)
		len += truncate ? 2 : DIR_SIZE;
	return (len);
}

static int		get_len(char c, t_instruction *instruc, char **pc, char *arena)
{
	int			len;
	int			i;

	len = 0;
	len += param_size(c >> 6, op_tab[instruc->op_code].truncate);
	i = -1;
	while (++i < len)
		*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
	if (op_tab[instruc->op_code].num_param > 1)
	{
		instruc->param[1] = *pc;
		len += param_size(c >> 4, op_tab[instruc->op_code].truncate);
		while (++i < len)
				*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		if (op_tab[instruc->op_code].num_param > 2)
		{
			instruc->param[1] = *pc;
			len += param_size(c >> 2, op_tab[instruc->op_code].truncate);
			while (++i < len)
				*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		}
	}
	return (len + 2);
}

/*
** Returns the Len of the instruction at PC. 0 if not an instruction
** Also will create an instruction to be passed to the executioner
** Also increments the Program Counter for the passed in Process
** PC is a pointer passed by reference so that it can be modified
** PC is incremented in a way to mimick cirular memory. See line 77
** line 77 explained:
** if pc+1 is larger than arena(address of the start of the shared mem)+memsize
** then pc becomes areana (first address in the mem) else pc++
*/

int				get_instruct(char **pc, char *arena, t_instruction *instruc)
{
	char		coding_byte;
	int			len;

	len = 0;
	if (**pc && **pc <= 16)
	{
		instruc->pc = *pc;
		instruc->op_code = **pc;
		*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		if (!op_tab[instruc->op_code].coding_byte)
		{
			instruc->param[0] = *pc;
			len = op_tab[instruc->op_code].truncate ? 2 : DIR_SIZE;
			while (--len >= 0)
				*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
			return (op_tab[instruc->op_code].truncate ? 3 : DIR_SIZE + 1);
		}
		coding_byte = **pc;
		*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		instruc->param[0] = *pc;
		len = get_len(coding_byte, instruc, pc, arena);
	}
	else
		*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;		
	return (len);	
}
