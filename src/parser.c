/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:53:12 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 16:55:13 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			gnl(int const fd, char **line)
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

static int				is_commentary(char *str)
{
	int		i;

	i = 0;
	if (str && str[0] == '#' && str[1] != '#')
		return (TRUE);
	else
		return (FALSE);
}

static int				is_ant(char *str)
{
	int		i;
	int		ants;

	i = -1;
	if (!str)
		return (NO_ANT_NUMBER);
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (NO_ANT_NUMBER);
	ants = ft_atoi(str);
	if (ants == 0)
		return (NO_ANT);
	if (errno)
		return (TOO_MANY_ANT);
	return (ants);
}

extern int				lemin_parse(t_map *rooms, uint32_t *ants)
{
	char	*op;
	int		end;
	int		ants;
	int		rooms;

	op = NULL;
	end = 0;
	ants = 0;
	rooms = 0;
	while (gnl(FD_IN, &op) == 1 && end != EXIT)
		if (is_commentary(op) == FALSE)
			end = EXIT;
	if ((ants = is_ant(op)) < 0)
		return (ants); // ERROR HANDLING TO DO
	while (gnl(FD_IN, &op) == 1 && end != EXIT)
		if (is_commentary(op) == TRUE)
			end = 0;
		else if (push_rooms(op) == SUCCESS)
	return (0);
}
