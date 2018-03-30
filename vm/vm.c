/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:11 by satkins           #+#    #+#             */
/*   Updated: 2018/03/30 11:37:38 by sbalcort         ###   ########.fr       */
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

	i = -1;
	while (++i < argc)
	{
		// if (!core_file(argv[i]))
		// 	continue;
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

t_env			*init_env(int count, char **input)
{
	t_env	*temp;
	int		index;

	index = flag_count(count, input);
	temp = (t_env*)ft_memalloc(sizeof(t_env));
	return (temp);
}

void			curate_input(t_env *env)
{
	int		word_count;
	t_env	*temp;
	int 	index;

	index = 0;
	word_count = 0;
	temp = env;
	while (temp)		//counts up the number of nodes
	{
		word_count++;
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	if (word_count > MAX_PLAYERS)
		print_starting_info();
	//allocates memory for each word/node in 2d char array
	env->list = (char**)malloc(sizeof(char*) * (word_count + 1));
	env->list[word_count] = NULL;
	temp = env;
	while (index < word_count)
	{
		env->list[index] = ft_strdup(temp->player_string);
		temp = temp->next;
		index++;
	}
	env->list_count = index;
}

int				main(int argc, char **argv)
{
	t_process	*players;
	t_arena		arena;
	t_env		*env;
	
	env = init_env(argc, argv);
	if (flag_check(argc, argv, &arena, env))
	{
		curate_input(env);
		//arena.num_players = argc; 			//original
		arena.num_players = env->list_count;	//new
		players = ft_memalloc(sizeof(t_process) * arena.num_players);
		ft_bzero(arena.arena, MEM_SIZE);
		init_players(&arena, players);
		create_arena(env->list_count, env->list, &arena, players);
		get_inital_instructs(players, &arena);
		start_game(env->list_count, env->list, &arena, env);
	}
	else
		print_starting_info();
	return (0);
}

/*
 * There was an initial problem in indexing and how the vm declared a winner.
 * So, I jimmied the input for the VM
 * from:										to:
 * 	./corewar -s 10 -n 5 ex.cor 42.cor				ex.cor 42.cor
 *
 * 	because the vm took no consideration for any number of possible flags, there was an indexing issue.
 *
 * 	Everything else works properly with one exeption
 * 		Beacuse the vm was meant to work as "./corewar ex.cor 42.cor
 *
 * 	It made a false player/process for	argv[0]={"./corewar"}	that was ignored
 * 	and spacing on the player field took argv[0] into account. making for an empty player 1
 * 	with the real player one being in the center of the playing field
 *
 * 	THE NEW VM INPUT
 * 		now gets only the player file name and the player number. either user assigned or ARGC assigned.
 *
 * 	HOWEVER
 * 		player zeros processes are not ending and leading to an infinite loop (beacuse before, its was a dummy filler for argv[0]).
 *		
 *		when that is fixed this project will be finished.
 */
