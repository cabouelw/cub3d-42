/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:32:24 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 18:03:10 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clcul_vert(t_pos step, t_pos vert, float rayangle, t_cub *cub)
{
	t_pos nextvert;

	nextvert.x = vert.x;
	nextvert.y = vert.y;
	if (nextvert.x >= 0 && nextvert.y >= 0)
		while (((int)nextvert.x / TILE_SIZE) < cub->prs.nb_line &&\
			(int)nextvert.y / TILE_SIZE < cub->prs.big)
		{
			if (haswallat(nextvert.x - isleft(rayangle), nextvert.y, cub))
			{
				cub->foundvertwallhit = 1;
				cub->vert_wallhit.x = nextvert.x;
				cub->vert_wallhit.y = nextvert.y;
				break ;
			}
			else
			{
				nextvert.y += step.y;
				nextvert.x += step.x;
			}
		}
}

void	clcul_horz(t_pos step, t_pos horz, float rayangle, t_cub *cub)
{
	t_pos	nexthorz;

	nexthorz.x = horz.x;
	nexthorz.y = horz.y;
	if (nexthorz.x >= 0 && nexthorz.y >= 0)
		while (((int)nexthorz.x / TILE_SIZE) < cub->prs.nb_line &&\
			((int)nexthorz.y / TILE_SIZE) < cub->prs.big)
		{
			if (haswallat(nexthorz.x, nexthorz.y - isup(rayangle), cub))
			{
				cub->foundhorzwallhit = 1;
				cub->horz_wallhit.x = nexthorz.x;
				cub->horz_wallhit.y = nexthorz.y;
				break ;
			}
			else
			{
				nexthorz.x += step.x;
				nexthorz.y += step.y;
			}
		}
}

void	get_first_vert_hitwall(float rayangle, t_cub *cub)
{
	t_pos step;
	t_pos vert;

	cub->foundvertwallhit = 0;
	cub->vert_wallhit.x = 0;
	cub->vert_wallhit.y = 0;
	vert.x = floor(cub->mlx.pos.x / TILE_SIZE) * TILE_SIZE;
	vert.x += (isrght(rayangle)) ? TILE_SIZE : 0;
	vert.y = cub->mlx.pos.y + (vert.x - cub->mlx.pos.x) * tan(rayangle);
	step.x = TILE_SIZE;
	step.x *= (isleft(rayangle)) ? -1 : 1;
	step.y = TILE_SIZE * tan(rayangle);
	step.y *= (step.y > 0 && isup(rayangle)) ? -1 : 1;
	step.y *= (step.y < 0 && isdown(rayangle)) ? -1 : 1;
	clcul_vert(step, vert, rayangle, cub);
}

void	get_first_horz_hitwall(float rayangle, t_cub *cub)
{
	t_pos step;
	t_pos horz;

	cub->foundhorzwallhit = 0;
	cub->horz_wallhit.x = 0;
	cub->horz_wallhit.y = 0;
	horz.y = floor(cub->mlx.pos.y / TILE_SIZE) * TILE_SIZE;
	horz.y += (isdown(rayangle)) ? TILE_SIZE : 0;
	horz.x = cub->mlx.pos.x + (horz.y - cub->mlx.pos.y) / tan(rayangle);
	step.y = TILE_SIZE;
	step.y *= (isup(rayangle)) ? -1 : 1;
	step.x = TILE_SIZE / tan(rayangle);
	step.x *= (step.x > 0 && (isleft(rayangle))) ? -1 : 1;
	step.x *= (step.x < 0 && (isrght(rayangle))) ? -1 : 1;
	clcul_horz(step, horz, rayangle, cub);
}

float	finnal_dist(float ray_angle, t_cub *cub)
{
	float dis_h;
	float dis_v;

	dis_v = INT_MAX;
	dis_h = INT_MAX;
	if (ray_angle < 0)
		ray_angle += 2 * PI;
	if (ray_angle >= 2 * PI)
		ray_angle -= 2 * PI;
	get_first_vert_hitwall(ray_angle, cub);
	get_first_horz_hitwall(ray_angle, cub);
	if (cub->foundhorzwallhit == 1)
		dis_h = get_dis(cub->mlx.pos, cub->horz_wallhit);
	if (cub->foundvertwallhit == 1)
		dis_v = get_dis(cub->mlx.pos, cub->vert_wallhit);
	cub->foundwallhit.x = (dis_h < dis_v) ? cub->horz_wallhit.x\
		: cub->vert_wallhit.x;
	cub->foundwallhit.y = (dis_h < dis_v) ? cub->horz_wallhit.y\
		: cub->vert_wallhit.y;
	cub->isverthit = (dis_h > dis_v) ? 1 : 0;
	return ((dis_h < dis_v) ? dis_h : dis_v);
}
