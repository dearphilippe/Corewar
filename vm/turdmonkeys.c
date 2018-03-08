/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turdmonkeys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 13:41:24 by sbalcort          #+#    #+#             */
/*   Updated: 2018/03/07 13:41:27 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    read_file_error(int i, int fd)
{
    if (i == FILE_ERROR)
        ft_printf("Error opening file");
    if (i == SIZE_ERROR)
        ft_printf("Improper file size");
    if (i == MAGIC_MISSING)
        ft_printf("Magic Number missing");
    if (fd > -1)
        close (fd);
    exit (1);
}

void     get_player_name(char *cont char *name)
{
    int i;
    int y;

    y = 0;
    i = sizeof(COREWAR_EXEC_MAGIC);
    while (i < PROG_NAME_LENGTH && content[i] != '\0')
    {
        content[y] = name[i - COREWAR_EXEC_MAGIC];
        y++;
        i++;
    }
}

int     get_player_comment(char *content, char *comment)
{
    int i;
    int y;

    y = 0;
    i = sizeof(PROG_NAME_LENGTH) + sizeof(COREWAR_EXEC_MAGIC) + 4;
    while (i < (PROGRAM_NAME_LENGTH + 16 + COMMENT_LENGTH) && content[i] != '\0')
    {
        content[y] = comment[i];
        i++;
        y++;
    }
}

void    get_player_stats(t_player *player, int fd)
{
    int i;
    char content[PROG_NAME_LENGTH + COMMENT_LENGTH + 17]

    ft_bzero(content, PROG_NAME_LENGTH + COMMENT_LENGTH + 17);
    if (read(fd, content, 0) < 0 || fd < 0)
        read_file_error(FILE_ERROR, fd);
    if (!read(fd, content, PROG_NAME_LENGTH + COMMENT_LENGTH + 16)) 
        read_file_error(SIZE_ERROR, fd);
    if ((content ^ COREWAR_EXEC_MAGIC)
        read_file_error(MAGIC_MISSING, fd);
    get_player_name(content, player->name);
    player->player_size = (int)content[sizeof(COREWAR_EXEC_MAGIC) + sizeof(PROG_NAME_LENGTH)];
    get_player_comment(content, payer->comment);
}
