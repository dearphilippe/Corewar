/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 23:55:45 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 19:08:09 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Returns 0 if ptr2 is a higher priority than ptr1
** This priority is decieded by 2 factors
** 1: The lowest Exec Cycle is prefered
** 2: The 'youngest' process is prefered
*/

int		comparison(void *ptr1, void *ptr2)
{
	t_process	*proc1;
	t_process	*proc2;

	proc1 = ptr1;
	proc2 = ptr2;
	if (proc1->execute_cycle < proc2->execute_cycle)
		return (1);
	if (proc1->execute_cycle > proc2->execute_cycle)
		return (0);
	return (proc1->process_num > proc2->process_num);
}