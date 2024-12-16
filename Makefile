NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra 
# CFLAGS += -fsanitize=address
SRC=\
	threads_start.c \
	threads_utils.c \
	philo_parsing.c \
	philo_utils_0.c \
	philo.c			\
	set_data.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean : 
	@rm -rf $(OBJ)
fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re 