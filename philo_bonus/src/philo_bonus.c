/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/03 20:20:56 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_game *game, t_philo *philo)
{
	sem_wait(game->forks_sem);
	print_fork(game, philo);
	sem_wait(game->forks_sem);
	print_fork(game, philo);
	print_state(game, philo->id, eating);
	set_last_meal(game, philo, ft_get_time());
	set_meals_eaten(game, philo, get_meals_eaten(game, philo) + 1);
	ft_usleep(philo->time_eat);
	sem_post(game->forks_sem);
	sem_post(game->forks_sem);
}

void	philo_think(t_game *game, t_philo *philo)
{
	print_state(game, philo->id, thinking);
}

void	philo_sleep(t_game *game, t_philo *philo)
{
	print_state(game, philo->id, sleeping);
	ft_usleep(philo->time_sleep);
}

void	*philo_routine(void *param)
{
	t_philo	*philo;
	t_game	*game;

	philo = (t_philo *)param;
	philo->last_meal = philo->start_time;
	while (ft_get_time() < philo->start_time)
		continue ;
	game = philo->game;
	pthread_create(&philo->death_thread, NULL, death_check, philo);
	pthread_detach(philo->death_thread);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_eat * 0.2);
	while (true)
	{
		philo_eat(game, philo);
		if (philo->nb_max_eat != -1
			&& (int)get_meals_eaten(game, philo) == philo->nb_max_eat)
		{
			sem_post(game->nb_eat_sem);
			exit(EXIT_SUCCESS);
		}
		philo_think(game, philo);
		philo_sleep(game, philo);
	}
	exit(EXIT_SUCCESS);
}

void	init_philos(t_game *game)
{
	size_t	i;

	i = -1;
	while (++i < game->nb_philo)
	{
		game->philos[i].id = i + 1;
		game->philos[i].game = game;
		game->philos[i].start_time = game->start_time;
		game->philos[i].time_die = game->time_die;
		game->philos[i].time_eat = game->time_eat;
		game->philos[i].time_sleep = game->time_sleep;
		game->philos[i].nb_max_eat = game->nb_max_eat;
		game->philos[i].pid = -1;
		game->philos[i].meals_eaten = 0;
	}
}
