/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:12:05 by satkins           #+#    #+#             */
/*   Updated: 2018/03/07 19:07:29 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void				zjmp(t_arena *arena, t_process *process)
{
	unsigned char	param [ 2 ];
	int				i;
	short			numbr;
	unsigned char	*addr;

	addr = process->instruct.param[0];
	i = -1;
	while (++i < 2)
	{
		param[1 - i] = *addr;
		addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena; 
	}
	numbr = *((short *)param) % IDX_MOD;
	if (process->carry)
	{
		addr = process->instruct.pc;
		i = -1;
		while (++i < abs(numbr))
			if (numbr > 0)
				addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
			else
				addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE - 1;
		process->pc = addr;
	}
	ft_printf("P %4d | zjmp %d %s\n", process->process_num, numbr, process->carry ? "OK" : "FAILED");
}
