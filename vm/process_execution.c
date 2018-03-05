/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 22:56:00 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 22:30:51 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** This is where we have the process that has an instruction that will execute
** on this cycle. This process has the highest priority. This function will
** create the instruction instance and pass it to execution. This function will
** also prepare the process for future actions by:
** Updating the program counter
** Updating the execution cycle
** Adding the process back to the p_queue
*/

void				process_execution(t_arena *arena, t_process *process)
{
	if (get_instruct(&(process->pc), arena->arena, &(process->instruct)))
	{
		op_control(arena, process);
	}
	process->execute_cycle = get_exec_cycle(process->pc) + arena->cycle + 1;
	ft_enpqueue(arena->proc_queue, process, sizeof(t_process), comparison);
	free(process);
}
