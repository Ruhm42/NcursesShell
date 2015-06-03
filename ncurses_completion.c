/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_completion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 15:18:39 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 14:45:58 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

void		clear_str(char **str)
{
	if (!(*str))
		return ;
	free(*str);
	*str = NULL;
}

void		nc_reset_completion(t_ncurses *nc)
{
	if (nc->search.target)
	{
		clear_str(&(nc->search.target));
		nc->str.pos_tab = 0;
	}
}

static char	*select_suggest(t_search *search, bool state)
{
	char	*ptr;

	if (!search->prefix)
		return (NULL);
	if (state && strcmp(search->target, search->prefix))
		return (search->prefix);
	if (search->cur)
	{
		ptr = search->cur->str;
		search->cur = search->cur->next;
		return (ptr);
	}
	return (NULL);
}

void		nc_tab(void *arg)
{
	t_ncurses			*nc;
	static t_ctn		*end = NULL;
	static unsigned int	left = 0;
	char				*suggest;

	nc = arg;
	if (!nc->search.tree)
		return ;
	if (!nc->search.target)
	{
		nc->str.pos_tab = nc->str.pos;
		if (!(nc->search.target = ncurses_str_extract(&(nc->str), &end, &left)))
			return ;
		rdx_search(&(nc->search), nc->search.target);
		suggest = select_suggest(&(nc->search), true);
	}
	else
		suggest = select_suggest(&(nc->search), false);
	if (suggest)
	{
		reset_extracted_str(&(nc->str), end, left);
		ncurses_str_import(&(nc->str), suggest, end, &left);
	}
}
