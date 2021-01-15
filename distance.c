/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:24:48 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 03:35:05 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_texture_x(t_map *tab)
{
	tab->len.text_xn = (int)(tab->len.wallx * tab->dst_n.width);
	if (tab->len.side == 0 && tab->len.raydx > 0)
		tab->len.text_xn = tab->dst_n.width - tab->len.text_xn - 1;
	if (tab->len.side == 1 && tab->len.raydy < 0)
		tab->len.text_xn = tab->dst_n.width - tab->len.text_xn - 1;
	tab->len.text_xs = (int)(tab->len.wallx * tab->dst_s.width);
	if (tab->len.side == 0 && tab->len.raydx > 0)
		tab->len.text_xs = tab->dst_s.width - tab->len.text_xs - 1;
	if (tab->len.side == 1 && tab->len.raydy < 0)
		tab->len.text_xs = tab->dst_s.width - tab->len.text_xs - 1;
	tab->len.text_xw = (int)(tab->len.wallx * tab->dst_w.width);
	if (tab->len.side == 0 && tab->len.raydx > 0)
		tab->len.text_xw = tab->dst_w.width - tab->len.text_xw - 1;
	if (tab->len.side == 1 && tab->len.raydy < 0)
		tab->len.text_xw = tab->dst_w.width - tab->len.text_xw - 1;
	tab->len.text_xe = (int)(tab->len.wallx * tab->dst_e.width);
	if (tab->len.side == 0 && tab->len.raydx > 0)
		tab->len.text_xe = tab->dst_e.width - tab->len.text_xe - 1;
	if (tab->len.side == 1 && tab->len.raydy < 0)
		tab->len.text_xe = tab->dst_e.width - tab->len.text_xe - 1;
}

void		wall_distance(t_map *tab)
{
	tab->len.wallx -= (int)tab->len.wallx;
	get_texture_x(tab);
	if (tab->len.side == 0)
		tab->len.perp_w_dist = fabs((((double)tab->map_x - tab->pos_x
		+ (1 - tab->len.stepx) / 2) / tab->len.raydx));
	else
		tab->len.perp_w_dist = fabs((((double)tab->map_y - tab->pos_y
		+ (1 - tab->len.stepy) / 2) / tab->len.raydy));
	tab->len.heightline = (tab->key.sprint ? abs((int)((double)tab->len.h
	/ tab->len.perp_w_dist)) * 1.35 :
	abs((int)((double)tab->len.h / tab->len.perp_w_dist)) * 1.7);
	tab->len.heightline = (tab->key.zoom ? abs((int)((double)tab->len.h
	/ tab->len.perp_w_dist)) * 4 : tab->len.heightline);
	tab->len.ray_start = (int)(-(tab->len.heightline / 2) + tab->len.h / 2);
	tab->len.ray_end = (int)((tab->len.heightline / 2) + tab->len.h / 2);
	if (tab->len.ray_start < 0)
		tab->len.ray_start = 0;
	if (tab->len.ray_end >= tab->len.h)
		tab->len.ray_end = tab->len.h - 1;
	tab->len.zbuff[tab->len.x] = tab->len.perp_w_dist;
}

void		calc_dist_xy(t_map *tab)
{
	if (tab->len.raydx < 0)
	{
		tab->len.stepx = -1;
		tab->len.side_dx = (tab->pos_x - tab->map_x) * tab->len.delta_dx;
	}
	else
	{
		tab->len.stepx = 1;
		tab->len.side_dx = (tab->map_x + 1.0 - tab->pos_x)
		* tab->len.delta_dx;
	}
	if (tab->len.raydy < 0)
	{
		tab->len.stepy = -1;
		tab->len.side_dy = (tab->pos_y - tab->map_y) * tab->len.delta_dy;
	}
	else
	{
		tab->len.stepy = 1;
		tab->len.side_dy = (tab->map_y + 1.0 - tab->pos_y)
		* tab->len.delta_dy;
	}
}

void		ft_init_ray(t_map *tab)
{
	tab->len.fov = (tab->key.sprint ? 40 : 30);
	tab->len.fov = (tab->key.fovgod ? 180 : tab->len.fov);
	tab->len.fov = (tab->key.zoom ? 10 : tab->len.fov);
	tab->len.w = tab->res_x;
	tab->len.h = tab->res_y;
	tab->len.camerax = (2 * (double)tab->len.x / (double)tab->len.w) - 1;
	tab->len.raydx = cos((tab->angle + (tab->len.fov * tab->len.camerax))
	* (M_PI / 180));
	tab->len.raydy = sin((tab->angle + (tab->len.fov * tab->len.camerax))
	* (M_PI / 180));
	tab->len.delta_dx = sqrt(1 + (tab->len.raydy * tab->len.raydy)
	/ (tab->len.raydx * tab->len.raydx));
	tab->len.delta_dy = sqrt(1 + (tab->len.raydx * tab->len.raydx)
	/ (tab->len.raydy * tab->len.raydy));
	tab->len.hit = 0;
	tab->map_x = (int)tab->pos_x;
	tab->map_y = (int)tab->pos_y;
	tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.54;
	tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.54;
}

void		calc_dist(t_map *tab)
{
	ft_init_ray(tab);
	calc_dist_xy(tab);
	while (tab->len.hit == 0)
	{
		tab->len.side = (tab->len.side_dx < tab->len.side_dy ? 0 : 1);
		if (tab->len.side_dx < tab->len.side_dy)
		{
			tab->len.side_dx += tab->len.delta_dx;
			tab->map_x += tab->len.stepx;
		}
		else
		{
			tab->len.side_dy += tab->len.delta_dy;
			tab->map_y += tab->len.stepy;
		}
		if (tab->map[tab->map_x][tab->map_y] == '1')
			tab->len.hit = 1;
	}
	side_choice(tab);
	wall_distance(tab);
}
