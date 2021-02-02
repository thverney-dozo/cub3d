/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 07:11:27 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		loop_game(t_map *tab)
{
	tab->len.x = -1;
	handle_move(tab);
	if (is_loopable(tab))
	{
		while (++tab->len.x < tab->res_x)
		{
			calc_dist(tab);
			display_ray(tab);
			display_ray_gun(tab);
		}
		display_sprites(tab);
		mlx_put_image_to_window(tab->mlx.mlx_ptr, tab->mlx.win, tab->mlx.img,
		0, 0);
		mlx_string_put(tab->mlx.mlx_ptr, tab->mlx.win, 20, 20, 0,
		"[W] Forward / [S] Backward / [A] Left / [D] Right");
		mlx_string_put(tab->mlx.mlx_ptr, tab->mlx.win, 20, 50, 0,
		"[<-] Rotate left / [->] Rotate right");
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_map	*tab;

	if (!(tab = (t_map*)malloc(sizeof(t_map))))
		return (-1);
	if (ac != 2 && check_save(av, ac))
	{
		ft_error(8, tab);
		free(tab);
		return (0);
	}
	parse_map(av, tab);
	ft_exit_error(tab);
	ft_init_mlx(tab);
	(!check_save(av, ac) ? create_screenshot(tab) : 0);
	mlx_hook(tab->mlx.win, 2, 0, key_press, tab);
	mlx_hook(tab->mlx.win, 3, 0, key_release, tab);
	mlx_hook(tab->mlx.win, 17, 0, exit_fct, tab);
	mlx_loop_hook(tab->mlx.mlx_ptr, loop_game, tab);
	mlx_loop(tab->mlx.mlx_ptr);
	return (0);
}
