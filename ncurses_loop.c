/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:34:50 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 17:59:01 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static int	nc_event(t_ncurses *nc)
{
	int				key;
	t_pt			sz;

	key = getch();
	doupdate();
	getmaxyx(nc->win, sz.y, sz.x);
	if (nc->sz.y != sz.y || nc->sz.x != sz.x)
	{
		nc->sz.y = sz.y;
		nc->sz.x = sz.x;
		return (RESIZE_LIB_RES);
	}
	return (key);
}

void		nc_add(t_ncurses *nc, char *ins)
{
	rmb_add(&(nc->remember), ins);
	nc_display(nc);
}

void		nc_loop(t_ncurses *nc)
{
	int	k;

	k = 0;
	if (nc->input)
	{
		free(nc->input);
		nc->input = NULL;
	}
	if ((k = nc_event(nc)) == ESC || nc->stopped)
	{
		nc->stopped = true;
		return ;
	}
	if (k > 0)
	{
		if (!nc_fct_exec(nc->fcts, k, nc) && isprint(k))
		{
			ctn_create(&(nc->str), k);
			nc_reset_history(nc);
		}
		nc_display(nc);
	}
}
