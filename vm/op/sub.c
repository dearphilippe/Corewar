/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:23:09 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 07:01:05 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	sub(t_arena *arena, t_process *process)
{
	int	*params;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	*(int *)process->regs[*process->instruct.param[2]] = params[0] - params[1];
	if ((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | sub r%d r%d r%d\n", process->process_num,
			*process->instruct.param[0], *process->instruct.param[1],
			*process->instruct.param[2]);
	free(params);
}
