/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:51:54 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/21 19:00:47 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_PARSER_H
# define LEMIN_PARSER_H

# include <stdlib.h>
# include <unistd.h>

# include "vertex.h"

# define COORD_LIMIT 500

extern int	lemin_parse(t_lemin *lemin, t_map *graph, int *ants);

#endif
