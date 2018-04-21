/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:09:34 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 16:29:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

void	instr_labels(t_ininit *handler, char **sfile, int i)
{
	int		labelen;
	int		j;

	j = 0;
	(*sfile)++;
	labelen = ft_strlen(*sfile);
	if (!(handler->tolabels[i] = (char *)ft_memalloc(sizeof(char) * labelen)))
		exit (1);
	while (**sfile)
		handler->tolabels[i][j++] = **sfile++;
}
