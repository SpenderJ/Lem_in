/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:51:54 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 15:11:47 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_LEMIN_H
# define LEMIN_LEMIN_H

# include "room.h"

#define OPT_VERB (1 << 0)
#define OPT_STEP (1 << 1)

typedef struct	s_lemin
{
	char const	*prg;
	int			input;
	int			output;
	int			options;
	t_room		*start;
	t_room		*end;
}				t_lemin;

#endif
