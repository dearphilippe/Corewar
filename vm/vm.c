/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 21:49:11 by satkins           #+#    #+#             */
/*   Updated: 2018/02/17 19:19:17 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <fcntl.h>

static int		is_hex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') ||
		(c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}
static int		hex_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

static void		create_bytes(unsigned char *buff, unsigned char *pc)
{
	int			i_buff;
	int			i_pc;

	i_pc = 0;
	i_buff = -1;
	while (buff[++i_buff])
	{
		if (is_hex(buff[i_buff]))
		{
			pc[i_pc] = ((i_pc % 2 == 0) ? (hex_val(buff[i_buff]) << 4) :
				pc[i_pc] + hex_val(buff[i_buff]));
			i_pc++;
		}
	}
}

static void			create_arena(char **argv, t_arena *arena, t_process *p)
{
	int				i;
	int				j;
	int				k;
	int				fd;
	unsigned char	str[ 4 ];

	i = -1;
	while (++i < arena->num_players)
	{
		if ((fd = open(argv[i + 1], O_RDONLY)) > 0)
		{
			//Validate .cor??
			lseek(fd, PROG_NAME_LENGTH + COMMENT_LENGTH + 4, SEEK_SET);
			k = 0;
			while ((j = read(fd, str, 1)) > 0)
				// while (j-- > 0)
					// ft_printf("%d\n", buff[0]);
				{
					ft_printf("here\n");
					*(p[i].pc + (k)) = *str;
					++k;
				// create_bytes(str, p[i].pc);
				}
			close(fd);
		}
	}
}

static void		init_players(t_arena arena, t_process *players)
{
	int			i;

	i = -1;
	while (++i < arena.num_players)
	{
		*((int *)((players[i]).regs[0])) = i;
		players[i].pc = (i * (MEM_SIZE / arena.num_players)) + arena.arena;
	}
}

int				main(int argc, char **argv)
{
	t_process	*players;
	t_arena		arena;

	arena.num_players = argc - 1; //Change to include options
	players = ft_memalloc(sizeof(t_process));
	init_players(arena, players);
	ft_bzero(arena.arena, MEM_SIZE);
	create_arena(argv, &arena, players);
	ft_printf("MEM");
	for (int i = 0; i < MEM_SIZE; i++)
	{
		if (i % (MEM_SIZE / 16) == 0)
			ft_printf("\n");
		ft_printf("%02x ", arena.arena[i]);
	}
	ft_printf("\n");
}