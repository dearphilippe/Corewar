/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:59:40 by passef            #+#    #+#             */
/*   Updated: 2018/03/08 06:43:38 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    op_live(t_process *process,  t_arena *arena)
{
    int player_num;
	unsigned char	*ptr;
	int	i;

	ptr = process->instruct.param[0];
	i = -1;
	player_num = 0;
	while (++i < 4)
	{
		player_num = player_num << 8;
		player_num += *ptr;
		ptr = ptr + 1 - arena->arena < MEM_SIZE ? ptr + 1 : arena->arena; 
	}
	i = -1;
	ft_printf("P %4d | live %d\n", process->process_num, player_num);	
	while (++i < arena->num_players)
		if (arena->players[i].player_num == player_num)
		{
			arena->last_alive = player_num;
			ft_printf("Player %d (%s) is said to be alive\n",
				arena->players[i].player_num * -1, arena->players[i].name);
		}
	process->num_live++;
	process->last_live = arena->cycle;
}
