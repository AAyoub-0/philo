/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/07/05 01:26:22 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_eat(t_game *game, t_philo *philo)
{
	if (!first_fork(game, philo))
		return (false);
	pthread_mutex_lock(&philo->prev->fork.fork_lock);
	if (get_dead(game) != NULL)
	{
		philo->fork.used = false;
		pthread_mutex_unlock(&philo->fork.fork_lock);
		pthread_mutex_unlock(&philo->prev->fork.fork_lock);
		return (false);
	}
	print_fork(game, philo);
	philo->prev->fork.used = true;
	print_state(game, philo, eating);
	set_last_meal(philo, ft_get_time());
	set_meals_eaten(philo, get_meals_eaten(philo) + 1);
	ft_usleep(game->time_eat);
	philo->prev->fork.used = false;
	pthread_mutex_unlock(&philo->prev->fork.fork_lock);
	philo->fork.used = false;
	pthread_mutex_unlock(&philo->fork.fork_lock);
	return (true);
}

t_bool	philo_think(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	print_state(game, philo, thinking);
	return (true);
}

t_bool	philo_sleep(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	print_state(game, philo, sleeping);
	ft_usleep(game->time_sleep);
	return (true);
}

void	*philo_routine(void *param)
{
	t_game	*game;
	t_philo	*philo;
	
	philo = (t_philo *)param;
	game = philo->game;
	while (!get_start(game))
		ft_usleep(100);
	set_last_meal(philo, ft_get_time());
	while (true)
	{
		if (!philo_eat(game, philo))
			break ;
		if (game->nb_max_eat != -1 && (int)get_meals_eaten(philo) == game->nb_max_eat)
		{
			set_nb_eat(game, game->nb_eat + 1);
			break ;
		}
		if (!philo_think(game, philo))
			break ;
		if (!philo_sleep(game, philo))
			break ;
	}
	return (NULL);
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
		game->philos[i].last_meal = ft_get_time();
		pthread_mutex_init(&game->philos[i].fork.fork_lock, NULL);
		pthread_mutex_init(&game->philos[i].meals_eaten_lock, NULL);
		pthread_mutex_init(&game->philos[i].last_meal_lock, NULL);
		if (i > 0)
			game->philos[i].prev = &game->philos[i - 1];
		else
		{
			if (game->nb_philo == 1)
				game->philos[i].prev = NULL;
			else
				game->philos[i].prev = &game->philos[game->nb_philo - 1];
		}
		pthread_create(&game->philos[i].thread, NULL, philo_routine,
			&game->philos[i]);
	}
}
