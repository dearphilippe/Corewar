/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:11 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 17:32:55 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			get_inital_instructs(t_process *p, t_arena *arena)
{
	int				i;

	i = -1;
	while (++i < arena->num_players)
	{
		p[i].execute_cycle = get_exec_cycle(p[i].pc);
		ft_enpqueue(arena->proc_queue, &(p[i]), sizeof(t_process), comparison);
	}
	free(p);
}

static void			create_arena(char **argv, t_arena *arena, t_process *p)
{
	int				i;
	int				k;
	int				fd;
	unsigned char	str[ 4 ];

	i = -1;
	while (++i < arena->num_players)
		if ((fd = open(argv[i + 1], O_RDONLY)) > 0)
		{
			//Validate .cor??
			lseek(fd, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, SEEK_SET);
			k = 0;
			while (read(fd, str, 1) > 0)
			{
				*(p[i].pc + (k)) = *str;			
				++k;
			}
			close(fd);
		}
	arena->proc_queue = init_pqueue();
}

static void		init_players(t_arena *arena, t_process *players)
{
	int			i;

	arena->players = ft_memalloc(sizeof(t_player) * arena->num_players);
	i = -1;
	while (++i < arena->num_players)
	{
		arena->players[i].num_of_process = 1;
		*((int *)((players[i]).regs[0])) = i;
		players[i].player_num = i;
		arena->players[i].player_id = i;
		players[i].pc = (i * (MEM_SIZE / arena->num_players)) + arena->arena;
	}
	
}

int				main(int argc, char **argv)
{
	t_process	*players;
	t_arena		arena;

	arena.num_players = argc - 1; //Change to include options
	players = ft_memalloc(sizeof(t_process) * arena.num_players);
	ft_bzero(arena.arena, MEM_SIZE);
	init_players(&arena, players);
	create_arena(argv, &arena, players);
	get_inital_instructs(players, &arena);
	ft_printf("MEM");
	for (int i = 0; i < MEM_SIZE; i++)
	{
		if (i % (MEM_SIZE / 16) == 0)
			ft_printf("\n");
		ft_printf("%02x ", arena.arena[i]);
	}
	ft_printf("\n");
}