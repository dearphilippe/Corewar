/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 20:09:26 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# include "libft.h"
# include "op.h"

typedef struct		s_instruction
{
	int				op_code;
	unsigned char	*pc;
	unsigned char	*param[ MAX_PARAM ];
	int				param_size[ MAX_PARAM ];
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
	unsigned char	arena[ MEM_SIZE ];
}					t_arena;

int					comparison(void *ptr1, void *ptr2);

void				process_execution(t_arena *arena, t_process *process);

int					get_exec_cycle(char *pc);

void				print_arena(t_arena arena);

#endif
