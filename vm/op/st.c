/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:50:29 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 07:40:43 by satkins          ###   ########.fr       */
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

static short		st_aux(t_arena *arena, t_process *process, int *params)
{
	short			dist;
	int				i;
	unsigned char	*addr;

	addr = process->instruct.pc;
	dist = read_mem(arena, process, process->instruct.param[1]);
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
	return (dist);
}

void				st(t_arena *arena, t_process *process)
{
	int				*params;
	short			dist;

	params = read_param(process, arena);
	dist = 0;
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	if (process->instruct.p_s[1] == 1)
		*(int *)process->regs[*process->instruct.param[1] - 1] =
		*(int *)process->regs[*process->instruct.param[0] - 1];
	else
		dist = st_aux(arena, process, params);
	if ((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | st r%d %d\n", process->process_num,
		*process->instruct.param[0], dist);
	free(params);
}
