/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:11 by satkins           #+#    #+#             */
/*   Updated: 2018/02/16 15:48:56 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int g_pc = 0;
int	g_cycle_num = 0;
int g_opcode = 0;
long long g_reg1 = 0;
long long g_reg2 = 0;
long long g_reg3 = 0;
int g_imm = 0;

char		*fetch(t_process *player)
{
	return (player->);
}

// void		decode(char *instruction)
// {
// 	// g_opcode = ((instruction >> OPCODE_OFFSET) & 0xFF);
// 	// g_reg1 = 
// 	;
// }

void	init_players(t_arena arena, t_process *players)
{
	int	i;

	i = -1;
	while (++i < arena.num_players)
	{
		*((int *)(((players[i]).regs[0]).reg)) = i;
		players[i].pc = (i * (MEM_SIZE / arena.num_players)) + arena.arena;
	}
}

void	init_arena(t_arena *arena)
{
	arena->arena = ft_memalloc(sizeof(char) * MEM_SIZE);
}

int	main(int argc, char **argv)
{
	t_process	*players;
	t_arena		arena;

	arena.num_players = argc - 1; //Change to include options
	init_arena(&arena);
	players = ft_memalloc(sizeof(t_process) * arena.num_players);
	init_players(arena, players);
	for (int i = 0; i < arena.num_players; ++i)
	{
		ft_printf("%d\n", *((int *)((players[i].regs[0]).reg)));
		ft_printf("pc: %p\n", players[i].pc);		
	}
	ft_printf("%s\n", argv[0]);
}