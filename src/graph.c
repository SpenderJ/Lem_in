/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/21 19:32:22 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	dumpvertex(t_lemin *lemin, t_map *graph)
{
	size_t		it;
	t_vertex	*v;
	t_vertex	**edge;

	it = 0;
	while (it < graph->cap)
		if (!(graph->bucks[it++] & BUCKET_BOTH))
		{
			if ((v = (t_vertex *)graph->vals + it - 1)->kind == VERTEX_NONE)
				ft_dprintf(lemin->output, "%s %d %d\n", v->id, v->x, v->y);
		}
	it = 0;
	while (it < graph->cap)
		if (!(graph->bucks[it++] & BUCKET_BOTH))
		{
			v = (t_vertex *)graph->vals + it - 1;
			if ((edge = ft_vecbeg(&v->edges)))
				while (edge < (t_vertex **)ft_vecend(&v->edges))
				{
					ft_dprintf(lemin->output, "%s-%s\n", v->id, (*edge)->id);
					++edge;
				}
		}
}

int			lemin_dump(t_lemin *lemin, t_map *graph, int ants)
{
	size_t		it;
	t_vertex	*v;

	it = 0;
	while (it < graph->cap)
		if (!(graph->bucks[it++] & BUCKET_BOTH))
		{
			if ((v = (t_vertex *)graph->vals + it - 1)->kind == VERTEX_START)
				lemin->start = v; //todo: check for duplicate start
			else if (v->kind == VERTEX_END)
				lemin->end = v; //todo: check for duplicate end
		}
	if (!lemin->start || !lemin->end)
	{
		if (lemin->options & OPT_VERB)
			ft_fprintf(g_stderr, "%s: No start/end rooms\n", lemin->prg);
		return (NOP);
	}
	ft_dprintf(lemin->output, "%d\n##start\n%s %d %d\n##end\n%s %d %d\n",
		ants, lemin->start->id, lemin->start->x, lemin->start->y,
		lemin->end->id, lemin->end->x, lemin->end->y);
	dumpvertex(lemin, graph);
	return (YEP);
}
