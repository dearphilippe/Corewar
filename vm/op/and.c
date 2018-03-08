/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 20:16:59 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 09:29:59 by satkins          ###   ########.fr       */
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
	if((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | and %d %d r%d\n", process->process_num, params[0], params[1], reg);
	free(params);
}
