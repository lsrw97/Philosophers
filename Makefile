
SRCS	=	main2.c \
			getter1.c \
			getter2.c \
			setter.c \
			createinit.c \
			time.c \
			utils.c \

OBJS	= ${SRCS:.c=.o}

NAME	= philo.a

CC		= gcc

AR		= ar rcs

RM		= rm -rf

CFLAGS		=	 -I$(INC) -g -fsanitize=address #  -fsanitize=address
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