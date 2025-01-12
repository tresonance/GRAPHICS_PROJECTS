NAME = tetris
PATH_OBJ = ./
PATH_INC = ./libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEAD = ./include/tetris.h

SRC =	./src/clear_piece.c \
		./src/display.c \
		./src/event.c  \
		./src/init2.c  \
		./src/piece.c  \
		./src/score.c \
		./src/destroy.c \
		./src/draw.c  \
		./src/init.c  \
		./src/pixel.c \
		./src/main.c 
		

OBJ = $(patsubst %.c,%.o,$(addprefix $(PATH_SRC), $(SRC)))


all: $(NAME)

$(NAME): $(OBJ) $(HEAD)
	make -C libft/
	$(CC) $(CFLAGS) -I $(PATH_INC) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ) -lm -L libft/ -lft -lmlx -L./minilibx_macos  -framework OpenGL -framework AppKit && ./$(NAME)

clean:
	make -C libft/ clean
	/bin/rm -f *.o libft/*.o src/*.o 

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME) 

re: fclean all

.PHONY: clean fclean