# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:29:40 by aboumall          #+#    #+#              #
#    Updated: 2025/09/24 14:32:19 by aboumall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo_bonus

HEAD 	= includes/philo_bonus.h

CC 		= cc

CFLAGS 	= -Werror -Wextra -Wall -Iincludes

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj

SRC_SRC 	= 	ft_time_bonus.c game_bonus.c philo_bonus.c \
				philo_utils_bonus.c utils_bonus.c main_bonus.c \
				philo_thread_bonus.c

SRC 		= 	$(addprefix $(SRC_DIR)/, $(SRC_SRC))
				
OBJ 		= 	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) $(SRC)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@) > /dev/null
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re