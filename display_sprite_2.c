/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprite_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 05:48:46 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 06:42:54 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dist_sprite(t_map *tab, int i)
{
	while (i < tab->len.nb_sp)
	{
		tab->sprite[i].dist = sqrt((double)((tab->pos_x
		- tab->sprite[i].x) *
		(tab->pos_x - tab->sprite[i].x) + (tab->pos_y
		- tab->sprite[i].y) *
		(tab->pos_y - tab->sprite[i].y)));
		i++;
	}
}

void	swap_sprite(t_map *tab, int i)
{
	tab->len.d_tmp = tab->sprite[i].dist;
	tab->sprite[i].dist = tab->sprite[i + 1].dist;
	tab->sprite[i + 1].dist = tab->len.d_tmp;
	tab->len.x_tmp = tab->sprite[i].x;
	tab->sprite[i].x = tab->sprite[i + 1].x;
	tab->sprite[i + 1].x = tab->len.x_tmp;
	tab->len.y_tmp = tab->sprite[i].y;
	tab->sprite[i].y = tab->sprite[i + 1].y;
	tab->sprite[i + 1].y = tab->len.y_tmp;
}

void	calc_dist_sp(t_map *tab, int i)
{
	tab->spritex = tab->sprite[i].x - tab->pos_x;
	tab->spritey = tab->sprite[i].y - tab->pos_y;
	tab->invdet = 1.0 / (tab->len.planx * sin(tab->angle
	* (M_PI / 180)) - cos(tab->angle * (M_PI / 180)) * tab->len.plany);
	tab->trsformx = tab->invdet * (sin(tab->angle * (M_PI / 180))
	* tab->spritex - cos(tab->angle * (M_PI / 180)) * tab->spritey);
	tab->trsformy = tab->invdet * (-tab->len.plany * tab->spritex
	+ tab->len.planx * tab->spritey);
	tab->vmv_screen = (int)(tab->dst_sp.width / tab->trsformy);
	tab->spscreenx = (int)((tab->len.w / 2) * (1 + tab->trsformx
	/ tab->trsformy));
	tab->spheight = abs((int)(tab->len.h / (tab->trsformy))) / 1;
	tab->drw_starty = (-tab->spheight / 2 + tab->len.h / 2) + tab->vmv_screen;
}

void	calc_dist_sp_two(t_map *tab)
{
	if (tab->drw_starty < 0)
		tab->drw_starty = 0;
	tab->drw_endy = (tab->spheight / 2 + tab->len.h / 2) + tab->vmv_screen;
	if (tab->drw_endy >= tab->len.h)
		tab->drw_endy = tab->len.h - 1;
	tab->spwidth = abs((int)(tab->len.h / (tab->trsformy))) / 1;
	tab->drw_startx = -tab->spwidth / 2 + tab->spscreenx;
	if (tab->drw_startx < 0)
		tab->drw_startx = 0;
	tab->drw_endx = tab->spwidth / 2 + tab->spscreenx;
	if (tab->drw_endx >= tab->len.w)
		tab->drw_endx = tab->len.w - 1;
	tab->len.stripe = tab->drw_startx;
	tab->len.texwidth = tab->dst_sp.width;
}

void	display_ray_sp(t_map *tab)
{
	tab->len.y = tab->drw_starty;
	while (tab->len.y < tab->drw_endy)
	{
		tab->len.d = (tab->len.y - tab->vmv_screen) * 256
		- tab->len.h * 128 + tab->spheight * 128;
		tab->len.tex_y = ((tab->len.d * tab->dst_sp.height)
		/ tab->spheight) / 256;
		if (tab->dst_sp.pix[tab->len.texwidth * tab->len.tex_y
		+ tab->len.tex_x] != 0x000000)
		{
			tab->mlx.pix[tab->len.y * tab->res_x + tab->len.stripe] =
			tab->dst_sp.pix[tab->len.texwidth * tab->len.tex_y
			+ tab->len.tex_x];
		}
		tab->len.y++;
	}
}
