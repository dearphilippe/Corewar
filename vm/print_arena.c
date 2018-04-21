/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 19:10:33 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 07:45:23 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_arena(t_arena *arena)
{
	int				i;
	t_node			*node;
	t_process		*proc;

	i = -1;
	write(1, "\f", 1);
	while (++i < MEM_SIZE)
	{
		if ( i && i % 64 == 0)
			ft_printf("\n");
		node = arena->proc_queue->first;
		while (node)
		{
			proc = node->content;
			if (proc->pc == &(arena->arena[i]) && proc->process_num == 26)
			{
				ft_printf("\033[1;43m");
				break ;
			}			
			if (proc->pc == &(arena->arena[i]))
			{
				ft_printf("\033[1;44m");
				break ;
			}
			node = node->next;
		}
		ft_printf("%02x\033[0m ", arena->arena[i]);
	}
	ft_printf("\n");
}
