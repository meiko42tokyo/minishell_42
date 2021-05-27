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

SRCS = exec.c\
	lstUtils.c\
	parse.c\
	buildin.c\
	ft_cd.c\
	ft_pwd.c\

CFLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) shell.c $(LIBFT) -ltermcap -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

sani:
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LIBFT) -ltermcap -o $(NAME)

term: $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJS) doubly_lstUtils.c termcap.c termmain.c $(LIBFT)  -ltermcap -o termcap

termc:
	rm -f doubly_lstUtils.o termcap.o termmain.o
	rm -rf termcap.dSYM
	rm -f termcap 
	$(MAKE) fclean -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	rm -f shell.o
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all re fclean clean
