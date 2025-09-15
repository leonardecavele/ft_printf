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

.PHONY: all bonus clean fclean re $(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	@if [ -f "$(NAME)" ]; then \
		if ! ar t "$(NAME)" | grep -qE 'bonus' \
		&& ! (find $(OBJS) -newer "$(NAME)" -print -quit | grep -q .); then \
			echo "make: Nothing to be done for 'all'."; \
		else \
			rm -f "$(NAME)"; \
			echo $(AR) $(NAME) $(OBJS); \
			$(AR) $(NAME) $(OBJS); \
		fi; \
	else \
		echo $(AR) $(NAME) $(OBJS); \
		$(AR) $(NAME) $(OBJS); \
	fi

bonus: $(BOBJS)
	@if [ -f "$(NAME)" ]; then \
		if ar t "$(NAME)" | grep -qE 'bonus' \
		&& ! (find $(BOBJS) -newer "$(NAME)" -print -quit | grep -q .); then \
			echo "make: Nothing to be done for 'bonus'."; \
		else \
			rm -f "$(NAME)"; \
			echo $(AR) $(NAME) $(BOBJS); \
			$(AR) $(NAME) $(BOBJS); \
		fi; \
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
