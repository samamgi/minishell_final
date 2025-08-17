
NAME = libftprintf.a

CC = cc

AR = ar

CFLAGS = -Werror -Wall -Wextra

SRC = ft_printf.c \
	put_x.c \
	put_x2.c \

OBJET = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJET)
	$(AR) rcs $(NAME) $(OBJET)

#$(OBJET): $(SRC)
#	$(CC) $(CFLAGS) -c $< -o $@
	
test : $(OBJET)
	echo

clean:
	rm -f $(OBJET)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
