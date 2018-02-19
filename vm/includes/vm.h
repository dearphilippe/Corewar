/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 16:50:08 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# include "libft.h"
# include "op.h"

typedef struct		s_process
{
	unsigned char	*pc;
	unsigned char	regs[ REG_NUMBER ][ REG_SIZE ];
	int				execute_cycle;
	int				carry : 1;
	int				process_num;
	int				num_live;
}					t_process;

typedef struct		s_instruction
{
	int				op_code;
	unsigned char	*pc;
	unsigned char	*param[ MAX_PARAM ];
	int				param_size[ MAX_PARAM ];
}					t_instruction;

typedef struct		s_arena
{
	int				num_players;
	int				cycle;
	t_pqueue		*proc_queue;
	int				*player_procs;
	unsigned char	arena[ MEM_SIZE ];
}					t_arena;

int					comparison(void *ptr1, void *ptr2);

void				process_execution(t_arena *arena, t_process *process);

int					get_exec_cycle(char *pc);
#endif
