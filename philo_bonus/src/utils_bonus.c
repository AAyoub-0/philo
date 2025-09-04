/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:27 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/04 12:52:25 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_game *game, size_t id, t_philo_state state)
{
	sem_wait(game->print_sem);
	printf(GREEN "%zu" RESET " %zu ", ft_get_delay(game->start_time), id);
	if (state == thinking)
		printf("is  " MAGENTA "thinking" RESET "\n");
	else if (state == eating)
		printf("is  " YELLOW "eating" RESET "\n");
	else if (state == sleeping)
		printf("is  " BLUE "sleeping" RESET "\n");
	else if (state == dead)
	{
		printf(BOLD "died" RESET "\n");
		return ;
	}
	sem_post(game->print_sem);
}

void	print_fork(t_game *game, t_philo *philo)
{
	sem_wait(game->print_sem);
	printf(GREEN "%zu" RESET " %zu ", ft_get_delay(game->start_time),
		philo->id);
	printf("has " CYAN "taken a fork" RESET "\n");
	sem_post(game->print_sem);
}

sem_t	*sem_clean_open(t_game *game, const char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
	{
		perror("Semaphore initialization failed");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	return (sem);
}

size_t	mini_atoi(char *str)
{
	size_t	result;
	int		i;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((int)result > (INT_MAX - (str[i] - '0')) / 10)
		{
			printf("Error: integer too large\n");
			exit(EXIT_FAILURE);
		}
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

t_bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
