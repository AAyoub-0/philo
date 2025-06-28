/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:27 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 01:42:58 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_game *game, t_philo *philo)
{
	if (game->dead_printed)
		return ;
	sem_wait(game->print_sem);
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
	}
	sem_post(game->print_sem);
}

void	print_fork(t_game *game, t_philo *philo)
{
	sem_wait(game->print_sem);
	printf("%zu %zu has " CYAN "taken a fork" RESET "\n", ft_get_time(), philo->id);
	sem_post(game->print_sem);
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
