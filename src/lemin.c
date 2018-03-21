/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 15:11:40 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	done(t_map *rooms, int ecode)
{
	ft_mapdtor(rooms, (t_dtor)ft_pfree, (t_dtor)lemin_roomdtor);
	exit(ecode);
}

int			main(void)
{
	t_map		rooms;
	uint32_t	ants;

	ft_mapctor(&rooms, g_strhash, sizeof(char *), sizeof(t_room));
	if (lemin_parse(&rooms, &ants))
		return (done(&rooms, EXIT_FAILURE));
	if (lemin_solve(&rooms, ants))
		return (done(&rooms, EXIT_FAILURE));
	return (done(&rooms, EXIT_SUCCESS));
}
