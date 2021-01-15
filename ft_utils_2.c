/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 05:05:20 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 05:30:57 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_in_hex(t_map *tab, int i)
{
	if (i == 0)
	{
		tab->doc.f.hex = tab->doc.f.blue | tab->doc.f.red << 16
		| tab->doc.f.green << 8;
	}
	if (i == 1)
	{
		tab->doc.c.hex = tab->doc.c.blue | tab->doc.c.red << 16
		| tab->doc.c.green << 8;
	}
}

void	ft_map_check(t_map *tab)
{
	int i;
	int len;
	int comp;

	i = 0;
	len = ft_strlen(tab->map[i]) - 1;
	while (tab->map[i])
	{
		comp = ft_strlen(tab->map[i]) - 1;
		if (comp != len)
		{
			ft_error(7, tab);
			free_doc_path(tab);
			break ;
		}
		if (splitmap(tab->map[i], i, len, tab) == 1)
		{
			ft_error(3, tab);
			free_doc_path(tab);
			break ;
		}
		i++;
	}
}

void	display_ray_gun(t_map *tab)
{
	int j;

	j = tab->res_y / 2 - 25;
	if (tab->len.x >= (tab->res_x / 2) - 1 && tab->len.x
	<= (tab->res_x / 2) + 1)
	{
		while (j <= tab->res_y / 2 + 25)
		{
			tab->mlx.pix[j * tab->res_x + tab->len.x] = 0xff0000;
			j++;
		}
	}
	j = tab->res_y / 2 - 1;
	if (tab->len.x >= (tab->res_x / 2) - 25 && tab->len.x <=
	(tab->res_x / 2) + 25)
	{
		while (j <= tab->res_y / 2 + 1)
		{
			tab->mlx.pix[j * tab->res_x + tab->len.x] = 0xff0000;
			j++;
		}
	}
}
