/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:15:47 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 05:12:04 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	doc_way_fd(t_map *tab, int way)
{
	int fd;

	fd = 0;
	if (way == 0)
		(((fd = open(tab->doc.no, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 1)
		(((fd = open(tab->doc.so, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 2)
		(((fd = open(tab->doc.we, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 3)
		(((fd = open(tab->doc.ea, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 4)
		(((fd = open(tab->doc.s, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 5)
		if (!(tab->doc.no) || !(tab->doc.so) || !(tab->doc.we)
		|| !(tab->doc.ea) || !(tab->doc.s))
		{
			ft_error(5, tab);
			free_doc_path(tab);
			exit(0);
		}
}

int		splitmap(char *str, int i, int len, t_map *tab)
{
	int j;

	j = 0;
	tab->len.err_map_zero = 0;
	if (i == 0 || i == -1)
	{
		while (str[j] != '\0')
		{
			if (str[j] == '0' && i == -1)
				tab->len.err_map_zero = 1;
			if (str[j] == '0')
				return (1);
			j++;
		}
	}
	if (str[0] == '0' && i != -1)
		return (1);
	if (str[len] == '0' && i != -1)
		return (1);
	return (0);
}

int		check_save(char **av, int ac)
{
	if (ac != 3 || av[2][0] != '-' || av[2][1] != 's' || av[2][2] != 'a'
	|| av[2][3] != 'v' || av[2][4] != 'e' || av[2][5] != '\0')
		return (1);
	return (0);
}

void	update_position(t_map *tab, int x, int y)
{
	tab->pos_y = y + 0.5;
	tab->pos_x = x + 0.5;
	tab->map[x][y] = '0';
	tab->len.spawnx = tab->pos_x;
	tab->len.spawny = tab->pos_y;
	tab->len.spawnangle = tab->angle;
	tab->len.way = 1;
}

void	position(t_map *tab)
{
	int		x;
	int		y;

	x = -1;
	while (tab->map[++x])
	{
		y = -1;
		while (tab->map[x][++y])
		{
			if (isnb(tab->map[x][y]) == 0)
			{
				if (tab->map[x][y] == 'E')
					tab->angle = 90;
				if (tab->map[x][y] == 'N')
					tab->angle = 180;
				if (tab->map[x][y] == 'W')
					tab->angle = 270;
				if (tab->map[x][y] == 'S')
					tab->angle = 0;
				update_position(tab, x, y);
			}
		}
	}
	(tab->len.way == 0 ? free_doc_path(tab) : 0);
	(tab->len.way == 0 ? ft_error(9, tab) : 0);
}
