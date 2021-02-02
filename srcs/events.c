/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:27:49 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 03:52:07 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_move_two(t_map *tab)
{
	(tab->angle < 0 ? tab->angle += 360 : 0);
	(tab->angle > 360 ? tab->angle -= 360 : 0);
	if (tab->key.front || tab->key.back)
		back_front(tab);
	if (tab->key.move_l || tab->key.move_r)
		left_right(tab);
	if (tab->key.rot_l || tab->key.rot_r)
	{
		tab->len.oldplanx = tab->len.planx;
		tab->len.planx = tab->len.planx * cos(-(2.5))
		- tab->len.plany * sin(-(2.5));
		tab->len.plany = tab->len.oldplanx * sin(-(2.5))
		+ tab->len.plany * cos(-(2.5));
	}
}

void	handle_move(t_map *tab)
{
	tab->key.speed = (tab->key.sprint == 1 ? 1 : 0.15);
	tab->key.speed = (tab->key.fovgod == 1 ? 0.4 : tab->key.speed);
	if (tab->key.respawn)
	{
		tab->pos_x = tab->len.spawnx;
		tab->pos_y = tab->len.spawny;
		tab->angle = tab->len.spawnangle;
	}
	if (tab->key.rot_l)
	{
		(tab->key.sneak == 1 ? tab->angle -= 0.5 : 0);
		(tab->key.fovgod == 1 ? tab->angle -= 5 : 0);
		(tab->key.fovgod != 1 && tab->key.sneak != 1 ? tab->angle -= 3 : 0);
	}
	if (tab->key.rot_r)
	{
		(tab->key.sneak == 1 ? tab->angle += 0.5 : 0);
		(tab->key.fovgod == 1 ? tab->angle += 5 : 0);
		(tab->key.fovgod != 1 && tab->key.sneak != 1 ? tab->angle += 3 : 0);
	}
	handle_move_two(tab);
}

void	back_front(t_map *tab)
{
	if (tab->key.front)
	{
		if (tab->map[(int)(tab->pos_x + cos(tab->angle * (M_PI / 180))
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x += cos(tab->angle * (M_PI / 180)) * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + sin(tab->angle
		* (M_PI / 180)) * tab->key.speed)] == '0')
			tab->pos_y += sin(tab->angle * (M_PI / 180)) * tab->key.speed;
	}
	if (tab->key.back)
	{
		if (tab->map[(int)(tab->pos_x - cos(tab->angle * (M_PI / 180))
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x -= cos(tab->angle * (M_PI / 180)) * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - sin(tab->angle
		* (M_PI / 180)) * tab->key.speed)] == '0')
			tab->pos_y -= sin(tab->angle * (M_PI / 180)) * tab->key.speed;
	}
}

void	left_right(t_map *tab)
{
	if (tab->key.move_l)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x - tab->len.planx
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x -= tab->len.planx * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - tab->len.plany
		* tab->key.speed)] == '0')
			tab->pos_y -= tab->len.plany * tab->key.speed;
	}
	if (tab->key.move_r)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x + tab->len.planx
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x += tab->len.planx * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + tab->len.plany
		* tab->key.speed)] == '0')
			tab->pos_y += tab->len.plany * tab->key.speed;
	}
}
