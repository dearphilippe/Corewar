/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:27:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/27 14:25:13 by nkouris          ###   ########.fr       */
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
	fd = open(argv[1], O_RDONLY);
	read(fd, str, MEM_SIZE);
	if (read(fd, str, 1) > 0)
		exit (1);
	terminus = ft_strnchr(str, '\n');
	*terminus = '\0';
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
	sfile = read_sfile(argv);
	init_passes(sfile);
	printf("done!\n");
	return (0);
}
