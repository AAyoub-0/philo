/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/23 21:12:28 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		game->philos[i].id = i + 1;
		game->philos[i].meals_eaten = 0;
		game->philos[i].last_meal = 0;
		game->philos[i].state = none;
		pthread_mutex_init(&game->philos[i].fork.fork_lock, NULL);
		pthread_mutex_init(&game->philos[i].meals_eaten_lock, NULL);
		pthread_mutex_init(&game->philos[i].last_meal_lock, NULL);
		pthread_mutex_init(&game->philos[i].state_lock, NULL);
		if (i > 0)
			game->philos[i].prev = &game->philos[i - 1];
		else
			game->philos[i].prev = &game->philos[game->nb_philo - 1];
		i++;
	}
}

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		pthread_mutex_destroy(&game->philos[i].fork.fork_lock);
		pthread_mutex_destroy(&game->philos[i].meals_eaten_lock);
		pthread_mutex_destroy(&game->philos[i].last_meal_lock);
		pthread_mutex_destroy(&game->philos[i].state_lock);
		i++;
	}
	free(game->philos);
	game->philos = NULL;
	pthread_mutex_destroy(&game->print_lock);
	pthread_cancel(game->death_thread);
	game->dead = NULL;
}

void	set_state(t_philo *philo, t_philo_state state)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_lock);
}

void	set_meals_eaten(t_philo *philo, size_t meals)
{
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten = meals;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}

void	set_last_meal(t_philo *philo, size_t last_meal)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	ft_get_delay(long start_time)
{
	return (ft_get_time() - start_time);
}

void	ft_usleep(long delay)
{
	long	start_time;

	start_time = ft_get_time();
	while (ft_get_delay(start_time) < delay)
		usleep(100); 
}

void try_eat(t_game *game, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork.fork_lock) == 0)
	{
		if (pthread_mutex_lock(&philo->prev->fork.fork_lock) == 0)
		{
			philo->state = eating;
			ft_usleep(game->time_eat);
			set_last_meal(philo, ft_get_time());
			set_meals_eaten(philo, philo->meals_eaten + 1);
			pthread_mutex_unlock(&philo->fork.fork_lock);
			pthread_mutex_unlock(&philo->prev->fork.fork_lock);
		}
		else
			pthread_mutex_unlock(&philo->fork.fork_lock);
	}
}

void	philo_routine(t_game *game, t_philo *philo)
{
	while (1)
	{
		set_state(philo, thinking);
		// Simulate thinking
		usleep(1000);

		set_state(philo, eating);
		// Simulate eating
		usleep(game->time_eat * 1000);
		pthread_mutex_lock(&philo->meals_eaten_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_lock);
		philo->last_meal = get_time(); // Assume get_time() is defined elsewhere

		set_state(philo, sleeping);
		// Simulate sleeping
		usleep(game->time_sleep * 1000);
	}
}
