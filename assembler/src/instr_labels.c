/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:09:34 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 15:02:55 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

void	instr_labels(t_ininit *handler, char **sfile, int i)
{
	int		labelen;
	int		j;

	ft_printf("adding label : %s\ni : %d\n", *sfile, i);
	j = 0;
	sfile ? (*sfile)++ : 0;
	ft_printf("adding label : %s\n", *sfile);
	labelen = ft_strlen(*sfile);
	ft_printf("len : %d\n", labelen);
	if (!(handler->tolabels[i] = (char *)ft_memalloc(sizeof(char) * labelen + 1)))
		exit (1);
	ft_printf("seg with this string %s\n", *sfile);
	while (**sfile)
		handler->tolabels[i][j++] = *(*sfile)++;
}
