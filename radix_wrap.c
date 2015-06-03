/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:57:03 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 15:05:27 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix.h"

static t_wrap	*new_wrap(char *str)
{
	t_wrap	*ret;

	if (!(ret = malloc(sizeof(t_wrap))))
		return (NULL);
	memset(ret, 0, sizeof(t_wrap));
	ret->str = str;
	return (ret);
}

void			wrap_build(t_wrap **start, t_wrap **cur, char *str)
{
	if (!str)
		return ;
	if (!*start)
	{
		*start = new_wrap(str);
		*cur = *start;
		(*cur)->next = *cur;
		(*cur)->prev = *cur;
		return ;
	}
	(*cur)->next = new_wrap(str);
	(*cur)->next->prev = *cur;
	(*cur)->next->next = *start;
	*cur = (*cur)->next;
	(*start)->prev = *cur;
}

static void		wrap_free_node(t_wrap *node)
{
	free(node->str);
	free(node);
}

void			wrap_free(t_wrap **start, t_wrap **cur)
{
	if (!(*start))
		return ;
	(*start)->prev->next = NULL;
	(*start)->prev = NULL;
	while (*start)
	{
		if ((*start)->prev)
			wrap_free_node((*start)->prev);
		if (!(*start)->next)
			wrap_free_node(*start);
		*start = (*start)->next;
	}
	*start = NULL;
	*cur = NULL;
}
