NAME = philosopher

SRCS = main.c actions.c check.c initialize.c prints.c threads.c utils.c monitoring_utils.c
# SRCS_UTILITIES = stack_utilities/advanced_stack_operations.c \
# 				stack_utilities/stack_initialization.c \
# 				stack_utilities/stack_management.c \
# 				stack_utilities/stack_operations_helper.c \
# 				stack_utilities/stack_operations.c \
# 				stack_utilities/stack_utilities.c \
# 				stack_utilities/stack_push_operations.c

OBJS = $(SRCS:.c=.o)
# OBJS_UTILITIES = $(SRCS_UTILITIES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

GREEN = \033[32m
BLUE = \033[34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(BLUE)[💭] $(NAME) compiling$(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)[✅] $(NAME) compiled$(RESET)\n"

clean:
	@printf "$(BLUE)[🧹] cleaning$(RESET)\n"
	@rm -f $(OBJS)
	@printf "$(GREEN)[✨] cleaned$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[✨] fully cleaned$(RESET)\n"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

.PHONY: all clean fclean re