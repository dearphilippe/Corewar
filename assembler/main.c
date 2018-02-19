/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:27:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/18 20:21:58 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

void	read_sfile()
{
}

void	usage_warning()
{
	ft_printf("Usage: ./asm [file ...]\n");
	errno = USAGE_ERR;
	exit (errno);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		usage_warning();
	read_sfile();
	lexicheck();
	syntcheck();
	paramcheck();
	labelcheck();
	printerrors();
	convertokens();
	write_cor();
	return (0);
}
