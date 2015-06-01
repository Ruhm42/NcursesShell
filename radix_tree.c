/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 11:44:04 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 14:55:31 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static t_rdx	*new_node(char *str)
{
	t_rdx	*ret;

	if (!(ret = malloc(sizeof(t_rdx))))
		return (NULL);
	memset(ret, 0, sizeof(t_rdx));
	ret->st = true;
	if (str)
		ret->str = strdup(str);
	return (ret);
}

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

static void		radix_add( t_rdx *actual, char *str)
{
	t_rdx	*tmp;

	tmp = new_node(str);
	actual->next = tmp;
	tmp->prev = actual;
}

static void		radix_split(t_rdx *actual, char *str, unsigned int index)
{
	radix_insert(&actual, str + index);
	radix_insert(&actual, actual->str + index);
	if (actual->str[index])
	{
		actual->str[index] = 0;
		if (str[index])
			actual->st = false;
	}
}

// void	radix_iterate(t_rdx **root, char *str)
// {
	
// }

void	radix_insert(t_rdx **root, char *str)
{
	t_rdx				*tmp;
	unsigned int		index;
	int					ret;

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



