/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 01:19:06 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	philo_eat(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	sem_wait(game->forks_sem);
	print_fork(game, philo);
	if (get_dead(game) != NULL)
	{
		sem_post(game->forks_sem);
		return (false);
	}
	sem_wait(game->forks_sem);
	print_fork(game, philo);
	set_state(philo, eating);
	print_state(game, philo);
	set_last_meal(philo, ft_get_time());
	set_meals_eaten(philo, get_meals_eaten(philo) + 1);
	ft_usleep(game->time_eat);
	sem_post(game->forks_sem);
	sem_post(game->forks_sem);
	return (true);
}

t_bool	philo_think(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	set_state(philo, thinking);
	print_state(game, philo);
	return (true);
}

t_bool	philo_sleep(t_game *game, t_philo *philo)
{
	if (get_dead(game) != NULL)
		return (false);
	set_state(philo, sleeping);
	ft_usleep(game->time_sleep);
	print_state(game, philo);
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
	philo->last_meal = ft_get_time();
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
		game->philos[i].last_meal = ft_get_time() + 10;
		game->philos[i].meals_eaten_sem = sem_open(MEALS_EATEN_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
		game->philos[i].last_meal_sem = sem_open(LAST_MEAL_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
		game->philos[i].state_sem = sem_open(STATE_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	}
}
