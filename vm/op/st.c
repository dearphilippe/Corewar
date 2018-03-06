/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:50:29 by satkins           #+#    #+#             */
/*   Updated: 2018/03/05 18:05:27 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	st(t_arena *arena, t_process *process)
{
	int	*params;
	int	dist;
	int	i;
	unsigned char	*addr;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	addr = process->instruct.pc;
	dist = params[1] % IDX_MOD;
	i = -1;
	while (++i < abs(dist))
		if (dist > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE;	
	i = -1;
	while (++i < REG_SIZE)
	{
		*addr = params[0] >> (24 - (i * 8));
		addr = addr + 1  - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
	}
	free(params);
	ft_printf("player %d calls st\n", process->player_num);
}
