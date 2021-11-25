NAME		= philo

SRCS		=	main.c \
				monitor.c \
				philo.c \
				philo_action.c \
				utils.c \

OBJS		= $(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

.SILENT:

all :		$(NAME)

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
			echo "Complete"

.c.o :
			echo "Compiling $^"
			$(CC) $(CFLAGS) -c $^ -o $(^:.c=.o)

clean :
			$(RM) $(OBJS)

fclean :	clean
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re