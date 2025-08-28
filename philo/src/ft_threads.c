/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:22:19 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/28 18:31:56 by aboumall         ###   ########.fr       */
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

void	pthread_safe_join(t_game *game, pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
	{
		game->thread_crashed = true;
		printf("thread failed to join\n");
	}
}

void	safe_mutex_init(t_game *game, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		msg_exit(game, "mutex init failure", 1);
}
