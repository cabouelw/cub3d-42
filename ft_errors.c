/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:26:24 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 15:23:39 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *msg)
{
	ft_putstr_fd("ERROR\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	ft_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

void	ft_error_in(char *msg, char *var)
{
	ft_putstr_fd("ERROR\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	update(t_cub *cub)
{
	mlx_clear_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	draw_3d(cub);
}

void	ft_check_comma(char *line, char **color)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	i = 0;
	while (i < (int)ft_strlen(line))
	{
		if (line[i] == ',')
			cnt++;
		i++;
	}
	i = 0;
	while (color[i])
		i++;
	if (cnt != 2 || i != 3)
		ft_error_in("invalid color! ", line);
	i = 1;
	while (line[i] != '\0')
		if (ft_isdigit(line[i]) || line[i] == ',' || line[i] == ' ')
			i++;
		else
			ft_error_in("invalid color! ", line);
	ft_check_spaces(color);
}
