/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 15:11:40 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin/solve.h"
#include "lemin/lemin.h"

void	dump(t_map *rooms, int ants)
{
	(void)rooms;
	(void)ants;
	ft_printf("");
}

int		lemin_solve(t_lemin *lemin, t_map *rooms, int ants)
{
	(void)lemin;
	dump(rooms, ants);
	return (YEP);
}
