NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c src/parse.c src/init.c src/launch.c src/routine.c \
	src/actions.c src/monitor.c src/time.c src/log.c src/cleanup.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
