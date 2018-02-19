/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:43:36 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 18:47:36 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_node(t_node *node, t_node *prev)
{
	if (node)
	{
		if (node->next)
			node->next->previous = node->previous;
		if (prev)
			prev->next = node->next;
		free(node);
	}
}