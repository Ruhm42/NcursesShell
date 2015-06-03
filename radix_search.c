/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:06:13 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 13:52:16 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix.h"

char		*rdx_find_prefix(t_rdx *root, char *str)
{
	unsigned int	sz;

	if (!root || !str || !str[0])
		return (NULL);
	root = root->down;
	while (root)
	{
		if (!min_strncmp(root->str, str, &sz))
		{
			if ((str + sz)[0])
				return (join_free(root->str, rdx_find_prefix(root, str + sz)));
			else
				return (strdup(root->str));
		}
		root = root->next;
	}
	return (NULL);
}

static void	clear_str(char **str)
{
	if (!(*str))
		return ;
	free(*str);
	*str = NULL;
}

static void	rdx_find_all(t_search *s, t_rdx *node, char *concat, char *prefix)
{
	unsigned int	sz;

	node = node->down;
	if (!node || !node->str || !node->str[0])
		return (clear_str(&concat));
	while (node)
	{
		if (!prefix || !prefix[0])
		{
			if (node->st)
			{
				wrap_build(&(s->start), &(s->cur),
					join_safe(concat, node->str));
			}
			rdx_call_back(s, node, concat, prefix);
		}
		else if (!min_strncmp(prefix, node->str, &sz))
		{
			rdx_call_back(s, node, concat, prefix + sz);
			return (clear_str(&concat));
		}
		node = node->next;
	}
	return (clear_str(&concat));
}

void		rdx_call_back(t_search *s, t_rdx *node, char *concat, char *prefix)
{
	if (!concat)
		rdx_find_all(s, node, strdup(node->str), prefix);
	else
		rdx_find_all(s, node, join_safe(concat, node->str), prefix);
}

void		rdx_search(t_search *s, char *target)
{
	if (!s->tree)
		return ;
	wrap_free(&(s->start), &(s->cur));
	clear_str(&(s->prefix));
	if ((s->prefix = rdx_find_prefix(s->tree, target)))
		rdx_find_all(s, s->tree, NULL, s->prefix);
}
