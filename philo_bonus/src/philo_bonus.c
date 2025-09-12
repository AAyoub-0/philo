/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/12 15:07:50 by aboumall         ###   ########.fr       */
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

void	free_philo(t_game *game)
{
	if (game->print_sem)
		sem_close(game->print_sem);
	if (game->nb_eat_sem)
		sem_close(game->nb_eat_sem);
	if (game->philo_dead_sem)
		sem_close(game->philo_dead_sem);
	if (game->forks_sem)
		sem_close(game->forks_sem);
	if (game->meals_eaten_sem)
		sem_close(game->meals_eaten_sem);
	if (game->last_meal_sem)
		sem_close(game->last_meal_sem);
	if (game->end_sim_sem)
		sem_close(game->end_sim_sem);
}

void	set_philo_dead(t_game *game, t_bool philo_dead)
{
	sem_wait(game->philo_dead_sem);
	game->philo_dead = philo_dead;
	sem_post(game->philo_dead_sem);
}

t_bool	get_philo_dead(t_game *game)
{
	t_bool	philo_dead;
	
	sem_wait(game->philo_dead_sem);
	philo_dead = game->philo_dead;
	sem_post(game->philo_dead_sem);
	return (philo_dead);
}

void	*end_sim_check(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	sem_wait(game->end_sim_sem);
	set_philo_dead(game, true);
	// sem_wait(game->print_sem);
	// free_philo(game);
	// exit(EXIT_SUCCESS);
	return (NULL);
}

void	philo_routine(t_philo *philo, t_game *game)
{
	while (ft_get_time() < philo->start_time)
		continue ;
	pthread_create(&philo->death_thread, NULL, death_check, philo);
	pthread_create(&philo->end_sim_thread, NULL, end_sim_check, game);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_eat * 0.2);
	while (true)
	{
		philo_eat(game, philo);
		if (philo->nb_max_eat != -1 && (int)get_meals_eaten(game,
				philo) == philo->nb_max_eat)
		{
			sem_post(game->nb_eat_sem);
			break ;
		}
		philo_think(game, philo);
		philo_sleep(game, philo);
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
		philos[i].time_die = game->time_die;
		philos[i].time_eat = game->time_eat;
		philos[i].time_sleep = game->time_sleep;
		philos[i].nb_max_eat = game->nb_max_eat;
		philos[i].pid = -1;
		philos[i].meals_eaten = 0;
	}
}
