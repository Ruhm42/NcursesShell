/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 17:27:27 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 17:59:51 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

void		nc_left(void *arg)
{
	t_ncurses	*nc;

	nc = (t_ncurses*)arg;
	if (nc->str.pos <= 0)
		return ;
	nc->str.pos--;
}

void		nc_right(void *arg)
{
	t_ncurses	*nc;

	nc = (t_ncurses*)arg;
	if (nc->str.pos >= nc->str.sz)
		return ;
	nc->str.pos++;
}

void		nc_del(void *arg)
{
	t_ncurses		*nc;
	t_ctn			*ptr;
	unsigned int	i;

	nc = (t_ncurses*)arg;
	ptr = nc->str.cur;
	i = 0;
	while (i < nc->str.pos - 1 && ptr)
	{
		ptr = ptr->next;
		i++;
	}
	if (!ptr)
		return ;
	if (ptr->prev)
		ptr->prev->next = ptr->next;
	else
		nc->str.cur = ptr->next;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	nc->str.pos--;
	nc->str.sz--;
	free(ptr);
}

void		nc_enter(void *arg)
{
	t_ncurses	*nc;

	nc = (t_ncurses*)arg;
	nc->input = rmb_create(&(nc->remember), &(nc->hist),
		&(nc->str), nc->prompt);
}
