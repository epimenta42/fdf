# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epimenta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/29 12:37:22 by epimenta          #+#    #+#              #
#    Updated: 2017/08/31 20:35:49 by epimenta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = $(addprefix ./src/, main.c \
				read.c \
				error.c \
				delete.c \
				window_scl.c \
				mlx.c \
				mlx_bis.c \
				render.c \
				bresenham.c \
				color.c)

OBJ = $(addprefix ./obj/, $(notdir $(SRC:.c=.o)))

PATHFT = ./libft

FLAGS = -Wall -Werror -Wextra

INCLUDE = -I ./include

MACOSVERS := $(shell (sw_vers -productVersion | cut -b 1-5))

SIERRA = ./mlx/sierra

ELCAPITAN = ./mlx/el_capitan

LIBFT = -L$(PATHFT) -lft

OPENCL = -framework OpenCL

ifeq ($(MACOSVERS),10.11)
	MLXPATH = -L$(ELCAPITAN)
else ifeq ($(MACOSVERS),10.12)
	MLXPATH = -L$(SIERRA)
endif

MLX = $(MLXPATH) -lmlx -framework OpenGL -framework Appkit

all: libft.a mlx.a $(NAME)

libft.a:
	make -C $(PATHFT)

mlx.a:
ifeq ($(MACOSVERS),10.11)
	make -C $(ELCAPITAN)
else ifeq ($(MACOSVERS),10.12)
	make -C $(SIERRA)
endif

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(INCLUDE) $(LIBFT) $(MLX) $(OPENCL) $(OBJ)

./obj/%.o: ./src/%.c
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $^

clean:
	make -C $(ELCAPITAN) clean
	make -C $(SIERRA) clean
	make -C $(PATHFT) clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C $(PATHFT) fclean
	/bin/rm -f $(NAME)

re: fclean all
