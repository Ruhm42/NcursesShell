/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 11:22:02 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 18:09:49 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		nc_place_history(t_str *str, t_ctn *n, t_ctn **start)
{
	if (!str->cur)
	{
		str->cur = n;
		*start = n;
	}
	else
	{
		(*start)->next = n;
		n->prev = *start;
		*start = n;
	}
}

void			nc_attrib_history(t_str *str, t_ctn *ev)
{
	t_ctn		*ptr;
	t_ctn		*n;
	t_ctn		*start;

	str_clear(str);
	if (!(ptr = ev))
		return ;
	while (ptr)
	{
		if (!(n = malloc(sizeof(t_ctn))))
			return ;
		memset(n, 0, sizeof(t_ctn));
		n->c = ptr->c;
		nc_place_history(str, n, &start);
		ptr = ptr->next;
		str->sz++;
	}
	str->pos = str->sz;
}

void			nc_add_history(t_rmb **lst, t_ctn *ptr)
{
	t_rmb			*n;

	if (!(n = malloc(sizeof(t_rmb))))
		return ;
	memset(n, 0, sizeof(t_rmb));
	n->str = (char *)ptr;
	n->next = *lst;
	if (*lst)
		(*lst)->prev = n;
	*lst = n;
}

void			nc_reset_history(t_ncurses *nc)
{
	t_rmb	*del;

	if (nc->cur_hist)
	{
		del = nc->hist;
		ctn_del((t_ctn*)(del->str));
		nc->hist = nc->hist->next;
		if (nc->hist)
			nc->hist->prev = NULL;
		free(del);
		nc->cur_hist = NULL;
	}
}
