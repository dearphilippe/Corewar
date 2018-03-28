/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:59:12 by sbalcort          #+#    #+#             */
/*   Updated: 2018/03/08 07:22:59 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_player_stats(int argc, char **argv, t_arena *arena)
{
	int	i;
	int player_count;
	
	i = flag_count(argc, argv);
	player_count = arena->num_players - i;
	ft_printf("Introducing contenstants...\n");
	//i = 0;
	while (i <= player_count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n", arena->players[i].player_num,
		arena->players[i].player_size, arena->players[i].name,
		arena->players[i].comment);
		i++;
	}
}

//FOR TESTING
void			PRINT_ENV(t_env *env)
{
	int		index;
	t_env	*temp;

	index = 0;
	temp = env;
	while (env)
	{
		ft_printf(" NODE\tPlayer file: %s\tPlayer assigned number: %d\tplayer index: %d\n\n", temp->player_string, temp->assign_number, temp->input_index);
		ft_printf("ENV\tindex: %d\tSTRING: %s\n\n", index, env->list[index]);
		index++;
		if (temp->next != NULL)
			temp = temp->next;
		else
			break ;
	}
	ft_printf("argument count = %d\n", env->list_count);
}

void	print_results(t_arena *arena, t_env *env)
{
	int index;

	ft_printf("last alive: %d\n", arena->last_alive);
	index = 0;
	PRINT_ENV(env);				//remove when done
	while (index < 20)
	{
		ft_printf("Contestant %d, \"%s\" has won! Glory\n",
		arena->players[index].player_num,
		//arena->players[arena->last_alive].player_num,
		arena->players[index].name);
		index++;
	}
	ft_printf("Cycle finished at: %d\n", arena->cycle);
}
