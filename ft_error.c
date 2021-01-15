/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 03:53:27 by thverney          #+#    #+#             */
/*   Updated: 2020/01/17 04:59:03 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error_two(int error, t_map *tab)
{
	if (error == 9)
		write(1, "\n\033[31m(ERROR) No spawn found (N/S/W/E/)\n", 41);
	if (error == 10)
		write(1, "\n\033[31m(ERROR) Width must be bigger than Heigth\n", 48);
	if (error == 11)
		write(1, "\n\033[31m(ERROR) Input file must be a .cub !!\n", 44);
	if (error == 12)
		write(1, "\n\033[31m(ERROR) Input file doesn't exist !!\n", 43);
	if (error == 13)
		write(1, "\n\033[31m(ERROR) Invalid Map !!\n", 30);
	tab->error = 1;
}

void	ft_error(int error, t_map *tab)
{
	if (error == 1)
		write(1, "\n\033[31m(ERROR!) Invalid Resolution\n", 35);
	if (error == 2)
		write(1, "\n\033[31m(ERROR!) Invalid Map, illegal characters\n", 48);
	if (error == 3)
		write(1, "\n\033[31m(ERROR) Map isn't surrounded by '1'\n", 43);
	if (error == 4)
	{
		write(1, "\n\033[31m(ERROR) Invalid Path texture\n", 36);
		free_doc_path(tab);
	}
	if (error == 5)
		write(1, "\n\033[31m(ERROR) Path(s) not found\n", 33);
	if (error == 6)
		write(1, "\n\033[31m(ERROR) Illegal RGB value(s)\n", 36);
	if (error == 7)
		write(1, "\n\033[31m(ERROR) Map isn't rectangular\n", 37);
	if (error == 8)
		write(1, "\n\033[31m(ERROR) Invalid arguments !!\n", 37);
	ft_error_two(error, tab);
}

void	ft_exit_error(t_map *tab)
{
	if (tab->error == 1)
	{
		free_all(tab, 0);
		exit(0);
	}
}
