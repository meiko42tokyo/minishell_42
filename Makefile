NAME := minishell

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	PLATFORM := LINUX
endif
ifeq ($(UNAME_S), Darwin)
	PLATFORM := MACOS
endif

ifeq ($(PLATFORM), LINUX)
endif

ifeq ($(PLATFORM), MACOS)
endif

SRCS = src/testShell.c\

CFLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

sani:
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all re fclean clean
