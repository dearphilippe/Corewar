/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_indirect_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:01:59 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 19:41:25 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int get_ind_val(int num, t_process *proc, t_arena *arena)
{
	unsigned char	*ptr;
	int				ret;
	int				i;

	ptr = proc->instruct.pc;
	if (num + ptr > arena->arena + MEM_SIZE)
	{
		num -= (arena->arena + MEM_SIZE - ptr);
		ptr = arena->arena;
	}
	else if (num + ptr < arena->arena)
	{
		num += ptr - arena->arena;
		ptr = arena->arena + MEM_SIZE;
	}
	ptr = ptr + num;
	ret = 0;
	i = -1;
	while (++i < REG_SIZE)
	{
		ret << 8;
		ret += *ptr;
		ptr = ptr + 1 - arena->arena < MEM_SIZE ? ptr + 1 : arena->arena;
	}
	return (ret);
}
