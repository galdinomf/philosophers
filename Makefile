SRCS	= main.c\
		  ft_isdigit.c\
		  ft_strlen.c\
		  check_input_and_initialize.c\
		  ft_atoi.c\
		  initialize_simulation.c\
		  initialize_data.c\
		  free_data.c\
		  get_timestamp.c\
		  try_to_eat.c\
		  display_message.c\
		  ft_strjoin.c\
		  ft_calloc.c\

SRCS_B	= 

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=thread

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)

PROG_NAME= philo

NAME	= $(PROG_NAME).a
NAME_B	= $(PROG_NAME)_bonus.a

HDR	= $(PROG_NAME).h

RM	= rm -f

all:   $(NAME)

bonus: $(NAME_B)

$(NAME): $(OBJS) $(HDR)
	$(RM) main_bonus.o
	ar -crs $(NAME) $(OBJS)
	$(RM) $(PROG_NAME)
	clang -fsanitize=thread $(NAME) -o $(PROG_NAME)

%.o: %.c $(HDR_DIR)$(HDR)
	clang $(CFLAGS) -c $< -o $@

$(NAME_B): $(OBJS_B) $(HDR)
	$(RM) main.o
	ar -crs $(NAME_B) $(OBJS_B)
	$(RM) $(PROG_NAME)
	gcc $(NAME_B) -o $(PROG_NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)
	$(RM) $(PROG_NAME)

re: fclean all

.PHONY: clean fclean re all bonus
