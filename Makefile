NAME	= philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS	=	fct_libft.c \
			main.c \
			parsing.c \
			utils.c \
			days.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean flcean re