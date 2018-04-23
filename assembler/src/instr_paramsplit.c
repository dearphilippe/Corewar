/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_paramsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 15:04:25 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 14:38:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

static void	param_err(t_ininit *handler, int i)
{
	if (!(handler->trans[i] & op_tab[(handler->op - 1)].param_type[i]))
	{
		ft_printf("parameter error, type mismatch\n");
		exit (1);
	}
}

static void	dircode_err(char *sfile, int trans)
{
	ft_printf("dircode err check : %d\n", *sfile);
	if (trans == T_DIR)
	{
		if (!(!IS_DIGIT(*(sfile + 1)) && *(sfile + 0) != '-'
			&& *(sfile + 1) != LABEL_CHAR))
		{
			ft_printf("dir num err\n");
			exit(1);
		}
	}
}

static void	idparam(t_ininit *handler, t_buffers *cor, char **sfile, int i)
{
	while (IS_WHSPC(**sfile))
		(*sfile)++;
	if (*(*sfile) == DIRECT_CHAR)
	{
		handler->trans[i] = T_DIR;
		dircode_err(((*sfile) + 1), handler->trans[i]);
	}
	else if (*(*sfile) == 'r')
		handler->trans[i] = T_REG;
	else if (*(*sfile) == LABEL_CHAR)
		handler->trans[i] = T_LAB;
	else
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
		ft_printf("string before delim_assoc : <%s>\n", *sfile);
		delim = delimiter_assoc(handler, sfile, cor);
		handler->hold = *delim;
		*delim = '\0';
		ft_printf("string after delim_assoc : <%s>, and char <%d>\n", *sfile, **sfile);
		if (!cor->pass && **sfile != LABEL_CHAR)
		{
			ft_printf("atoi string after delim_assoc : <%s>\n", *sfile);
			(handler->param[i] = ft_atoi(*sfile));
		}
		ft_printf("char to check at instr_paramsplit : %d\n", **sfile);
		if (!cor->pass && **sfile == LABEL_CHAR)
			instr_labels(handler, sfile, i);
		else if (!handler->param[i] && **sfile != '0')
		{
			ft_printf("dir num err, not a number : %d\n", handler->param[i]);
			exit(1);
		}
		instr_assoc(cor, handler, i);
		param_err(handler, i);
		!(handler->eof) ? *delim = handler->hold : *delim;
		*delim == SEPARATOR_CHAR ? (*sfile = delim + 1) : (*sfile = delim);
		i++;
	}
}
