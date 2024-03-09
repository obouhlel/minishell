NAME = minishell

# Path
SRC_PATH = ./srcs/
INC_PATH = ./incs/
OBJ_PATH = ./objs/

# Files
SRCS = main.c minishell.c utils.c
SRCS += environement/init.c environement/add.c environement/del.c environement/get.c \
	environement/print.c environement/update.c environement/free.c environement/convert.c
SRCS += parsing/parsing.c parsing/invalid_token.c
SRCS += parsing/expend.c parsing/expend_utils.c
SRCS := $(addprefix $(SRC_PATH), $(SRCS))

OBJS := $(subst $(SRC_PATH), $(OBJ_PATH), $(SRCS:.c=.o))
DEPS := $(OBJS:.o=.d)

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -I$(INC_PATH)
CFLAGS += -g3 -fsanitize=address
LDFLAGS = -lreadline

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)
