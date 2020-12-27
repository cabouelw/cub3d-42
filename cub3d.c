/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:14:51 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/26 16:37:20 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(char **ptr)
{
	int i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

float	get_dis(t_pos dprt, t_pos fin)
{
	return (sqrt(((fin.x - dprt.x) * (fin.x - dprt.x)) +\
			((fin.y - dprt.y) * (fin.y - dprt.y))));
}

void	move_player(t_cub *cub)
{
	float angle;
	float x;
	float y;

	if (cub->keyboard[1])
		angle = PI;
	else if (cub->keyboard[2])
		angle = PI / 2;
	else if (cub->keyboard[0])
		angle = 3 * PI / 2;
	else
		angle = 0;
	x = cub->mlx.pos.x + cub->mlx.size_pers * cos(cub->mlx.view_angle + angle);
	y = cub->mlx.pos.y + cub->mlx.size_pers * sin(cub->mlx.view_angle + angle);
	if (!haswallat(x, y, cub) && !hassprtat(x, y, cub))
	{
		cub->mlx.pos.x = x;
		cub->mlx.pos.y = y;
	}
}

void	ft_initialize(t_cub *cub)
{
	int		i;

	cub->prs.var = (struct s_check){0};
	prsing(cub);
	cnt_sprites(cub);
	cub->sprt = (t_sprt*)malloc(sizeof(t_sprt) * cub->nb_sprt);
	if (cub->argc == 3)
		cub->bmp = (char *)malloc(cub->prs.h * cub->prs.w * 3);
	cub->fov = (60 * (PI / 180));
	cub->mlx.size_pers = MOVE_SPEED;
	cub->mlx.mlx_ptr = mlx_init();
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr,\
		cub->prs.w, cub->prs.h, "CUB3D");
	cub->mlx.half_of_windows = cub->prs.h / 2;
	i = 0;
	while (i < 300)
	{
		cub->keyboard[i] = 0;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_cub	cub;

	(argc < 2 || argc > 3) ? ft_error("Invalid arguments! ") : (void)0;
	if ((open(argv[1], O_RDONLY)) == -1)
		ft_error_in("Filename doesn't exist: ", argv[1]);
	check_fils(argv[1], ".cub");
	cub.argc = argc;
	cub.prs.path = argv[1];
	ft_initialize(&cub);
	img_loading(&cub);
	load_textures(&cub);
	draw_all_first(&cub);
	update(&cub);
	if (argc == 3 && ft_strlen("--save") == ft_strlen(argv[2]) &&\
		!ft_strncmp("--save", argv[2], ft_strlen("--save")))
		ft_bmp(&cub);
	(argc == 3) ? ft_error("aka : --save") : (void)0;
	mlx_hook(cub.mlx.win_ptr, 2, 0, key_pressed, &cub);
	mlx_hook(cub.mlx.win_ptr, 3, 0, key_released, &cub);
	mlx_hook(cub.mlx.win_ptr, 17, 0, exit_cub, &cub);
	mlx_loop_hook(cub.mlx.mlx_ptr, key_press, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	return (0);
}
