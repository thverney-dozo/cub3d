/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:56:13 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 07:13:54 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_loopable(t_map *tab)
{
	if (tab->first_disp-- == 1 || tab->key.rot_l || tab->key.rot_r
	|| tab->key.front || tab->key.back || tab->key.move_l
	|| tab->key.move_r || tab->key.respawn)
		return (1);
	return (0);
}

void	check_dot_cub(char *str, t_map *tab)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i] != 'b' || str[i - 1] != 'u' || str[i - 2] != 'c'
	|| str[i - 3] != '.' || str[i + 1] != '\0')
	{
		ft_error(11, tab);
		free(tab);
		exit(0);
	}
}

void	side_choice(t_map *tab)
{
	if (tab->len.side == 1)
		tab->len.wallx = (double)((double)tab->pos_x + (((double)tab->map_y
		- tab->pos_y + (1 - (double)tab->len.stepy) / 2) / tab->len.raydy)
		* tab->len.raydx);
	else
		tab->len.wallx = (double)((double)tab->pos_y + (((double)tab->map_x
		- tab->pos_x + (1 - (double)tab->len.stepx) / 2) / tab->len.raydx)
		* tab->len.raydy);
}

int		key_press(int keycode, t_map *tab)
{
	tab->key.rot_l = (keycode == 123 ? 1 : tab->key.rot_l);
	tab->key.rot_r = (keycode == 124 ? 1 : tab->key.rot_r);
	tab->key.front = (keycode == 13 ? 1 : tab->key.front);
	tab->key.back = (keycode == 1 ? 1 : tab->key.back);
	tab->key.move_l = (keycode == 0 ? 1 : tab->key.move_l);
	tab->key.move_r = (keycode == 2 ? 1 : tab->key.move_r);
	tab->key.sprint = (keycode == 49 ? 1 : tab->key.sprint);
	tab->key.respawn = (keycode == 15 ? 1 : tab->key.respawn);
	tab->key.fovgod = (keycode == 3 ? 1 : tab->key.fovgod);
	tab->key.sneak = (keycode == 257 ? 1 : tab->key.sneak);
	tab->key.zoom = (keycode == 12 ? 1 : tab->key.zoom);
	if (keycode == 53)
	{
		mlx_destroy_window(tab->mlx.mlx_ptr, tab->mlx.win);
		free_all(tab, 0);
		exit(0);
	}
	return (0);
}

int		key_release(int keycode, t_map *tab)
{
	(keycode == 123 ? tab->key.rot_l-- : 0);
	(keycode == 124 ? tab->key.rot_r-- : 0);
	(keycode == 13 ? tab->key.front-- : 0);
	(keycode == 1 ? tab->key.back-- : 0);
	(keycode == 0 ? tab->key.move_l-- : 0);
	(keycode == 2 ? tab->key.move_r-- : 0);
	(keycode == 49 ? tab->key.sprint-- : 0);
	(keycode == 15 ? tab->key.respawn-- : 0);
	(keycode == 3 ? tab->key.fovgod-- : 0);
	(keycode == 257 ? tab->key.sneak-- : 0);
	(keycode == 12 ? tab->key.zoom-- : 0);
	return (0);
}
