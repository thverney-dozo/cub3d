/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:31:16 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 01:27:13 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_map *tab)
{
	t_text *src;

	if (!(src = (t_text*)malloc(sizeof(t_text))))
		return ;
	src->img = mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.no,
	&(tab->dst_n.width), &(tab->dst_n.height));
	tab->dst_n.pix = (int *)mlx_get_data_addr(src->img, &src->bpp, &src->size,
	&src->endian);
	tab->dst_n.smallval = (tab->dst_n.width <= tab->dst_n.height ?
	tab->dst_n.width : tab->dst_n.height);
	src->img = mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.so,
	&(tab->dst_s.width), &(tab->dst_s.height));
	tab->dst_s.pix = (int *)mlx_get_data_addr(src->img, &src->bpp,
	&src->size, &src->endian);
	tab->dst_s.smallval = (tab->dst_s.width <= tab->dst_s.height ?
	tab->dst_s.width : tab->dst_s.height);
	get_texture_two(src, tab);
}

void	get_texture_two(t_text *src, t_map *tab)
{
	src->img = mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.we,
	&(tab->dst_w.width), &(tab->dst_w.height));
	tab->dst_w.pix = (int *)mlx_get_data_addr(src->img, &src->bpp,
	&src->size, &src->endian);
	tab->dst_w.smallval = (tab->dst_w.width <= tab->dst_w.height ?
	tab->dst_w.width : tab->dst_w.height);
	src->img = mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.ea,
	&(tab->dst_e.width), &(tab->dst_e.height));
	tab->dst_e.pix = (int *)mlx_get_data_addr(src->img, &src->bpp,
	&src->size, &src->endian);
	tab->dst_e.smallval = (tab->dst_e.width <= tab->dst_e.height ?
	tab->dst_e.width : tab->dst_e.height);
	src->img = mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.s,
	&(tab->dst_sp.width), &(tab->dst_sp.height));
	tab->dst_sp.pix = (int *)mlx_get_data_addr(src->img, &src->bpp,
	&src->size, &src->endian);
	tab->dst_sp.smallval = (tab->dst_sp.width <= tab->dst_sp.height ?
	tab->dst_sp.width : tab->dst_sp.height);
	free_doc_path(tab);
	free(src);
}
