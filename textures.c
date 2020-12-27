/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:26:37 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 18:06:52 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		wall_horz_face(t_cub *cub)
{
	int		tex_num;

	if (cub->mlx.angle < 2 * PI && cub->mlx.angle > PI)
		tex_num = 3;
	else
		tex_num = 2;
	return (tex_num);
}

int		wall_vert_face(t_cub *cub)
{
	int		tex_num;

	if (cub->mlx.angle < PI / 2 || cub->mlx.angle > 3 * PI / 2)
		tex_num = 0;
	else
		tex_num = 1;
	return (tex_num);
}

void	img_loading(t_cub *cub)
{
	int		tile;

	tile = (TILE_SIZE * MINI_MAP);
	cub->mlx.img[0].img_ptr = mlx_new_image(cub->mlx.mlx_ptr, tile, tile);
	cub->mlx.img[0].data = (int *)mlx_get_data_addr(cub->mlx.img[0].img_ptr,\
		&cub->mlx.img[0].bpp, &cub->mlx.img[0].size_l, &cub->mlx.img[0].endian);
	cub->mlx.img[1].img_ptr = mlx_new_image(cub->mlx.mlx_ptr, tile, tile);
	cub->mlx.img[1].data = (int *)mlx_get_data_addr(cub->mlx.img[1].img_ptr,\
		&cub->mlx.img[1].bpp, &cub->mlx.img[1].size_l, &cub->mlx.img[1].endian);
	cub->mlx.img[3].img_ptr = mlx_new_image(cub->mlx.mlx_ptr, tile, tile);
	cub->mlx.img[3].data = (int *)mlx_get_data_addr(cub->mlx.img[3].img_ptr,\
		&cub->mlx.img[3].bpp, &cub->mlx.img[3].size_l, &cub->mlx.img[3].endian);
}

void	load_textures(t_cub *cub)
{
	cub->tex[0].ptr = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,\
		cub->prs.no, &cub->tex[0].width, &cub->tex[0].height);
	cub->tex[0].data = (int*)mlx_get_data_addr(cub->tex[0].ptr,\
		&cub->tex[0].bpp, &cub->tex[0].size_line, &cub->tex[0].endian);
	cub->tex[1].ptr = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,\
		cub->prs.so, &cub->tex[1].width, &cub->tex[1].height);
	cub->tex[1].data = (int *)mlx_get_data_addr(cub->tex[1].ptr,\
		&cub->tex[1].bpp, &cub->tex[1].size_line, &cub->tex[1].endian);
	cub->tex[2].ptr = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,\
		cub->prs.ea, &cub->tex[2].width, &cub->tex[2].height);
	cub->tex[2].data = (int *)mlx_get_data_addr(cub->tex[2].ptr,\
		&cub->tex[2].bpp, &cub->tex[2].size_line, &cub->tex[2].endian);
	cub->tex[3].ptr = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,\
		cub->prs.we, &cub->tex[3].width, &cub->tex[3].height);
	cub->tex[3].data = (int *)mlx_get_data_addr(cub->tex[3].ptr,\
		&cub->tex[3].bpp, &cub->tex[3].size_line, &cub->tex[3].endian);
	cub->tex[4].ptr = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,\
		cub->prs.s, &cub->tex[4].width, &cub->tex[4].height);
	cub->tex[4].data = (int *)mlx_get_data_addr(cub->tex[4].ptr,\
		&cub->tex[4].bpp, &cub->tex[4].size_line, &cub->tex[4].endian);
}

int		rgb(t_clr rgb)
{
	int		color;

	color = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
	return (color);
}
