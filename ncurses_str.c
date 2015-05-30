/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:58:48 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 17:57:18 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		str_update(t_str *str)
{
	str->pos++;
	str->sz++;
}

static void		ctn_assign(t_str *str, t_ctn *n, t_ctn *ptr)
{
	n->next = ptr;
	n->prev = ptr->prev;
	if (ptr->prev)
		ptr->prev->next = n;
	else
		str->cur = n;
	ptr->prev = n;
	str_update(str);
}

static void		ctn_place(t_str *str, t_ctn *n)
{
	unsigned int	i;
	t_ctn			*ptr;

	i = 0;
	ptr = str->cur;
	while (ptr && i < str->pos)
	{
		if (ptr->next == NULL)
		{
			ptr->next = n;
			n->prev = ptr;
			return (str_update(str));
		}
		ptr = ptr->next;
		i++;
	}
	ctn_assign(str, n, ptr);
}

void			ctn_create(t_str *str, char c)
{
	t_ctn			*n;

	if (!(n = malloc(sizeof(t_ctn))))
		return ;
	memset(n, 0, sizeof(t_ctn));
	n->c = c;
	if (str->cur == NULL)
	{
		str->cur = n;
		return (str_update(str));
	}
	ctn_place(str, n);
}
