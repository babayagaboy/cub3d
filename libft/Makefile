# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 16:55:10 by hgutterr          #+#    #+#              #
#    Updated: 2025/04/08 16:55:12 by hgutterr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEPS = includes
SRCDIR = .
OBJDIR = obj

SRCS = \
	ft_atoi.c ft_memset.c ft_strlcpy.c \
	ft_bzero.c ft_putchar_fd.c ft_strlen.c \
	ft_calloc.c ft_putendl_fd.c ft_strmapi.c \
	ft_isalnum.c ft_putnbr_fd.c ft_strncmp.c \
	ft_isalpha.c ft_putstr_fd.c ft_strnstr.c \
	ft_isascii.c ft_split.c ft_strrchr.c \
	ft_isdigit.c ft_strchr.c ft_strtrim.c \
	ft_isprint.c ft_memchr.c ft_strdup.c ft_substr.c \
	ft_itoa.c ft_memcmp.c ft_striteri.c ft_tolower.c \
	ft_memcpy.c ft_strjoin.c ft_toupper.c \
	ft_memmove.c ft_strlcat.c

BONUS_SRCS = \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstnew.c \
	ft_lstmap.c ft_lstlast.c ft_lstiter.c ft_lstsize.c \
	ft_lstclear.c ft_lstdelone.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJDIR)/%.o)

NAME = libft.a

all: $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(DEPS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(BONUS_OBJS) $(NAME)
	@echo "Adding bonus objects to $(NAME)..."
	ar r $(NAME) $(BONUS_OBJS)
	@touch .bonus

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) .bonus

re: fclean all

.PHONY: all clean fclean re bonus