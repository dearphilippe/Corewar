/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:26 by satkins           #+#    #+#             */
/*   Updated: 2018/02/16 15:48:38 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# include "libft.h"

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}                 header_t;

# define OPCODE_OFFSET 56;

typedef struct	s_op
{
	char		op[6];
	int			num_param;
	int			*param_type;
	int			op_code;
	int			num_cycles;
	char		comment[COMMENT_LENGTH];
	int			carry_success : 1;
	int			carry_failure : 1;
}				t_op;

typedef struct  s_reg
{
	char        reg[REG_SIZE];
}               t_reg;

typedef struct  s_process
{
	void		*pc;
	t_reg		regs[ REG_NUMBER ];
	int			execute_cycle;
	int			carry : 1;
	int			process_num;

}               t_process;

typedef struct	s_arena
{
	int			num_players;
	char		*arena;
}				t_arena;

#endif
