/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:12:05 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 22:34:33 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	zjmp(t_arena *arena, t_process *process)
{
	int	*params;
	int	i;
	unsigned char	*addr;

	if (!process->carry)
		return ;
	params = read_param(process, arena);
	params[0] = params[0] % IDX_MOD;
	addr = process->instruct.pc;
	i = -1;
	while (++i < ABS(params[0]))
		if (params[0] > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE;
	process->pc = addr;
	free(params);
	ft_printf("player %d calls zjmp\n", proc->player_num);
}