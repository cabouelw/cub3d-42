/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_prs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:29:07 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 19:47:50 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		alpha_player(char check)
{
	if (check == 'N' || check == 'E' || check == 'S' || check == 'W')
		return (1);
	else if (check == '0' || check == '2')
		return (1);
	return (0);
}

void	check_last_line(t_cub *cub)
{
	t_bcl	bcl;

	bcl.i = 0;
	while (bcl.i < cub->prs.big)
	{
		if (alpha_player(cub->prs.n_map[cub->prs.nb_line - 1][bcl.i]))
			ft_error_in("line Should end with 1 or spaces in: ",\
					cub->prs.n_map[cub->prs.nb_line - 1]);
		bcl.i++;
	}
	bcl.i = 0;
	while (bcl.i < cub->prs.big)
	{
		if (alpha_player(cub->prs.n_map[0][bcl.i]))
			ft_error_in("line Should start with 1 or spaces in: ",\
					cub->prs.n_map[0]);
		bcl.i++;
	}
}

void	check_last_col(t_cub *cub)
{
	t_bcl bcl;

	bcl.i = 0;
	while (bcl.i < cub->prs.nb_line)
	{
		if (alpha_player(cub->prs.n_map[bcl.i][cub->prs.big - 1]))
			ft_error_in("line Should end with 1 or spaces in: ",\
					cub->prs.n_map[bcl.i]);
		bcl.i++;
	}
	bcl.i = 0;
	while (bcl.i < cub->prs.nb_line)
	{
		if (alpha_player(cub->prs.n_map[bcl.i][0]))
			ft_error_in("line Should start with 1 or spaces in: ",\
					cub->prs.n_map[bcl.i]);
		bcl.i++;
	}
}

int		hassprtat(float x, float y, t_cub *cub)
{
	t_bcl	tst;

	tst.i = floor(x / TILE_SIZE);
	tst.j = floor(y / TILE_SIZE);
	if ((x < 0 || y < 0) || tst.i >= cub->prs.nb_line ||\
		tst.j >= (int)ft_strlen(cub->prs.n_map[tst.i]))
		return (1);
	if (cub->prs.n_map[tst.i][tst.j] == '2')
		return (1);
	return (0);
}

int		haswallat(float x, float y, t_cub *cub)
{
	t_bcl	tst;

	tst.i = floor(x / TILE_SIZE);
	tst.j = floor(y / TILE_SIZE);
	if ((x < 0 || y < 0) || tst.i >= cub->prs.nb_line ||\
		tst.j >= (int)ft_strlen(cub->prs.n_map[tst.i]))
		return (1);
	if (cub->prs.n_map[tst.i][tst.j] == '1')
		return (1);
	return (0);
}
