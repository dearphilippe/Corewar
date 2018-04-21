/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:59:12 by sbalcort          #+#    #+#             */
/*   Updated: 2018/04/21 12:28:29 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Prints the beginning announcement
*/

void	print_player_stats(int argc, char **argv, t_arena *arena, t_env *env)
{
	int	i;
	int player_number;
	
	i = 0;
	ft_printf("Introducing contenstants...\n");
	while (i < argc)
	{
		if (env->assign_number > 0 )
			player_number = env->assign_number;
		else
			player_number = env->input_index;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
		player_number,
		arena->players[i].player_size, arena->players[i].name,
		arena->players[i].comment);
		env = env->next;
		i++;
	}
}

/*
**announces the winner of the game
*/

void	print_results(t_arena *arena, t_env *env)
{
	int index;

	if (arena->last_alive > 0)
	{
		index = arena->last_alive;
		while (index--)
			env = env->next;
	}
	(env->assign_number == 0) ? (index = env->input_index) : (index = env->assign_number);
	ft_printf("Contestant %d, \"%s\" has won! Glory\n",
	index,
	arena->players[arena->last_alive].name);
	ft_printf("Cycle finished at: %d\n", arena->cycle);
	//free_env(env);	//need to make
}
