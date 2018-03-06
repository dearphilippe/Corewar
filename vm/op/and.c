/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 20:16:59 by satkins           #+#    #+#             */
/*   Updated: 2018/03/05 22:11:05 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	op_and(t_arena *arena, t_process *process)
{
	int	*params;
	int	reg;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	process->carry = (params[0] & params[1]) ? 0 : 1;
	reg = *(process->instruct.param[2]);
	*(int *)process->regs[reg - 1] = (params[0] & params[1]);
	free(params);
	ft_printf("player %d calls and\n", process->player_num);
}
