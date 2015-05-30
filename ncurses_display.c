/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 14:52:36 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 18:11:51 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		nc_write_ptr(t_ncurses *nc, char *ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		waddch(nc->win, (unsigned int)ptr[i]);
}

static void		nc_display_remember(t_ncurses *nc, t_rmb *rmb)
{
	t_rmb	*tmp;

	tmp = rmb;
	while (tmp)
	{
		nc_write_ptr(nc, tmp->str);
		nc_carriage_return(nc);
		tmp = tmp->next;
	}
}

static int		eval_line(t_ncurses *nc, unsigned int sz)
{
	int	ret;

	ret = sz / nc->sz.x;
	if (sz % nc->sz.x > 0)
		ret++;
	return (ret);
}

static t_rmb	*find_first(t_ncurses *nc, t_rmb *rmb)
{
	unsigned int	i;

	if (!rmb)
		return (NULL);
	i = eval_line(nc, strlen(nc->prompt) + nc->str.sz) + 1;
	while (rmb->next)
		rmb = rmb->next;
	while (rmb->prev && i < nc->sz.y - 2)
	{
		i += eval_line(nc, strlen(rmb->str));
		rmb = rmb->prev;
	}
	if (i > nc->sz.y - 2)
		rmb = rmb->next;
	return (rmb);
}

void			nc_display(t_ncurses *nc)
{
	t_ctn			*ptr;
	unsigned int	len;
	t_pt			init;

	nc_getprompt(nc);
	len = nc->str.sz;
	wclear(nc->win);
	wmove(nc->win, 0, 0);
	ptr = nc->str.cur;
	nc_display_remember(nc, find_first(nc, nc->remember));
	nc_write_ptr(nc, nc->prompt);
	getyx(nc->win, init.y, init.x);
	while (ptr)
	{
		waddch(nc->win, ptr->c);
		ptr = ptr->next;
	}
	wmove(nc->win, init.y + (init.x + nc->str.pos) / nc->sz.x,
		(init.x + nc->str.pos) % nc->sz.x);
}
