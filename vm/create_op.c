/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 19:26:00 by satkins           #+#    #+#             */
/*   Updated: 2018/03/01 15:48:45 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		param_size(unsigned char coding_byte, int truncate)
{
	int			len;

	len = 0;
	if (((coding_byte) & 0xFF) == REG_CODE)
		len += 1;
	else if (((coding_byte) & 0xFF) == IND_CODE)
		len += IND_SIZE;
	else if (((coding_byte) & 0xFF) == DIR_CODE)
		len += truncate ? 2 : DIR_SIZE;
	return (len);
}

/*
** get_len will call param size for each of the parameters for the instruct
** param_size will be passed the corrisponding coding bits for that parameter
** get_len will increment pc in a circular fashion. incrementing past all
** params
*/

static int		get_len(unsigned char c, t_instruction *instruc, 
	unsigned char **pc, unsigned char *arena)
{
	int			len;
	int			i;

	len = 0;
	instruc->p_s[0] = param_size(c >> 6, op_tab[instruc->op_code].tr);
	len += instruc->p_s[0];
	i = -1;
	while (++i < len)
		*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
	if (op_tab[instruc->op_code].num_param > 1)
	{
		instruc->param[1] = *pc;
		instruc->p_s[1] = param_size(c >> 4, op_tab[instruc->op_code].tr);
		len += instruc->p_s[1];
		while (++i < len)
				*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		if (op_tab[instruc->op_code].num_param > 2)
		{
			instruc->param[2] = *pc;
			instruc->p_s[2] = param_size(c >> 2, op_tab[instruc->op_code].tr);
			len += instruc->p_s[2];
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
** PC is incremented in a way to mimick cirular memory. See line 89
** line 89 explained:
** if pc+1 is larger than arena(address of the start of the shared mem)+memsize
** then pc becomes areana (a)(first address in the mem) else pc++
*/

int				get_instruct(unsigned char **pc, unsigned char *a,
	t_instruction *in)
{
	unsigned char	coding_byte;
	int				len;

	len = 0;
	ft_bzero(in, sizeof(t_instruction));
	if (**pc && **pc <= 16)
	{
		in->pc = *pc;
		in->op_code = **pc;
		*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
		if (!op_tab[in->op_code].coding_byte)
		{
			in->param[0] = *pc;
			len = op_tab[in->op_code].tr ? 2 : DIR_SIZE;
			while (--len >= 0)
				*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
			return (op_tab[in->op_code].tr ? 3 : DIR_SIZE + 1);
		}
		coding_byte = **pc;
		*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
		in->param[0] = *pc;
		len = get_len(coding_byte, in, pc, a);
	}
	else
		*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;		
	return (len);	
}
