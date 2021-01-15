/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:29:47 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 04:40:23 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	doc_resolution(char *str, t_map *tab)
{
	int i;
	int indic;

	indic = 0;
	i = 0;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->res_x = ft_atoi(str + i);
	tab->res_x > 2560 ? tab->res_x = 2560 : 0;
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->res_y = ft_atoi(str + i);
	tab->res_y > 1440 ? tab->res_y = 1440 : 0;
	tab->res_y > tab->res_x ? ft_error(10, tab) : 0;
	(tab->res_y == 0 || tab->res_x == 0 || str[i] == '\0' || str[1] != ' ' ?
	indic++ : 0);
	(indic > 0 ? ft_error(1, tab) : 0);
	(indic > 0 ? free_doc_path(tab) : 0);
	(indic > 0 ? exit(0) : 0);
}

void	doc_way(char *str, t_map *tab, int way)
{
	if (ft_strchr(str, '.') == NULL)
	{
		ft_error(4, tab);
		return ;
	}
	if (way == 0 && !tab->doc.no)
		tab->doc.no = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 1 && !tab->doc.so)
		tab->doc.so = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 2 && !tab->doc.we)
		tab->doc.we = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 3 && !tab->doc.ea)
		tab->doc.ea = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 4 && !tab->doc.s)
		tab->doc.s = sdupfr(ft_strchr(str, '.'), 0);
	doc_way_fd(tab, way);
}

void	doc_color_f(char *str, t_map *tab)
{
	int i;
	int indic;

	indic = 0;
	i = 0;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.f.red = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.f.green = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.f.blue = ft_atoi(str + i);
	(str[i] == '\0' || tab->doc.f.blue < 0 || tab->doc.f.blue > 255
	|| tab->doc.f.red < 0 || tab->doc.f.red > 255
	|| tab->doc.f.green < 0 || tab->doc.f.green > 255 ? indic++ : 0);
	(indic > 0 ? free_doc_path(tab) : 0);
	(indic > 0 ? ft_error(6, tab) : 0);
	(indic > 0 ? exit(0) : 0);
	ft_put_in_hex(tab, 0);
}

void	doc_color_c(char *str, t_map *tab)
{
	int i;
	int indic;

	indic = 0;
	i = 0;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.c.red = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.c.green = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.c.blue = ft_atoi(str + i);
	(str[i] == '\0' || tab->doc.c.blue < 0 || tab->doc.c.blue > 255
	|| tab->doc.c.red < 0 || tab->doc.c.red > 255
	|| tab->doc.c.green < 0 || tab->doc.c.green > 255 ? indic++ : 0);
	(indic > 0 ? free_doc_path(tab) : 0);
	(indic > 0 ? ft_error(6, tab) : 0);
	(indic > 0 ? exit(0) : 0);
	ft_put_in_hex(tab, 1);
}
