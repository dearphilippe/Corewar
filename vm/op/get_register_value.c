/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_register_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:11:39 by satkins           #+#    #+#             */
/*   Updated: 2018/03/05 17:56:33 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	get_reg_val(int reg_num, t_process *proc, t_arena *a)
{
	if (reg_num > REG_NUMBER || reg_num <= 0)
	{
		proc->pc = (proc->instruct.pc + 1 - a->arena < MEM_SIZE ?
			proc->instruct.pc + 1 : a->arena);
		proc->instruct.illegal = 1;
		return (-1);
	}
	return (*((int *)proc->regs[reg_num - 1]));
}
