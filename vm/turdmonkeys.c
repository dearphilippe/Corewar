#include "vm.h"

/*
**function prototype in create_arena
**
**			get_player_stats(&arena->players[i], fd);
**
    typedef struct		s_player
    {
    int				player_num;
    int				player_id;
    int				num_of_process;
    int				player_size;
    char			name[ PROG_NAME_LENGTH + 1 ];
    char			comment[ COMMENT_LENGTH + 1 ];
    }					t_player;
**
*/

void    read_file_error(int i, int fd)
{
    if (i == 0)     //open file error
        ft_printf("Error opening file");
    if (i == 1)     //file could not read initial PROG_NAME_LENGTH + COMMENT_LENGTH + 16 bytes
        ft_printf("Improper file size");
    if (i == 2)     //magic number missing. Is it a core war file ?
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
        read_file_error(0, fd);
    if (!read(fd, content, PROG_NAME_LENGTH + COMMENT_LENGTH + 16)) 
        read_file_error(1, fd);
    if ((content ^ COREWAR_EXEC_MAGIC)
        read_file_error(2);
    get_player_name(content, player->name);
    player->player_size = (int)content[sizeof(COREWAR_EXEC_MAGIC) + sizeof(PROG_NAME_LENGTH)];
    get_player_comment(content, payer->comment);
}