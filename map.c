/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:28:13 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 14:21:54 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_all_first(t_cub *cub)
{
	t_bcl	map;

	map.i = 0;
	while (cub->prs.n_map[map.i])
	{
		map.j = 0;
		while (map.j < (int)ft_strlen(cub->prs.n_map[map.i]))
		{
			if (ft_isalpha(cub->prs.n_map[map.i][map.j]))
			{
				ft_player_angle(cub->prs.n_map[map.i][map.j], cub);
				cub->mlx.pos.x = (map.i + 0.6) * TILE_SIZE;
				cub->mlx.pos.y = (map.j + 0.6) * TILE_SIZE;
			}
			map.j++;
		}
		map.i++;
	}
}

void	fixing_angle(t_cub *cub)
{
	if (cub->mlx.angle < 0)
		cub->mlx.angle += 2 * PI;
	if (cub->mlx.angle >= 2 * PI)
		cub->mlx.angle -= 2 * PI;
	if (cub->mlx.view_angle < 0)
		cub->mlx.view_angle += 2 * PI;
	if (cub->mlx.view_angle > 2 * PI)
		cub->mlx.view_angle -= 2 * PI;
}

void	help_get_map(char *line, int t, t_cub *cub)
{
	char	**map;
	int		j;

	map = (char**)malloc((t + 2) * sizeof(char*));
	j = 0;
	while (cub->prs.map[j])
	{
		map[j] = ft_strdup(cub->prs.map[j]);
		j++;
	}
	ft_free(cub->prs.map);
	map[j] = ft_strdup(line);
	map[j + 1] = NULL;
	cub->prs.map = (char**)malloc((t + 2) * sizeof(char*));
	j = 0;
	while (map[j])
	{
		cub->prs.map[j] = ft_strdup(map[j]);
		j++;
	}
	ft_free(map);
	cub->prs.map[j] = NULL;
}

void	making_map(int big, t_cub *cub)
{
	t_bcl	m;

	m.i = 0;
	cub->prs.n_map = (char**)malloc((cub->prs.nb_line + 1) * sizeof(char*));
	cub->prs.n_map[cub->prs.nb_line] = NULL;
	while (m.i < cub->prs.nb_line)
	{
		m.j = 0;
		cub->prs.n_map[m.i] = (char*)malloc((big + 1) * sizeof(char));
		cub->prs.n_map[m.i][big] = '\0';
		ft_memset(cub->prs.n_map[m.i], ' ', big);
		while (cub->prs.map[m.i][m.j])
		{
			cub->prs.n_map[m.i][m.j] = cub->prs.map[m.i][m.j];
			m.j++;
		}
		m.i++;
	}
	ft_free(cub->prs.map);
	cub->prs.big = big;
	check_player(cub);
	ft_check_map(cub);
}

void	get_map(char *line, int t, t_cub *cub)
{
	if (t == 0)
	{
		cub->prs.map = (char**)malloc(2 * sizeof(char*));
		cub->prs.map[0] = ft_strdup(line);
		cub->prs.map[1] = NULL;
	}
	else
		help_get_map(line, t, cub);
	ft_mapline_check(cub->prs.map[t], cub);
}
