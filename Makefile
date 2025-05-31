# Only include each .c file once
SRCS = \
	srcs/main/main.c \
	srcs/lexing/split.c \
	srcs/nodes/nodes.c \
	srcs/init/init.c \
	srcs/clean/free.c \
	srcs/clean/free_utils.c \
	srcs/lexing/qoutes.c \
	srcs/lexing/splits_utils.c \
	srcs/expander/envp.c \
	srcs/expander/expander.c \
	srcs/excution/excution.c \
	srcs/exit/exit.c \
	srcs/signals/signals.c \
	srcs/lexing/split_cmds.c \
	srcs/built_ins/echo.c \
	srcs/built_ins/cd.c \
	srcs/built_ins/env.c \
	srcs/built_ins/export.c \
	srcs/built_ins/pwd.c \
	srcs/built_ins/unset.c \
	srcs/built_ins/built_in.c

# Convert srcs/ to objs/
OBJS = $(SRCS:srcs/%.c=objs/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline -lncurses -L$(LIB_PATH) -lft
INCLUDES = -I./includes -I./libft

LIB_PATH = ./libft
NAME = minishell

all: LIB $(NAME)

LIB:
	$(MAKE) -C $(LIB_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Make sure to create obj dirs as needed
objs/%.o: srcs/%.c includes/minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf objs
	$(MAKE) clean -C $(LIB_PATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_PATH)

re: fclean all

.PHONY: all clean fclean re LIB
