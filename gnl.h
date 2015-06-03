/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 09:09:07 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/02 11:06:45 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFF_SIZE 5000
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

int	gnl(int const fd, char **line);

#endif
