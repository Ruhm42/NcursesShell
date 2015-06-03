/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 11:44:04 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/02 13:49:41 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix.h"

static void		radix_join(t_rdx **root, t_rdx *actual, char *str)
{
	t_rdx	*tmp;

	tmp = new_node(str);
	if (actual->prev)
		actual->prev->next = tmp;
	tmp->prev = actual->prev;
	tmp->next = actual;
	actual->prev = tmp;
	if (*root == actual)
		*root = tmp;
}

static void		radix_add(t_rdx *actual, char *str)
{
	t_rdx	*tmp;

	tmp = new_node(str);
	actual->next = tmp;
	tmp->prev = actual;
}

static void		radix_split(t_rdx *actual, char *str, unsigned int index)
{
	t_rdx *save;

	save = actual->down;
	actual->down = NULL;
	radix_insert(&actual, actual->str + index);
	if (actual->down)
	{
		actual->down->st = actual->st;
		actual->down->down = save;
	}
	else
		actual->down = save;
	radix_insert(&actual, str + index);
	if (actual->str[index])
		actual->st = false;
	actual->str[index] = 0;
}

static void		radix_iterate(t_rdx **root, t_rdx *tmp, char *str)
{
	unsigned int		index;
	int					ret;

	while (tmp)
	{
		index = 0;
		while (str[index] && tmp->str && tmp->str[index])
		{
			ret = tmp->str[index] - str[index];
			if (ret != 0)
				break ;
			index++;
		}
		if (index)
			return (radix_split(tmp, str, index));
		else if (ret > 0)
			return (radix_join(&((*root)->down), tmp, str));
		if (!tmp->next)
			return (radix_add(tmp, str));
		tmp = tmp->next;
	}
}

void			radix_insert(t_rdx **root, char *str)
{
	t_rdx				*tmp;

	if (!str || !str[0])
		return ;
	if (!(*root))
	{
		*root = new_node(NULL);
		(*root)->st = false;
		return (radix_insert(root, str));
	}
	if (!(tmp = (*root)->down))
	{
		(*root)->down = new_node(str);
		return ;
	}
	radix_iterate(root, tmp, str);
}
