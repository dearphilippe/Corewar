/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:59:25 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 17:07:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"
#include <errno.h>
#include <fcntl.h>

void	progsizetobyte(unsigned char **head_cor, int *prog_len)
{
	int				i;
	unsigned char	*transfer;

	transfer = (unsigned char *)prog_len;
	i = 4;
	while (i--)
	{
		printf("progsize byte: %x\n", transfer[i]);
		*(*head_cor)++ = (transfer[i]);
	}
}

void	magictobyte(unsigned char **head_cor)
{
	int				i;
	int				magic;
	unsigned char	*trans;

	magic = COREWAR_EXEC_MAGIC;
	trans = (unsigned char *)(&magic);
	i = 4;
	while (i--)
		*(*head_cor)++ = (trans[i]);
}

void	build_header(char *sfile, unsigned char **head_cor, int prog_len)
{
	char			*name;
	char			*nend;
	char			*comment;
	char			*cend;
	int				bytes_written;

	ft_printf("build header\n");
	ft_printf("file buffer is \n<%s>\n", sfile);
	/* Build magic num */
	magictobyte(head_cor);
	/* Build name */
	name = (ft_strnstr(sfile, NAME_CMD_STRING, sizeof(header_t)) + ft_strlen(NAME_CMD_STRING));
	printf("name: %s\n", name);
	name = ft_strchr(name, '"') + 1;
	nend = ft_strchr(name, '"');
	bytes_written = (nend - name);
	ft_printf("byte written : %d\n", bytes_written);
	printf("nend: %s\n", nend);
	while (name != nend)
		 *(*head_cor)++ = *(unsigned char *)(name++);
	while (bytes_written++ < (PROG_NAME_LENGTH + 4))
		*(*head_cor)++ = '\0';
	/* Build progsize num */
	progsizetobyte(head_cor, &prog_len);
	/* Build comment */
	comment = (ft_strnstr(sfile, COMMENT_CMD_STRING, sizeof(header_t)) + ft_strlen(NAME_CMD_STRING));
	comment = ft_strchr(comment, '"') + 1;
	cend = ft_strchr(comment, '"');
	bytes_written = (cend - comment);
	while (comment != cend)
		*(*head_cor)++ = *(unsigned char *)(comment++);
	while (bytes_written++ < (COMMENT_LENGTH + 4))
		*(*head_cor)++ = '\0';
}

void	write_bytes(t_buffers *cor)
{
	int i = 0;
	int					writefd;

	writefd = open("test.cor", (O_CREAT | O_TRUNC | O_WRONLY), (S_IRUSR | S_IWUSR | S_IXUSR));
	write(writefd, cor->storhead_cor, (PROG_NAME_LENGTH + COMMENT_LENGTH + 16));
	printf("%d\n", cor->prog_len);
	i = 0;
	while (i < cor->prog_len)
		write(writefd, &(cor->storprog_cor[i++]), 1);
}

void	init_passes(char *sfile)
{
	struct s_buffers	*cor;
	int					strlen;

	strlen = ft_strlen(sfile);
	/* build cor buffer struct to pass critical info */
	if (!(cor = (t_buffers *)ft_memalloc(sizeof(t_buffers)))
		|| !(cor->prog_cor = (unsigned char *)ft_memalloc((CHAMP_MAX_SIZE) + 1))
		|| !(cor->head_cor = (unsigned char *)ft_memalloc((PROG_NAME_LENGTH + COMMENT_LENGTH + 16))))
		printexit();
	cor->storhead_cor = cor->head_cor;
	cor->storprog_cor = cor->prog_cor;
	cor->sfile = sfile;
	/*
	** Begin the two pass check for errors / build of associative arrays
	** for the labels within the assembly program
	*/
	tokenize(cor);
	/*
	** After verification of all elements and program size, header
	** is built in a separate buffer
	*/
	build_header(cor->sfile, &(cor->head_cor), (cor->prog_len));
	build_prog(cor);
	write_bytes(cor);
}
