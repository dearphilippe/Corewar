/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:59:12 by sbalcort          #+#    #+#             */
/*   Updated: 2018/03/07 21:59:14 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_player_stats(t_arena *arena)
{
	int	i;

	i = 1;
	printf("Introducing contenstants...\n");
	while (i <= 2)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n", i,
		arena->players[i].player_size, arena->players[i].name,
		arena->players[i].comment);
		i++;
	}
}

void	print_results(t_arena *arena)
{
	if (arena->last_alive > 0)
	{
		ft_printf("Contestant %d, \"%s\" has won! Glory\n", arena->last_alive,
		arena->players[arena->last_alive - 1].name);
		ft_printf("Cycle finished at: %d\n", arena->cycle);
	}
	else
		ft_printf("Sorry there was no winner");
}

void	print_starting_info(void)
{
	ft_printf("\nUsage: ./corewar [-d N -s N -v N]| <champion1.cor> <...>\n#
	### TEXT OUTPUT MODE ####\n\t-d N\t: Dumps memory after N cycles then ex
	its\n\t-s N\t: Runs N cycles, dump memory, pauses, then repeats\n\t-v N
	\t: Verbosity lvls, can be added with ^ to enable several\n\t\t- 0 : Sho
	w only essentials\n\t\t- 1 : Show lives\n\t\t- 2 : Show cycles\n\t\t- 4 :
	 Show operations(Params are NOT litteral ...)\n\t\t- 8 : Show deaths\n\t
	 \t- 16 : Show PC movements (Except for jumps)\n########################
	 ###\n\n");
	exit(1);
}
