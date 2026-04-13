# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/16 20:02:52 by hgutterr          #+#    #+#              #
#    Updated: 2026/04/13 15:45:52 by hgutterr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
CFLAGS		+= -Iinc -I$(LIBFT_DIR)
MLX_DIR		= mlx
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS 	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz


LIBFT_DIR	= inc/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		=	$(SRCDIR)/parser.c	\
				$(SRCDIR)/free.c	\
				$(SRCDIR)/check_elements.c \
				$(SRCDIR)/check_map.c \
				$(SRCDIR)/clean_string.c \
				$(SRCDIR)/elements_helper.c \
				$(SRCDIR)/get_elements.c \
				$(SRCDIR)/get_map.c \
				$(SRCDIR)/p_utils.c \
				$(SRCDIR)/read_file.c \
				$(SRCDIR)/exec.c \
				$(SRCDIR)/main.c



SRCDIR		= src
OBJDIR		= obj

OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "Ready!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

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
