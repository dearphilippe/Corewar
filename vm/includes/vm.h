/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/02/17 17:41:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# include "libft.h"
# include "op.h"

# define OPCODE_OFFSET 56;

typedef struct  s_process
{
	char		*pc;
	char		regs[ REG_NUMBER ][ REG_SIZE ];
	int			execute_cycle;
	int			carry : 1;
	int			process_num;

}               t_process;

typedef struct	s_arena
{
	int			num_players;
	char		arena[ MEM_SIZE ];
}				t_arena;

#endif
