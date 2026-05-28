NAME := philo

RULE := all

CC := cc
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -I incs
OFLAGS := -lpthread

SRCDIR := srcs
OBJDIR := objs

SRCS	:= 	main.c \
			valid.c \
			ft_atoi.c \
			mutex.c \
			philo.c \
			philo_routine.c \
			philo_helper.c \
			waiter.c \
			fork.c \
			status.c \
			print.c \
			time.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

debug: RULE=debug
debug: CC=gcc
debug: CFLAGS=-g3 -Wall -Wextra -Werror
debug: $(NAME)

memory: RULE=memory
memory: CC=cc
memory: CFLAGS=-Wall -Wextra -Werror -fsanitize=address
memory: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(OFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
