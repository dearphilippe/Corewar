/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:06:16 by sbalcort          #+#    #+#             */
/*   Updated: 2018/03/07 19:06:18 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			read_file_error(int i, int fd, char *file)
{
	if (i == OPEN_FILE_ERR)
		ft_printf("Error opening file: %s\n", file);
	if (i == FILE_TOO_SMALL)
		ft_printf("Improper file size: %s\n", file);
	if (i == MISSING_MAGIC)
		ft_printf("Magic Number missing %s\n", file);
	if (fd > -1)
		close(fd);
	exit(1);
}

void			get_player_name(char *cont, char *name)
{
	int i;
	int y;

	y = 0;
	i = sizeof(COREWAR_EXEC_MAGIC);
	while (i < PROG_NAME_LENGTH && cont[i] != '\0')
	{
		name[y] = cont[i];
		y++;
		i++;
	}
	name[y] = '\0';
}

void			get_player_comment(char *content, char *comment)
{
	int i;
	int y;

	y = 0;
	i = (PROG_NAME_LENGTH + sizeof(COREWAR_EXEC_MAGIC) + 8);
	while (i < (PROG_NAME_LENGTH + 16 + COMMENT_LENGTH) && content[i] != '\0')
	{
		comment[y] = content[i];
		i++;
		y++;
	}
	comment[y] = '\0';
}

unsigned int	get_magic(char *str, int count)
{
	int				i;
	unsigned int	number;

	number = 0;
	i = 0;
	while (i <= count)
	{
		number <<= 8;
		number += (unsigned char)str[i];
		i++;
	}
	return (number);
}

void			get_player_stats(t_player *player, int fd, char *file)
{
	int		i;
	char	content[PROG_NAME_LENGTH + COMMENT_LENGTH + 17];

	ft_bzero(content, PROG_NAME_LENGTH + COMMENT_LENGTH + 17);
	if (read(fd, content, 0) < 0 || fd < 0)
		read_file_error(OPEN_FILE_ERR, fd, file);
	if (!read(fd, content, PROG_NAME_LENGTH + COMMENT_LENGTH + 16))
		read_file_error(FILE_TOO_SMALL, fd, file);
	if (get_magic(content, 3) ^ COREWAR_EXEC_MAGIC)
		read_file_error(MISSING_MAGIC, fd, file);
	get_player_name(content, player->name);
	player->player_size = get_magic(&content[sizeof(COREWAR_EXEC_MAGIC)
	+ PROG_NAME_LENGTH], 7);
	get_player_comment(content, player->comment);
}
