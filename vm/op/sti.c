/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:10:46 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 09:30:25 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void				sti(t_arena *arena, t_process *proc)
{
	int				*par;
	int				dist;
	int				reg;
	int				i;
	unsigned char	*addr;

	par = read_param(proc, arena);
	if (proc->instruct.illegal)
	{
		free(par);
		return ;
	}
	reg = *proc->instruct.param[0];
	dist = (par[1] + par[2]) % IDX_MOD;
	addr = proc->instruct.pc;
	i = -1;
	while (++i < abs(dist))
		if (dist > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE;			
	ft_printf("p %1d | sti r%d %d %d\n", proc->process_num, reg, par[1], par[2]);
	ft_printf("    | with pc and mod (%d)\n", dist + proc->instruct.pc - arena->arena);
	i = REG_SIZE;
	while (--i >= 0)
	{
		*addr = proc->regs[reg - 1][i];
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	free(par);
}
