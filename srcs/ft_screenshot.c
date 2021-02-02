/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 02:53:34 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 03:02:43 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				create_screenshot(t_map *tab)
{
	int						fd;

	loop_game(tab);
	fd = open("fi.bmp", O_CREAT);
	close(fd);
	create_bmp(tab);
	return (1);
}

/*
** Le codage de l’image se fait en écrivant successivement les bits
** correspondant à chaque pixel, ligne par ligne en commençant par le pixel en
** bas à gauche.
*/

void			get_pixels(t_map *tab, int fd)
{
	unsigned char			rgb[3];
	int						x;
	int						y;

	y = -1;
	while (++y < tab->res_y - 1)
	{
		x = -1;
		while (++x < tab->res_x)
		{
			rgb[0] = (240 & (tab->mlx.pix[(tab->res_y - 1 - y)
			* tab->res_x + x]));
			rgb[1] = (240 & (tab->mlx.pix[(tab->res_y - 1 - y)
			* tab->res_x + x]) >> 8);
			rgb[2] = (240 & (tab->mlx.pix[(tab->res_y - 1 - y)
			* tab->res_x + x]) >> 16);
			write(fd, rgb, 3);
		}
	}
}

/*
** “L’entête du fichier fournit des informations sur le
** type de fichier (Bitmap), sa taille et indique où commencent les
** informations concernant l’image à proprement parler.”
**
** nb_octet = 54 (headers) + 3 (rgb) * nb pixels (x * y) + padding
** pad = ajustement car chaque ligne doit comporter un nb d’octets * de 4
**
** bmp_file_header[0:1] = ‘BM’ pour “Bitmap windows (signature du fichier)
** bfType
** bmp_file_header[2] = taille totale du fichier en octets
** bmp_file_header[10] = adresse de la zone de définition de l’image
*/

unsigned char	*create_file_header(int res_y, int res_x)
{
	int						nb_octet;
	static unsigned char	bmp_file_header[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	int						padding;

	padding = (4 - (res_x * 3) % 4) % 4;
	nb_octet = 14 + 40 + (3 * res_x + padding) * res_y;
	bmp_file_header[0] = (unsigned char)('B');
	bmp_file_header[1] = (unsigned char)('M');
	bmp_file_header[2] = (unsigned char)(nb_octet);
	bmp_file_header[3] = (unsigned char)(nb_octet >> 8);
	bmp_file_header[4] = (unsigned char)(nb_octet >> 16);
	bmp_file_header[5] = (unsigned char)(nb_octet >> 24);
	bmp_file_header[10] = (unsigned char)(54);
	return (bmp_file_header);
}

/*
** “L’entête de l’image fournit des informations sur l’image, notamment
** ses dimensions et ses couleurs.”
** bmp_bitmap_header[0] = taille en octets de l’en-tête BITMAPINFOHEADER
** bmp_bitmap_header[4] = Largeur de l’image en pixels
** bmp_bitmap_header[8] = Hauteur de l’image en pixels
** bmp_bitmap_header[12] = Nombre de plans
** bmp_bitmap_header[14] = Nombre de bits par pixel (3 car rgb)
*/

unsigned char	*create_bitmap_header(int res_y, int res_x)
{
	static unsigned char	bmp_bitmap_header[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	bmp_bitmap_header[0] = (unsigned char)(40);
	bmp_bitmap_header[4] = (unsigned char)(res_x);
	bmp_bitmap_header[5] = (unsigned char)(res_x >> 8);
	bmp_bitmap_header[6] = (unsigned char)(res_x >> 16);
	bmp_bitmap_header[7] = (unsigned char)(res_x >> 24);
	bmp_bitmap_header[8] = (unsigned char)(res_y);
	bmp_bitmap_header[9] = (unsigned char)(res_y >> 8);
	bmp_bitmap_header[10] = (unsigned char)(res_y >> 16);
	bmp_bitmap_header[11] = (unsigned char)(res_y >> 24);
	bmp_bitmap_header[12] = (unsigned char)(1);
	bmp_bitmap_header[14] = (unsigned char)(3 * 8);
	return (bmp_bitmap_header);
}

/*
** 14 pour l’en-tête du fichier (BITMAPFILEHEADER)
** 40 pour l’en-tête du bitmap (BITMAPINFOHEADER)
** O_WRONLY : ouverture du fichier en écriture seule
*/

int				create_bmp(t_map *tab)
{
	int						fd;
	unsigned char			*file_header;
	unsigned char			*bitmap_header;

	file_header = create_file_header(tab->res_y - 1, tab->res_x);
	bitmap_header = create_bitmap_header(tab->res_y - 1, tab->res_x);
	fd = open("fi.bmp", O_WRONLY);
	write(fd, file_header, 14);
	write(fd, bitmap_header, 40);
	get_pixels(tab, fd);
	close(fd);
	return (0);
}
