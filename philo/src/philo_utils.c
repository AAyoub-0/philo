/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:39:42 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/25 23:56:17 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meals_eaten(t_philo *philo, size_t meals)
{
	pthread_mutex_lock(&philo->meals_eaten_lock.mutex);
	philo->meals_eaten = meals;
	pthread_mutex_unlock(&philo->meals_eaten_lock.mutex);
}

size_t	get_meals_eaten(t_philo *philo)
{
	size_t	meals;

	pthread_mutex_lock(&philo->meals_eaten_lock.mutex);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_lock.mutex);
	return (meals);
}

void	set_last_meal(t_philo *philo, size_t last_meal)
{
	pthread_mutex_lock(&philo->last_meal_lock.mutex);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock.mutex);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->last_meal_lock.mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock.mutex);
	return (last_meal);
}

void	init_philos(t_game *game)
{
	size_t	i;

	i = -1;
	while (++i < game->nb_philo)
	{
		game->philos[i].game = game;
		game->philos[i].id = i + 1;
		game->philos[i].meals_eaten = 0;
		game->philos[i].last_meal = game->start_time;
		game->philos[i].done = false;
		game->philos[i].fork.used = false;
		safe_mutex_init(game, &game->philos[i].fork.fork_lock);
		safe_mutex_init(game, &game->philos[i].meals_eaten_lock);
		safe_mutex_init(game, &game->philos[i].last_meal_lock);
		safe_mutex_init(game, &game->philos[i].done_lock);
		if (i > 0)
			game->philos[i].prev = &game->philos[i - 1];
		else if (game->nb_philo == 1)
			game->philos[i].prev = NULL;
		else
			game->philos[i].prev = &game->philos[game->nb_philo - 1];
		game->philos[i].thread_created = true;
	}
}
