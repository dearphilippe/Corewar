/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:27:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/23 10:42:57 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "state.h"

void	printexit(void)
{
	perror(strerror(errno));
	exit (0);
}

char	*read_sfile(char **argv)
{
	int				fd;
	char			*str;
	char			*terminus;

	if (!(str = (char *)ft_strnew(MEM_SIZE)))
		exit (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (NULL);
	read(fd, str, MEM_SIZE);
	if (read(fd, str, 1) > 0)
	{
		ft_printf("Champion is too heavy at weigh in.  Reduce byte size\n");
		return (NULL);
	}
	return (str);
}

static void	usage_warning(void)
{
	ft_printf("Usage: ./asm [file ...]\n");
	exit (errno);
}

int		main(int argc, char **argv)
{
	char	*sfile;

	if (argc == 1)
		usage_warning();
	if (!(sfile = read_sfile(argv)))
	{
		printexit();
		return (-1);
	}
	init_passes(sfile);
	printf("done!\n");
	return (0);
}
