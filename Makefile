# build
NAME = libftprintf.a
CC = cc
AR = ar rcs
BUILD = build

# flags
CFLAGS = -MMD -MP -Wall -Wextra -Werror -I includes
MAKEFLAGS+= -j $$(nproc)

# files
SRCF = mandatory
SRCS =\
	$(SRCF)/ft_printf.c
BSRCF = bonus
BSRCS =\
	$(BSRCF)/ft_printf_bonus.c\
	$(BSRCF)/szput_en_bonus.c\
	$(BSRCF)/format_bonus.c\
	$(BSRCF)/utils_bonus.c

OBJS = $(SRCS:%.c=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

# rules
all:
	@rm -rf $(BUILD)/$(BSRCF)
	@mkdir -p $(BUILD)/$(SRCF)
	@$(MAKE) $(NAME) --no-print-directory

bonus:
	@rm -rf $(BUILD)/$(SRCF)
	@mkdir -p $(BUILD)/$(BSRCF)
	@$(MAKE) $(NAME) SRCS="$(BSRCS)" --no-print-directory

$(NAME): $(OBJS)
	@rm -f $(NAME)
	$(AR) $(NAME) $(OBJS)

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all --no-print-directory

.PHONY: all bonus clean fclean re
-include $(DEPS)
