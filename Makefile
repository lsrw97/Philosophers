
SRCS	=	main2.c

OBJS	= ${SRCS:.c=.o}

NAME	= philo2.a

CC		= gcc

AR		= ar rcs

RM		= rm -rf

CFLAGS		=	 -I$(INC) -g -fsanitize=thread #  -fsanitize=address
all:	philo

philo: ${NAME}
	gcc ${NAME} ${CFLAGS} -o philo

$(NAME):	$(OBJS)
	ar rcs ${NAME} ${OBJS}

clean:
		$(RM) $(OBJS) $(BOBJ) 

fclean: 
	$(RM) $(NAME) $(OBJS) push_swap 

re:
	${MAKE} fclean
	${MAKE}

.PHONY:		all clean fclean re