/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:56:30 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 14:22:33 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
#define STATE_H

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define KEY "live ld st add sub and or xor zjmp ldi sti fork lld lldi lfork aff"
#define L_STR label->str_label
#define L_LOC label->loc_label
# define TO_UPPER(x) (x ^ 0x20)
# define TO_LOWER(x) (x | 0x20)
# define IS_DIGIT(x) (x >= 48 && x <= 57)
# define IS_PRINT(x) (x >= 32 && x<= 126)
# define IS_ALPHA(x) ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
# define IS_ALNUM(x) (IS_DIGIT(x) || IS_ALPHA(x))
# define IS_WHSPC(x) (x == 32 || x == 10 || x == 11 || x == 9 || x == 12)
# define IS_ASCII(x) (x >= 0 && x <= 127)

typedef enum	e_instruct
{
	LIVE = 1, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP, LDI, STI, FORK, LLD,
LLDI, LFORK, AFF
}				t_instruct;

typedef struct	s_label
{
	char	*str_label;
	int		loc_label;
}				t_label;

typedef struct		s_buffers
{
	unsigned char	*prog_cor;
	unsigned char	*head_cor;
	unsigned char	*storhead_cor;
	unsigned char	*storprog_cor;
	char			*sfile;
	char			*stor_sfile;
	t_list			*instructions;
	t_list			*labels;
	char			*col;
	char			*name;
	char			*comment;
	int				line;
	int				prog_len;
	int				pass;
}					t_buffers;

typedef struct		s_ininit
{
	int				param[3];
	int				trans[3];
	char			*tolabels[3];
	int				eof;
	int				params;
	int				op;
	unsigned char	opbyte;
	int				prog_byte;
	char			hold;
}					t_ininit;



void	pass_one(char *sfile, t_buffers *cor);

/*
**	PASS ONE, building label associations
*/

void	tokenize(t_buffers *cor);

int		remove_comment(char **temp, t_buffers *cor);

/*  
** subsequent calls
*/

void	instr_paramsplit(t_ininit *handler, t_buffers *cor, char **sfile);

/* subsequent calls */

char	*delimiter_assoc(t_ininit *handler, char **sfile, t_buffers *cor);
void	instr_labels(t_ininit *handler, char **sfile, int i);
void	instr_assoc(t_buffers *cor, t_ininit *handler, int i);

/* subsequent calls */
void	handle_dir(t_buffers *cor, t_ininit *handlers, int i);
void	handle_ind(t_buffers *cor, t_ininit *handlers, int i);

void	printexit(void);
void	init_passes(char *sfile);
void	build_prog(t_buffers *cor);

#include "asmops.h"

#endif
