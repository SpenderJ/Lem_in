/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:51:54 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 19:00:47 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_PARSER_H
# define LEMIN_PARSER_H

# include <stdlib.h>
# include <unistd.h>

# include "room.h"

# ifndef FD_IN
#  define FD_IN STDIN_FILENO
# endif

# ifndef EXIT
#  define EXIT 84
# endif

# ifndef TRUE
#  define TRUE 0
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FALSE
#  define FALSE 1
# endif

# ifndef COORD_LIMIT
#  define COORD_LIMIT 500
# endif

/*
** All these defines are made for the return value of the parsing function.
** 0 Mean the file is well formatted, otherwise an error is returned and these
** appropriate error message will be sent
*/

# ifndef SUCCESS_PARSING
#  define SUCCESS_PARSING 0
# endif

# ifndef NO_ANT_NUMBER
#  define NO_ANT_NUMBER (-1)
# endif

# ifndef TOO_MANY_ANT
#  define TOO_MANY_ANT (-2)
# endif

# ifndef NO_ANT
#  define NO_ANT (-3)
# endif

# ifndef INVALID_ROOM_NAME
#  define INVALID_ROOM_NAME (-4)
# endif

# ifndef NO_POSITION
#  define NO_POSITION (-5)
# endif

# ifndef WRONG_POSITION
#  define WRONG_POSITION (-6)
# endif

# ifndef INVALID_COORD
#  define INVALID_COORD (-7)
# endif

# ifndef MALLOC_FAILED 
#  define MALLOC_FAILED (-8)
# endif

# ifndef NO_ROOM
#  define NO_ROOM (-9)
# endif

extern int	lemin_parse(t_map *rooms, int *ants);
extern int	push_rooms(char *op, t_map *rooms);

#endif
