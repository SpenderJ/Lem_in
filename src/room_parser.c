/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:58:19 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 20:06:44 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	gnl(int const fd, char **line)
{
	static t_sds	c[OPEN_MAX];
	char			b[FT_PAGE_SIZE + 1];
	ssize_t			i;
	char			*eol;

	eol = NULL;
	if (line && *line)
		free(*line);
	if (!line || fd < 0 || fd > OPEN_MAX)
		return (-1);
	while ((!c[fd].len || (eol || !(eol = ft_strchr(c[fd].buf, '\n')))))
		if ((i = read(fd, b, FT_PAGE_SIZE)) == 0)
			break ;
		else if (i == -1 || !(eol = ft_sdsmpush(c + fd, b, (size_t)i)))
			return (-1);
		else if ((eol = ft_strchr(eol, '\n')))
			break ;
	if (!(i = eol ? (eol - c[fd].buf + 1) : (ssize_t)c[fd].len))
		return (ft_pfree((void **)&c[fd].buf));
	if (!(*line = malloc((size_t)(i + (eol ? 1 : 0)) * sizeof(char))))
		return (-1);
	(*line)[ft_sdsnsht(c + fd, (size_t)i, *line) - (eol ? 1 : 0)] = '\0';
	return (1);
}

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

static int	start_end(char *op, t_room *room)
{
	int		ret;

	if (ft_strcmp(&op[2], "end") == 0)
	{
		dprintf(2, "END PUSHED\n");
		room->kind = ROOM_END;
	}
	else if (ft_strcmp(&op[2], "start") == 0)
	{
		dprintf(2, "START PUSHED\n");
		room->kind = ROOM_START;
	}
	if ((ret = gnl(FD_IN, &op)) != 1)
		dprintf(2, "Gnl return value >>> %d\n", ret);
	return (0);
}

int			push_rooms(char *op, t_map *rooms)
{
	int		i;
	t_room	room;

	lemin_roomctor(&room);
	if ((i = -1) == -1 && op && op[0] == '#' && op[1] == '#')
		start_end(op, &room);
	else
		room.kind = ROOM_NONE;
	if (!op || op[0] == ' ' || op[0] == '\0' || op[0] == 'L' || op[0] == '#')
		return (INVALID_ROOM_NAME);
	dprintf(2, "alive\n");
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
	lemin_roomadd(rooms, room);
	return (SUCCESS);
}
