/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 10:25:28 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/06 03:41:39 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, size_t content_size)
{
	t_list	*head;

	if (!(head = (t_list *)ft_memalloc(sizeof(t_list))))
		exit (0);
	if (!(head = (t_list *)ft_memalloc(sizeof(t_list)))
		|| !(head->data = ft_memalloc(content_size)))
		return (0);
	if (!content)
		content_size = 0;
	head->data = ft_memmove(head->data, content, content_size);
	head->d_size = content_size;
	free(content);
	return (head);
}

void	ft_lstadd(t_list **alst, void *content, size_t content_size)
{
	t_list	*new;

	if (!*alst)
	{
		*alst = ft_lstnew(content, content_size);
		return;
	}
	new = ft_lstnew(content, content_size);
	new->next = *alst;
	*alst = new;
}
