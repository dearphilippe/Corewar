/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:51:10 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 07:18:49 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

static void			make_proc(t_arena *arena, t_process *process,
	unsigned char *addr)
{
	t_process		proc_child;
	int				cycles;

	ft_memcpy(&proc_child, process, sizeof(t_process));
	ft_bzero(&(proc_child.instruct), sizeof(t_instruction));
	proc_child.pc = addr;
	cycles = get_exec_cycle(addr);
	cycles = cycles ? cycles : 1;
	proc_child.execute_cycle = cycles + arena->cycle;
	proc_child.instruct.op_code = *proc_child.pc;
	proc_child.process_num = arena->num_processes;
	++(arena->num_processes);
	++((arena->players)[proc_child.player_num].num_of_process);
	ft_enpqueue(arena->proc_queue, &proc_child, sizeof(t_process), comparison);
}

void				op_lfork(t_arena *arena, t_process *process)
{
	unsigned char	param [ 2 ];
	int				i;
	unsigned char	*addr;
	t_process		proc_child;

	addr = process->instruct.param[0];
	i = -1;
	while (++i < 2)
	{
		param[1 - i] = *addr;
		addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena; 
	}
	*((short *)param) = *((short *)param);
	addr = process->instruct.pc;
	i = -1;
	while (++i < abs((*((short *)param))))
		if (*((short *)param) > 0)
			addr = addr + 1 - arena->arena < MEM_SIZE ? addr + 1 : arena->arena;
		else
			addr = addr - 1 >= arena->arena ? addr - 1 : addr + MEM_SIZE - 1;
	make_proc(arena, process, addr);
	if((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | lfork %d\n", process->process_num, *(short *)param);
}
