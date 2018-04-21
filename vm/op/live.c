/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:59:40 by passef            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/18 19:04:42 by passef           ###   ########.fr       */
=======
/*   Updated: 2018/03/08 07:18:08 by satkins          ###   ########.fr       */
>>>>>>> dev_vm
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			get_player_num(t_arena *arena, t_process *process)
{
<<<<<<< HEAD
    unsigned char *tmp;

    t_process->pc;

=======
	int				player_num;
	unsigned char	*ptr;
	int				i;

	ptr = process->instruct.param[0];
	i = -1;
	player_num = 0;
	while (++i < 4)
	{
		player_num = player_num << 8;
		player_num += *ptr;
		ptr = ptr + 1 - arena->arena < MEM_SIZE ? ptr + 1 : arena->arena; 
	}
	return (player_num);
}

void  				op_live(t_process *process,  t_arena *arena)
{
    int				player_num;
	int				i;

	player_num = get_player_num(arena, process);
	i = -1;
	while (++i < arena->num_players)
		if (arena->players[i].player_num == player_num)
		{
			arena->last_alive = player_num;
			if ((VERB_1 & arena->flag ) == 2)
				ft_printf("A process shows that player %d \"%s\" is alive\n",
			arena->players[i].player_num, arena->players[i].name);
		}
	process->num_live++;
	process->last_live = arena->cycle;
	if((VERB_4 & arena->flag) == 8)
		ft_printf("P% 5d | live %d\n", process->process_num, player_num);
>>>>>>> dev_vm
}
