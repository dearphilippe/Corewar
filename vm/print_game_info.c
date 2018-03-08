/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 23:13:38 by sbalcort          #+#    #+#             */
/*   Updated: 2018/03/07 23:13:40 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				extended_verbose(int i, int number, t_arena *arena, char **argv)
{
	if (ft_atoi(argv[i]))
	{
		number = (unsigned short)ft_atoi(argv[i]);
		(number & 16) == 16 ? arena->flag |= VERB_16 : 0;
		(number & 16) == 16 ? number |= VERB_16 : 0;
		(number & 8) == 8 ? arena->flag |= VERB_8 : 0;
		(number & 8) == 8 ? number |= VERB_8 : 0;
		(number & 4) == 4 ? arena->flag |= VERB_4 : 0;
		(number & 4) == 4 ? number |= VERB_4 : 0;
		(number & 2) == 2 ? arena->flag |= VERB_2 : 0;
		(number & 2) == 2 ? number |= VERB_2 : 0;
		(number & 1) == 1 ? arena->flag |= VERB_1 : 0;
		(number & 1) == 1 ? number |= VERB_0 : 0;
		((number & 0) == 0) ? arena->flag |= VERB_0 : 0;
		((number & 0) == 0) ? number |= VERB_0 : 0;
	}
	arena->flag |= VEBOSE;
	if (argv[i][0] && ft_isdigit(argv[i][0]))
		return (1);
	else
		return (0);
}

int				extended_dump(int i, t_arena *arena, char **argv)
{
	arena->flag |= MEM_DUMP;
	(ft_atoi(argv[i])) ? arena->mem_dump = ft_atoi(argv[i]) : 0;
	if (argv[i][0] && ft_isdigit(argv[i][0]))
		return (i);
	else
		return (1);
}

int				extended_cycles(int i, t_arena *arena, char **argv)
{
	arena->flag |= MEM_CYCLES;
	(ft_atoi(argv[i])) ? arena->cycles = ft_atoi(argv[i]) : 0;
	if (argv[i][0] && ft_isdigit(argv[i][0]))
		return (1);
	else
		return (0);
}

int				flags(int argc, char **argv, t_arena *arena, int i)
{
	unsigned int number;

	number = 0;
	while (i < argc)
	{
		if (ft_strncmp(VERBOSE_FLAG, argv[i], sizeof(VERBOSE_FLAG)) == 0)
		{
			i++;
			i += extended_verbose(i, number, arena, argv);
		}
		else if (ft_strcmp(DUMP_FLAG, argv[i]) == 0)
		{
			i++;
			i += extended_dump(i, arena, argv);
		}
		else if (ft_strcmp(CYCLE_FLAG, argv[i]) == 0)
		{
			i++;
			i += extended_cycles(i, arena, argv);
		}
		else
			break ;
	}
	return (i);
}

int				flag_check(int argc, char **argv, t_arena *arena)
{
	int		len;
	int		i;
	int		off_set;

	i = 1;
	off_set = 0;
	if (argc > 0)
	{
		if (argc > 2)
			off_set = flags(argc, argv, arena, 0);
		while (i < argc)
		{
			len = ft_strlen(argv[i + off_set]);
			len -= 4;
			if (ft_strcmp(&argv[i + off_set][len], ".cor"))
				print_starting_info();
			i++;
		}
	}
	else
		print_starting_info();
	if (off_set != 0)
		return (off_set);
	return (0);
}
