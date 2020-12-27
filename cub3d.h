/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:09:40 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 15:23:28 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "./get_next_line/get_next_line.h"
# include "libft/libft.h"
# define TILE_SIZE 		64
# define TILE_SIZE_SPRT	64
# define PI				3.14159265359
# define MINI_MAP		0.1
# define MOVE_SPEED		8
# define RETATION_SPEED 0.04

typedef struct	s_pos
{
	float		x;
	float		y;
}				t_pos;

typedef struct	s_sprite
{
	t_pos		pos;
	float		angle;
	int			loc;
	float		dist;
	int			nb;
	t_pos		texoffset;
}				t_sprt;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_tex
{
	void		*ptr;
	int			*data;
	t_pos		start;
	t_pos		end;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_tex;

typedef struct	s_boucle
{
	int			i;
	int			j;
}				t_bcl;

typedef struct	s_check
{
	int			valid_resul;
	int			valid_textues;
	int			valid_color;
	int			vld_r;
	int			vld_so;
	int			vld_s;
	int			vld_no;
	int			vld_we;
	int			vld_ea;
	int			vld_f;
	int			vld_c;
	int			vld_map;
}				t_check;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_clr;

typedef struct	s_parse
{
	char		*path;
	char		*r;
	int			h;
	int			w;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	t_clr		f;
	t_clr		c;
	t_check		var;
	char		**map;
	char		**n_map;
	int			nb_line;
	int			big;
}				t_prs;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pos		pos;
	float		view_angle;
	float		angle;
	int			key;
	float		half_of_windows;
	t_img		img[4];
	int			size_pers;
	t_pos		dir;
}				t_mlx;

typedef struct	s_cub3d
{
	float		fov;
	float		dist_wall[2560];
	t_img		frame;
	t_tex		tex[9];
	int			foundvertwallhit;
	t_pos		vert_wallhit;
	int			foundhorzwallhit;
	t_pos		horz_wallhit;
	t_pos		foundwallhit;
	int			isverthit;
	int			nb_sprt;
	t_sprt		*sprt;
	t_sprt		temp_sprt;
	t_prs		prs;
	t_mlx		mlx;
	char		*bmp;
	int			fd;
	int			argc;
	int			keyboard[300];
}				t_cub;

void			draw_all_first(t_cub *cub);
void			draw_3d(t_cub *cub);
float			finnal_dist(float ray_angle, t_cub *cub);
int				haswallat(float x, float y, t_cub *cub);
int				isleft(float angle);
int				isrght(float angle);
int				isup(float angle);
int				isdown(float angle);
void			update(t_cub *cub);
void			move_player(t_cub *cub);
void			fixing_angle(t_cub *cub);
void			load_textures(t_cub *cub);
int				wall_vert_face(t_cub *cub);
int				wall_horz_face(t_cub *cub);
int				hassprtat(float x, float y, t_cub *cub);
float			get_dis(t_pos dprt, t_pos fin);
void			sprites(t_cub *cub);
int				prsing(t_cub *cub);
void			ft_error(char *msg);
void			ft_error_in(char *msg, char *var);
void			sprtes_pos(t_cub *cub);
int				rgb(t_clr rgb);
void			check_fils(char *path, char *s);
void			check_color(t_cub *cub);
void			ft_free(char **ptr);
void			ft_msg(char *msg);
void			ft_mapline_check(char *line, t_cub *cub);
void			ft_check_map(t_cub *cub);
void			ft_player_angle(char vec, t_cub *cub);
void			cnt_sprites(t_cub *cub);
void			check_player(t_cub *cub);
void			ft_initialize(t_cub *cub);
void			img_loading(t_cub *cub);
void			ft_bmp(t_cub *cub);
int				key_pressed(int keycode, t_cub *cub);
int				key_released(int keycode, t_cub *cub);
int				exit_cub(t_cub *cub);
int				key_press(t_cub *cub);
void			update_angle(t_cub *cub);
void			frame_helper(float wallstripheight, float start,\
	float ray, t_cub *cub);
void			calcul_sprites(t_cub *cub);
void			color_to_rgb(int color, t_cub *cub, int pos);
void			help_get_map(char *line, int t, t_cub *cub);
int				help_parsing(t_cub *cub, t_bcl *bcl, int fd, int big);
void			making_map(int big, t_cub *cub);
int				get_info(char *line, t_cub *cub);
void			get_map(char *line, int t, t_cub *cub);
void			get_tex(char *line, t_cub *cub);
void			get_color(char *line, t_cub *cub);
int				alpha_player(char check);
void			ft_check_comma(char *line, char **color);
void			rgb_to_bmp(t_clr color, t_cub *cub, int pos);
void			check_last_col(t_cub *cub);
void			check_last_line(t_cub *cub);
void			ft_check_all_good(t_cub *cub);
void			valid_tex(char *line, t_cub *cub);
void			ft_check_res(char **splt);
void			ft_check_spaces(char **color);
#endif
