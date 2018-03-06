/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:44:38 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 05:29:10 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	add(t_arena *arena, t_process *process)
{
	int	reg;
	int	*params;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	reg = *process->instruct.param[2];
	*((int *)process->regs[reg - 1]) = params[0] + params[1];
	process->carry = params[0] + params[1] ? 0 : 1;
	ft_printf("player %d calls add\n", process->player_num);
	free(params);
}
