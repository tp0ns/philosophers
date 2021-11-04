SRCS	= main.c init.c close.c utils.c philo_utils.c routine.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror 

#-fsanitize=thread

INCLUDE = -lpthread

all:	$(NAME)

.PHONY:	clean fclean re bonus

$(NAME): $(OBJS)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDE)
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)