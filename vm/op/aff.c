/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:05:16 by satkins           #+#    #+#             */
/*   Updated: 2018/03/07 00:28:53 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	aff(t_arena *arena, t_process *process)
{
	if (*process->instruct.param[0] > 0 && *process->instruct.param[0] <= REG_NUMBER)
		ft_printf("%c", (*(int *)process->regs[*process->instruct.param[0] - 1]) % 256);
}
