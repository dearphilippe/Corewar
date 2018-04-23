/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:19:35 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 14:21:13 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "op.h"

static void	(*ops[])(char **, t_buffers *) = {
			0,
			ft_live,
			ft_ld,
			ft_st,
			ft_add,
			ft_sub,
			ft_and,
			ft_or,
			ft_xor,
			ft_zjmp,
			ft_ldi,
			ft_sti,
			ft_fork,
			ft_lld,
			ft_lldi,
			ft_lfork,
			ft_aff
};

static void	head_err(char **strp1, t_buffers *cor)
{
	size_t			nlen;
	size_t			clen;
	int				i;

	nlen = ft_strlen(NAME_CMD_STRING);
	clen = ft_strlen(COMMENT_CMD_STRING);
	i = 0;
	while (i < 2)
	{
		cor->col = *strp1;
		while (IS_WHSPC(**strp1))
				(*strp1)++;
		if ((!(ft_strnequ(*strp1, NAME_CMD_STRING, nlen) ?
				(*strp1 += (nlen)) : 0)
			&& !(ft_strnequ(*strp1, COMMENT_CMD_STRING, clen) ?
				(*strp1 += (clen)) : 0))
			|| (!((*strp1 = ft_strchr(*strp1, '"')) ? *strp1 += 1 : 0)))
		{
			printf("head lexical error on line: %d col: %ld\n",
					cor->line, (*strp1 - cor->col));
			exit (1);
		}
		if 	(!((*strp1 = ft_strchr(*strp1, '"')) ? (*strp1 += 1) : 0))
		{
			printf("head syntax error on line: %d col: %ld\n",
					cor->line, (*strp1 - cor->col));
			exit (1);
		}
		(remove_comment(strp1, cor) == EXIT_FAILURE) ? cor->line : cor->line++;
		i++;
	}
}

static void	label_err(t_label *label, char *end)
{
	char	*temp;

	temp = label->str_label;
	// lexical check
	while (*temp)
	{
		ft_printf("%c", *temp);
		if (!ft_strchr(LABEL_CHARS, *temp))
		{
			printf("label lexical error\n");
			exit (1);
		}
		temp++;
	}
	ft_printf("\n");
	if (ft_isalnum(*(end + 1)))
	{
		printf("label syntax error\n");
		exit (1);
	}
}

static void	label(char **sfile, t_buffers *cor)
{
	char			*end;
	t_label			*label;
	int				labelen;

	ft_printf("%s\n", *sfile);
	if (!(**sfile))
		return ;
	if (!(end = ft_strchr(*sfile, LABEL_CHAR)))
	{
		if ((end = ft_strchr(*sfile, '\n')))
			*end = '\0';
		ft_printf("lexical error: %s\n", *sfile);
		exit (1);
	}
//	ft_printf("sfile: %p\nend  : %p\n", *sfile, end);
	labelen = end - *sfile;
	if (!(label = (t_label *)ft_memalloc(sizeof(t_label)))
		|| !(L_STR = (char *)ft_strnew(sizeof(char) * labelen)))
		exit (1);
	labelen = 0;
	while (*sfile != end)
		L_STR[labelen++] = *(*sfile)++;
	L_LOC = cor->prog_len;
	label_err(label, end);
	ft_lstadd(&cor->labels, label, sizeof(*label));
	(*sfile)++;
}

void		tokenize(t_buffers *cor)
{
	char	*strp1;
	int		token;

	strp1 = cor->sfile;
	cor->stor_sfile = cor->sfile;
	remove_comment(&strp1, cor);
	head_err(&strp1, cor);
	ft_printf("start tokenize\n");
	while (*strp1)
	{
		ft_printf("cycle, char : %d\n", *strp1);
		remove_comment(&strp1, cor);
		ft_printf("<%s>\n", strp1);
		*strp1 ? (token = ft_nlookup(KEY, strp1, 5, ' ')) : (token = 0);
		if (token)
		{
			ft_printf("op\n");
			ops[token](&strp1, cor);
		}
		else
		{
			ft_printf("possible label\n");
			remove_comment(&strp1, cor);
			label(&strp1, cor);
		}
	}
}
