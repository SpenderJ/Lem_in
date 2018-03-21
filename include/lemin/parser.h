/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:51:54 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 16:55:15 by juspende         ###   ########.fr       */
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

<<<<<<< HEAD
# ifndef EXIT
#  define EXIT 84
# endif

# ifndef TRUE
#  define TRUE 0
# endif

# ifndef FALSE
#  define FALSE 1
# endif

/* All these defines are made for the return value of the parsing function.
=======
/*
** All these defines are made for the return value of the parsing function.
>>>>>>> 61fbee079ea89e89f7a63aa13a90623f179376a4
** 0 Mean the file is well formatted, otherwise an error is returned and these
** appropriate error message will be sent
*/

# ifndef SUCCESS_PARSING
#  define SUCCESS_PARSING 0
# endif

# ifndef NO_ANT_NUMBER
#  define NO_ANT_NUMBER -1
# endif

# ifndef TOO_MANY_ANT
#  define TOO_MANY_ANT -2
# endif

# ifndef NO_ANT
#  define NO_ANT -3
# endif

extern int	lemin_parse(t_map *rooms, uint32_t *ants);

#endif
