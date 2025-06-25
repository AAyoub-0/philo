/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/25 19:12:56 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_game *game, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork.fork_lock) == 0)
	{
		print_fork(game, philo);
		philo->fork.used = true;
		if (pthread_mutex_lock(&philo->prev->fork.fork_lock) == 0)
		{
			print_fork(game, philo);
			philo->prev->fork.used = true;
			philo->state = eating;
			print_state(game, philo);
			ft_usleep(game->time_eat);
			set_last_meal(philo, ft_get_time());
			set_meals_eaten(philo, philo->meals_eaten + 1);
			philo->prev->fork.used = false;
			pthread_mutex_unlock(&philo->prev->fork.fork_lock);
		}
		philo->fork.used = false;
		pthread_mutex_unlock(&philo->fork.fork_lock);
	}
}

void	philo_think(t_game *game, t_philo *philo)
{
	set_state(philo, thinking);
	print_state(game, philo);
}

void	philo_sleep(t_game *game, t_philo *philo)
{
	set_state(philo, sleeping);
	ft_usleep(game->time_sleep);
	print_state(game, philo);
}

void	*philo_routine(void *param)
{
	t_game	*game;
	t_philo	*philo;
	
	philo = (t_philo *)param;
	game = philo->game;
	while (true)
	{
		philo_think(game, philo);
		philo_eat(game, philo);
		philo_sleep(game, philo);
		if (game->nb_max_eat != -1 && (int)philo->meals_eaten == game->nb_max_eat)
			break ;
	}
	return (NULL);
}

void	init_philos(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		game->philos[i].game = game;
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
		pthread_create(&game->philos[i].thread, NULL, philo_routine,
			&game->philos[i]);
		i++;
	}
}
