/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 04:45:53 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 04:53:37 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	list_to_tab(t_map *tab)
{
	t_sp	*tmp;
	t_sp	*temp;
	int		i;

	i = 0;
	if (!(tab->sprite = (t_sprite*)malloc(sizeof(t_sprite)
	* (tab->len.nb_sp + 1))))
		return ;
	tmp = tab->sp;
	while (tmp)
	{
		tab->sprite[i].indic = 1;
		tab->sprite[i].x = tmp->x;
		tab->sprite[i].y = tmp->y;
		tab->sprite[i].dist = tmp->dist;
		i++;
		temp = tmp->next;
		free(tmp);
		tmp = temp;
	}
	tab->sprite[i].indic = 0;
}

void	list_to_dist(t_map *tab)
{
	int		i;
	t_sp	*tmp;

	tmp = tab->sp;
	i = 0;
	while (i < tab->len.nb_sp)
	{
		tmp->dist = ((tab->pos_x - tmp->x) *
		(tab->pos_x - tmp->x) + (tab->pos_y - tmp->y) *
		(tab->pos_y - tmp->y));
		tmp = tmp->next;
		i++;
	}
	list_to_tab(tab);
}

int		ft_sps_stock(double x, double y, t_map *tab)
{
	tab->new = NULL;
	tab->tmp = NULL;
	if (tab->sp == NULL)
	{
		if (!(tab->sp = (t_sp*)malloc(sizeof(t_sp))))
			return (0);
		tab->sp->x = x + 0.5;
		tab->sp->y = y + 0.5;
		tab->sp->next = NULL;
	}
	else
	{
		if (!(tab->new = (t_sp*)malloc(sizeof(t_sp))))
			return (0);
		tab->tmp = tab->sp;
		while (tab->tmp->next)
			tab->tmp = tab->tmp->next;
		tab->tmp->next = tab->new;
		tab->new->x = x + 0.5;
		tab->new->y = y + 0.5;
		tab->new->next = NULL;
	}
	return (1);
}
