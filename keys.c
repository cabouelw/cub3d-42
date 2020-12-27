/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:26:49 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/22 18:04:51 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int keycode, t_cub *cub)
{
	cub->keyboard[keycode] = 1;
	return (0);
}

int		key_released(int keycode, t_cub *cub)
{
	cub->keyboard[keycode] = 0;
	return (0);
}

int		exit_cub(t_cub *cub)
{
	mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	ft_msg("See U next Time ;)");
	return (1);
}

int		key_press(t_cub *cub)
{
	if (cub->keyboard[124] || cub->keyboard[123])
		update_angle(cub);
	if ((cub->keyboard[1] || cub->keyboard[2] || cub->keyboard[0])\
		|| cub->keyboard[13])
		move_player(cub);
	if (cub->keyboard[53])
	{
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		ft_msg("See U next Time ;)");
	}
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img[2].img_ptr);
	update(cub);
	return (0);
}

void	update_angle(t_cub *cub)
{
	if (cub->keyboard[124])
		cub->mlx.view_angle += RETATION_SPEED;
	else
		cub->mlx.view_angle -= RETATION_SPEED;
	fixing_angle(cub);
}
