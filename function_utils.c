/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:32:32 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 19:48:07 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		isdown(float angle)
{
	return (angle > 0 && angle < PI);
}

int		isup(float angle)
{
	return (!isdown(angle));
}

int		isrght(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

int		isleft(float angle)
{
	return (!isrght(angle));
}

void	frame_helper(float wallstripheight, float start, float ray, t_cub *cub)
{
	int		color;
	t_pos	texoffset;
	int		n_wall;
	t_bcl	frm;
	int		pos;

	frm.j = 0;
	texoffset.x = (cub->isverthit) ? (int)cub->foundwallhit.y % TILE_SIZE :\
		(int)cub->foundwallhit.x % TILE_SIZE;
	n_wall = (cub->isverthit) ? wall_vert_face(cub) : wall_horz_face(cub);
	frm.i = cub->prs.h;
	while (frm.j < cub->prs.h)
	{
		frm.i--;
		if (frm.j >= start && frm.i > (int)(start))
		{
			texoffset.y = (frm.j - start) * ((float)64 / wallstripheight);
			color = cub->tex[n_wall].data[(int)((64 * floor(texoffset.y))\
				+ floor(texoffset.x))];
			cub->mlx.img[2].data[((frm.j * cub->prs.w) + (int)ray)] = color;
			pos = (((frm.i) * cub->prs.w) + (int)ray);
			(cub->argc == 3) ? color_to_rgb(color, cub, pos) : (void)0;
		}
		frm.j++;
	}
}
