# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/16 20:02:52 by hgutterr          #+#    #+#              #
#    Updated: 2026/05/07 19:13:37 by hgutterr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
CFLAGS		+= -Iinc -I$(LIBFT_DIR)
CFLAGS		+= -O3 -march=native -flto -ftree-vectorize -funroll-loops -ffast-math
MLX_DIR		= mlx
MLX			= $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS 	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz


LIBFT_DIR	= inc/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		=	$(SRCDIR)/parser.c	\
				$(SRCDIR)/free.c	\
				$(SRCDIR)/free_utils.c \
				$(SRCDIR)/check_elements.c \
				$(SRCDIR)/handle_floor_ceiling.c \
				$(SRCDIR)/check_map.c \
				$(SRCDIR)/check_map_utils.c \
				$(SRCDIR)/check_doors.c \
				$(SRCDIR)/clean_string.c \
				$(SRCDIR)/elements_helper.c \
				$(SRCDIR)/get_elements.c \
				$(SRCDIR)/get_map.c \
				$(SRCDIR)/p_utils.c \
				$(SRCDIR)/read_file.c \
				$(SRCDIR)/textures.c \
				$(SRCDIR)/get_guns_sprite.c \
				$(SRCDIR)/get_attack_sprite.c \
				$(SRCDIR)/run_weapon_animation.c \
				$(SRCDIR)/minimap.c \
				$(SRCDIR)/dda.c \
				$(SRCDIR)/init.c \
				$(SRCDIR)/rays.c \
				$(SRCDIR)/time.c \
				$(SRCDIR)/draw.c \
				$(SRCDIR)/draw_attack_hud.c \
				$(SRCDIR)/draw_fc.c \
				$(SRCDIR)/draw_weapon_hud.c \
				$(SRCDIR)/handle_inputs.c \
				$(SRCDIR)/handle_mouse.c \
				$(SRCDIR)/handle_mouse_clicks.c \
				$(SRCDIR)/doors.c \
				$(SRCDIR)/door_utils.c \
				$(SRCDIR)/door_utils2.c \
				$(SRCDIR)/general_utils.c \
				$(SRCDIR)/move.c \
				$(SRCDIR)/start.c \
				$(SRCDIR)/main.c



SRCDIR		= src
OBJDIR		= obj

OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "Ready!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
