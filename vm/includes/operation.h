/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:21:25 by satkins           #+#    #+#             */
/*   Updated: 2018/03/08 07:21:34 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H

# define OPERATION_H

void	aff(t_arena *arena, t_process *process);
void	op_or(t_arena *arena, t_process *process);
void	op_and(t_arena *arena, t_process *process);
void	zjmp(t_arena *arena, t_process *process);
void	st(t_arena *arena, t_process *process);
void	sti(t_arena *arena, t_process *proc);
void    op_live(t_process *process,  t_arena *arena);
void	op_xor(t_arena *arena, t_process *process);
void	add(t_arena *arena, t_process *process);
void	ldi(t_arena *arena, t_process *process);
void	ld(t_arena *arena, t_process *process);
void	op_fork(t_arena *arena, t_process *process);
void	lldi(t_arena *arena, t_process *process);
void	sub(t_arena *arena, t_process *process);
void	lld(t_arena *arena, t_process *process);
void	op_lfork(t_arena *arena, t_process *process);

#endif