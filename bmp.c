/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:12:02 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/23 15:22:49 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_info(t_cub *cub, char *temp, int filesize)
{
	temp[0] = ('B');
	temp[1] = ('M');
	temp[2] = (filesize);
	temp[3] = (filesize >> 8);
	temp[4] = (filesize >> 16);
	temp[10] = (54);
	temp[14] = (40);
	temp[18] = (cub->prs.w);
	temp[19] = (cub->prs.w >> 8);
	temp[20] = (cub->prs.w >> 16);
	temp[21] = (cub->prs.w >> 24);
	temp[22] = (cub->prs.h);
	temp[23] = (cub->prs.h >> 8);
	temp[24] = (cub->prs.h >> 16);
	temp[25] = (cub->prs.h >> 24);
	temp[26] = (1);
	temp[28] = (24);
}

void	file_header_info(t_cub *cub)
{
	char	temp[54];
	int		pad;
	char	tabpad[3];
	int		i;
	int		filesize;

	pad = (4 - (cub->prs.w * 3) % 4) % 4;
	filesize = 54 + cub->prs.h * cub->prs.w * 3;
	ft_memset(tabpad, 0, 3);
	ft_memset(temp, 0, 54);
	file_info(cub, temp, filesize);
	write(cub->fd, temp, 54);
	i = 0;
	while (i < cub->prs.h)
	{
		write(cub->fd, cub->bmp + (i * cub->prs.w * 3), cub->prs.w * 3);
		write(cub->fd, tabpad, pad);
		i++;
	}
}

void	ft_bmp(t_cub *cub)
{
	cub->fd = open("Screenshot.bmp", O_WRONLY | O_CREAT, 0777);
	file_header_info(cub);
	ft_msg("saved!");
}

void	rgb_to_bmp(t_clr color, t_cub *cub, int pos)
{
	cub->bmp[pos * 3 + 2] = color.r;
	cub->bmp[pos * 3 + 1] = color.g;
	cub->bmp[pos * 3 + 0] = color.b;
}

void	color_to_rgb(int color, t_cub *cub, int pos)
{
	(pos > cub->prs.h * cub->prs.w * 3) ? ft_error("BMP! ") : (void)0;
	cub->bmp[pos * 3 + 2] = color >> 16;
	cub->bmp[pos * 3 + 1] = color >> 8;
	cub->bmp[pos * 3 + 0] = color;
}
