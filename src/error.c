/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/21 19:32:22 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		verror(t_lemin *lemin, char const *fmt, va_list ap)
{
	if (lemin->options & OPT_VERB)
	{
		if (isatty(STDERR_FILENO))
			ft_fprintf(g_stderr, COLOR_BRED"%s: "COLOR_RESET, lemin->prg);
		else
			ft_fprintf(g_stderr, "%s: ", lemin->prg);
		ft_vfprintf(g_stderr, fmt, ap);
	}
	else
		ft_fprintf(g_stderr, "ERROR\n");
}

int				lemin_error(t_lemin *lemin, char const *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	verror(lemin, fmt, ap);
	va_end(ap);
	return (OUF);
}
