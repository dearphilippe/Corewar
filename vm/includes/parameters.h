/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 16:56:32 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 23:41:53 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H

# define PARAMETERS_H

# include "vm.h"

int	get_reg_val(int num, t_process *proc, t_arena *arena);

int get_ind_val(int num, t_process *proc, t_arena *arena);

int get_dir_val(int num, t_process *proc, t_arena *arena);

int	*read_param(t_process *proc, t_arena *arena);

// extern int (*get_value[4])(int num, t_process *proc, t_arena *arena);

#endif
