# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 12:50:04 by cabouelw          #+#    #+#              #
#    Updated: 2020/12/26 19:13:58 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC =	cub3d.c\
		keys.c\
		draw.c\
		ft_calcul.c\
		textures.c\
		handl_sprites.c\
		draw_sprites.c\
		parsing.c\
		parssing_2.c\
		libft/ft_isdigit.c\
		libft/ft_strncmp.c\
		libft/ft_atoi.c\
		libft/ft_memset.c\
		libft/ft_putstr_fd.c\
		libft/ft_putchar_fd.c\
		libft/ft_memcmp.c\
		libft/ft_isalpha.c\
		libft/ft_split.c\
		map.c\
		get_next_line/get_next_line_utils.c\
		get_next_line/get_next_line.c\
		ft_errors.c\
		ft_check.c\
		ft_check_prs.c\
		function_utils.c\
		bmp.c\
		ft_check_all.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all