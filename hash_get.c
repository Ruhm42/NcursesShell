/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 11:42:03 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/05 16:00:38 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_val	*hash_get(t_map *map, t_key *key)
{
	size_t	index;
	size_t	start;

	index = hash_get_index(map, key);
	start = index;
	while (!cell_is_free(&(map->data[index]))
		&& map->methods.cmp_key(key, map->data[index].key))
	{
		if ((index = (index + 1) % map->sz) == start)
			return (NULL);
	}
	return (map->data[index].val);
}

void	hash_del(t_map *map, t_key *key)
{
	size_t	index;
	size_t	start;

	index = hash_get_index(map, key);
	start = index;
	while (!cell_is_free(&(map->data[index]))
		&& map->methods.cmp_key(key, map->data[index].key))
	{
		if ((index = (index + 1) % map->sz) == start)
			return ;
	}
	cell_delete(map, &(map->data[index]));
	map->cur_sz -= 1;
}
