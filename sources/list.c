/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:51 by Minjun            #+#    #+#             */
/*   Updated: 2022/03/29 00:04:49 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

t_maplist
	*create_linked_list(void)
{
	t_maplist	*maplist;

	maplist = (t_maplist *)malloc(sizeof(t_maplist));
	if (!maplist)
		return (NULL);
	maplist->head = NULL;
	maplist->tail = NULL;
	maplist->size = 0;
	return (maplist);
}

t_node
	*create_new_node(char *line)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->map = ft_strdup(line);
	if (!node->map)
		return (NULL);
	node->next = NULL;
	return (node);
}

void
	add_node(t_maplist *list, t_node *node)
{
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}
