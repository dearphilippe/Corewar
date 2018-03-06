/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:20:25 by satkins           #+#    #+#             */
/*   Updated: 2018/03/05 22:08:00 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "operation.h"

void	op_control(t_arena *arena, t_process *proc)
{
	if (proc->instruct.op_code == 1)
		op_live(proc, arena);
	else if (proc->instruct.op_code == 9)
		zjmp(arena, proc);
	else if (proc->instruct.op_code == 11)
		sti(arena, proc);
	else if (proc->instruct.op_code == 3)
		st(arena, proc);
	else if (proc->instruct.op_code == 6)
		op_and(arena, proc);
	else if (proc->instruct.op_code == 8)
		op_xor(arena, proc);
	else if (proc->instruct.op_code == 4)
		add(arena, proc);
	else if (proc->instruct.op_code == 10)
		ldi(arena, proc);
	else if (proc->instruct.op_code == 2)
		ld(arena, proc);
	else if (proc->instruct.op_code == 12)
		op_fork(arena, proc);

}
