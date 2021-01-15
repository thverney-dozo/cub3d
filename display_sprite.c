/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 01:11:58 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 06:44:49 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_disp_sp(t_map *tab, int i)
{
	while (i < tab->len.nb_sp)
	{
		calc_dist_sp(tab, i);
		calc_dist_sp_two(tab);
		while (tab->len.stripe < tab->drw_endx)
		{
			tab->len.tex_x = (int)(256 * (tab->len.stripe - (-tab->spwidth
			/ 2 + tab->spscreenx)) * tab->len.texwidth / tab->spwidth)
			/ 256;
			if (tab->trsformy > 0 && tab->len.stripe > 0 && tab->len.stripe
			< tab->len.w && tab->trsformy < tab->len.zbuff[tab->len.stripe])
			{
				display_ray_sp(tab);
			}
			tab->len.stripe++;
		}
		i++;
	}
}

void	sort_sprite(t_map *tab, int i)
{
	i = 0;
	dist_sprite(tab, i);
	while (i < tab->len.nb_sp)
	{
		if (tab->sprite[i].dist < tab->sprite[i + 1].dist
		&& tab->sprite[i + 1].indic)
		{
			swap_sprite(tab, i);
			i = 0;
		}
		i++;
	}
	i = 0;
	calc_disp_sp(tab, i);
}

void	display_sprites(t_map *tab)
{
	tab->len.x_tmp = 0.0;
	tab->len.y_tmp = 0.0;
	tab->len.d_tmp = 0.0;
	if (tab->len.nb_sp > 0)
	{
		sort_sprite(tab, 0);
	}
}
