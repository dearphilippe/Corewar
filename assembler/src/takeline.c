/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:59:25 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 13:58:36 by nkouris          ###   ########.fr       */
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
	i = 2;
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
	int				pads;

	printf("build header\n");
	/* Build magic num */
	magictobyte(head_cor);
	/* Build name */
	name = (ft_strnstr(sfile, NAME_CMD_STRING, sizeof(header_t)) + ft_strlen(NAME_CMD_STRING));
	printf("name: %s\n", name);
	name = ft_strchr(name, '"') + 1;
	nend = ft_strchr(name, '"');
	printf("nend: %s\n", nend);
	while (name != nend)
		 *(*head_cor)++ = *(unsigned char *)(name++);
	pads = (nend - name);
	while (pads++ <= ((PROG_NAME_LENGTH + 1) - (nend - name)))
		*(*head_cor)++ = '\0';
	/* Build progsize num */
	progsizetobyte(head_cor, &prog_len);
	/* Build comment */
	comment = (ft_strnstr(sfile, COMMENT_CMD_STRING, sizeof(header_t)) + ft_strlen(NAME_CMD_STRING));
	comment = ft_strchr(comment, '"') + 1;
	cend = ft_strchr(comment, '"');
	while (comment != cend)
		*(*head_cor)++ = *(unsigned char *)(comment++);
	pads = (cend - comment);
	while (pads++ <= (PROG_NAME_LENGTH + 1))
		*(*head_cor)++ = '\0';
}

void	write_bytes(t_buffers *cor)
{
	int i = 0;
	int					writefd;

	writefd = open("test.cor", (O_CREAT | O_WRONLY | O_APPEND));
	while (i < 2201)
		write(writefd, &(cor->storhead_cor[i++]), 1);
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
		|| !(cor->prog_cor = (unsigned char *)ft_memalloc(strlen))
		|| !(cor->head_cor = (unsigned char *)ft_memalloc(sizeof(header_t))))
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
