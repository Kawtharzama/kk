SRCS = srcs/main/main.c \
       srcs/lexing/split.c \
       srcs/nodes/nodes.c \
       srcs/init/init.c    \
	   srcs/clean/free.c	\
	   srcs/lexing/qoutes.c	\
	   srcs/lexing/splits_utils.c	\
	   srcs/expander/envp.c  \
	   srcs/expander/expander.c  \
	   srcs/excution/excution.c	\
	   srcs/exit/exit.c	\
	   srcs/signals/signals.c



OBJS = $(SRCS:srcs/%.c=objs/%.o) #ending with .c replace it with .o just as string 

CC = cc

CFLAGS= -Wall -Wextra -Werror -g 
LDFLAGS= -lreadline -lncurses -L$(LIB_PATH) -lft
INCLUDES= -I./includes -I./libft 

LIB_PATH = ./libft


#LIB = ./libft/libft.a


NAME = minishell

all: LIB $(NAME)

LIB:
	make -C $(LIB_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

objs/%.o : srcs/%.c  includes/minishell.h     #implicit rule , trace the header file    $@   $< $^ $1 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf objs 
	make clean -C $(LIB_PATH) 

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_PATH)	

re: fclean all

.PHONY: all clean fclean re LIB


