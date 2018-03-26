/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:59:40 by passef            #+#    #+#             */
/*   Updated: 2018/02/18 20:57:56 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void        print_player_alive(int player_id, t_arena *arena)
{
    ft_printf("A process shows that player %d %s is alive",
        arena->players[player_id].player_num, arena->players[player_id].name);
}

int         get_data(t_process *proc, t_arena *arena)
{
    if (proc->instruct.op_code == 1)
        op_live(proc, arena);
    if (proc->instruct.op_code == 2)
        op_load(proc,arena);
}

int       get_player_id(int player_num, t_arena *arena)
{
    int     player_id;

    player_id = -1;
    while (++player_id < arena->num_players)
    {
        if (player_num == arena->players[player_id].player_num)
            return (player_id);
    }
    return (-1);
}

void    op_live(t_process *proc, t_arena *arena)
{
    unsigned char *tmp;
    int             player_id;

    player_id = get_player_id(proc->instruct.param[0], arena);
    proc->num_live++;
    arena->last_alive = proc->player_num;
    print_player_alive(player_id, arena);
}

void    op_load(t_process *proc, t_arena *arena)
{
    
}