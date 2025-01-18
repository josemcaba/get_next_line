NAME = a.exe

HDR = get_next_line.h

SRC = get_next_line.c get_next_line_utils.c main.c

SRC_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c main.c

HDR_BONUS = get_next_line_bonus.h

LIB = ../libft/libft.a

CC = gcc -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
	$(CC) $(SRC) -o $(NAME)
	./a.exe lorem.txt

bonus : $(SRC_BONUS) $(HDR_BONUS)
	$(CC) $(SRC_BONUS) -o $(NAME)
	./a.exe lorem.txt

clean :
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

