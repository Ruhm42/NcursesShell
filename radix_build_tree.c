/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_build_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 15:00:38 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 15:08:42 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

t_rdx	*new_node(char *str)
{
	t_rdx	*ret;

	if (!(ret = malloc(sizeof(t_rdx))))
		return (NULL);
	memset(ret, 0, sizeof(t_rdx));
	ret->st = true;
	if (str)
		ret->str = strdup(str);
	return (ret);
}
