# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myivanov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/16 20:02:52 by hgutterr          #+#    #+#              #
#    Updated: 2026/03/24 16:03:11 by myivanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -Iinc -I$(LIBFT_DIR)
#MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm -lbsd 

#CFLAGS += -I"$(shell brew --prefix readline)/include"

#LDFLAGS = -L"$(shell brew --prefix readline)/lib"

LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	$(SRCDIR)/parser.c \



SRCDIR = src
OBJDIR = obj

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -no-pie -o $(NAME)
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