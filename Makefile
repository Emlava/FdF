NAME = fdf
LIBRARY_1 = libft/libft.a
LIBRARY_2 = minilibx-linux/libmlx_Linux.a 
CC = cc
# FLAGS = -g -Wall -Werror -Wextra -fsanitize=address
FLAGS = -g -Wall -Werror -Wextra
MLX_FLAGS = -lXext -lX11 -lm
OBJECTS = main.o argument_check.o manage_file_coordinates.o utilities/manage_file_coordinates_utilities_1.o \
	utilities/manage_file_coordinates_utilities_2.o create_image.o utilities/create_image_utilities.o \
	hooks.o utilities/cleaning_utilities.o

.PHONY: all clean fclean re

all: $(NAME)

$(LIBRARY_1):
	$(MAKE) -C ./libft

$(LIBRARY_2):
	$(MAKE) -C ./minilibx-linux

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBRARY_1) $(LIBRARY_2) $(OBJECTS)
	$(CC) $(FLAGS)  $(OBJECTS) $(LIBRARY_1) $(LIBRARY_2) $(MLX_FLAGS) -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	rm -rf minilibx-linux/obj
	rm -f $(OBJECTS)

fclean:
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./minilibx-linux clean
	rm -f $(OBJECTS) $(NAME)

re: fclean all
