/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:51:54 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 15:11:47 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>

# ifndef FD_OUT
#  define FD_OUT 0
# endif

/* All these defines are made for the return value of the parsing function.
** 0 Mean the file is well formatted, otherwise an error is returned and these
** appropriate error message will be sent
*/

# ifndef SUCCESS_PARSING
#  define SUCCESS_PARSING 0
# endif

# ifndef NO_ANT_NUMBER
#  define NO_ANT_NUMBER 1
# endif

int parsing(void);

#endif
