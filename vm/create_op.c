/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 19:26:00 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 00:19:15 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	advance_pc(unsigned char coding_byte, unsigned char op_code,
	unsigned char **pc, unsigned char *arena)
{
	int		num_param;
	int		len;
	int		i;

	num_param = op_tab[op_code - 1].num_param;
	len = 1;
	i = -1;
	while (++i < num_param)
	{
		if (((coding_byte >> (6 - i * 2)) & 0x3) == DIR_CODE)
			len += op_tab[op_code - 1].tr ? 2 : DIR_SIZE;
		if (((coding_byte >> (6 - i * 2)) & 0x3) == IND_CODE)
			len += IND_SIZE;
		if (((coding_byte >> (6 - i * 2)) & 0x3) == REG_CODE)
			len += 1;
	}
	i = -1;
	while (++i < len)
		*pc = *pc + 1 < arena + MEM_SIZE ? *pc + 1 : arena;
	return (0);
}

static int	check_coding_byte(unsigned char coding_byte, t_instruction *instruc)
{
	int		i;

	i = MAX_PARAM;
	coding_byte = coding_byte >> 2;
	while (--i >= 0)
	{
		if ((coding_byte & 0x3) == REG_CODE &&
			!(op_tab[instruc->op_code - 1].param_type[i] & T_REG))
			return (0);
		else if ((coding_byte & 0x3) == DIR_CODE &&
			!(op_tab[instruc->op_code - 1].param_type[i] & T_DIR))
			return (0);
		else if ((coding_byte & 0x3) == IND_CODE &&
			!(op_tab[instruc->op_code - 1].param_type[i] & T_IND))
			return (0);
		else if ((coding_byte & 0x3) == 0 &&
			op_tab[instruc->op_code - 1].param_type[i] != 0)
			return (0);
		coding_byte = coding_byte >> 2;
	}
	return (1);
}

static int	p_size(unsigned char coding_byte, int truncate)
{
	int		len;

	len = 0;
	if (((coding_byte) & 0x3) == REG_CODE)
		len += 1;
	else if (((coding_byte) & 0x3) == IND_CODE)
		len += IND_SIZE;
	else if (((coding_byte) & 0x3) == DIR_CODE)
		len += truncate ? 2 : DIR_SIZE;
	return (len);
}

/*
** get_len will call param size for each of the parameters for the instruct
** p_size will be passed the corrisponding coding bits for that parameter
** get_len will increment pc in a circular fashion. incrementing past all
** params
*/

static int	get_len(unsigned char c, t_instruction *instruc,
	unsigned char **pc, unsigned char *arena)
{
	int len;
	int i;

	len = 0;
	instruc->p_s[0] = p_size(c >> 6, op_tab[instruc->op_code - 1].tr);
	len += instruc->p_s[0];
	i = -1;
	while (++i < len)
		*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
	if (op_tab[instruc->op_code - 1].num_param > 1)
	{
		instruc->param[1] = *pc;
		instruc->p_s[1] = p_size(c >> 4, op_tab[instruc->op_code - 1].tr);
		len += instruc->p_s[1];
		while (++i < len + 1)
			*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		if (op_tab[instruc->op_code - 1].num_param > 2)
		{
			instruc->param[2] = *pc;
			instruc->p_s[2] = p_size(c >> 2, op_tab[instruc->op_code - 1].tr);
			len += instruc->p_s[2];
			while (++i < len + 2)
				*pc = (*pc + 1 - arena < MEM_SIZE) ? *pc + 1 : arena;
		}
	}
	return (len + 2);
}

/*
** Returns the Len of the instruction at PC. 0 if not an instruction
** This validation of instruction includes checking op_code & checking ACB
** Also will create an instruction to be passed to the executioner
** Also increments the Program Counter for the passed in Process
** PC is a pointer passed by reference so that it can be modified
** PC is incremented in a way to mimick cirular memory. See line 120
** line 120 explained:
** if pc+1 is larger than arena(address of the start of the shared mem)+memsize
** then pc becomes areana (a)(first address in the mem) else pc++
*/

int			get_instruct(unsigned char **pc, unsigned char *a,
	t_instruction *in)
{
	int len;

	len = 0;
	if (in->op_code > 0 && in->op_code <= 16)
	{
		in->pc = *pc;
		*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
		if (!op_tab[in->op_code - 1].coding_byte)
		{
			in->param[0] = *pc;
			len = op_tab[in->op_code - 1].tr ? 2 : DIR_SIZE;
			while (--len >= 0)
				*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
			return (op_tab[in->op_code - 1].tr ? 3 : DIR_SIZE + 1);
		}
		in->coding_byte = **pc;
		if (!check_coding_byte(in->coding_byte, in))
			return (advance_pc(in->coding_byte, in->op_code, pc, a));
		*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
		in->param[0] = *pc;
		len = get_len(in->coding_byte, in, pc, a);
	}
	else
		*pc = (*pc + 1 - a < MEM_SIZE) ? *pc + 1 : a;
	return (len);
}
