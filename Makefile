# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:29:40 by aboumall          #+#    #+#              #
#    Updated: 2025/02/25 16:31:41 by aboumall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

HEAD 	= includes/philo.h
LIBFT_A = libft.a

CC 		= cc

CFLAGS 	= -Werror -Wextra -Wall -Iincludes

LIBFT_DIR 	= 	libft
SRC_DIR 	= 	src
OBJ_DIR 	= 	obj

SRC_SRC 	= 	main.c

LIBFT 		= 	$(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

SRC 		= 	$(addprefix $(SRC_DIR)/, $(SRC_SRC))
				
OBJ 		= 	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: lib $(NAME)

$(NAME): $(OBJ) $(HEAD) $(SRC)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@) > /dev/null
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

lib:
	@echo "Checking libft..."
	@if $(MAKE) -C $(LIBFT_DIR) -q; then \
		echo "Libft is already up to date!"; \
	else \
		echo "Making libft..."; \
		$(MAKE) -C $(LIBFT_DIR) > /dev/null; \
	fi

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null

fclean: clean
	@echo "Removing executable and libraries..."
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null

re: fclean all

.PHONY: all clean fclean re lib