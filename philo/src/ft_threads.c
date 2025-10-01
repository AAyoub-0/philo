/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:22:19 by aboumall          #+#    #+#             */
/*   Updated: 2025/10/01 16:34:27 by aboumall         ###   ########.fr       */
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
	philo->thread_created = true;
}

void	pthread_safe_death_thread(t_game *game)
{
	if (pthread_create(&game->death_thread, NULL, death_check, game) != 0)
	{
		game->thread_crashed = true;
		game->death_thread_created = false;
		printf("thread failed to create\n");
	}
	game->death_thread_created = true;
}

void	safe_mutex_init(t_game *game, t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
	{
		printf("mutex init failure\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	mutex->created = true;
}

void	safe_mutex_destroy(t_mutex *mutex)
{
	if (mutex->created == true)
		pthread_mutex_destroy(&mutex->mutex);
}

t_bool	get_done(t_philo *philo)
{
	t_bool	done;

	pthread_mutex_lock(&philo->done_lock.mutex);
	done = philo->done;
	pthread_mutex_unlock(&philo->done_lock.mutex);
	return (done);
}
