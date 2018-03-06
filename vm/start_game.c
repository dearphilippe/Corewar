/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 16:46:56 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 05:33:58 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** count_live will count the total number of lives called in this cycle
** this will also remove and kill any process that did not call live
** this will also decrement the number of processes each player has
*/

static int		count_live(t_arena *arena)
{
	t_node		*node;
	t_node		*prev;
	t_process	*proc;
	int			live_count;
	t_node		*next;

	live_count = 0;
	node = arena->proc_queue->first;
	prev = NULL;
	while (node)
	{
		next = node->next;
		proc = node->content;
		live_count += proc->num_live;
		if (!proc->num_live)
		{
			if (prev)
				prev->next = node->next;
			else
				arena->proc_queue->first = node->next;
			node = NULL;
			arena->players[proc->player_num].num_of_process--;
			free(proc);
		}
		else
			proc->num_live = 0;
		prev = node ? node : prev;
		node = next;
	}
	return (live_count);
}

static void		die_check(t_arena *arena)
{
	static int	checkups = 0;

	if (count_live(arena) >= NBR_LIVE || ++checkups == MAX_CHECKS)
	{
		checkups = 0;
		arena->cycle_to_die -= CYCLE_DELTA;
		ft_printf("Cycle to die is now %d\n", arena->cycle_to_die);
	}
}

static int		check_players(t_player *players, int num_players)
{
	int			i;
	int			first_flag;

	first_flag = 0;
	i = -1;
	while (++i < num_players)
		if (players[i].num_of_process > 0)
		{
			if (first_flag)
				return (1);
			else
				first_flag = 1;
		}
	return (0);
}

void			start_game(t_arena *arena)
{
	t_process	*process;

	arena->cycle = 0;
	arena->cycle_to_die = CYCLE_TO_DIE;
	while (arena->proc_queue->first)
	{
		process = arena->proc_queue->first->content;
		while (process->execute_cycle == arena->cycle)
		{
			ft_depqueue(arena->proc_queue);
			process_execution(arena, process);
			process = arena->proc_queue->first->content;
		}
		++arena->cycle;
		if (arena->cycle % arena->cycle_to_die == 0)
		{
			die_check(arena);
		}
		ft_printf("It is now cycle %d\n", arena->cycle);
		// if (arena->cycle == 200)
		// {
		// 	ft_printf("reg2 %x\n", *(int *)((t_process *)arena->proc_queue->first->content)->regs[1]);
		//  break ;
		// }
	}
	ft_printf("Player %d has won! Glory\n", arena->players[arena->last_alive].player_num);
	ft_printf("Cycle finished at: %d\n", arena->cycle);
}