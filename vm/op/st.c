/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:50:29 by satkins           #+#    #+#             */
/*   Updated: 2018/03/07 19:04:57 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

static short		read_mem(t_arena *arena, t_process *process,
	unsigned char *addr)
{
	int				i;
	int				ret;

	ret = 0;
	i = -1;
	while (++i < IND_SIZE)
	{
		ret = ret << 8;
		ret += *addr;
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	return (ret);
}

void				st(t_arena *arena, t_process *process)
{
	int				*params;
	short			dist;
	int				i;
	unsigned char	*addr;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	if (process->instruct.p_s[1] == 1)
		*(int *)process->regs[*process->instruct.param[1] - 1] = *(int *)process->regs[*process->instruct.param[0] - 1];
	else
	{
		addr = process->instruct.pc;
		dist = read_mem(arena, process, process->instruct.param[1]);
		ft_printf("P %4d | st r%d %d\n", process->process_num, *process->instruct.param[0], dist);
		i = -1;
		while (++i < abs(dist % IDX_MOD))
			if (dist > 0)
				addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
			else
				addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE - 1;	
		i = -1;
		while (++i < REG_SIZE)
		{
			*addr = params[0] >> (24 - (i * 8));
			addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		}
	}
	free(params);
}
