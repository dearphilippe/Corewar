/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:10:46 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 21:24:57 by satkins          ###   ########.fr       */
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
	if (proc->pc == proc->instruct.coding_byte)
	{
		free(par);
		return ;
	}
	dist = (par[1] + par[2]) % IDX_MOD;
	addr = proc->instruct.pc;
	i = -1;
	while (++i < dist)
		addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	i = -1;
	while (++i < REG_SIZE)
	{
		*addr = par[0] >> (28 - (i * 4));
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	free(par);
}
