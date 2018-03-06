/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:08:06 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 02:55:30 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"

int (*get_value[4])(int num, t_process *proc, t_arena *arena) = {
	NULL,
	get_reg_val,
	get_dir_val,
	get_ind_val
	};

int					*read_param(t_process *proc, t_arena *arena)
{
	int				*ret;
	unsigned char	*addr;
	unsigned char	hold;
	int				i;
	int				k;

	if (!(ret = ft_memalloc(sizeof(int) *
		op_tab[proc->instruct.op_code - 1].num_param)))
		exit(0);
	k = -1;
	while (++k < op_tab[proc->instruct.op_code - 1].num_param)
	{
		ret[k] = 0;
		addr = proc->instruct.param[k];
		i = -1;
		while (++i < proc->instruct.p_s[k])
		{
			ret[k] = ret[k] << 8;
			ret[k] += *addr;
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		}
		if (proc->instruct.p_s[k] == 2 && (ret[k] & 0x8000))
			ret[k] = (ret[k] | 0xFFFF0000);
		hold = (proc->instruct.coding_byte >> ((3 - k) * 2)) & 0x3;
		ret[k] = get_value[hold] (ret[k], proc, arena);
	}
	return (ret);
}
