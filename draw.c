/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:35:14 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 18:12:23 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	frame(int ray, float start, float wallstripheight, t_cub *cub)
{
	t_bcl	frm;

	frm.j = 0;
	frm.i = 0;
	while (frm.j < cub->prs.h)
	{
		if (frm.j < start)
		{
			cub->mlx.img[2].data[((frm.j * cub->prs.w) + ray)] =\
				rgb(cub->prs.c);
			(cub->argc == 3) ? rgb_to_bmp(cub->prs.f, cub,\
				(frm.j * cub->prs.w) + ray) : (void)0;
		}
		else if (frm.j > (wallstripheight + start))
		{
			cub->mlx.img[2].data[((frm.j * cub->prs.w) + ray)] =\
				rgb(cub->prs.f);
			(cub->argc == 3) ? rgb_to_bmp(cub->prs.c, cub,
				(frm.j * cub->prs.w) + ray) : (void)0;
		}
		frm.j++;
	}
	frame_helper(wallstripheight, start, ray, cub);
}

void	render3dprojectedwalls(float dist, int ray, float rayangle, t_cub *cub)
{
	float	distanceprojectionplane;
	float	wallstripheight;
	float	raydistance;

	raydistance = dist * cos(rayangle - cub->mlx.view_angle);
	distanceprojectionplane = (cub->prs.w / 2) / tan(cub->fov / 2);
	wallstripheight = (TILE_SIZE / raydistance) * distanceprojectionplane;
	frame(ray, cub->mlx.half_of_windows - (wallstripheight / 2),\
			wallstripheight, cub);
}

void	draw_3d(t_cub *cub)
{
	int		i;
	float	dis;

	i = 0;
	cub->mlx.img[2].img_ptr = mlx_new_image(cub->mlx.mlx_ptr,\
		cub->prs.w, cub->prs.h);
	cub->mlx.img[2].data = (int *)mlx_get_data_addr(cub->mlx.img[2].img_ptr,\
		&cub->mlx.img[2].bpp, &cub->mlx.img[2].size_l, &cub->mlx.img[2].endian);
	cub->mlx.angle = cub->mlx.view_angle - (cub->fov / 2);
	sprtes_pos(cub);
	while (i < cub->prs.w)
	{
		fixing_angle(cub);
		dis = finnal_dist(cub->mlx.angle, cub);
		cub->dist_wall[i] = dis;
		render3dprojectedwalls(dis, i, cub->mlx.angle, cub);
		cub->mlx.angle += (cub->fov / cub->prs.w);
		i++;
	}
	sprites(cub);
	mlx_put_image_to_window(cub->mlx.mlx_ptr,\
			cub->mlx.win_ptr, cub->mlx.img[2].img_ptr, 0, 0);
}
