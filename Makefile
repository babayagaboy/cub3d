

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -Iincludes -I$(LIBFT_DIR)
#CFLAGS += -I"$(shell brew --prefix readline)/include"

#LDFLAGS = -L"$(shell brew --prefix readline)/lib"

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(SRCDIR)/parser.c


SRCDIR = src
OBJDIR = obj

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re