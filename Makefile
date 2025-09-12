NAME = libftprintf.a

CC = cc
AR = ar rcs
CFLAGS = -MMD -MP -Wall -Wextra -Werror -I.

SRCS = \
	ft_printf.c \
	ft_printf_utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)
