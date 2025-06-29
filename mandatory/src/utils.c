/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:27 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 21:57:00 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_game *game, t_philo *philo)
{
	if (game->dead_printed)
		return ;
	pthread_mutex_lock(&game->print_lock);
	printf(GREEN "%zu" RESET " %zu ", ft_get_time(), philo->id);
	if (philo->state == thinking)
		printf("is  " MAGENTA "thinking" RESET "\n");
	else if (philo->state == eating)
		printf("is  " YELLOW "eating" RESET "\n");
	else if (philo->state == sleeping)
		printf("is  " BLUE "sleeping" RESET "\n");
	else if (philo->state == dead)
	{
		printf( BOLD "died" RESET "\n");
		game->dead_printed = true;
		return ;
	}
	pthread_mutex_unlock(&game->print_lock);
}

void	print_fork(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->print_lock);
	printf(GREEN "%zu" RESET " %zu ", ft_get_time(), philo->id);
	printf("has " CYAN "taken a fork" RESET "\n");
	pthread_mutex_unlock(&game->print_lock);
}

size_t	mini_atoi(char *str)
{
	size_t	result;
	int		i;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

t_bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

t_bool	first_fork(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	if (philo->id % 2 == 0)
		ft_usleep(game->time_eat / 2);
	pthread_mutex_lock(&philo->fork.fork_lock);
	if (get_dead(game) != NULL)
	{
		pthread_mutex_unlock(&philo->fork.fork_lock);
		return (false);
	}
	philo->fork.used = true;
	print_fork(game, philo);
	if (philo->prev == NULL)
	{
		philo->fork.used = false;
		pthread_mutex_unlock(&philo->fork.fork_lock);
		while (get_dead(game) == NULL)
			ft_usleep(100);
		return (false);
	}
	return (true);
}
