# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:29:40 by aboumall          #+#    #+#              #
#    Updated: 2025/02/26 14:50:44 by aboumall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

HEAD 	= includes/philo.h

CC 		= cc

CFLAGS 	= -Werror -Wextra -Wall -Iincludes

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj

SRC_SRC 	= 	game.c philo.c thread.c utils.c main.c


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