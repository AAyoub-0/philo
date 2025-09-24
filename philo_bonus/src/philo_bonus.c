/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/24 14:24:45 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_game *game, t_philo *philo)
{
	sem_wait(game->forks_sem);
	print_fork(game, philo);
	if (game->nb_philo == 1)
	{
		while (get_philo_dead(game) == false)
			usleep(100);
	}
	usleep(500);
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

void	philo_routine(t_philo *philo, t_game *game)
{
	while (ft_get_time() < philo->start_time)
		usleep(100);
	pthread_create(&philo->death_thread, NULL, death_check, philo);
	pthread_create(&philo->end_sim_thread, NULL, end_sim_check, game);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_eat / 2);
	while (get_philo_dead(game) == false)
	{
		philo_eat(game, philo);
		if (philo->nb_max_eat != -1 && (int)get_meals_eaten(game,
				philo) == philo->nb_max_eat)
		{
			sem_post(game->nb_eat_sem);
			break ;
		}
		philo_sleep(game, philo);
		philo_think(game, philo);
		usleep(100);
	}
	pthread_join(philo->death_thread, NULL);
	pthread_join(philo->end_sim_thread, NULL);
	free_philo(game);
	exit(EXIT_SUCCESS);
}

void	init_philos(t_game *game)
{
	t_philo	*philos;
	size_t	i;

	i = -1;
	philos = game->philos;
	while (++i < game->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].game = game;
		philos[i].start_time = game->start_time;
		philos[i].last_meal = game->start_time;
		philos[i].time_die = game->time_die;
		philos[i].time_eat = game->time_eat;
		philos[i].time_sleep = game->time_sleep;
		philos[i].nb_max_eat = game->nb_max_eat;
		philos[i].pid = -1;
		philos[i].meals_eaten = 0;
	}
}
