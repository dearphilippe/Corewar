/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:10:46 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 22:48:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void				sti(t_arena *arena, t_process *proc)
{
	int				*par;
	int				dist;
	int				i;
	unsigned char	*addr;

	par = read_param(proc, arena);
	if (proc->instruct.illegal)
	{
		free(par);
		return ;
	}
	dist = (par[1] + par[2]) % IDX_MOD;
	addr = proc->instruct.pc;
	i = -1;
	while (++i < ABS(dist))
		if (dist > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE;			
	i = -1;
	while (++i < REG_SIZE)
	{
		*addr = par[0] >> (28 - (i * 4));
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	free(par);
	ft_printf("player %d calls sti\n", proc->player_num);
}
