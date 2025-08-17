
NAME = ./minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 

OBJET = $(SRC:.c=.o)

SRC = 	main/else.c	\
	main/signals.c	\
	main/main.c	\
	builts_in/builts_in.c	\
	builts_in/cd.c   \
	builts_in/echo.c   \
	builts_in/else.c   \
	builts_in/exit.c   \
	builts_in/export_annex.c   \
	builts_in/export.c   \
	builts_in/pwd.c   \
	builts_in/unset.c   \
	exec/path_checker.c	\
	exec/dup_maker_utils.c     \
	exec/dup_maker.c     \
	exec/else.c     \
	exec/exe.c     \
	exec/exe2.c     \
	exec/file_opener.c     \
	exec/file_opener2.c     \
	exec/free_utils.c     \
	exec/free_utils2.c     \
	exec/pipex.c     \
	syntaxer_parser_tokenizer/args_set.c	\
      	syntaxer_parser_tokenizer/args_clr.c	\
	syntaxer_parser_tokenizer/else.c    \
	syntaxer_parser_tokenizer/syntaxer.c    \
	syntaxer_parser_tokenizer/getenv.c    \
	syntaxer_parser_tokenizer/list.c    \
	syntaxer_parser_tokenizer/else2.c    \
	syntaxer_parser_tokenizer/cmdsplit.c    \
	syntaxer_parser_tokenizer/syntaxer2.c    \
	syntaxer_parser_tokenizer/wrdsplit2.c    \
	syntaxer_parser_tokenizer/wrdsplit.c    \
	syntaxer_parser_tokenizer/killquote.c    \
	libft/ft_itoa.c				\
	libft/ft_atoi.c				\
	libft/ft_bzero.c				\
	libft/ft_split.c				\
	libft/ft_memcmp.c				\
	libft/ft_memchr.c				\
	libft/ft_memcpy.c				\
	libft/ft_memset.c				\
	libft/ft_strchr.c				\
	libft/ft_strlen.c				\
	libft/ft_calloc.c				\
	libft/ft_substr.c				\
	libft/ft_strdup.c				\
	libft/ft_strlcat.c				\
	libft/ft_isalnum.c				\
	libft/ft_isalpha.c				\
	libft/ft_isascii.c				\
	libft/ft_isdigit.c				\
	libft/ft_isprint.c				\
	libft/ft_strncmp.c				\
	libft/ft_strnstr.c				\
	libft/ft_strrchr.c				\
	libft/ft_tolower.c				\
	libft/ft_toupper.c				\
	libft/ft_strtrim.c				\
	libft/ft_memmove.c				\
	libft/ft_strjoin.c				\
	libft/ft_strlcpy.c				\
	libft/ft_strmapi.c				\
	libft/ft_striteri.c			\
	libft/ft_putnbr_fd.c			\
	libft/ft_putstr_fd.c			\
	libft/ft_putchar_fd.c			\
	libft/ft_putendl_fd.c			\
	libft/printf_ex/ft_printf.c	\
	libft/printf_ex/put_x.c		\
	libft/printf_ex/put_x2.c	\

all: $(NAME)

$(NAME): $(OBJET)
	$(CC) $(CFLAGS) $(OBJET) -o $(NAME) -lreadline

test : $(OBJET)
	echo

clean:
	rm -f $(OBJET) ./minishell

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
