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

SRCS = shell.c\
	exec.c\
	exec_utils.c\
	lstUtils.c\
	lstutils2.c\
	syntax_error.c\
	heredoc.c\
	token_util.c\
	token_classify_utils.c\
	state_manage.c\
	parse.c\
	parse_utils.c\
	parse_utils2.c\
	parse_utils3.c\
	expand.c\
	expand_utils.c\
	expand_utils2.c\
	expand_utils3.c\
	buildin.c\
	ft_cd.c\
	ft_pwd.c\
	ft_echo.c\
	ft_exit.c\
	ft_export.c\
	ft_export_utils.c\
	ft_export_utils2.c\
	ft_env.c\
	ft_unset.c\
	redirect.c\
	env_utils.c\
	error.c\
	termcap.c\
	termcap_utils.c\
	termcap_utils2.c\
	doubly_lstUtils.c\
	doubly_lstutils2.c\
	signal.c\

B_SRCS = $(SRCS)

CFLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:%.c=%.o)

CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS)  $(LIBFT) -ltermcap -o $(NAME)

debug: CFLAGS += -g3
debug: re

bonus: $(B_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(B_OBJS) shell.c $(LIBFT) -ltermcap -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

sani:
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) shell.c $(LIBFT) -ltermcap -o $(NAME)

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
