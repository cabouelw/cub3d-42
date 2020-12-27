/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:24:03 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 18:00:09 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cnt_sprites(t_cub *cub)
{
	t_bcl	s;

	cub->nb_sprt = 0;
	s.i = 0;
	while (s.i < cub->prs.nb_line)
	{
		s.j = 0;
		while (s.j < cub->prs.big)
		{
			if (cub->prs.n_map[s.i][s.j] == '2')
				cub->nb_sprt++;
			s.j++;
		}
		s.i++;
	}
}

void	list_sprites(t_sprt *sprt, t_cub *cub)
{
	t_bcl		s;
	t_sprt		temp;

	s.i = 0;
	while (s.i < cub->nb_sprt)
	{
		s.j = s.i;
		while (s.j < cub->nb_sprt)
		{
			if (sprt[s.i].dist < sprt[s.j].dist)
			{
				temp = sprt[s.j];
				sprt[s.j] = sprt[s.i];
				sprt[s.i] = temp;
			}
			s.j++;
		}
		s.i++;
	}
	s.i = 0;
	cub->sprt = sprt;
}

void	sprtes_pos(t_cub *cub)
{
	t_bcl	s;
	int		num_sprt;

	s.i = 0;
	num_sprt = 0;
	while (cub->prs.n_map[s.i] && num_sprt < cub->nb_sprt)
	{
		s.j = 0;
		while (s.j < (int)ft_strlen(cub->prs.n_map[s.i]))
		{
			if (cub->prs.n_map[s.i][s.j] == '2')
			{
				cub->sprt[num_sprt].pos.x = s.i * TILE_SIZE + TILE_SIZE / 2;
				cub->sprt[num_sprt].pos.y = s.j * TILE_SIZE + TILE_SIZE / 2;
				cub->sprt[num_sprt].dist =\
					get_dis(cub->sprt[num_sprt].pos, cub->mlx.pos);
				num_sprt++;
			}
			s.j++;
		}
		s.i++;
	}
}

void	sprites(t_cub *cub)
{
	int		nb_sprt;

	sprtes_pos(cub);
	list_sprites(cub->sprt, cub);
	nb_sprt = 0;
	while (nb_sprt < cub->nb_sprt)
	{
		cub->temp_sprt = cub->sprt[nb_sprt];
		calcul_sprites(cub);
		nb_sprt++;
	}
}
