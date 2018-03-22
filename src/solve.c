/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 10:47:57 by juspende          #+#    #+#             */
/*   Updated: 2018/03/21 15:11:40 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin/solve.h"
#include "lemin/lemin.h"

static void	updatedist(t_lemin *lemin, size_t dist, t_vertex *v, t_vertex *prev)
{
	t_vertex **edge;
	t_vertex **end;

	if (dist > 500 || !(edge = ft_vecbeg(&v->edges)))
		return ;
	if (v->dist > dist)
		v->dist = dist;
	else
		return ;
	end = ft_vecend(&v->edges);
	while (edge < end)
	{
		if (!prev || *edge != prev)
			updatedist(lemin, dist + 1, *edge, v);
		++edge;
	}
}

static int	prepare(t_lemin *lemin, t_map *graph)
{
	size_t		it;
	t_vertex	*v;
	t_vertex	**edge;

	it = 0;
	while (it < graph->cap)
		if (!(graph->bucks[it++] & BUCKET_BOTH))
		{
			v = (t_vertex *)graph->vals + it - 1;
			if ((edge = ft_vecbeg(&v->edges)))
				while (edge < (t_vertex **)ft_vecend(&v->edges))
				{
					if (!lemin_edged(*edge, v))
						*(t_vertex **)ft_vecpush(&(*edge)->edges) = v;
					++edge;
				}
		}
	updatedist(lemin, 0, lemin->end, NULL);
	if (lemin->start->dist == UINT32_MAX || lemin->end->dist != 0)
		return (lemin_error(lemin, "Start and end room aren't linked\n"));
	return (YEP);
}

static void	move(t_lemin *lemin, t_vertex *v, t_vertex *prev)
{
	t_vertex	*path;
	t_vertex	**edge;
	t_vertex	**end;

	if (v->visited || !(edge = ft_vecbeg(&v->edges)) || lemin->end == v)
		return ;
	--edge;
	path = NULL;
	end = ft_vecend(&v->edges);
	v->visited = 1;
	while (++edge < end)
		if (!prev || prev != *edge)
		{
			if (!path || (*edge)->dist < path->dist)
				path = *edge;
			move(lemin, *edge, v);
		}
	v->visited = 0;
	if (!v->occupied || !path)
		return ;
	if (lemin->options & OPT_VERB)
		ft_dprintf(lemin->output, "%d[%s > %s] ", v->occupied, v->id, path->id);
	else
		ft_dprintf(lemin->output, "L%d-%s ", v->occupied, path->id);
	path->occupied = path == lemin->end ? path->occupied + 1 : v->occupied;
	v->occupied = 0;
}

static void	solve(t_lemin *lemin, int ants)
{
	t_vertex	**edge;
	t_vertex	**end;

	if (lemin->end->occupied == lemin->ants)
		return ;
	edge = (t_vertex **)ft_vecbeg(&lemin->start->edges) - 1;
	end = ft_vecend(&lemin->start->edges);
	if (ants < lemin->ants)
	{
		lemin->start->occupied = ++ants;
		move(lemin, lemin->start, NULL);
	}
	else
	{
		while (++edge < end)
			move(lemin, *edge, lemin->start);
	}
	ft_dprintf(lemin->output, "\n");
	solve(lemin, ants);
}

int			lemin_solve(t_lemin *lemin, t_map *graph, int ants)
{
	if (lemin_dump(lemin, graph, ants))
		return (NOP);
	if (prepare(lemin, graph))
		return (NOP);
	lemin->ants = ants;
	ft_dprintf(lemin->output, "\n");
	solve(lemin, 0);
	return (YEP);
}
