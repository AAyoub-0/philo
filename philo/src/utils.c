/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:27 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/28 22:58:15 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_game *game, t_philo *philo, t_philo_state state)
{
	size_t	time;

	if (game->dead_printed)
		return ;
	time = ft_get_delay(game->start_time);
	pthread_mutex_lock(&game->print_lock);
	if (get_dead(game) != NULL && state != dead)
	{
		pthread_mutex_unlock(&game->print_lock);
		return ;
	}
	printf(GREEN "%zu" RESET " %zu ", time, philo->id);
	if (state == thinking)
		printf("is  " MAGENTA "thinking" RESET "\n");
	else if (state == eating)
		printf("is  " YELLOW "eating" RESET "\n");
	else if (state == sleeping)
		printf("is  " BLUE "sleeping" RESET "\n");
	else if (state == dead)
	{
		printf(BOLD "died" RESET "\n");
		game->dead_printed = true;
	}
	pthread_mutex_unlock(&game->print_lock);
}

void	print_fork(t_game *game, t_philo *philo)
{
	size_t	time;

	if (get_dead(game) != NULL)
		return ;
	time = ft_get_delay(game->start_time);
	pthread_mutex_lock(&game->print_lock);
	if (get_dead(game) != NULL)
	{
		pthread_mutex_unlock(&game->print_lock);
		return ;
	}
	printf(GREEN "%zu" RESET " %zu ", time, philo->id);
	printf("has " CYAN "taken a fork" RESET "\n");
	pthread_mutex_unlock(&game->print_lock);
}

void	msg_exit(t_game *game, char *msg, int code)
{
	if (msg)
		printf("%s\n", msg);
	free_game(game);
	exit(code);
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

t_bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
