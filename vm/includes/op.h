/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:24:25 by satkins           #+#    #+#             */
/*   Updated: 2018/03/06 03:52:21 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H

# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define MAX_PARAM              3


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define MAX_OPNAME              6

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16


# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_sizes;
	char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct	s_op
{
	char		op[MAX_OPNAME];
	int			num_param;
	int			param_type[MAX_PARAM];
	int			op_code;
	int			num_cycles;
	char		comment[COMMENT_LENGTH];
	int			coding_byte : 1;
	int			tr : 1;
}				t_op;

extern t_op    op_tab[17];

#endif
