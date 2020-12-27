/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:58:13 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 18:22:26 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_all_good(t_cub *cub)
{
	if (cub->prs.var.vld_c == 0 || cub->prs.var.vld_f == 0)
		ft_error("Color missing!");
	else if (cub->prs.var.vld_ea != 1 || cub->prs.var.vld_no != 1\
		|| cub->prs.var.vld_so != 1 || cub->prs.var.vld_we != 1 \
		|| cub->prs.var.vld_s != 1)
		ft_error("Texture Missing! ");
	else if (cub->prs.var.valid_resul != 1)
		ft_error("Resolution Missing! ");
	else if (cub->prs.var.vld_map != 1)
		ft_error("Map missing! ");
}

void	valid_tex(char *line, t_cub *cub)
{
	if ((line[0] == 'N') && cub->prs.var.vld_no == 0)
		cub->prs.var.vld_no = 1;
	else if (line[0] == 'S' && line[1] == 'O' && cub->prs.var.vld_so == 0)
		cub->prs.var.vld_so = 1;
	else if (line[0] == 'S' && line[1] != 'O' && cub->prs.var.vld_s == 0)
		cub->prs.var.vld_s = 1;
	else if (line[0] == 'E' && cub->prs.var.vld_ea == 0)
		cub->prs.var.vld_ea = 1;
	else if (line[0] == 'W' && cub->prs.var.vld_we == 0)
		cub->prs.var.vld_we = 1;
	else
		ft_error("Double Texture! ");
}

void	ft_check_res(char **splt)
{
	int		cnt;
	int		i;

	i = 0;
	cnt = 0;
	while (splt[cnt])
		cnt++;
	if (cnt != 3 || splt[0][1])
		ft_error_in("Invalid Resolution ", *splt);
	cnt = 1;
	while (splt[cnt])
	{
		i = 0;
		while (splt[cnt][i])
			(ft_isdigit(splt[cnt][i])) ? i++ :\
				ft_error_in("Invalid Resolution ", splt[cnt]);
		cnt++;
	}
}
