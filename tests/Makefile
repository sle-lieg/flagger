NAME	= test_flagger
CC		= gcc
CCFLAGS	= -Wall -Wextra -Werror

SRC_DIR = $(PWD)/sources/
OBJ_DIR = $(PWD)/objects/

SRC_FILES = test_1.c

INC	=	-I$(PWD)/../includes/
INC +=	-I$(PWD)/../libft/inc/

LIBFTPRINTF = $(PWD)/../libft/libftprintf.a
LIBFLAGGER = $(PWD)/../libflagger.a

all : $(NAME)

$(NAME)	:
	gcc -o $@ $(SRC_FILES) $(LIBFLAGGER) $(LIBFTPRINTF) $(INC)

clean :
	@echo "\033[1;31m◊ ----- DELETING $(NAME) OBJECTS	: √\033[0m"
	@rm -f $(PWD)/*.o

fclean : clean
	@echo "\033[1;31m◊ ----- DELETING $(NAME)		: √\033[0m"
	@rm -f $(NAME)

re : fclean all
