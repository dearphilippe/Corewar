/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 06:24:09 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H

# include "../../libstar/libft.h"
# include "op.h"

# define OPEN_FILE_ERR	0
# define FILE_TOO_SMALL	1
# define MISSING_MAGIC	2

# define MEM_DUMP		0b0000000010000000
# define VEBOSE			0b0000000001000000
# define VERB_0			0b0000000000000001
# define VERB_1			0b0000000000000010
# define VERB_2			0b0000000000000100
# define VERB_4			0b0000000000001000
# define VERB_8			0b0000000000010000
# define VERB_16		0b0000000000100000
# define MEM_CYCLES		0b0000000100000000
# define VERBOSE_FLAG   "-v"
# define DUMP_FLAG      "-d"
# define CYCLE_FLAG     "-s"
# define SLEEP_TIME		3

typedef struct		s_instruction
{
	int				op_code;
	unsigned char	coding_byte;
	unsigned char	*pc;
	unsigned char	*param[MAX_PARAM];
	int				p_s[MAX_PARAM];
	int				illegal : 1;
}					t_instruction;

typedef struct		s_process
{
	unsigned char	*pc;
	unsigned char	regs[REG_NUMBER][REG_SIZE];
	int				execute_cycle;
	int				carry : 1;
	int				process_num;
	int				player_num;
	int				num_live;
	int				last_live;
	t_instruction	instruct;
}					t_process;

typedef struct		s_player
{
	int				player_num;
	int				player_id;
	int				num_of_process;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				player_size;
}					t_player;

typedef struct		s_arena
{
	int				num_players;
	int				cycle;
	int				cycle_to_die;
	int				next_check;
	t_pqueue		*proc_queue;
	t_player		*players;
	int				last_alive;
	int				num_processes;
	unsigned char	arena[MEM_SIZE];
	unsigned short	flag;
	int				mem_dump;
	int				cycles;
	int				file_offset;
}					t_arena;

int					comparison(void *ptr1, void *ptr2);

void				process_execution(t_arena *arena, t_process *process);

int					get_exec_cycle(unsigned char *pc);

void				print_arena(t_arena *arena);

void				start_game(t_arena *arena);

int					get_instruct(unsigned char **pc, unsigned char *a,
	t_instruction *in);

void				op_control(t_arena *arena, t_process *proc);

void				print_player_stats(t_arena *arena);

void				print_results(t_arena *arena);

void				print_starting_info(void);

int					flag_check(int argc, char **argv, t_arena *arena);

void				op_control(t_arena *arena, t_process *proc);

//void				get_player_stats(t_player *player, int fd);

void				get_player_stats(t_player *player, int fd, char *file);

int					flags(int argc, char **argv, t_arena *arena, int i);


#endif