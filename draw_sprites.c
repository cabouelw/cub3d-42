/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:24:06 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 18:00:59 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fram(float start, float sprtheight, t_cub *cub, t_bcl *bcl)
{
	int		color;
	int		i;
	int		end;

	i = 0;
	end = (int)(sprtheight + start);
	while (bcl->j < sprtheight + start && bcl->j < cub->prs.h)
	{
		cub->temp_sprt.texoffset.y = (bcl->j - start) *\
			((float)TILE_SIZE / sprtheight);
		if (cub->temp_sprt.angle > -(cub->fov) &&\
			cub->temp_sprt.angle < (cub->fov))
		{
			i++;
			color = cub->tex[4].data[(int)((TILE_SIZE * floor(cub->\
				temp_sprt.texoffset.y)) + floor(cub->temp_sprt.texoffset.x))];
			if (color != 0 && bcl->i >= 0 && bcl->j >= 0)
			{
				cub->mlx.img[2].data[((bcl->j * cub->prs.w) + bcl->i)] = color;
				(cub->argc == 3) ? color_to_rgb(color, cub,\
					(((end - i) * cub->prs.w) + bcl->i)) : (void)0;
			}
		}
		bcl->j++;
	}
}

void	frame_sprt(int ray, float start, float sprtheight, t_cub *cub)
{
	t_bcl	bcl;

	bcl.i = ray;
	while (bcl.i < ray + (sprtheight) && bcl.i < cub->prs.w &&\
		bcl.i > -(sprtheight / 1.3))
	{
		bcl.j = start + 2;
		cub->temp_sprt.texoffset.x = (bcl.i - ray) *\
			((float)TILE_SIZE / sprtheight);
		if (cub->dist_wall[bcl.i] > cub->temp_sprt.dist && bcl.i < cub->prs.w)
			draw_fram(start, sprtheight, cub, &bcl);
		bcl.i++;
	}
}

void	calcul_sprites(t_cub *cub)
{
	float distanceprojectionplane;
	float wallstripheight;

	cub->temp_sprt.angle = acos((cub->temp_sprt.pos.x - cub->mlx.pos.x)\
		/ cub->temp_sprt.dist);
	cub->temp_sprt.pos.y - cub->mlx.pos.y < 0 ? cub->temp_sprt.angle *= -1\
		: cub->temp_sprt.angle;
	cub->temp_sprt.angle -= cub->mlx.view_angle;
	if (cub->temp_sprt.angle < -PI)
		cub->temp_sprt.angle += 2. * PI;
	if (cub->temp_sprt.angle > PI)
		cub->temp_sprt.angle -= 2. * PI;
	cub->temp_sprt.loc = cub->prs.w / cub->fov *\
		cub->temp_sprt.angle + cub->prs.w / 2;
	distanceprojectionplane = (cub->prs.w / 2) / tan(cub->fov / 2);
	wallstripheight = (TILE_SIZE / cub->temp_sprt.dist) *\
		distanceprojectionplane;
	frame_sprt(cub->temp_sprt.loc - (wallstripheight / 2)\
		, cub->mlx.half_of_windows -\
		(wallstripheight / 2), wallstripheight, cub);
}
