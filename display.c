/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:26:19 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 03:47:14 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_mlx(t_map *tab)
{
	int		lol;

	tab->first_disp = 1;
	tab->mlx.mlx_ptr = mlx_init();
	tab->mlx.win = mlx_new_window(tab->mlx.mlx_ptr, tab->res_x, tab->res_y,
	"cub3d");
	tab->mlx.img = mlx_new_image(tab->mlx.mlx_ptr, tab->res_x, tab->res_x);
	tab->mlx.pix = (int *)mlx_get_data_addr(tab->mlx.img, &lol, &lol, &lol);
	get_texture(tab);
}

void	display_ray_three(t_map *tab, int i)
{
	if (tab->len.side == 0 && tab->map_x < tab->pos_x)
	{
		tab->len.texty = (((double)i * 2. - (double)tab->res_y
		+ (double)tab->len.heightline) * (tab->dst_w.width / 2)
		/ (double)tab->len.heightline);
		tab->mlx.pix[i * tab->res_x + tab->len.x] =
		tab->dst_w.pix[(int)tab->len.texty * tab->dst_w.width
		+ tab->len.text_xw];
	}
	else if (tab->len.side == 0)
	{
		tab->len.texty = (((double)i * 2. - (double)tab->res_y
		+ (double)tab->len.heightline) * (tab->dst_e.width / 2)
		/ (double)tab->len.heightline);
		tab->mlx.pix[i * tab->res_x + tab->len.x] =
		tab->dst_e.pix[(int)tab->len.texty * tab->dst_e.width
		+ tab->len.text_xe];
	}
}

void	display_ray_two(t_map *tab, int i)
{
	tab->len.texty = (((double)i * 2. - (double)tab->res_y
	+ (double)tab->len.heightline) * (tab->dst_n.width / 2)
	/ (double)tab->len.heightline);
	if (tab->len.side == 1 && tab->map_y < tab->pos_y)
		tab->mlx.pix[i * tab->res_x + tab->len.x] =
		tab->dst_n.pix[(int)tab->len.texty * tab->dst_n.width
		+ tab->len.text_xn];
	else if (tab->len.side == 1)
	{
		tab->len.texty = (((double)i * 2. - (double)tab->res_y
		+ (double)tab->len.heightline) * (tab->dst_s.width / 2)
		/ (double)tab->len.heightline);
		tab->mlx.pix[i * tab->res_x + tab->len.x] =
		tab->dst_s.pix[(int)tab->len.texty * tab->dst_s.width
		+ tab->len.text_xs];
	}
	display_ray_three(tab, i);
}

void	display_ray(t_map *tab)
{
	int i;
	int y;

	i = -1;
	if (tab->map[tab->map_x][tab->map_y] == '1' || tab->map[tab->map_x]
	[tab->map_y] == '0')
	{
		while (++i <= (int)tab->len.ray_start)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->doc.c.hex;
		y = --i + 1;
		while (++i <= (int)tab->len.ray_end)
		{
			display_ray_two(tab, i);
			(i == y ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0);
			(i == tab->len.ray_end ? tab->mlx.pix[i * tab->res_x + tab->len.x] =
			0x000000 : 0);
		}
		i--;
		while (++i < tab->res_y)
		{
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->doc.f.hex;
		}
	}
}
