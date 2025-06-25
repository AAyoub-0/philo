/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:27 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/25 18:22:40 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->print_lock);
	if (philo->state == thinking)
		printf("%zu %d is thinking\n", ft_get_time(), philo->id);
	else if (philo->state == eating)
		printf("%zu %d is eating\n", ft_get_time(), philo->id);
	else if (philo->state == sleeping)
		printf("%zu %d is sleeping\n", ft_get_time(), philo->id);
	else if (philo->state == dead)
		printf("%zu %d died\n", ft_get_time(), philo->id);
	pthread_mutex_unlock(&game->print_lock);
}

void	print_fork(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->print_lock);
	printf("%zu %d has taken a fork\n", ft_get_time(), philo->id);
	pthread_mutex_unlock(&game->print_lock);
}
