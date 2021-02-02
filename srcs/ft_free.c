/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 04:56:45 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 04:58:49 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_doc_path(t_map *tab)
{
	free(tab->doc.no);
	free(tab->doc.so);
	free(tab->doc.we);
	free(tab->doc.ea);
	free(tab->doc.s);
}

void	free_no_file(t_map *tab)
{
	ft_error(12, tab);
	free(tab);
	exit(0);
}

void	free_all(t_map *tab, int indic)
{
	int	i;

	i = 0;
	if (indic == 0)
	{
		while (tab->map[i])
		{
			free(tab->map[i]);
			i++;
		}
		free(tab->map);
		free(tab->len.zbuff);
		free(tab->sprite);
		free(tab);
	}
	if (indic == 1)
	{
		free(tab);
		free(tab->doc.map);
	}
}

int		exit_fct(t_map *tab)
{
	free_all(tab, 0);
	exit(0);
}
