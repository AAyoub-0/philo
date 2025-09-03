/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/03 19:00:11 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_eat(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	if (get_fork_used(&philo->fork) == false)
		set_fork_used(&philo->fork, true);
	print_fork(game, philo);
	if (philo->prev == NULL)
	{
		while (get_dead(game) != NULL)
			continue ;
		return (false);
	}
	if (get_fork_used(&philo->prev->fork) == false)
		set_fork_used(&philo->prev->fork, true);
	print_fork(game, philo);
	print_state(game, philo, eating);
	set_last_meal(philo, ft_get_time());
	set_meals_eaten(philo, get_meals_eaten(philo) + 1);
	ft_usleep(game, game->time_eat);
	set_fork_used(&philo->fork, false);
	set_fork_used(&philo->prev->fork, false);
	return (true);
}

t_bool	philo_sleep_n_think(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	print_state(game, philo, sleeping);
	ft_usleep(game, game->time_sleep);
	if (get_dead(game) != NULL)
		return (false);
	print_state(game, philo, thinking);
	return (true);
}

void	*philo_routine(void *param)
{
	t_game	*game;
	t_philo	*philo;

	philo = (t_philo *)param;
	game = philo->game;
	while (ft_get_time() < game->start_time)
		continue ;
	if (game->thread_crashed)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(game, game->time_eat / 2);
	while (true)
	{
		if (!philo_eat(game, philo))
			return (NULL);
		if (game->nb_max_eat != -1
			&& (int)get_meals_eaten(philo) == game->nb_max_eat)
		{
			set_nb_eat(game, get_nb_eat(game) + 1);
			return (NULL);
		}
		if (!philo_sleep_n_think(game, philo))
			return (NULL);
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
		game->philos[i].last_meal = game->start_time;
		safe_mutex_init(game, &game->philos[i].fork.fork_lock);
		safe_mutex_init(game, &game->philos[i].meals_eaten_lock);
		safe_mutex_init(game, &game->philos[i].last_meal_lock);
		if (i > 0)
			game->philos[i].prev = &game->philos[i - 1];
		else if (game->nb_philo == 1)
			game->philos[i].prev = NULL;
		else
			game->philos[i].prev = &game->philos[game->nb_philo - 1];
		game->philos[i].thread_created = true;
	}
}
