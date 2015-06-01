NAME =	client

SRC =	main.c\
		ncurses_start.c\
		ncurses_utils.c\
		ncurses_loop.c\
		ncurses_str.c\
		ncurses_keys.c\
		ncurses_fct.c\
		ncurses_display.c\
		ncurses_remember.c\
		ncurses_history.c\
		ncurses_extension.c\
		ncurses_completion.c\
		radix_tree.c\
		radix_build_tree.c\

OBJ =	$(SRC:.c=.o)
 
GCC =	gcc -g -Wall -Wextra -Werror

%.o:		%.c
	@echo "\033[1;36;m[Compiling $<]\t\033[0m: " | tr -d '\n'
	$(GCC) -c $< 

all:		$(NAME)

$(NAME):	$(OBJ) 
	@echo "\033[1;35;m[Linking] \t\t\033[0m: " | tr -d '\n'
	$(GCC) -o $@ $(OBJ)  -lncurses
	@echo "\033[1;32;m[Success] \t\t\t\033[0m"

clean:
	@echo "\033[0;33;m[Cleaning] \t\t\033[0m: " | tr -d '\n'
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(NAME)] \t\033[0m: " | tr -d '\n'
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re