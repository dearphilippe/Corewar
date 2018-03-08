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

	i = 0;
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