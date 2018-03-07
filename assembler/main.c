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

#include "assembler.h"

char	*read_sfile(char *path)
{
	int		fd;
	char	*content;

	//printf("Path:%s\n", path);
	if ((fd = open(path, O_RDONLY, S_IRUSR)) < 0)
		err_usage_warning(path);
	content = ft_read_alloc(fd);
	if (content == NULL)
		err_usage_warning(path);
	return (content);
}

int		main(int argc, char **argv)
{
	char	*content;

	if (argc == 1)
		err_usage_warning(NULL);
	content = read_sfile(argv[argc - 1]);
	lexi_check(content);
	syntcheck(content);
	paramcheck(content);
//	labelcheck();
//	printerrors();
//	convertokens();
//	write_cor();
printf("is all gud\n");
	return (0);
}


//	errno = USAGE_ERR;
//	exit (errno);