/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:58:19 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 18:58:51 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	get_coord(char *op, int i, t_room *room)
{
	int		error;

	error = 0;
	if (op[i++] == '\0')
		error = FALSE;
	if (error != FALSE && op[i] == '\0')
		error = FALSE;
	if (error != FALSE && ((room->x = ft_atoi(&op[i])) > COORD_LIMIT || errno))
		error = FALSE;
	while (error != FALSE && op[i] != '\0' && !ft_isspace(op[i]))
		if (op[i] < '0' || op[i] > '9')
			error = FALSE;
	if (error != FALSE && op[i++] == '\0')
		error = FALSE;
	if (error != FALSE && ((room->y = ft_atoi(&op[i])) > COORD_LIMIT || errno))
		error = FALSE;
	while (error != FALSE && op[i] != '\0')
		if (op[i] < '0' || op[i] > '9')
			error = FALSE;
	if (error == FALSE)
	{
		free(op);
		free(room->id);
	}
	return (error == FALSE ? FALSE : TRUE);
}

int			push_rooms(char *op, t_map *rooms)
{
	int		i;
	t_room	room;

	i = -1;
	lemin_roomctor(&room);
	if (op && op[0] == '#' && op[1] == '#')
		return (0); // SPECIAL TO EDIT
	if (!op || op[0] == ' ' || op[0] == '\0' || op[0] == 'L' || op[0] == '#')
		return (INVALID_ROOM_NAME);
	while (op[++i] != '\0' && !ft_isspace(op[i]))
		;
	if (op[i] == '\0')
		return (NO_POSITION);
	if ((room.id = malloc(sizeof(char) * (i + 1))) == NULL)
		return (MALLOC_FAILED);
	i = -1;
	while (op[++i] != '\0' && !ft_isspace(op[i]))
		room.id[i] = op[i];
	room.id[i] = '\0';
	if (get_coord(op, i, &room) != SUCCESS)
		return (WRONG_POSITION);
	room.kind = ROOM_NONE;
	lemin_roomadd(rooms, room);
	return (SUCCESS);
}
