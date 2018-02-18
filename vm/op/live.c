/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:59:40 by passef            #+#    #+#             */
/*   Updated: 2018/02/18 15:06:18 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    op_live(t_process *pc,  t_arena *arena)
{
    int player_id;
    int player_pos;

    
    if (player_pos > -1)
    {
        t_arena->lives += 1;
        t_arena->winner = player_pos;
    }
}