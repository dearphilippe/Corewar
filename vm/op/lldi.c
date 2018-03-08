/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:58:36 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 23:59:34 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

static void			read_mem(t_arena *arena, t_process *process,
	unsigned char *addr)
{
	int				i;
	int				reg;

	reg = *process->instruct.param[2];
	*((int *)process->regs[reg - 1]) = 0;
	i = -1;
	while (++i < REG_SIZE)
	{
		*(int *)process->regs[reg - 1] = *(int *)process->regs[reg - 1] << 8;
		*(int *)process->regs[reg - 1] += *addr;
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
}

void				lldi(t_arena *arena, t_process *process)
{
	unsigned char	*addr;
	int				*params;
	int				dist;
	int				i;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	dist = params[0] + params[1];
	addr = process->instruct.pc;
	i = -1;
	while (++i < abs(dist))
		if (dist > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE - 1;
	if((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | lldi %d %d r%d\n", process->process_num, params[0],
		params[1], *process->instruct.param[2]);
	free(params);
	read_mem(arena, process, addr);
}
