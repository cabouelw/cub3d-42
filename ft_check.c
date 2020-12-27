/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:28:26 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 15:21:45 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(t_cub *cub)
{
	if (cub->prs.c.b > 255 || cub->prs.c.b < 0)
		ft_error("format color C:B!");
	if (cub->prs.c.g > 255 || cub->prs.c.g < 0)
		ft_error("format color C:G!");
	if (cub->prs.c.r > 255 || cub->prs.c.r < 0)
		ft_error("format color C:R!");
	if (cub->prs.f.b > 255 || cub->prs.f.b < 0)
		ft_error("format color F:R!");
	if (cub->prs.f.r > 255 || cub->prs.f.r < 0)
		ft_error("format color F:R!");
	if (cub->prs.f.g > 255 || cub->prs.f.g < 0)
		ft_error("format color F:R!");
}

void	check_fils(char *path, char *s)
{
	int		len;

	len = ft_strlen(path) - 4;
	if (open(path, O_RDONLY) == -1 || ft_memcmp(s, path + len, 4))
		ft_error_in("filename : ", path);
}

void	ft_mapline_check(char *line, t_cub *cub)
{
	t_bcl	b;

	b.i = 0;
	if (cub->prs.var.valid_color < 2 || cub->prs.var.valid_resul != 1\
		|| cub->prs.var.valid_textues < 5)
		ft_error_in("Map should be the last! ", line);
	while (line[b.i])
	{
		if (line[b.i] != ' ' && line[b.i] != '0' && line[b.i] != '1'\
			&& line[b.i] != 'W' && line[b.i] != 'S' && line[b.i] != 'N'\
			&& line[b.i] != 'E' && line[b.i] != '2')
			ft_error_in("map feild in: ", line);
		b.i++;
	}
}

void	check_player(t_cub *cub)
{
	t_bcl	m;
	int		check;

	m.i = 0;
	check = 0;
	while (m.i < cub->prs.nb_line)
	{
		m.j = 0;
		while (m.j < cub->prs.big)
		{
			if ((cub->prs.n_map[m.i][m.j] == 'N' ||\
						cub->prs.n_map[m.i][m.j] == 'E' ||\
						cub->prs.n_map[m.i][m.j] == 'S' ||\
						cub->prs.n_map[m.i][m.j] == 'W'))
				(check == 0) ? check = 1 :\
						ft_error("map should have 1 position for player !");
			m.j++;
		}
		m.i++;
	}
	(check == 0) ? ft_error("map have 0 position for player !") : 0;
}

void	ft_check_map(t_cub *cub)
{
	t_bcl bcl;

	check_last_col(cub);
	check_last_line(cub);
	bcl.i = 1;
	while (bcl.i < cub->prs.nb_line)
	{
		bcl.j = 1;
		while (bcl.j < cub->prs.big)
		{
			if (alpha_player(cub->prs.n_map[bcl.i][bcl.j]))
			{
				if (cub->prs.n_map[bcl.i][bcl.j - 1] == ' ' ||\
						cub->prs.n_map[bcl.i][bcl.j + 1] == ' ')
					ft_error_in("Should be 1 before Or after 0/2/P in: ",\
							cub->prs.n_map[bcl.i]);
				if (cub->prs.n_map[bcl.i - 1][bcl.j] == ' ' ||\
						cub->prs.n_map[bcl.i + 1][bcl.j] == ' ')
					ft_error_in("Should be 1 Above Or Blow 0/2/P in: ",\
							cub->prs.n_map[bcl.i]);
			}
			bcl.j++;
		}
		bcl.i++;
	}
}
