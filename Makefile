NAME		= philo

HEADER		= -I./philo.h

SRCS		= main.c monitor.c philo.c philo_action.c utils.c \

OBJS		= $(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-g3 -fsanitize=address
RM			= rm -rf

all :		$(NAME)

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(SRCS) $(HEADER) -o $(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -c $(SRCS)

clean :
			$(RM) $(OBJS)

fclean :	clean
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re