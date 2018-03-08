/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:16:47 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 09:28:46 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"


void	ld(t_arena *arena, t_process *process)
{
	int	*params;
	int	reg;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	reg = *process->instruct.param[1];
	*(int *)process->regs[reg - 1] = params[0];
	process->carry = params[0] ? 0 : 1;
	if((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | ld %d r%d\n", process->process_num, params[0], reg);
	free(params);
}
