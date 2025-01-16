NAME = philo

SRCS = main.c threads.c
SRCS_UTILITIES = utils/actions.c \
					utils/check.c \
					utils/errors.c \
					utils/initialize.c \
					utils/main_utils.c \
					utils/monitoring_utils.c \
					utils/prints.c \
					utils/utils.c

OBJS = $(SRCS:.c=.o)
OBJS_UTILITIES = $(SRCS_UTILITIES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

GREEN = \033[32m
BLUE = \033[34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_UTILITIES)
	@printf "$(BLUE)[💭] $(NAME) compiling$(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)[✅] $(NAME) compiled$(RESET)\n"

clean:
	@printf "$(BLUE)[🧹] cleaning$(RESET)\n"
	@rm -f $(OBJS)
	@rm -f $(OBJS_UTILITIES)
	@printf "$(GREEN)[✨] cleaned$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[✨] fully cleaned$(RESET)\n"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

.PHONY: all clean fclean re