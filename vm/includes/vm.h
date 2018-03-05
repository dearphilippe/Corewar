/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 16:58:13 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H

# include "libft.h"
# include "op.h"

typedef struct		s_instruction
{
	int				op_code;
	unsigned char	coding_byte;
	unsigned char	*pc;
	unsigned char	*param[ MAX_PARAM ];
	int				p_s[ MAX_PARAM ];
}					t_instruction;

typedef struct		s_process
{
	unsigned char	*pc;
	unsigned char	regs[ REG_NUMBER ][ REG_SIZE ];
	int				execute_cycle;
	int				carry : 1;
	int				process_num;
	int				player_num;
	int				num_live;
	t_instruction	instruct;
}					t_process;

typedef struct		s_player
{
	int				player_num;
	int				player_id;
	int				num_of_process;
	char			name[ PROG_NAME_LENGTH + 1 ];
	char			comment[ COMMENT_LENGTH + 1 ];
}					t_player;

typedef struct		s_arena
{
	int				num_players;
	int				cycle;
	int				cycle_to_die;
	t_pqueue		*proc_queue;
	t_player		*players;
	int				last_alive;
	int				num_processes;
	unsigned char	arena[ MEM_SIZE ];
}					t_arena;

int					comparison(void *ptr1, void *ptr2);

void				process_execution(t_arena *arena, t_process *process);

int					get_exec_cycle(unsigned char *pc);

void				print_arena(t_arena *arena);

void				start_game(t_arena *arena);

int					get_instruct(unsigned char **pc, unsigned char *a,
	t_instruction *in);

#endif
