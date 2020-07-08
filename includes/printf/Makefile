NAME	=	libftprintf.a

SRCS	=	ft_convert_to_char.c \
			ft_print_finalstring.c \
			ft_print_hexadecimals.c \
			ft_print_numbers.c \
			ft_printf_char.c \
			ft_width.c \
			ft_precision.c	\
			ft_printf_printwpstr.c \
			ft_printf.c

OBJS	:= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I.
RM		= rm -f

all:	${NAME}

%.o: %.c
		${CC} ${CFLAGS} -c $< -o $@

%.o: libft/%.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}:${OBJS}
		make -C libft 
		ar rc ${NAME} libft/*.o ${OBJS}

debug:
		$(CC) $(CFLAGS) -g $(SRCS) libft/ft_*.c -I libft

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME} libft/*.o *.o

re:		fclean all
.PHONY: all clean fclean re
