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

static void	dumprooms(t_map *rooms)
{
	size_t it;
	t_room *room;
	t_room **link;

	it = 0;
	while (it < rooms->cap)
		if (!(rooms->bucks[it++] & BUCKET_BOTH))
		{
			if ((room = (t_room *)rooms->vals + it - 1)->kind == ROOM_NONE)
				ft_printf("%s %d %d\n", room->id, room->x, room->y);
		}
	it = 0;
	while (it < rooms->cap)
		if (!(rooms->bucks[it++] & BUCKET_BOTH))
		{
			room = (t_room *)rooms->vals + it - 1;
			if ((link = ft_vecbeg(&room->links)))
				while (link < (t_room **)ft_vecend(&room->links))
				{
					ft_printf("%s-%s\n", room->id, (*link)->id);
					++link;
				}
		}
}

static void	doublelink(t_map *rooms)
{
	size_t it;
	t_room *room;
	t_room **link;

	it = 0;
	while (it < rooms->cap)
		if (!(rooms->bucks[it++] & BUCKET_BOTH))
		{
			room = (t_room *)rooms->vals + it - 1;
			if ((link = ft_vecbeg(&room->links)))
				while (link < (t_room **)ft_vecend(&room->links))
				{
					if (!lemin_linked(*link, room))
						*(t_room **)ft_vecpush(&(*link)->links) = room;
				}
		}
}

static int	dump(t_lemin *lemin, t_map *rooms, int ants)
{
	size_t it;
	t_room *room;

	it = 0;
	while (it < rooms->cap)
		if (!(rooms->bucks[it++] & BUCKET_BOTH))
		{
			if ((room = (t_room *)rooms->vals + it - 1)->kind == ROOM_START)
				lemin->start = room;
			else if (room->kind == ROOM_END)
				lemin->end = room;
		}
	if (!lemin->start || !lemin->end)
	{
		if (lemin->options & OPT_VERB)
			ft_fprintf(g_stderr, "%s: No start/end rooms\n.", lemin->prg);
		return (NOP);
	}
	ft_printf("%d\n##start\n%s %d %d\n##end\n%s %d %d\n",
		ants, lemin->start->id, lemin->start->x, lemin->start->y,
		lemin->end->id, lemin->end->x, lemin->end->y);
	dumprooms(rooms);
	doublelink(rooms);
	return (YEP);
}

int		lemin_solve(t_lemin *lemin, t_map *rooms, int ants)
{
	if (dump(lemin, rooms, ants))
		return (NOP);
	return (YEP);
}
