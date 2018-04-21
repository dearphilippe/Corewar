/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_paramsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 15:04:25 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 16:30:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

static void	param_err(t_ininit *handler, int i)
{
	while (i >= 0)
	{
		if (!(handler->trans[i] & op_tab[(handler->op - 1)].param_type[i]))
		{
			printf("parameter error, type mismatch\n");
			exit (1);
		}
		i--;
	}
}

static void	dircode_err(char *sfile, int trans)
{
	if (trans == T_DIR)
	{
		if (!(ft_isdigit(*(sfile + 1)) && *(sfile + 1) != '-'
			&& *(sfile + 1) != ':'))
		{
			printf("dir num err\n");
			exit(1);
		}
	}
}

static void	idparam(t_ininit *handler, t_buffers *cor, char **sfile, int i)
{
	(*sfile) += ft_skip_spaces(*sfile);
	if (*(*sfile) == DIRECT_CHAR)
	{
		handler->trans[i] = T_DIR;
		dircode_err(*sfile, handler->trans[i]);
	}
	else if (*(*sfile) == 'r')
		handler->trans[i] = T_REG;
	else if (*(*sfile) == ':')
		handler->trans[i] = T_LAB;
	else if (!handler->trans[i])
		handler->trans[i] = T_IND;
	handler->trans[i] != T_IND ? (*sfile)++ : (*sfile);
}

void		instr_paramsplit(t_ininit *handler, t_buffers *cor, char **sfile)
{
	char	*delim;
	int		i;

	i = 0;
	while (i < handler->params)
	{
		idparam(handler, cor, sfile, i);
		delim = delimiter_assoc(handler, sfile, cor);
		handler->hold = *delim;
		*delim = '\0';
		if (!cor->pass && **sfile != ':')
			(handler->param[i] = ft_atoi(*sfile));
		else if (!cor->pass && handler->param[i] == T_LAB)
			instr_labels(handler, sfile, i);
		instr_assoc(cor, handler);
		param_err(handler, i);
		!(handler->eof) ? *delim = handler->hold : *delim;
		*delim == SEPARATOR_CHAR ? (*sfile = delim + 1) : (*sfile = delim);
		i++;
	}
}
