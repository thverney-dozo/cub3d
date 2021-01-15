/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:13:10 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 02:51:25 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_map(t_map *tab, int k, int i, int j)
{
	char	*res;

	while (tab->map[++k])
	{
		if (!(res = malloc(sizeof(char) * (ft_strlen(tab->map[k]) + 1))))
			return ;
		j = 0;
		i = -1;
		while (tab->map[k][++i])
		{
			if (tab->map[k][i] != 32)
			{
				res[j] = tab->map[k][i];
				(res[j] != '1' && res[j] != '0' && res[j] != '2'
				? tab->tmp_err++ : 0);
				res[j] == '2' ? ft_sps_stock((double)k, (double)j, tab) : 0;
				res[j] == '2' ? tab->len.nb_sp++ : 0;
				j++;
			}
		}
		res[j] = 0;
		free(tab->map[k]);
		tab->map[k] = sdupfr(res, 1);
	}
	list_to_dist(tab);
}

void	doc_checker_two(char *str, t_map *tab)
{
	if (str[0] == '1' || (str[0] == ' ' && ft_strchr(str, '1') != NULL))
	{
		tab->tmp_err = -1;
		tab->doc.map = ft_sjoin_free(tab->doc.map, str, 1);
		tab->doc.map = ft_sjoin_free(tab->doc.map, ".", 1);
	}
	if (tab->tmp_err == -1 && str[0] != '1')
	{
		ft_error(13, tab);
		free(tab->doc.map);
		free_doc_path(tab);
		free(tab);
		exit(0);
	}
}

void	doc_checker(char *str, t_map *tab)
{
	if (str[0] == 'R')
	{
		doc_resolution(str, tab);
	}
	if ((str[0] == 'N' || str[0] == 'S') && str[1] == 'O')
		(str[0] == 'N' ? doc_way(str, tab, 0) : doc_way(str, tab, 1));
	if (str[0] == 'W' && str[1] == 'E')
		doc_way(str, tab, 2);
	if (str[0] == 'E' && str[1] == 'A')
		doc_way(str, tab, 3);
	if (str[0] == 'S' && str[1] == ' ')
		doc_way(str, tab, 4);
	if (str[0] == 'F' && str[1] == ' ')
		doc_color_f(str, tab);
	if (str[0] == 'C' && str[1] == ' ')
		doc_color_c(str, tab);
	if (str[0] == '0')
		ft_error(3, tab);
	doc_checker_two(str, tab);
}

void	parse_map_two(t_map *tab)
{
	doc_way(".", tab, 5);
	tab->map = ft_split(tab->doc.map, '.');
	free(tab->doc.map);
	tab->tmp_err = 0;
	tab->len.nb_sp = 0;
	clean_map(tab, -1, 0, 0);
	(tab->tmp_err > 1 ? ft_error(2, tab) : 0);
	ft_map_check(tab);
	(tab->len.err_map_zero ? ft_error(3, tab) : 0);
	position(tab);
	if (!(tab->len.zbuff = (double*)malloc(sizeof(double) * (tab->res_x + 1))))
		return ;
}

void	parse_map(char **av, t_map *tab)
{
	int		fd;
	int		i;

	tab->tmp_err = 0;
	tab->error = 0;
	check_dot_cub(av[1], tab);
	i = 1;
	fd = open(av[1], O_RDONLY);
	(fd == -1 ? free_no_file(tab) : 0);
	tab->doc.map = malloc(1);
	tab->doc.map[0] = 0;
	tab->len.way = 0;
	while (i)
	{
		i = get_next_line(fd, &tab->doc.temp);
		doc_checker(tab->doc.temp, tab);
		if (i == 0)
		{
			splitmap(tab->doc.temp, -1, 0, tab);
		}
		free(tab->doc.temp);
	}
	parse_map_two(tab);
}
