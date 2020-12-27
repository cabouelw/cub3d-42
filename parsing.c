/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:22:23 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 18:22:09 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_color(char *line, t_cub *cub)
{
	char	**color;
	char	f_or_c;

	f_or_c = line[0];
	(cub->prs.var.valid_color == 2) ? ft_error("double input! ") : (void)0;
	if (!(color = ft_split(++line, ',')))
		ft_error("in Color lines !");
	ft_check_comma(line, color);
	if (f_or_c == 'F')
	{
		cub->prs.f.r = ft_atoi(color[0]);
		cub->prs.f.g = ft_atoi(color[1]);
		cub->prs.f.b = ft_atoi(color[2]);
		cub->prs.var.vld_f++;
	}
	else if (f_or_c == 'C')
	{
		cub->prs.c.r = ft_atoi(color[0]);
		cub->prs.c.g = ft_atoi(color[1]);
		cub->prs.c.b = ft_atoi(color[2]);
		cub->prs.var.vld_c++;
	}
	cub->prs.var.valid_color++;
	ft_free(color);
	check_color(cub);
}

void	get_tex(char *line, t_cub *cub)
{
	char	**splt;

	(cub->prs.var.valid_textues > 5) ? ft_error("double input! ") : (void)0;
	splt = ft_split(line, ' ');
	if (ft_isalpha(splt[0][0]) && splt[1] && ft_strlen(splt[0]) < 3)
	{
		if (splt[0][0] == 'N' && splt[0][1] == 'O')
			cub->prs.no = ft_strdup(splt[1]);
		else if (splt[0][0] == 'S' && splt[0][1] == 'O')
			cub->prs.so = ft_strdup(splt[1]);
		else if (splt[0][0] == 'W' && splt[0][1] == 'E')
			cub->prs.we = ft_strdup(splt[1]);
		else if (splt[0][0] == 'E' && splt[0][1] == 'A')
			cub->prs.ea = ft_strdup(splt[1]);
		else if (splt[0][0] == 'S' && splt[0][1] != 'O')
			cub->prs.s = ft_strdup(splt[1]);
		else
			ft_error("texture!");
		check_fils(splt[1], ".xpm");
		ft_free(splt);
		cub->prs.var.valid_textues++;
	}
	else
		ft_error("texture!");
	valid_tex(line, cub);
}

int		get_info(char *line, t_cub *cub)
{
	char			**splt;

	if (cub->prs.var.valid_resul == 1)
		ft_error("double input! ");
	splt = ft_split(line, ' ');
	ft_check_res(splt);
	(splt[1] && !ft_isdigit(splt[1][0])) ?\
		ft_error_in("invalid Resolution ", line) : (void)0;
	if (splt[0][0] == 'R')
	{
		cub->prs.w = ft_atoi(splt[1]);
		cub->prs.w = (cub->prs.w > 2560 || cub->prs.w < 0) ? 2560 : cub->prs.w;
		cub->prs.h = ft_atoi(splt[2]);
		cub->prs.h = (cub->prs.h > 1440 || cub->prs.h < 0) ? 1440 : cub->prs.h;
	}
	ft_free(splt);
	if (cub->prs.h <= 0 || cub->prs.w <= 0)
		ft_error("Resolution!");
	cub->prs.var.valid_resul = 1;
	return (1);
}

int		prsing(t_cub *cub)
{
	int		fd;
	t_bcl	bcl;
	int		big;

	if (!(fd = open(cub->prs.path, O_RDONLY)))
		return (0);
	bcl.i = 1;
	bcl.j = 0;
	big = 0;
	while (bcl.i == 1)
	{
		big = help_parsing(cub, &bcl, fd, big);
	}
	cub->prs.nb_line = bcl.j;
	ft_check_all_good(cub);
	making_map(big, cub);
	close(fd);
	return (1);
}
