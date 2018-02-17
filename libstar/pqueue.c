/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:13:22 by satkins           #+#    #+#             */
/*   Updated: 2018/02/10 21:27:42 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pqueue			*init_pqueue(void)
{
	t_pqueue		*node;

	node = (t_pqueue *)malloc(sizeof(t_pqueue));
	node->first = NULL;
	return (node);
}

void				ft_enpqueue(t_pqueue *queue, void *content, size_t c_size,
	int (*comparer)(void *, void *))
{
	t_node			*node;
	t_node			*tmp;

	node = (t_node *)malloc(sizeof(t_node));
	node->content = ft_memalloc(c_size);
	node->content = ft_memmove(node->content, content, c_size);
	node->next = NULL;
	if (!queue->first)
		queue->first = node;
	else
	{
		tmp = queue->first;
		if (!comparer(tmp->content, node->content))
		{
			queue->first = node;
			node->next = tmp;
		}
		else
		{
			while (tmp->next && comparer(tmp->next->content, node->content))
				tmp = tmp->next;
			node->next = tmp->next;
			tmp->next = node;
		}
	}
}

void				*ft_depqueue(t_pqueue *queue)
{
	t_node			*tmp;

	tmp = queue->first;
	if (tmp)
	{
		queue->first = tmp->next;
		return (tmp->content);
	}
	return (NULL);
}

void				*pqueue_find(t_pqueue *queue, void *trgt,
	int (*equality)(void *, void *))
{
	t_node			*tmp;
	void			*hold;

	if (!(tmp = queue->first))
		return (NULL);
	if (equality(tmp->content, trgt))
	{
		queue->first = tmp->next;
		hold = tmp->content;
		free(tmp);
		return (hold);
	}
	while (tmp->next)
	{
		if (equality(tmp->next->content, trgt) && (hold = tmp->next))
		{
			tmp->next = tmp->next->next;
			tmp = hold;
			hold = tmp->content;
			free(tmp);
			return (hold);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void				del_pqueue(t_pqueue *queue, void (*deconstruct)(void *ptr))
{
	t_node			*node;
	t_node			*hold;

	node = queue->first;
	while (node)
	{
		deconstruct(node->content);
		free(node->content);
		hold = node->next;
		free(node);
		node = hold;
	}
	free(queue);
}
