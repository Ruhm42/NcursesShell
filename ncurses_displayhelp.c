/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_displayhelp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 09:51:08 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/06 10:21:55 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

void	display_help(t_ncurses *nc)
{
	if (!nc->help)
		return ;
	attron(COLOR_PAIR(1));
	nc_carriage_return(nc);
	nc_write_ptr(nc, nc->help);
	nc_carriage_return(nc);
	attroff(COLOR_PAIR(1));
}
