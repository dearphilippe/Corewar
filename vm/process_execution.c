/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 22:56:00 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 00:07:26 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			get_exec_cycle(char *pc)
{
	if (*pc && *pc <= 16)
		return (op_tab[*pc].num_cycles);
	return (1);
}

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
	t_instruction	instruct;

	if (get_instruct(&(process->pc), arena->arena, &instruct))
	{
		//execute!! PHILL THIS IS UR MOMENT DONT LET US ALL DOWN
		;
	}
	process->execute_cycle = get_exec_cycle(process->pc) + arena->cycle + 1;
	ft_enpqueue(arena->proc_queue, process, sizeof(t_process), comparison);
	free(process);
}