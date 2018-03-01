/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:10:46 by satkins           #+#    #+#             */
/*   Updated: 2018/02/28 14:11:51 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		read_param(int size, unsigned char *addr, t_arena *arena)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	while (++i < size)
	{
		ret << 8;
		ret += *addr;
		addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	return (ret);
}

void	sti(t_arena *arena, t_process *process)
{
	int	params[3];

	params[0] = *process->instruct.param[0];
	if (params[0] > REG_NUMBER || params[0] <= 0)
	{
		invalid_param(process);
		return ;
	}
	params[0] = process->regs[params[0]];

}