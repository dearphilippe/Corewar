/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:59:40 by passef            #+#    #+#             */
/*   Updated: 2018/02/18 19:20:31 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int         get_data(t_instruction *ins, t_arena *arena)
{
    if (ins->op_code == 1)
        op_live(ins->param[0], arena);
}

int       get_player_id(int n)
{
    
}

void    op_live(unsigned char *player_num, t_arena *arena)
{
    unsigned char *tmp;
    int             player_id;

    player_id = get_player_id(player_num);
    pc = arena->players->player_num;

}
