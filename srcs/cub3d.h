/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:10:34 by thverney          #+#    #+#             */
/*   Updated: 2021/02/02 13:04:06 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

typedef struct	s_sp
{
	double		x;
	double		y;
	double		dist;
	struct s_sp	*next;
}				t_sp;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
	int			indic;
}				t_sprite;

typedef struct	s_color
{
	int			blue;
	int			green;
	int			red;
	int			hex;
}				t_color;

typedef struct	s_doc
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	t_color		f;
	t_color		c;
	char		*map;
	char		*temp;
}				t_doc;

typedef struct	s_key
{
	double		speed;
	int			front;
	int			back;
	int			rot_l;
	int			rot_r;
	int			move_r;
	int			move_l;
	int			sprint;
	int			respawn;
	int			fovgod;
	int			sneak;
	int			zoom;
}				t_key;

typedef struct	s_text
{
	int			width;
	int			height;
	void		*img;
	int			*pix;
	int			bpp;
	int			size;
	int			endian;
	int			smallval;
}				t_text;

typedef struct	s_libx
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	int		*pix;
}				t_libx;

typedef struct	s_len
{
	int			fov;
	int			x;
	int			w;
	int			h;
	int			d;
	int			y;
	int			stripe;
	int			tex_x;
	int			tex_y;
	int			ray_start;
	int			ray_end;
	int			hit;
	int			side;
	int			text_xn;
	int			text_xs;
	int			text_xw;
	int			text_xe;
	int			texwidth;
	int			nb_sp;
	int			way;
	int			err_map_zero;
	double		x_tmp;
	double		y_tmp;
	double		d_tmp;
	double		spawnx;
	double		spawny;
	double		spawnangle;
	double		planx;
	double		plany;
	double		oldplanx;
	double		heightline;
	double		camerax;
	double		perp_w_dist;
	double		raydx;
	double		raydy;
	double		delta_dx;
	double		delta_dy;
	double		stepx;
	double		stepy;
	double		norme;
	double		side_dx;
	double		side_dy;
	double		wallx;
	double		texty;
	double		*zbuff;
}				t_len;

typedef struct	s_map
{
	char		**map;
	double		angle;
	double		pos_x;
	double		pos_y;
	double		spritex;
	double		spritey;
	double		invdet;
	double		trsformx;
	double		trsformy;
	int			res_y;
	int			res_x;
	int			map_x;
	int			map_y;
	int			spscreenx;
	int			spheight;
	int			drw_starty;
	int			drw_startx;
	int			drw_endy;
	int			drw_endx;
	int			vmv_screen;
	int			spwidth;
	int			first_disp;
	int			error;
	int			tmp_err;
	t_sp		*sp;
	t_sp		*new;
	t_sp		*tmp;
	t_sprite	*sprite;
	t_doc		doc;
	t_key		key;
	t_len		len;
	t_libx		mlx;
	t_text		dst_n;
	t_text		dst_s;
	t_text		dst_sp;
	t_text		dst_w;
	t_text		dst_e;
}				t_map;

void			parse_map(char **av, t_map *tab);
void			parse_map_two(t_map *tab);
void			clean_map(t_map *tab, int k, int i, int j);
void			position(t_map *tab);
void			update_position(t_map *tab, int x, int y);
void			wall_distance(t_map *tab);
void			ft_init_ray(t_map *tab);
void			calc_dist_xy(t_map *tab);
void			calc_dist(t_map *tab);
void			side_choice(t_map *tab);
void			ft_init_mlx(t_map *tab);
void			display_ray(t_map *tab);
void			display_ray_two(t_map *tab, int i);
void			handle_angle(t_map *tab);
void			handle_move(t_map *tab);
void			handle_move_two(t_map *tab);
void			back_front(t_map *tab);
void			left_right(t_map *tab);
int				key_release(int keycode, t_map *tab);
int				key_press(int keycode, t_map *tab);
int				loop_game(t_map *tab);
void			get_texture(t_map *tab);
void			get_texture_two(t_text *src, t_map *tab);
void			display_ray_three(t_map *tab, int i);
int				is_loopable(t_map *tab);
void			get_texture_x(t_map *tab);
void			doc_checker(char *str, t_map *tab);
void			doc_checker_two(char *str, t_map *tab);
void			doc_resolution(char *str, t_map *tab);
void			doc_way(char *str, t_map *tab, int way);
void			doc_color_f(char *str, t_map *tab);
void			doc_color_c(char *str, t_map *tab);
void			ft_error(int error, t_map *tab);
void			ft_error_two(int error, t_map *tab);
void			doc_way_fd(t_map *tab, int way);
void			ft_map_check(t_map *tab);
int				splitmap(char *str, int i, int len, t_map *tab);
void			ft_exit_error(t_map *tab);
void			ft_put_in_hex(t_map *tab, int i);
void			display_ray_gun(t_map *tab);
void			display_sprites(t_map *tab);
int				ft_sps_stock(double x, double y, t_map *tab);
void			display_sprites(t_map *tab);
void			list_to_dist(t_map *tab);
void			list_to_tab(t_map *tab);
void			calc_disp_sp(t_map *tab, int i);
void			calc_dist_sp(t_map *tab, int i);
void			calc_dist_sp_two(t_map *tab);
void			display_ray_sp(t_map *tab);
void			sort_sprite(t_map *tab, int i);
void			dist_sprite(t_map *tab, int i);
void			swap_sprite(t_map *tab, int i);
int				exit_fct(t_map *tab);
void			check_dot_cub(char *str, t_map *tab);
void			free_all(t_map *tab, int indic);
int				check_save(char **av, int ac);
int				create_screenshot(t_map *tab);
void			get_pixels(t_map *tab, int fd);
unsigned char	*create_file_header(int res_y, int res_x);
unsigned char	*create_bitmap_header(int res_y, int res_x);
int				create_bmp(t_map *tab);
void			free_doc_path(t_map *tab);
void			free_no_file(t_map *map);

#endif
