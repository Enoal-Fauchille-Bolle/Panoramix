##
## EPITECH PROJECT, 2025
## Panoramix
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run unit_tests coverage

SRC_DIR =	src
SRC	=	\
		$(SRC_DIR)/main.c	\
		$(SRC_DIR)/options.c	\
		$(SRC_DIR)/villager.c	\
		$(SRC_DIR)/druid.c	\
		$(SRC_DIR)/pot.c	\

NAME	=	panoramix

OBJ	=	$(SRC:.c=.o)

CFLAGS += -I./include/ -Werror -Wall -Wextra -g -lpthread

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)	\

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

TEST_DIR	=	tests/
NAME_TEST	=	unit_tests

SRC_TESTS =	\

FLAGS_TEST = \
			-lcriterion --coverage

unit_tests: re
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	gcc -o $(NAME_TEST) $(SRC_TESTS) $(CFLAGS) $(FLAGS_TEST)

tests_run: unit_tests
	./$(NAME_TEST)

coverage: unit_tests
	./$(NAME_TEST)
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch
	rm $(NAME_TEST)
