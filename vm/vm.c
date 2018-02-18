/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:11 by satkins           #+#    #+#             */
/*   Updated: 2018/02/17 19:15:06 by satkins          ###   ########.fr       */
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


static int		param_size(char coding_byte, int truncate)
{
	int			len;

	len = 0;
	if ((coding_byte) & 0xFF == REG_CODE)
		len += 1;
	else if ((coding_byte) & 0xFF == IND_CODE)
		len += IND_SIZE;
	else if ((coding_byte) & 0xFF == DIR_CODE)
		len += truncate ? 2 : DIR_SIZE;
	return (len);
}

/*
** Returns the Len of the instruction at PC. 0 if not an instruction
*/

int				get_instruct_len(char *pc, char *arena_start)
{
	char		coding_byte;
	int			len;

	len = 0;
	if (*pc && *pc <= 16)
	{
		if (!op_tab[*pc - 1].coding_byte)
			return (op_tab[*pc - 1].truncate ? 3 : DIR_SIZE + 1);
		if (pc + 1 - arena_start < MEM_SIZE)
			coding_byte = *(pc + 1);
		else
			coding_byte = *arena_start;
		len = 2;
		len += param_size(coding_byte >> 6, op_tab[*pc - 1].truncate);
		len += param_size(coding_byte >> 4, op_tab[*pc - 1].truncate);
		len += param_size(coding_byte >> 2, op_tab[*pc - 1].truncate);
	}
	return (len);	
}

char			*fetch(t_process *player)
{
	return (player->);
}

// void		decode(char *instruction)
// {
// 	// g_opcode = ((instruction >> OPCODE_OFFSET) & 0xFF);
// 	// g_reg1 = 
// 	;
// }

static void		init_players(t_arena arena, t_process *players)
{
	int			i;

	i = -1;
	while (++i < arena.num_players)
	{
		*((int *)((players[i]).regs[0])) = i;
		players[i].pc = (i * (MEM_SIZE / arena.num_players)) + arena.arena;
	}
}

int				main(int argc, char **argv)
{
	t_process	*players;
	t_arena		arena;

	arena.num_players = argc - 1; //Change to include options
	players = ft_memalloc(sizeof(t_process) * arena.num_players);
	init_players(arena, players);
	for (int i = 0; i < arena.num_players; ++i)
	{
		ft_printf("%d\n", *((int *)((players[i].regs[0]).reg)));
		ft_printf("pc: %p\n", players[i].pc);		
	}
	ft_printf("%s\n", argv[0]);
}