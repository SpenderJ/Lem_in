/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 15:11:40 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin/room.h"

void		lemin_roomctor(t_room *room)
{
	ft_bzero(room, sizeof(t_room));
	ft_vecctor(&room->links, sizeof(t_room *));
}

void		lemin_roomdtor(t_room *room)
{
	ft_vecdtor(&room->links, NULL);
}

int			lemin_roomadd(t_map *rooms, t_room room)
{
	uint32_t it;

	if (ft_mapput(rooms, (void *)room.id, &it))
		return (NOP);
	((t_room *)rooms->vals)[it] = room;
	return (YEP);
}

static int	lemin_linkexists(t_room *from, t_room *to)
{
	t_room		**it;

	if ((it = ft_vecbeg(&from->links)))
		while (it < (t_room **)ft_vecend(&from->links))
		{
			if (!ft_strcmp((*it)->id, to->id))
				return (1);
			++it;
		}
	return (0);
}

int			lemin_linkadd(t_map *rooms, char const *from, char const *to)
{
	uint32_t	itf;
	uint32_t	itt;
	t_room		*roomf;
	t_room		*roomt;

	if (!ft_mapget(rooms, (void *)from, &itf))
		return (NOP);
	if (!ft_mapget(rooms, (void *)to, &itt))
		return (NOP);
	roomf = (t_room *)rooms->vals + itf;
	roomt = (t_room *)rooms->vals + itt;
	if (lemin_linked(roomf, roomt) || lemin_linked(roomt, roomf))
		return (NOP);
	*(t_room **)ft_vecpush(&roomf->links) = roomt;
	return (YEP);
}
