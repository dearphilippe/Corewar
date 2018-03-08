/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:44:38 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 22:28:13 by satkins          ###   ########.fr       */
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
	if (params[0] != *(int *)process->regs[*process->instruct.param[0] - 1] ||
		params[1] != *(int *)process->regs[*process->instruct.param[1] - 1])
		{
			ft_printf("IT  DOESNT WORK\n");
			exit(0);
		}
	*((int *)process->regs[reg - 1]) = params[0] + params[1];
	process->carry = params[0] + params[1] ? 0 : 1;
	if((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | add r%d r%d r%d\n", process->process_num, *process->instruct.param[0], *process->instruct.param[1], *process->instruct.param[2]);
	free(params);
}
