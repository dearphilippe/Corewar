/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/02/17 14:44:09 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# include "libft.h"
# include "op.h"

# define OPCODE_OFFSET 56;

typedef struct  s_reg
{
	char        reg[ REG_SIZE ];
}               t_reg;

typedef struct  s_process
{
	void		*pc;
	t_reg		regs[ REG_NUMBER ];
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
