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

void			print_starting_info(void)
{
    ft_printf("\nUsage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n\
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

int    flags(int argc, char **argv, t_arena *arena)
{
    int i;
    unsigned int number;

    arena->flag = 0;
    number = 0;
    i = 1;
    while (i < argc)
    {
        if (ft_strncmp(VERBOSE_FLAG, argv[i], sizeof(VERBOSE_FLAG)) == 0)
        {
            i++;
            if (ft_atoi(argv[i]))
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
 //           printf("(number & 1) == %d\n", (number & 1));

            ((number & 0) == 0) ? arena->flag |= VERB_0 : 0;
            ((number & 0) == 0) ? number |= VERB_0 : 0;

            if (argv[i][0] && ft_isdigit(argv[i][0]))
                i++;
            arena->flag |= VEBOSE;
//            ft_printf("verbose: %u", arena->flag);
        }
        else if (ft_strcmp(DUMP_FLAG, argv[i]) == 0)
        {
            arena->flag |= MEM_DUMP;
            i++;
            (ft_atoi(argv[i])) ? arena->mem_dump = ft_atoi(argv[i]) : 0;
            if (argv[i][0] && ft_isdigit(argv[i][0]))
                i++;
//            ft_printf("dump: %d, %u\n", arena->mem_dump, arena->flag & MEM_DUMP);
        }
        else if (ft_strcmp(CYCLE_FLAG, argv[i]) == 0)
        {
            arena->flag |= MEM_CYCLES;
            i++;
            (ft_atoi(argv[i])) ? arena->cycles = ft_atoi(argv[i]) : 0;
            if (argv[i][0] && ft_isdigit(argv[i][0]))
                i++;
//            ft_printf("cycle: %d, %u", arena->cycles, arena->flag & MEM_CYCLES);
        }
        else 
            break;
    }
//    printf ("returning %d\n", i);
    return (i);
}

int     flag_check(int argc, char **argv, t_arena *arena)
{
    int     len;
    int     i;
    int     off_set;

    i = 1;
    off_set = 0;
    if (argc >= 3)
    {
        if (argc > 3)
            off_set = flags(argc, argv, arena);
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
    return (i);
}