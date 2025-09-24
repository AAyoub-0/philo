/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/24 10:40:49 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_eat(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	while (get_fork_used(&philo->fork) == true)
		usleep(100);
	set_fork_used(&philo->fork, true);
	print_fork(game, philo);
	if (philo->prev == NULL)
	{
		while (get_dead(game) != NULL)
			continue ;
		return (false);
	}
	while (get_fork_used(&philo->prev->fork) == true)
		usleep(100);
	set_fork_used(&philo->prev->fork, true);
	print_fork(game, philo);
	print_state(game, philo, eating);
	set_last_meal(philo, ft_get_time());
	set_meals_eaten(philo, get_meals_eaten(philo) + 1);
	ft_usleep(game->time_eat);
	set_fork_used(&philo->fork, false);
	set_fork_used(&philo->prev->fork, false);
	return (true);
}

t_bool	philo_sleep_n_think(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	print_state(game, philo, sleeping);
	ft_usleep(game->time_sleep);
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
		ft_usleep(game->time_eat / 2);
	while (true)
	{
		if (!philo_eat(game, philo))
			return (NULL);
		if (game->nb_max_eat != -1
			&& (int)get_meals_eaten(philo) == game->nb_max_eat)
		{
			set_done(philo, true);
			return (NULL);
		}
		if (!philo_sleep_n_think(game, philo))
			return (NULL);
	}
	return (NULL);
}

void	set_done(t_philo *philo, t_bool done)
{
	pthread_mutex_lock(&philo->done_lock);
	philo->done = done;
	pthread_mutex_unlock(&philo->done_lock);
}

t_bool	get_done(t_philo *philo)
{
	t_bool	done;

	pthread_mutex_lock(&philo->done_lock);
	done = philo->done;
	pthread_mutex_unlock(&philo->done_lock);
	return (done);
}
