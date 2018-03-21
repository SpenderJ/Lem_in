/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin/room.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:46:24 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 18:55:26 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_ROOM_H
# define LEMIN_ROOM_H

# include <libft.h>

enum			e_room
{
	ROOM_NONE,
	ROOM_START,
	ROOM_END
};

typedef struct	s_room
{
	uint8_t		kind;
	char		*id;
	int			x;
	int			y;
	t_vec		links;
}				t_room;

/*
** Construct a `room`.
** @param room   The room to initialize
*/
extern void		lemin_roomctor(t_room *room);

/*
** Deconstruct a `room`.
** Does not free the room id, it will be freed on the rooms hash map
** deconstruction.
** @param room   The room to destroy
*/
extern void		lemin_roomdtor(t_room *room);

/*
** Try to add a `room` to the `rooms` hash map.
** @param rooms  The rooms hash map
** @param room   The room to add
** @return       `NOP`(1) if already exists, `YEP`(0) otherwise
*/
extern int		lemin_roomadd(t_map *rooms, t_room room);

/*
** Try to link two rooms using there ids.
** @param rooms  The rooms hash map
** @param from   The from room id to link
** @param to     The to room id to link
** @return       `NOP`(1) if already one the ids `from` or `to` does not exists
**               in the `rooms`, `NOP`(1) on duplicate links, `YEP`(0) otherwise
*/
extern int		lemin_linkadd(t_map *rooms, char const *from, char const *to);

extern int		lemin_linked(t_room *from, t_room *to);

#endif
