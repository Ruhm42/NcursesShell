/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:57:46 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/05 15:59:23 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void	cell_delete(t_map *map, t_cell *cell)
{
	map->methods.del_key(&(cell->key));
	map->methods.del_val(&(cell->val));
}

bool	cell_is_free(t_cell *cell)
{
	return (!cell->key);
}

void	hash_print(t_map *map)
{
	size_t	i;

	i = 0;
	printf("map : size = %lu, nb of valid cells = %lu | %lu : %lu\n",
		map->sz, map->cur_sz, map->cur_sz, map->sz);
	while (i < map->sz)
	{
		if (!cell_is_free(&(map->data[i])))
			printf("cell nb %lu, %s == %s\n",
				i, map->data[i].key, map->data[i].val);
		i++;
	}
}
