/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:15:13 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 16:55:26 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		help_parsing(t_cub *cub, t_bcl *bcl, int fd, int big)
{
	char	*line;

	bcl->i = get_next_line(fd, &line);
	if (line[0] == 'R')
		get_info(line, cub);
	else if (line[0] == 'N' || line[0] == 'W' ||\
		line[0] == 'S' || line[0] == 'E')
		get_tex(line, cub);
	else if (line[0] == 'F' || line[0] == 'C')
		get_color(line, cub);
	else if (line[0] == ' ' || line[0] == '1' || alpha_player(*line))
	{
		cub->prs.var.vld_map = 1;
		get_map(line, bcl->j, cub);
		if (big < (int)ft_strlen(line))
			big = ft_strlen(line);
		bcl->j++;
	}
	else if (line[0])
		ft_error_in("invalid line! ", line);
	free(line);
	return (big);
}

void	ft_player_angle(char vec, t_cub *cub)
{
	if (vec == 'N')
		cub->mlx.view_angle = PI;
	else if (vec == 'S')
		cub->mlx.view_angle = 0;
	else if (vec == 'E')
		cub->mlx.view_angle = 3 * PI / 2;
	else if (vec == 'W')
		cub->mlx.view_angle = PI / 2;
	else
		ft_error("this not for spawning orientation! ");
}

void	ft_check_spaces(char **color)
{
	int		cnt;
	int		i;

	i = 0;
	while (color[i] != NULL)
	{
		cnt = 0;
		while (color[i][cnt] == ' ' && color[i][cnt] != '\0')
			cnt++;
		while (ft_isdigit(color[i][cnt]) && color[i][cnt] != '\0')
			cnt++;
		while (color[i][cnt] == ' ' && color[i][cnt] != '\0')
			cnt++;
		(ft_isdigit(color[i][cnt])) ? ft_error("invalid color! ") : (void)0;
		i++;
	}
	i = 0;
	while (color[i])
	{
		cnt = 0;
		while (color[i][cnt] == ' ' && color[i][cnt] != '\0')
			cnt++;
		(!ft_isdigit(color[i][cnt])) ? ft_error("invalid color! ") : (void)0;
		i++;
	}
}
