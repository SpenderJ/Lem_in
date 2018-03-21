/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin/room.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:46:24 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 16:55:20 by juspende         ###   ########.fr       */
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
	char const	*id;
	int			x;
	int			y;
	t_vec		links;
}				t_room;

extern int	lemin_roomctor(t_room *room);
extern void	lemin_roomdtor(t_room *room);
extern int	lemin_roomadd(t_map *rooms, t_room room);
extern int	lemin_linkadd(t_map *rooms, char const *from, char const *to);

#endif
