NAME	= libflagger.a
CC		= gcc
CCFLAGS	= -Wall -Wextra -Werror

SRC_DIR = $(PWD)/sources/
OBJ_DIR = $(PWD)/objects/

SRC_FILES = flagger.c

SRC	= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC	= -I$(PWD)/includes/ -I$(PWD)/libft/inc/
LIBFTPRINTF = $(PWD)/libft/libftprintf.a

all : createDir $(NAME)

debug: CCFLAGS += -g
debug: all

createDir:
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)

# $(NAME) : $(OBJ)
# 	@echo "\033[1;32m◊ +++++ CREATING $(NAME)	: √\033[0m"
# 	@echo "ar rc $(NAME)"
# 	@ar rc $(NAME) $(OBJ) $(LIBFTPRINTF)
# 	ranlib $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[1;32m◊ +++++ CREATING $(NAME)	: √\033[0m"
	@ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CCFLAGS) -c $^ -o $@ $(INC)

clean :
	@echo "\033[1;31m◊ ----- DELETING $(NAME) OBJECTS	: √\033[0m"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "\033[1;31m◊ ----- DELETING $(NAME)		: √\033[0m"
	@rm -f $(NAME)

install :
	cp $(NAME) /usr/local/lib/

uninstall :
	rm -f /usr/local/lib/$(NAME)

re : fclean all
