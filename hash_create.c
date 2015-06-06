/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 18:04:20 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/05 16:02:40 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void	hash_rehash(t_map *map)
{
	t_cell			*data;
	size_t			i;
	size_t			sz;

	data = map->data;
	sz = map->sz;
	hash_create(map, map->sz * 2);
	i = 0;
	while (i < sz)
	{
		if (data[i].key)
		{
			hash_put(map, data[i].key, data[i].val);
			cell_delete(map, &(data[i]));
		}
		i++;
	}
	free(data);
}

void	hash_create(t_map *map, unsigned int sz)
{
	map->sz = sz;
	map->cur_sz = 0;
	if (!(map->data = malloc(sizeof(t_cell) * sz)))
		return ;
	memset(map->data, 0, sizeof(t_cell) * sz);
}
