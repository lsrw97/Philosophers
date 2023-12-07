
SRCS	=	srcs/main.c \
			srcs/getter1.c \
			srcs/getter2.c \
			srcs/setter.c \
			srcs/createinit.c \
			srcs/time.c \
			srcs/utils.c \
			srcs/routines.c

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC		= cc

AR		= ar rcs

RM		= rm -rf

CFLAGS		= -Werror -Wall -Wextra -g -lpthread  #-fsanitize=address

all:	philo

philo: $(OBJS)
	cc $(OBJS) ${CFLAGS} -o ${NAME}

clean:
		$(RM) $(OBJS) $(BOBJ)

fclean: 
	$(RM) $(NAME) $(OBJS) philo 

re:
	${MAKE} fclean
	${MAKE}

.PHONY:		all clean fclean re
