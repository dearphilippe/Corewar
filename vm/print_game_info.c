/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 23:13:38 by sbalcort          #+#    #+#             */
/*   Updated: 2018/04/11 22:15:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_starting_info(void)
{
	ft_printf("\nUsage: ./corewar [-d N -s N -v N [[-n N ] <champion1.cor>] <...>\n\
#### TEXT OUTPUT MODE ##########################################################\n\
\t-d N\t: Dumps memory after N cycles then exits\n\
\t-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n\
\t-v N\t: Verbosity levels, can be added together to enable several\n\
\t\t- 0 : Show only essentials\n\
\t\t- 1 : Show lives\n\
\t\t- 2 : Show cycles\n\
\t\t- 4 : Show operations (Params are NOT litteral ...)\n\
\t\t- 8 : Show deaths\n\
\t\t- 16 : Show PC movements (Except for jumps)\n\
################################################################################\n\n");
	exit(1);
}

int     get_number(char *str)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while(str[i] != '\0' && !ft_isspace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		num *= 10;
		num += (str[i] - '0');
		i++;
	}
	return(num);
}

int    flags(int argc, char **argv, t_arena *arena)
{
	int i;
	unsigned int number;

	i = 0;
	arena->flag = 0;
	number = 0;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_strncmp(VERBOSE_FLAG, argv[i], ft_strlen(VERBOSE_FLAG)) == 0)
		{
			arena->flag |= VEBOSE;
			i++;
			if ((number = get_number(argv[i])) == -1)
				print_starting_info();
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
 //           printf("(number & 1) == %d\n", (number & 1));

			((number & 0) == 0) ? arena->flag |= VERB_0 : 0;
			((number & 0) == 0) ? number |= VERB_0 : 0;
			i++;
			
//            ft_printf("verbose: %u", arena->flag);
		}
		else if (ft_strcmp(DUMP_FLAG, argv[i]) == 0)
		{
			arena->flag |= MEM_DUMP;
			i++;
			arena->mem_dump = get_number(argv[i]);
			(arena->mem_dump == -1) ? arena->mem_dump = 0 : i++;
//            ft_printf("dump: %d, %u\n", arena->mem_dump, arena->flag & MEM_DUMP);
		}
		else if (ft_strcmp(CYCLE_FLAG, argv[i]) == 0)
		{
			arena->flag |= MEM_CYCLES;
			i++;
			arena->cycles = ft_atoi(argv[i]);
			if (arena->cycles)
				i++;
//            ft_printf("cycle: %d, %u", arena->cycles, arena->flag & MEM_CYCLES);
		}
		else 
			break;
	}
//    printf ("returning %d\n", i);
	return (i);
}

int     flag_count(int argc, char **argv)
{
	int y;
	int len;

	len = 0;
	y = 0;
	while (++y < argc)
	{
		len = ft_strlen(argv[y]);
		if (len >= 5 && !ft_strcmp(&argv[y][len - 4], ".cor"))
			return (y - 1);
	}
	return (1);
}

/*
**This recognizes the -n flag in the argument vectors
**then checks for number ahead of it, if none exists default to 0
**if one or both flags exist, the index is incremented
*/

int     player_number_check(char **argv, int i, int offset, t_env *env)
{
	int     count;

	count = 0;
	if (ft_strcmp(PLAYER_NUMBER, argv[i + offset]))
		return (0);
	count++;
	i++;
	if ((env->assign_number = ft_atoi(argv[i + offset])))
		count++;
	else
		print_starting_info();
	return (count);
}

int     file_check(char **argv, int i, int offset, t_env *env)
{
	int len;

	len = ft_strlen(argv[i + offset]);
	if (ft_strcmp(&argv[i + offset][len - 4], ".cor"))
		print_starting_info();
	env->player_string = ft_strdup(argv[i + offset]);
	env->input_index = offset + i;
	return (1);
}

t_env	*append_node_env(t_env *env)
{
	if(env->player_string != NULL)
	{
		env->next = (t_env*)ft_memalloc(sizeof(t_env));
		env->next->last = env->next;
		return ((t_env*)env->next);
	}
	return (env);
}


int     flag_check(int argc, char **argv, t_arena *arena, t_env *env)
{
	int     len;
	int     i;
	int     off_set;

	i = 1;
	off_set = 0;
	if (argc >= 2)
	{
		if (argc > 2)
			off_set = flags(argc, &argv[i], arena);
		while ((i + off_set) < argc)
		{
			env = append_node_env(env);
			i += player_number_check(argv, i, off_set, env);
			i += file_check(argv, i, off_set, env);
		}
	}
	else
		print_starting_info();
	if (off_set != 0)
		return (off_set);
	return (i);
}