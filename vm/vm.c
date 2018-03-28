/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:11 by satkins           #+#    #+#             */
/*   Updated: 2018/03/22 10:34:03 by satkins          ###   ########.fr       */
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
		p[i].instruct.op_code = *p[i].pc;
		ft_enpqueue(arena->proc_queue, &(p[i]), sizeof(t_process), comparison);
	}
	free(p);
}

int					core_file(char *name)
{
	int len;

	len = ft_strlen(name);
	if (len < 4)
		return (0);
	if (!ft_strcmp(&name[len - 4], ".cor"))
		return (1);
	return (0);
}

static void			create_arena(int argc, char **argv, t_arena *arena,
t_process *p)
{
	int				i;
	int				k;
	int				fd;
	unsigned char	str[4];

	i = flag_count(argc, argv);
	while (++i < argc)
	{
		if (!core_file(argv[i]))
			continue;
		fd = open(argv[i], O_RDONLY);
		get_player_stats(&arena->players[i], fd, argv[i]);
		lseek(fd, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, SEEK_SET);
		k = 0;
		while (read(fd, str, 1) > 0)
		{
			*(p[i].pc + (k)) = *str;
			++k;
		}
		close(fd);
	}
	arena->num_processes = arena->num_players;
	arena->proc_queue = init_pqueue();
	arena->last_alive = 0;
}

/*
**Starting from the first .cor file on command line
**
*/

static void		init_players(t_arena *arena, t_process *players)
{
	int			i;
	int			k;

	arena->players = ft_memalloc(sizeof(t_player) * arena->num_players);
	i = -1;
	while (++i < arena->num_players)
	{
		arena->players[i].num_of_process = 1;
		/*
		** Setting the player number either index or specified by commandline
		*/
		//(player_nums[i] > 0) ? (arena->players[i + set + 1].label = player_nums[i]) : (arena->players[i + set + 1].label = i + set);
		//arena->players[i].player_num = player_nums[i] ? player_nums[i] : i;
		 //arena->players[i].player_num = -(i + 1);
		players[i].player_num = i;
		*((int *)((players[i]).regs[0])) = -(i + 1);
		k = 0;
		while (++k < REG_NUMBER)
			*((int *)((players[i]).regs[k])) = 0;
		players[i].process_num = i + 1;
		arena->players[i].player_id = i;
		players[i].pc = (i * (MEM_SIZE / arena->num_players)) + arena->arena;
	}
}

int				main(int argc, char **argv)
{
	t_process	*players;
	t_arena		arena;
	
	if (flag_check(argc, argv, &arena))
	{
		arena.num_players = argc; // count .cor files ?
		players = ft_memalloc(sizeof(t_process) * arena.num_players);
		ft_bzero(arena.arena, MEM_SIZE);
		init_players(&arena, players);
		create_arena(argc, argv, &arena, players);
		get_inital_instructs(players, &arena);
		start_game(argc, argv, &arena);
	}
	else
		print_starting_info();
	return (0);
}