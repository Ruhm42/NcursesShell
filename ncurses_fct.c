/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 13:47:54 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 18:10:45 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

void	nc_fct_init(t_fct *fct, int k, void (*f)(void *))
{
	fct->k = k;
	fct->call = f;
}

bool	nc_fct_exec(t_fct *fct, int k, void *arg)
{
	int	i;

	i = -1;
	while (++i < TAB_SIZE)
	{
		if (fct[i].k == k)
		{
			fct[i].call(arg);
			return (true);
		}
	}
	return (false);
}

void	nc_up(void *arg)
{
	t_ncurses	*nc;

	nc = arg;
	if (!nc->hist)
		return ;
	if (!nc->cur_hist)
	{
		nc->cur_hist = nc->hist;
		nc_add_history(&(nc->hist), nc->str.cur);
		nc->str.cur = NULL;
		nc->str.sz = 0;
		nc->str.pos = 0;
	}
	else if (nc->cur_hist->next)
		nc->cur_hist = nc->cur_hist->next;
	else
		return ;
	nc_attrib_history(&(nc->str), (t_ctn*)nc->cur_hist->str);
}

void	nc_down(void *arg)
{
	t_ncurses	*nc;

	nc = arg;
	if (!nc->cur_hist)
		return ;
	if (nc->cur_hist->prev)
	{
		nc->cur_hist = nc->cur_hist->prev;
		nc_attrib_history(&(nc->str), (t_ctn*)nc->cur_hist->str);
	}
}
