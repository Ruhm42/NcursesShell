/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:41:42 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/05 16:00:14 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static void		hash_insert(t_map *map, t_cell *cell, t_key *key, t_val *val)
{
	cell->key = map->methods.dup_key(key);
	cell->val = map->methods.dup_val(val);
	map->cur_sz += 1;
}

int				hash_put(t_map *map, t_key *key, t_val *val)
{
	size_t	index;
	size_t	start;

	if (!key || !val)
		return (MAP_ERROR);
	if (map->cur_sz >= map->sz)
	{
		hash_rehash(map);
		return (hash_put(map, key, val));
	}
	index = hash_get_index(map, key);
	start = index;
	while (1)
	{
		if (cell_is_free(&(map->data[index])))
			break ;
		if (!map->methods.cmp_key(key, map->data[index].key))
			return (MAP_EXIST);
		if ((index = (index + 1) % map->sz) == start)
			return (MAP_FULL);
	}
	hash_insert(map, &(map->data[index]), key, val);
	return (MAP_OK);
}

void			hash_update(t_map *map, t_key *key, t_val *val)
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
	map->methods.del_val(&(map->data[index].val));
	map->data[index].val = map->methods.dup_val(val);
}
