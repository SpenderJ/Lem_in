/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 18:58:49 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	usage(char *av[])
{
	ft_printf(
		"usage: %s [-hvs] [-i <filename>] [-o <filename>]\n"
		"  -h              Show this help.\n",
		"  -s              Execute the program step by step (imply -v).\n",
		"  -v              Output some verbose to the standard error output.\n",
		"  -i <filename>   Use `filename` as input.\n",
		"  -o <filename>   Output standard output to `filename`.\n",
		av[0]);
	return (EXIT_FAILURE);
}


static int	done(t_map *rooms, int ecode)
{
	ft_mapdtor(rooms, (t_dtor)ft_pfree, (t_dtor)lemin_roomdtor);
	exit(ecode);
}

static int	tryopen(t_lemin *lemin, char const *filename, int flags, int *out)
{
	int fd;

	if ((fd = open(filename, flags, 0666)) < 0)
	{
		if (lemin->options & OPT_VERB)
			ft_fprintf(g_stderr, "%s: %s: %m\n", lemin->prg, filename);
		return (WUT);
	}
	*out = fd;
	return (YEP);
}

static int	opt(t_lemin *l, int ac, char *av[])
{
	int opt;

	g_optind = 1;
	l->prg = av[0];
	while ((opt = ft_getopt(ac, av, "hvsi:o:")) != WUT)
		if (opt == 'h')
			return (NOP);
		else if (opt == 'v')
			l->options |= OPT_VERB;
		else if (opt == 's')
			l->options |= OPT_STEP;
		else if (opt == 'i')
		{
			if (tryopen(l, g_optarg, O_RDONLY, &l->input))
				return (NOP);
		}
		else if (opt == 'o')
		{
			if (tryopen(l, g_optarg, O_WRONLY | O_CREAT | O_TRUNC, &l->output))
				return (NOP);
		}
		else
			return (NOP);
	return (g_optind < ac);
}

int			main(int ac, char *av[])
{
	t_lemin		lemin;
	t_map		rooms;
	int			ants;

	ft_bzero(&lemin, sizeof(t_lemin));
	if (opt(&lemin, ac, av))
	{
		if ((g_optind < ac) && (lemin.options & OPT_VERB))
			ft_fprintf(g_stderr, "%s: %s: Unexpected argument.\n",
				lemin.prg, av[g_optind]);
		return (usage(av));
	}
	ft_mapctor(&rooms, g_strhash, sizeof(char *), sizeof(t_room));
	if (lemin_parse(&rooms, &ants))
		return (done(&rooms, EXIT_FAILURE));
	if (lemin_solve(&rooms, ants))
		return (done(&rooms, EXIT_FAILURE));
	return (done(&rooms, EXIT_SUCCESS));
}
