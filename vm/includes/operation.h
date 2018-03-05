/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:21:25 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 22:26:20 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H

# define OPERATION_H

void	op_and(t_arena *arena, t_process *process);
void	zjmp(t_arena *arena, t_process *process);
void	st(t_arena *arena, t_process *process);
void	sti(t_arena *arena, t_process *proc);
void    op_live(t_process *process,  t_arena *arena);


#endif