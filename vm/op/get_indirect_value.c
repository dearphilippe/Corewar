/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_indirect_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:01:59 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 23:40:28 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int get_ind_val(int num, t_process *proc, t_arena *arena)
{
	unsigned char	*ptr;
	int				ret;
	int				i;

	ptr = proc->instruct.pc;
	if (proc->instruct.op_code < 13)
		num = num % IDX_MOD;
	i = -1;
	while (++i < abs(num))
		if (num > 0)
			ptr = ptr + 1 - arena->arena < MEM_SIZE ? ptr + 1 : arena->arena;
		else
			ptr = ptr - 1 >= arena->arena ? ptr - 1 : arena->arena + MEM_SIZE - 1;
	ret = 0;
	i = -1;
	while (++i < REG_SIZE)
	{
		ret = ret << 8;
		ret += *ptr;
		ptr = ptr + 1 - arena->arena < MEM_SIZE ? ptr + 1 : arena->arena;
	}
	return (ret);
}
