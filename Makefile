NAME = a.exe

HDR = get_next_line.h

SRC = get_next_line.c get_next_line_utils.c main.c

LIB = ../libft/libft.a

CC = gcc -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
	$(CC) $(SRC)
	./a.exe lorem.txt
	rm ./a.exe

clean :
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

