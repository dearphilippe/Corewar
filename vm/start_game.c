/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 16:46:56 by satkins           #+#    #+#             */
/*   Updated: 2018/03/22 10:42:37 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		*count_aux(t_arena *arena, t_process *proc, t_node *node,
	t_node *prev)
{
	if ((VERB_8 & arena->flag) == 16)
		ft_printf("Process %d hasn't lived for %d cycles\n",
			proc->process_num, arena->cycle_to_die);
	if (prev)
		prev->next = node->next;
	else
		arena->proc_queue->first = node->next;
	arena->players[proc->player_num].num_of_process--;
	free(proc);
	return (NULL);
}

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
		if (!proc->num_live || arena->cycle_to_die <= 0)
			node = count_aux(arena, proc, node, prev);
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
		if ((VERB_1 & arena->flag) == 2)
			ft_printf("Cycle to die is now %d\n", arena->cycle_to_die);
	}
	arena->next_check = arena->cycle + arena->cycle_to_die;
}

void			start_game(int argc, char **argv, t_arena *arena, t_env *env)
{
	t_process	*process;

	arena->cycle = 0;
	arena->cycle_to_die = CYCLE_TO_DIE;
	arena->next_check = CYCLE_TO_DIE;
	print_player_stats(argc, argv, arena);
	while (arena->proc_queue->first)
	{
		process = arena->proc_queue->first->content;
		/*
		**-v verbose
		*/
		if ((VERB_2 & arena->flag) == 4)
			ft_printf("It is now cycle %d\n", arena->cycle);
		/*
		** -dump flag
		*/
		if ((MEM_DUMP & arena->flag) == MEM_DUMP &&
		arena->cycle >= arena->mem_dump)
		{
			print_arena(arena);
			exit(0);
		}
		/*
		** -s flag
		*/
		if (((MEM_CYCLES & arena->flag) == MEM_CYCLES) &&
			(arena->cycle % arena->cycles == 0))
		{
			print_arena(arena);
			sleep(SLEEP_TIME);
		}
		while (process->execute_cycle == arena->cycle)
		{
			ft_depqueue(arena->proc_queue);
			process_execution(arena, process);
			process = arena->proc_queue->first->content;
		}
		if (arena->cycle >= arena->next_check)
			die_check(arena);
		++arena->cycle;
		
	}
	print_results(arena, env);
}
