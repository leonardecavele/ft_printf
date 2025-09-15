NAME = libftprintf.a

CC = cc
AR = ar rcs
CFLAGS = -MMD -MP -Wall -Wextra -Werror -I includes

SRCF = mandatory
SRCS = \
	$(SRCF)/ft_printf.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

BSRCF = bonus
BSRCS = \
	$(BSRCF)/ft_printf_bonus.c \
	$(BSRCF)/szput_en_bonus.c \
	$(BSRCF)/format_bonus.c \
	$(BSRCF)/utils_bonus.c

BOBJS = $(BSRCS:.c=.o)
BDEPS = $(BOBJS:.o=.d)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BOBJS)
	@if [ -f $(NAME) ] && ar t $(NAME) | grep -Eq 'bonus'; then \
		echo "make: Nothing to be done for 'bonus'."; \
	else \
		echo $(AR) $(NAME) $(BOBJS); \
		$(AR) $(NAME) $(BOBJS); \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(BOBJS) $(BDEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS) $(BDEPS)
