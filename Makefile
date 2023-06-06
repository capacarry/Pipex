NAME = pipex
HEADER = pipex.h 
CC = cc 
RM = rm -f 
CFLAGS = -Wall -Wextra -Werror -g
OBJS = $(SRC:.c=.o)
SRC = pipex_utils.c  path_and_check.c pipex.c ft_split.c	ft_free_all.c

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(^) -o $(@) 
all:	$(NAME)
clean:
		$(RM) $(OBJS)
fclean: clean
		$(RM) $(NAME)
re: fclean all