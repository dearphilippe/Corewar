/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 19:10:33 by satkins           #+#    #+#             */
/*   Updated: 2018/02/28 13:12:48 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_arena(t_arena *arena)
{
	int				i;
	t_node			*node;
	t_process		*proc;

	ft_printf("MEM");
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % (MEM_SIZE / 128) == 0)
			ft_printf("\n");
		node = arena->proc_queue->first;
		while (node)
		{
			proc = node->content;
			if (proc->pc == &(arena->arena[i]))
			{
				ft_printf("\033[1;35m");
				break ;
			}
			node = node->next;
		}
		ft_printf("%02x\033[0m ", arena->arena[i]);
	}
	ft_printf("\n");
}
