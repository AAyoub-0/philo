/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:22:19 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/25 23:53:25 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_safe_philo(t_game *game, t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, philo_routine,
			philo) != 0)
	{
		game->thread_crashed = true;
		philo->thread_created = false;
		printf("thread failed to create\n");
	}
}

void	pthread_safe_death_thread(t_game *game)
{
	if (pthread_create(&game->death_thread, NULL, death_check, game) != 0)
	{
		game->thread_crashed = true;
		game->death_thread_created = false;
		printf("thread failed to create\n");
	}
}

void	safe_mutex_init(t_game *game, t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
	{
		msg_exit(game, "mutex init failure", 1);
		mutex->created = false;
	}
	mutex->created = true;
}

void	safe_mutex_destroy(t_mutex *mutex)
{
	if (mutex->created == true)
		pthread_mutex_destroy(&mutex->mutex);
}
