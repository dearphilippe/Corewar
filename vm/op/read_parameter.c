/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:08:06 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 21:24:43 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"

int					*read_param(t_process *proc, t_arena *arena)
{
	int				*ret;
	unsigned char	*addr;
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
			ret[k] << 8;
			ret[k] += *addr;
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		}
		ret[k] = get_value[(proc->instruct.coding_byte >> ((k + 1) * 2)) & 0x3]
			(ret[k], proc, arena);
	}
	return (ret);
}
