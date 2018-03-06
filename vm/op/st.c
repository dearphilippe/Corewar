/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:50:29 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 04:49:45 by satkins          ###   ########.fr       */
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
	addr = process->instruct.pc;
	dist = read_mem(arena, process, process->instruct.param[1]);
	i = -1;
	while (++i < abs(dist % IDX_MOD))
		if (dist > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE;	
	ft_printf("p %d | st r%d %d\n", process->player_num, *process->instruct.param[0], dist);
	i = -1;
	while (++i < REG_SIZE)
	{
		*addr = params[0] >> (24 - (i * 8));
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	free(params);
}
