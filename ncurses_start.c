/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:53:17 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 16:47:20 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		init_fcts(t_ncurses *nc)
{
	nc_fct_init(&(nc->fcts[0]), KEY_LEFT, nc_left);
	nc_fct_init(&(nc->fcts[1]), KEY_RIGHT, nc_right);
	nc_fct_init(&(nc->fcts[2]), '\n', nc_enter);
	nc_fct_init(&(nc->fcts[3]), DEL_K, nc_del);
	nc_fct_init(&(nc->fcts[4]), KEY_UP, nc_up);
	nc_fct_init(&(nc->fcts[5]), KEY_DOWN, nc_down);
	nc_fct_init(&(nc->fcts[6]), '\t', nc_tab);
}

bool			nc_start(t_ncurses *nc)
{
	memset(nc, 0, sizeof(t_ncurses));
	memset(&(nc->str), 0, sizeof(t_str));
	if (!(nc->win = initscr()))
		return (false);
	noecho();
	keypad(nc->win, TRUE);
	cbreak();
	nodelay(nc->win, TRUE);
	getmaxyx(nc->win, nc->sz.y, nc->sz.x);
	nc->stopped = false;
	init_fcts(nc);
	nc_display(nc);
	return (true);
}
