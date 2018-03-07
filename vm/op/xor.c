/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:48:33 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 09:30:31 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	op_xor(t_arena *arena, t_process *process)
{
	int	*params;
	int	reg;

	params = read_param(process, arena);
	if (process->instruct.illegal)
	{
		free(params);
		return ;
	}
	reg = *process->instruct.param[2];
	*((int *)process->regs[reg - 1]) = params[0] ^ params[1];
	process->carry = params[0] ^ params[1] ? 0 : 1;
	ft_printf("p %d | xor %d %d r%d\n", process->process_num, params[0], params[1], reg);	
	free(params);
}
